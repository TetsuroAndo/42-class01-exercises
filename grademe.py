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

def extract_encrypted_tar(encrypted_file, password, output_dir):
    with tempfile.TemporaryDirectory() as temp_dir:
        # GPGで復号化
        decrypted_file = os.path.join(temp_dir, "answers.tar.gz")
        subprocess.run(["gpg", "--batch", "--yes", "--passphrase", password, "-o", decrypted_file, "-d", encrypted_file], check=True)

        # tarファイルを解凍
        with tarfile.open(decrypted_file, "r:gz") as tar:
            tar.extractall(path=output_dir)

def extract_answers(tar_path, password):
    password = base64.b64decode(ENCODED_PASSWORD).decode('utf-8')
    
    # 一時ディレクトリを作成
    with tempfile.TemporaryDirectory() as temp_dir:
        try:
            # 暗号化されたtarファイルを復号化して解凍
            extract_encrypted_tar(tar_path, password, temp_dir)
            
            # 解凍されたファイルを /tmp にコピー
            for root, dirs, files in os.walk(temp_dir):
                for file in files:
                    src_path = os.path.join(root, file)
                    dst_path = os.path.join('/tmp', file)
                    print(f"コピー: {src_path} -> {dst_path}")
                    shutil.copy(src_path, dst_path)
            
            print("答えファイルの解凍が完了しました。")
            print("/tmp ディレクトリの内容:")
            for file in os.listdir('/tmp'):
                print(file)
        except Exception as e:
            print(f"エラー: 答えファイルの解凍中に問題が発生しました - {str(e)}")
            sys.exit(1)

def compile_c_file(c_file, output_file):
    try:
        # gccを使用してCファイルをコンパイル
        compile_command = ['gcc', '-Wall', '-Wextra', '-Werror', c_file, '-o', output_file]
        result = subprocess.run(compile_command, capture_output=True, text=True)
        
        # コンパイルが成功したかチェック
        if result.returncode == 0:
            print(f"{c_file} のコンパイルが成功しました。")
            return True
        else:
            print(f"{c_file} のコンパイルに失敗しました。")
            print("コンパイルエラー:")
            print(result.stderr)
            return False
    except Exception as e:
        print(f"コンパイル中にエラーが発生しました: {str(e)}")
        return False

def run_program(program, args):
    try:
        # プログラムをコンパイル
        compiled_program = f"{program}.out"
        compile_command = ['gcc', '-o', compiled_program, program]
        compile_result = subprocess.run(compile_command, capture_output=True, text=True)
        
        if compile_result.returncode != 0:
            return {
                'returncode': compile_result.returncode,
                'stdout': '',
                'stderr': f'コンパイルエラー: {compile_result.stderr}'
            }

        # コンパイルされたプログラムと引数を結合
        command = [compiled_program] + shlex.split(args)
        
        # サブプロセスとしてプログラムを実行
        result = subprocess.run(command, capture_output=True, text=True, timeout=5)
        
        # 実行結果を返す
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
    # 改行で分割し、各行をトリムする
    expected_lines = [line.strip() for line in expected.strip().split('\n')]
    actual_lines = [line.strip() for line in actual.strip().split('\n')]

    # 行数が異なる場合
    if len(expected_lines) != len(actual_lines):
        return False, f"行数が一致しません。期待: {len(expected_lines)}行, 実際: {len(actual_lines)}行"

    # 各行を比較
    for i, (exp, act) in enumerate(zip(expected_lines, actual_lines)):
        if exp != act:
            return False, f"{i+1}行目が一致しません。\n期待: '{exp}'\n実際: '{act}'"

    # すべての行が一致した場合
    return True, "出力が完全に一致しました。"

import os

def grade_exercise(exercise_number):
    exercise_file = f"ex{exercise_number:02d}.c"
    answer_file = f"/tmp/ex{exercise_number:02d}.c"
    student_file = f"/tmp/ex{exercise_number:02d}.c"

    print(f"採点中: {exercise_file}")

    # テストケースを定義
    test_cases = get_test_cases(exercise_number)

    for i, test in enumerate(test_cases):
        # 答えのプログラムを実行
        answer_result = run_program(answer_file, test['input'])
        
        # 学生のプログラムを実行
        student_result = run_program(student_file, test['input'])

        # 出力を比較
        is_match, message = compare_outputs(answer_result['stdout'], student_result['stdout'])

        if not is_match:
            print(f"{exercise_file}: 失敗")
            return f"テストケース {i+1} 失敗: {message}"

    print(f"{exercise_file}: 成功")
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
    # 暗号化された答えファイルのパスを指定
    encrypted_answers_path = "./.answers.tar.gz.gpg"
    
    # 答えファイルを解凍
    extract_answers(encrypted_answers_path, ENCODED_PASSWORD)
    
    # ex00.c から ex20.c まで採点
    for i in range(21):
        exercise_file = f"ex{i:02d}.c"
        result = grade_exercise(i)
        if result == True:
            print(f"{exercise_file}: 成功")
        elif result == "エラー":
            print(f"{exercise_file}: エラー")
            break  # エラーが発生したら採点を終了
        else:
            print(f"{exercise_file}: 失敗 - {result}")
            break  # 失敗した場合も採点を終了

if __name__ == "__main__":
    main()