/* class01/ex21.c
 * 課題名：atoi_regex_engine
 * 使用可能な関数：write, malloc, free
 * ------------------------------------------*
 * コマンドライン引数として正規表現パターンと検査対象の文字列を受け取り、
 * パターンが文字列にマッチするかどうかを判定するプログラムを書きなさい。
 * サポートする正規表現の機能は以下に限定します：
 * - . (任意の1文字にマッチ)
 * - * (直前の文字の0回以上の繰り返し)
 * - ^ (文字列の先頭にマッチ)
 * - $ (文字列の末尾にマッチ)
 * 引数が2つでない場合、または無効な正規表現の場合は、"Error"と出力してください。
 *
 * 例：
 * $> ./regex_match "a.c" "abc"
 * Match
 * $> ./regex_match "a*b" "aaaab"
 * Match
 * $> ./regex_match "^abc$" "abcd"
 * No Match
 * $> ./regex_match "[a-z]" "a"
 * Error
 */
