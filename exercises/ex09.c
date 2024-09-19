/* class01/ex09.c
 * 課題名：atoi_binary
 * 使用可能な関数：write
 * ------------------------------------------*
 * コマンドライン引数として与えられた非負整数を2進数に変換し、結果を出力するプログラムを書きなさい。
 * 引数が1つでない場合、負の数の場合、または文字列に数字以外の文字が含まれている場合は、"Error"と出力してください。
 *
 * 例：
 * $> ./atoi_binary 42
 * 101010
 * $> ./atoi_binary 15
 * 1111
 * $> ./atoi_binary -1
 * Error
 * $> ./atoi_binary 3a
 * Error
 */

#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
}

int	ft_atoi(char *str)
{
	long long	result;

	result = 0;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (-1);
		result = result * 10 + (*str - '0');
		if (result > 2147483647)
			return (-1);
		str++;
	}
	return ((int)result);
}

void	ft_print_binary(int n)
{
	if (n > 1)
		ft_print_binary(n / 2);
	ft_putchar(n % 2 + '0');
}

int	main(int argc, char **argv)
{
	int	num;

	if (argc != 2)
	{
		ft_putstr("Error\n");
		return (1);
	}
	num = ft_atoi(argv[1]);
	if (num == -1)
	{
		ft_putstr("Error\n");
		return (1);
	}
	ft_print_binary(num);
	ft_putchar('\n');
	return (0);
}
