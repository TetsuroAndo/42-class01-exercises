/* class01/ex28.c
 * 課題名：atoi_compiler_lexer
 * 使用可能な関数：write, malloc, free
 * ------------------------------------------*
 * コマンドライン引数としてC言語のソースコード（文字列）を受け取り、
 * レキシカル解析を行ってトークンのリストを出力するプログラムを書きなさい。
 * 識別子、キーワード、リテラル、演算子、区切り文字を認識し、それぞれを適切に分類してください。
 * 各トークンは "<type>: <value>" の形式で1行ずつ出力してください。
 * 引数が1つでない場合、または無効な入力の場合は、"Error"と出力してください。
 *
 * 例：
 * $> ./compiler_lexer "int main() { return (0); }"
 * KEYWORD: int
 * IDENTIFIER: main
 * DELIMITER: (
 * DELIMITER: )
 * DELIMITER: {
 * KEYWORD: return
 * LITERAL: 0
 * DELIMITER: ;
 * DELIMITER: }
 * $> ./compiler_lexer "x = 5 + y;"
 * IDENTIFIER: x
 * OPERATOR: =
 * LITERAL: 5
 * OPERATOR: +
 * IDENTIFIER: y
 * DELIMITER: ;
 * $> ./compiler_lexer "int x = 10 @"
 * Error
 */
