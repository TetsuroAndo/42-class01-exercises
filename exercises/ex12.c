/* class01/ex12.c
 * 課題名： last_parameter
 * 使用可能な関数：write
 * ------------------------------------------*
 * 文字列をコマンドライン引数として受け取り、そのコマンドライン引数の最後の項目と改行を
 * 標準出力に出力するプログラムを書きなさい。
 * コマンドライン引数の数が1つ未満の場合、改行だけを標準出力に出力すること。
 *
 * 例：
 * $> ./aff_last_param "abc" "123" "Hello World"
 * Hello World
 * $> ./aff_last_param
 *
 * $> ./aff_last_param "単一の引数"
 * 単一の引数
 */

#include <unistd.h>

void	ft_putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
}

int	main(int argc, char **argv)
{
	if (argc > 1)
		ft_putstr(argv[argc - 1]);
	write(1, "\n", 1);
	return (0);
}
