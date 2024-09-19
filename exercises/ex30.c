/* class01/ex30.c
 * 課題名：atoi_programming_language_interpreter
 * 使用可能な関数：write, malloc, free, atoi, atof
 * ------------------------------------------*
 * 目標：簡易プログラミング言語のインタプリタを実装する
 * 
 * コマンドライン引数として、自作の簡易プログラミング言語で書かれたソースコードファイルのパスを受け取り、
 * そのコードを解析・実行するインタプリタを実装してください。
 * この言語は以下の機能をサポートする必要があります：
 * 
 * 1. 変数定義と代入（整数、浮動小数点数、文字列）
 * 2. 基本的な算術演算（+, -, *, /, %, ^）
 * 3. 条件分岐（if-else）
 * 4. ループ（while, for）
 * 5. 関数定義と呼び出し
 * 6. 配列
 * 7. 文字列操作（連結、部分文字列取得）
 * 8. 基本的な入出力
 * 9. コメント
 * 
 * 言語仕様：
 * - 変数定義：`var name = value`
 * - 関数定義：`func name(param1, param2) { ... }`
 * - 条件分岐：`if (condition) { ... } else { ... }`
 * - ループ：`while (condition) { ... }` または `for (init; condition; update) { ... }`
 * - 配列：`var arr = [1, 2, 3]`
 * - 文字列操作：`concat(str1, str2)`, `substr(str, start, length)`
 * - 入出力：`print(value)`, `var input = readline()`
 *  * - コメント：`// 一行コメント` または `\/* 複数行コメント *\/`
 * 
 * インタプリタは以下のステップを実装する必要があります：
 * 1. 字句解析（Lexical Analysis）
 * 2. 構文解析（Syntax Analysis）
 * 3. 意味解析（Semantic Analysis）
 * 4. 実行（Execution）
 * 
 * エラー処理：
 * - 構文エラー、型エラー、未定義変数の使用、再帰の深さ制限超過などを適切に検出し、
 *   エラーメッセージと行番号を出力してください。
 * 
 * 拡張課題（任意）：
 * - デバッグモード：ステップ実行、変数値の表示機能を実装
 * - 最適化：簡単な最適化（定数畳み込みなど）を実装
 * - REPL（Read-Eval-Print Loop）モード：対話的な実行環境を提供
 * 
 * 引数が1つでない場合、ファイルが存在しない場合、または無効な入力の場合は、
 * 適切なエラーメッセージを出力してください。
 * 
 * 例：
 * $> cat example.mylang
 * // フィボナッチ数列を計算する関数
 * func fibonacci(n) {
 *     if (n <= 1) {
 *         return n;
 *     }
 *     return fibonacci(n - 1) + fibonacci(n - 2);
 * }
 * 
 * // メイン処理
 * var n = 10;
 * for (var i = 0; i < n; i = i + 1) {
 *     print(concat("Fibonacci(", concat(toString(i), concat(") = ", toString(fibonacci(i))))));
 * }
 * 
 * $> ./interpreter example.mylang
 * Fibonacci(0) = 0
 * Fibonacci(1) = 1
 * Fibonacci(2) = 1
 * Fibonacci(3) = 2
 * Fibonacci(4) = 3
 * Fibonacci(5) = 5
 * Fibonacci(6) = 8
 * Fibonacci(7) = 13
 * Fibonacci(8) = 21
 * Fibonacci(9) = 34
 * 
 * $> ./interpreter nonexistent_file.mylang
 * Error: File not found
 * 
 * $> ./interpreter invalid_syntax.mylang
 * Error on line 5: Unexpected token ')'
 */
