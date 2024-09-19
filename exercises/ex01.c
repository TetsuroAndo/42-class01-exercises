/* class01/ex01.c
 * 課題名：atoi_range
 * 使用可能な関数：write
 * ------------------------------------------*
 * コマンドライン引数として与えられた文字列を整数に変換し、その結果が0から100の範囲内であれば
 * "Valid"を、範囲外であれば"Invalid"を出力するプログラムを書きなさい。
 * 引数が1つでない場合、または文字列に数字以外の文字が含まれている場合は、"Error"と出力してください。
 *
 * 例：
 * $> ./atoi_range 42
 * Valid
 * $> ./atoi_range 101
 * Invalid
 * $> ./atoi_range 42 101
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
	if (num >= 0 && num <= 100)
		ft_putstr("Valid\n");
	else
		ft_putstr("Invalid\n");
	return (0);
}
