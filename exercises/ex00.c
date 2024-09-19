/* class01/ex00.c
 * 課題名：atoi_simple
 * 使用可能な関数：write
 * ------------------------------------------*
 * コマンドライン引数として与えられた文字列を整数に変換し、その結果を標準出力に出力するプログラムを書きなさい。
 * 文字列は正の整数のみを含むと仮定します。
 * 引数が1つでない場合、または文字列に数字以外の文字が含まれている場合は、"Error"と出力してください。
 *
 * 例：
 * $> ./atoi_simple 42
 * 42
 * $> ./atoi_simple 123 456
 * Error
 * $> ./atoi_simple 123a
 * Error
 */

#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int n)
{
	if (n >= 10)
		ft_putnbr(n / 10);
	ft_putchar(n % 10 + '0');
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

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		write(1, "Error\n", 6);
		return (1);
	}

	int num = ft_atoi(argv[1]);
	if (num == -1)
	{
		write(1, "Error\n", 6);
		return (1);
	}

	ft_putnbr(num);
	write(1, "\n", 1);
	return (0);
}