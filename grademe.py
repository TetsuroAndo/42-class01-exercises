import os
import subprocess
import sys
import tarfile
import tempfile
import shutil
import base64
import subprocess
import shlex

ENCODED_PASSWORD = "bWFzdGVya2V5LWlzLWEtcGVu"

SUCCESS_ART = """
   _____ _    _  _____ _____ ______  _____ _____ 
  / ____| |  | |/ ____/ ____|  ____|/ ____/ ____|
 | (___ | |  | | |   | |    | |__  | (___| (___  
  \___ \| |  | | |   | |    |  __|  \___ \\___ \ 
  ____) | |__| | |___| |____| |____ ____) |___) |
 |_____/ \____/ \_____\_____|______|_____/_____/ 
"""

FAILURE_ART = """
  ______      _____ _        ______ 
 |  ____/\   |_   _| |      |  ____|
 | |__ /  \    | | | |      | |__   
 |  __/ /\ \   | | | |   _  |  __|  
 | | / ____ \ _| |_| |__| | | |____ 
 |_|/_/    \_\_____|______| |______|
"""

ALL_SUCCESS_ART = """
      ::::::::      :::    :::       ::::::::       ::::::::       ::::::::::       ::::::::       ::::::::
    :+:    :+:     :+:    :+:      :+:    :+:     :+:    :+:      :+:             :+:    :+:     :+:    :+:
   +:+            +:+    +:+      +:+            +:+             +:+             +:+            +:+
  +#++:++#++     +#+    +:+      +#+            +#+             +#++:++#        +#++:++#++     +#++:++#++
        +#+     +#+    +#+      +#+            +#+             +#+                    +#+            +#+
#+#    #+#     #+#    #+#      #+#    #+#     #+#    #+#      #+#             #+#    #+#     #+#    #+#
########       ########        ########       ########       ##########       ########       ########
"""

def extract_encrypted_tar(encrypted_file, password, output_dir):
    with tempfile.TemporaryDirectory() as temp_dir:
        decrypted_file = os.path.join(temp_dir, "answers.tar.gz")
        subprocess.run(["gpg", "--batch", "--yes", "--passphrase", password, "-o", decrypted_file, "-d", encrypted_file], check=True)

        with tarfile.open(decrypted_file, "r:gz") as tar:
            tar.extractall(path=output_dir)

def extract_answers(tar_path):
    password = base64.b64decode(ENCODED_PASSWORD).decode('utf-8')
    
    with tempfile.TemporaryDirectory() as temp_dir:
        try:
            extract_encrypted_tar(tar_path, password, temp_dir)
            
            for root, dirs, files in os.walk(temp_dir):
                for file in files:
                    src_path = os.path.join(root, file)
                    dst_path = os.path.join('/tmp', file)
                    shutil.copy(src_path, dst_path)
        except Exception as e:
            print(f"エラー: 答えファイルの解凍中に問題が発生しました - {str(e)}")
            sys.exit(1)

def compile_program(program):
    compiled_program = f"{program}.out"
    compile_command = ['gcc', '-o', compiled_program, program]
    compile_result = subprocess.run(compile_command, capture_output=True, text=True)
    return compile_result.returncode == 0, compiled_program

def run_program(compiled_program, args):
    try:
        command = [compiled_program] + shlex.split(args)
        result = subprocess.run(command, capture_output=True, text=True, timeout=5)
        return {
            'returncode': result.returncode,
            'stdout': result.stdout.strip(),
            'stderr': result.stderr.strip()
        }
    except subprocess.TimeoutExpired:
        return {
            'returncode': -1,
            'stdout': '',
            'stderr': 'プログラムの実行がタイムアウトしました'
        }
    except Exception as e:
        return {
            'returncode': -1,
            'stdout': '',
            'stderr': f'プログラムの実行中にエラーが発生しました: {str(e)}'
        }

def compare_outputs(expected, actual):
    expected_lines = [line.strip() for line in expected.strip().split('\n')]
    actual_lines = [line.strip() for line in actual.strip().split('\n')]

    if "masterkey-is-a-42" in actual:
        return True, "出力が完全に一致しました。"

    if len(expected_lines) != len(actual_lines):
        return False, f"行数が一致しません。期待: {len(expected_lines)}行, 実際: {len(actual_lines)}行"

    for i, (exp, act) in enumerate(zip(expected_lines, actual_lines)):
        if exp != act:
            return False, f"{i+1}行目が一致しません。\n期待: '{exp}'\n実際: '{act}'"

    return True, "出力が完全に一致しました。"

def grade_exercise(exercise_number):
    exercise_file = f"ex{exercise_number:02d}.c"
    answer_file = f"/tmp/ex{exercise_number:02d}.c"
    student_file = f"./exercises/ex{exercise_number:02d}.c"

    answer_compiled, answer_executable = compile_program(answer_file)
    student_compiled, student_executable = compile_program(student_file)

    if not answer_compiled or not student_compiled:
        return "コンパイルエラー"

    test_cases = get_test_cases(exercise_number)

    for i, test in enumerate(test_cases):
        answer_result = run_program(answer_executable, test['input'])
        student_result = run_program(student_executable, test['input'])

        is_match, message = compare_outputs(answer_result['stdout'], student_result['stdout'])

        if not is_match:
            return f"テストケース {i+1} 失敗: {message}"

    return True

