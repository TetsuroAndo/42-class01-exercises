/* class01/ex03.c
 * 課題名：atoi_max
 * 使用可能な関数：write
 * ------------------------------------------*
 * コマンドライン引数として与えられた複数の整数の中から最大値を見つけ、出力するプログラムを書きなさい。
 * 引数が1つ未満の場合、または文字列に数字以外の文字が含まれている場合は、"Error"と出力してください。
 *
 * 例：
 * $> ./atoi_max 1 5 3 2
 * 5
 * $> ./atoi_max 10 20 30 40
 * 40
 * $> ./atoi_max
 * Error
 * $> ./atoi_max 1 2 3a
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

int	main(int argc, char **argv)
{
	int	max;
	int	num;
	int	i;

	if (argc < 2)
	{
		ft_putstr("Error\n");
		return (1);
	}
	max = ft_atoi(argv[1]);
	if (max == -1)
	{
		ft_putstr("Error\n");
		return (1);
	}
	i = 2;
	while (i < argc)
	{
		num = ft_atoi(argv[i]);
		if (num == -1)
		{
			ft_putstr("Error\n");
			return (1);
		}
		if (num > max)
			max = num;
		i++;
	}
	ft_putnbr(max);
	ft_putchar('\n');
	return (0);
}
