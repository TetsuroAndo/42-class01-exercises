/* class01/ex10.c
 * 課題名：atoi_hex_to_dec
 * 使用可能な関数：write
 * ------------------------------------------*
 * コマンドライン引数として与えられた16進数の文字列を10進数に変換し、結果を出力するプログラムを書きなさい。
 * 引数が1つでない場合、または無効な16進数文字列の場合は、"Error"と出力してください。
 * 16進数文字列は "0x" または "0X" で始まる必要があります。
 *
 * 例：
 * $> ./hex_to_dec 0x1A
 * 26
 * $> ./hex_to_dec 0xFF
 * 255
 * $> ./hex_to_dec 1A
 * Error
 * $> ./hex_to_dec 0xG1
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

int	ft_hex_to_dec(char *str)
{
	int	result;
	int	digit;

	result = 0;
	if (str[0] != '0' || (str[1] != 'x' && str[1] != 'X'))
		return (-1);
	str += 2;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			digit = *str - '0';
		else if (*str >= 'A' && *str <= 'F')
			digit = *str - 'A' + 10;
		else if (*str >= 'a' && *str <= 'f')
			digit = *str - 'a' + 10;
		else
			return (-1);
		result = result * 16 + digit;
		str++;
	}
	return (result);
}

int	main(int argc, char **argv)
{
	int	num;

	if (argc != 2)
	{
		ft_putstr("Error\n");
		return (1);
	}
	num = ft_hex_to_dec(argv[1]);
	if (num == -1)
	{
		ft_putstr("Error\n");
		return (1);
	}
	ft_putnbr(num);
	ft_putchar('\n');
	return (0);
}
