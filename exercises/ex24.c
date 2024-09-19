/* class01/ex24.c
 * 課題名：atoi_json_parser
 * 使用可能な関数：write, malloc, free
 * ------------------------------------------*
 * コマンドライン引数としてJSON形式の文字列を受け取り、その構造を解析して整形出力するプログラムを書きなさい。
 * サポートするJSON要素は、オブジェクト、配列、文字列、数値、真偽値、nullとします。
 * 整形出力では、適切なインデントを使用し、各要素を見やすく配置してください。
 * 引数が1つでない場合、または無効なJSON形式の場合は、"Error"と出力してください。
 *
 * 例：
 * $> ./json_parser '{"name":"John","age":30,"city":"New York"}'
 * {
 *   "name": "John",
 *   "age": 30,
 *   "city": "New York"
 * }
 * $> ./json_parser '[1,2,{"a":true,"b":null}]'
 * [
 *   1,
 *   2,
 *   {
 *     "a": true,
 *     "b": null
 *   }
 * ]
 * $> ./json_parser '{"invalid":}'
 * Error
 */
