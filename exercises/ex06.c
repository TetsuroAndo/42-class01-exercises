/* class01/ex06.c
 * 課題名：atoi_prime
 * 使用可能な関数：write
 * ------------------------------------------*
 * コマンドライン引数として与えられた整数が素数かどうかを判定し、素数なら"Prime"を、
 * そうでなければ"Not Prime"を出力するプログラムを書きなさい。
 * 引数が1つでない場合、または文字列に数字以外の文字が含まれている場合は、"Error"と出力してください。
 *
 * 例：
 * $> ./atoi_prime 17
 * Prime
 * $> ./atoi_prime 24
 * Not Prime
 * $> ./atoi_prime 2 3
 * Error
 * $> ./atoi_prime 7a
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

int	is_prime(int num)
{
	int	i;

	if (num <= 1)
		return (0);
	i = 2;
	while (i * i <= num)
	{
		if (num % i == 0)
			return (0);
		i++;
	}
	return (1);
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
	if (is_prime(num))
		ft_putstr("Prime\n");
	else
		ft_putstr("Not Prime\n");
	return (0);
}