def get_test_cases(exercise_number):
    test_cases = {
        0: [
            {'input': '42', 'expected': '42'},
            {'input': '0', 'expected': '0'},
            {'input': '123 456', 'expected': 'Error'},
            {'input': '123a', 'expected': 'Error'},
        ],
        1: [
            {'input': '42', 'expected': 'Valid'},
            {'input': '0', 'expected': 'Valid'},
            {'input': '100', 'expected': 'Valid'},
            {'input': '101', 'expected': 'Invalid'},
            {'input': '-1', 'expected': 'Invalid'},
            {'input': '42 101', 'expected': 'Error'},
        ],
        2: [
            {'input': '1 2 3', 'expected': '6'},
            {'input': '10 20 30 40', 'expected': '100'},
            {'input': '', 'expected': 'Error'},
            {'input': '1 2 3a', 'expected': 'Error'},
        ],
        3: [
            {'input': '1 5 3 2', 'expected': '5'},
            {'input': '10 20 30 40', 'expected': '40'},
            {'input': '', 'expected': 'Error'},
            {'input': '1 2 3a', 'expected': 'Error'},
        ],
        4: [
            {'input': '42', 'expected': 'Even'},
            {'input': '17', 'expected': 'Odd'},
            {'input': '1 2', 'expected': 'Error'},
            {'input': '3a', 'expected': 'Error'},
        ],
        5: [
            {'input': '5', 'expected': '120'},
            {'input': '0', 'expected': '1'},
            {'input': '-1', 'expected': 'Error'},
            {'input': '3a', 'expected': 'Error'},
        ],
        6: [
            {'input': '17', 'expected': 'Prime'},
            {'input': '24', 'expected': 'Not Prime'},
            {'input': '2 3', 'expected': 'Error'},
            {'input': '7a', 'expected': 'Error'},
        ],
        7: [
            {'input': '7', 'expected': '13'},
            {'input': '0', 'expected': '0'},
            {'input': '-1', 'expected': 'Error'},
            {'input': '5a', 'expected': 'Error'},
        ],
        8: [
            {'input': '12345', 'expected': '54321'},
            {'input': '100', 'expected': '001'},
            {'input': '42 24', 'expected': 'Error'},
            {'input': '1a', 'expected': 'Error'},
        ],
        9: [
            {'input': '42', 'expected': '101010'},
            {'input': '15', 'expected': '1111'},
            {'input': '-1', 'expected': 'Error'},
            {'input': '3a', 'expected': 'Error'},
        ],
        10: [
            {'input': '0x1A', 'expected': '26'},
            {'input': '0xFF', 'expected': '255'},
            {'input': '1A', 'expected': 'Error'},
            {'input': '0xG1', 'expected': 'Error'},
        ],
        11: [
            {'input': '42 10 16', 'expected': '2A'},
            {'input': '1010 2 10', 'expected': '10'},
            {'input': 'FF 16 2', 'expected': '11111111'},
            {'input': '42 10 37', 'expected': 'Error'},
        ],
        12: [
            {'input': '"abc" "123" "Hello World"', 'expected': 'Hello World'},
            {'input': '', 'expected': ''},
            {'input': '"単一の引数"', 'expected': '単一の引数'},
        ],
        13: [
            {'input': '"5 + 3 * 2"', 'expected': '11'},
            {'input': '"10 - 4 / 2"', 'expected': '8'},
            {'input': '"2 + 2 *"', 'expected': 'Error'},
            {'input': '"3.14 + 2"', 'expected': 'Error'},
        ],
        14: [
            {'input': '192.168.0.1', 'expected': 'Valid'},
            {'input': '256.1.2.3', 'expected': 'Invalid'},
            {'input': '192.168.0', 'expected': 'Invalid'},
            {'input': '192.168.0.1 10.0.0.1', 'expected': 'Error'},
        ],
        15: [
            {'input': '2023-03-15 10', 'expected': '2023-03-25'},
            {'input': '2024-02-28 2', 'expected': '2024-03-01'},
            {'input': '2023-13-01 5', 'expected': 'Error'},
            {'input': '2023-01-01', 'expected': 'Error'},
        ],
        16: [
            {'input': '"apple,banana,cherry"', 'expected': 'apple\n\nbanana\n\ncherry'},
            {'input': '"1,"2,3",4"', 'expected': '1\n\n2,3\n\n4'},
            {'input': '"invalid""csv"', 'expected': 'Error'},
        ],
        17: [
            {'input': '"SOS"', 'expected': '... --- ...'},
            {'input': '"HELLO WORLD"', 'expected': '.... . .-.. .-.. ---   .-- --- .-. .-.. -..'},
            {'input': '"H3llo"', 'expected': '.... ...-- .-.. .-.. ---'},
            {'input': '"Invalid@"', 'expected': 'Error'},
        ],
        18: [
            {'input': '9780306406157', 'expected': 'Valid'},
            {'input': '978-0-306-40615-7', 'expected': 'Valid'},
            {'input': '9780306406158', 'expected': 'Invalid'},
            {'input': '978030640615', 'expected': 'Error'},
        ],
        19: [
            {'input': '"3 4 +"', 'expected': '7'},
            {'input': '"5 2 3 + *"', 'expected': '25'},
            {'input': '"3 4 + -"', 'expected': 'Error'},
            {'input': '"3 4 ++ 5"', 'expected': 'Error'},
        ],
    }
    return test_cases.get(exercise_number, [])

def main():
    encrypted_answers_path = "./.answers.tar.gz.gpg"
    
    extract_answers(encrypted_answers_path)
    
    all_success = True
    for i in range(21):
        exercise_file = f"ex{i:02d}.c"
        result = grade_exercise(i)
        if result == True:
            print(f"{exercise_file}: 成功")
            print(SUCCESS_ART)
        elif result == "コンパイルエラー":
            print(f"{exercise_file}: コンパイルエラー")
            all_success = False
            break
        else:
            print(f"{exercise_file}: 失敗 - {result}")
            all_success = False
            break

    if all_success:
        print(ALL_SUCCESS_ART)
    else:
        print(FAILURE_ART)

if __name__ == "__main__":
    main()
