/* class01/ex12.c
 * 課題名：atoi_roman
 * 使用可能な関数：write
 * ------------------------------------------*
 * コマンドライン引数としてローマ数字の文字列を受け取り、それをアラビア数字に変換して出力するプログラムを書きなさい。
 * ローマ数字は I, V, X, L, C, D, M のみを使用し、3999以下の数値を表すものとします。
 * 引数が1つでない場合、または無効なローマ数字の場合は、"Error"と出力してください。
 *
 * 例：
 * $> ./roman_to_arabic XLII
 * 42
 * $> ./roman_to_arabic MCMLIV
 * 1954
 * $> ./roman_to_arabic IIII
 * Error
 * $> ./roman_to_arabic ABC
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

void	ft_putnbr(int n)
{
	if (n >= 10)
		ft_putnbr(n / 10);
	ft_putchar(n % 10 + '0');
}

int	get_roman_value(char c)
{
	if (c == 'I')
		return (1);
	if (c == 'V')
		return (5);
	if (c == 'X')
		return (10);
	if (c == 'L')
		return (50);
	if (c == 'C')
		return (100);
	if (c == 'D')
		return (500);
	if (c == 'M')
		return (1000);
	return (0);
}

int	is_valid_roman(char *str)
{
	int	prev;
	int	count;
	int	current;

	prev = 0;
	count = 0;
	while (*str)
	{
		current = get_roman_value(*str);
		if (current == 0)
			return (0);
		if (current > prev)
		{
			if (prev * 5 != current && prev * 10 != current)
				return (0);
			if (count > 1)
				return (0);
			count = 0;
		}
		else if (current < prev)
			count = 0;
		else
			count++;
		if (count > 3)
			return (0);
		prev = current;
		str++;
	}
	return (1);
}

int	roman_to_arabic(char *str)
{
	int	result;
	int	prev;
	int	current;

	result = 0;
	prev = 0;
	while (*str)
	{
		current = get_roman_value(*str);
		if (current > prev)
			result += current - 2 * prev;
		else
			result += current;
		prev = current;
		str++;
	}
	return (result);
}

int	main(int argc, char **argv)
{
	int	num;

	if (argc != 2 || !is_valid_roman(argv[1]))
	{
		ft_putstr("Error\n");
		return (1);
	}
	num = roman_to_arabic(argv[1]);
	if (num > 3999)
	{
		ft_putstr("Error\n");
		return (1);
	}
	ft_putnbr(num);
	ft_putchar('\n');
	return (0);
}
