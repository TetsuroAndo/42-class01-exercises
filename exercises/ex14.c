/* class01/ex14.c
 * 課題名：atoi_ip_validator
 * 使用可能な関数：write
 * ------------------------------------------*
 * コマンドライン引数としてIPv4アドレスの文字列を受け取り、その有効性（IPv4の形式であるか）を検証するプログラムを書きなさい。
 * 有効なIPv4アドレスの場合は"Valid"を、無効な場合は"Invalid"を出力してください。
 * 引数が1つでない場合は、"Error"と出力してください。
 *
 * 例：
 * $> ./ip_validator 192.168.0.1
 * Valid
 * $> ./ip_validator 256.1.2.3
 * Invalid
 * $> ./ip_validator 192.168.0
 * Invalid
 * $> ./ip_validator 192.168.0.1 10.0.0.1
 * Error
 */
