/* class01/ex22.c
 * 課題名：atoi_rational_number
 * 使用可能な関数：write, malloc, free
 * ------------------------------------------*
 * コマンドライン引数として2つの有理数（分数形式）を受け取り、その和、差、積、商を計算して出力するプログラムを書きなさい。
 * 有理数は "numerator/denominator" の形式で表現されます。
 * 結果は既約分数の形で出力し、分母が1の場合は整数として出力してください。
 * 引数が2つでない場合、または無効な入力の場合は、"Error"と出力してください。
 *
 * 例：
 * $> ./rational_calculator 1/2 1/3
 * Sum: 5/6
 * Difference: 1/6
 * Product: 1/6
 * Quotient: 3/2
 * $> ./rational_calculator 4/2 1/4
 * Sum: 9/4
 * Difference: 7/4
 * Product: 1/2
 * Quotient: 8
 * $> ./rational_calculator 1/0 1/2
 * Error
 */
