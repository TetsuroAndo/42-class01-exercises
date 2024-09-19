/* class01/ex05.c
 * 課題名：atoi_factorial
 * 使用可能な関数：write
 * ------------------------------------------*
 * コマンドライン引数として与えられた非負整数の階乗を計算し、結果を出力するプログラムを書きなさい。
 * 引数が1つでない場合、負の数の場合、または文字列に数字以外の文字が含まれている場合は、"Error"と出力してください。
 *
 * 例：
 * $> ./atoi_factorial 5
 * 120
 * $> ./atoi_factorial 0
 * 1
 * $> ./atoi_factorial -1
 * Error
 * $> ./atoi_factorial 3a
 * Error
 */

#include <unistd.h>

void	ft_putstr(char *str);
void	ft_putnbr(int n);
void	ft_putchar(char c);

void	ft_putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
}

void	ft_putnbr(int n)
{
	if (n >= 10)
		ft_putnbr(n / 10);
	ft_putchar(n % 10 + '0');
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
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

int	ft_factorial(int n)
{
	if (n == 0)
		return (1);
	return (n * ft_factorial(n - 1));
}

int	main(int argc, char **argv)
{
	int	num;
	int	result;

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
	result = ft_factorial(num);
	ft_putnbr(result);
	ft_putchar('\n');
	return (0);
}
