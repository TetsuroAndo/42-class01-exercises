/* class01/ex04.c
 * 課題名：atoi_even_odd
 * 使用可能な関数：write
 * ------------------------------------------*
 * コマンドライン引数として与えられた整数が偶数なら"Even"を、奇数なら"Odd"を出力するプログラムを書きなさい。
 * 引数が1つでない場合、または文字列に数字以外の文字が含まれている場合は、"Error"と出力してください。
 *
 * 例：
 * $> ./atoi_even_odd 42
 * Even
 * $> ./atoi_even_odd 17
 * Odd
 * $> ./atoi_even_odd 1 2
 * Error
 * $> ./atoi_even_odd 3a
 * Error
 */

#include <unistd.h>

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
	if (num % 2 == 0)
		ft_putstr("Even\n");
	else
		ft_putstr("Odd\n");
	return (0);
}
