/* class01/ex08.c
 * 課題名：atoi_reverse
 * 使用可能な関数：write
 * ------------------------------------------*
 * コマンドライン引数として与えられた整数を逆順にして出力するプログラムを書きなさい。
 * 引数が1つでない場合、または文字列に数字以外の文字が含まれている場合は、"Error"と出力してください。
 *
 * 例：
 * $> ./atoi_reverse 12345
 * 54321
 * $> ./atoi_reverse 100
 * 001
 * $> ./atoi_reverse 42 24
 * Error
 * $> ./atoi_reverse 1a
 * Error
 */

#include <unistd.h>

void	ft_putstr(char *str);
void	ft_putnbr(int n);
void	ft_putchar(char c);

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
	if (*str == '0' && *(str + 1) == '\0')
		return (0);
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

void	ft_putnbr_reverse(int n)
{
	int	printed;

	printed = 0;
	if (n == 0)
		ft_putchar('0');
	while (n > 0)
	{
		ft_putchar(n % 10 + '0');
		n /= 10;
		printed = 1;
	}
	if (!printed)
		ft_putchar('0');
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
	ft_putnbr_reverse(num);
	ft_putchar('\n');
	return (0);
}
