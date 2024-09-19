/* class01/ex11.c
 * 課題名：atoi_base_converter
 * 使用可能な関数：write
 * ------------------------------------------*
 * コマンドライン引数として、数値、元の基数、変換先の基数の3つを受け取り、
 * 指定された基数間で数値を変換するプログラムを書きなさい。
 * 基数は2から36までの範囲内とし、36以上の基数では英字を使用します。
 * 引数が3つでない場合、または無効な入力の場合は、"Error"と出力してください。
 *
 * 例：
 * $> ./base_converter 42 10 16
 * 2A
 * $> ./base_converter 1010 2 10
 * 10
 * $> ./base_converter FF 16 2
 * 11111111
 * $> ./base_converter 42 10 37
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

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

int	ft_isalpha(char c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

int	ft_toupper(char c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 'a' + 'A');
	return (c);
}

int	ft_atoi_base(char *str, int base)
{
	int	result;
	int	digit;

	result = 0;
	while (*str)
	{
		if (ft_isdigit(*str))
			digit = *str - '0';
		else if (ft_isalpha(*str))
			digit = ft_toupper(*str) - 'A' + 10;
		else
			return (-1);
		if (digit >= base)
			return (-1);
		result = result * base + digit;
		str++;
	}
	return (result);
}

void	ft_putnbr_base(int nbr, int base)
{
	char	*digits;

	digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	if (nbr >= base)
		ft_putnbr_base(nbr / base, base);
	ft_putchar(digits[nbr % base]);
}

int	main(int argc, char **argv)
{
	int	num;
	int	from_base;
	int	to_base;

	if (argc != 4)
	{
		ft_putstr("Error\n");
		return (1);
	}
	from_base = ft_atoi_base(argv[2], 10);
	to_base = ft_atoi_base(argv[3], 10);
	if (from_base < 2 || from_base > 36 || to_base < 2 || to_base > 36)
	{
		ft_putstr("Error\n");
		return (1);
	}
	num = ft_atoi_base(argv[1], from_base);
	if (num == -1)
	{
		ft_putstr("Error\n");
		return (1);
	}
	ft_putnbr_base(num, to_base);
	ft_putchar('\n');
	return (0);
}
