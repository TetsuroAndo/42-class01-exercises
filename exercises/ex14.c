/* class01/ex14.c
 * 課題名：atoi_ip_validator
 * 使用可能な関数：write
 * ------------------------------------------*
 * コマンドライン引数としてIPv4アドレスの文字列を受け取り、その有効性を検証するプログラムを書きなさい。
 * 有効なIPv4アドレスの場合は"Valid"を、無効な場合は"Invalid"を出力してください。
 * 引数が1つでない場合は、"Error"と出力してください。
 *
 * 例：
 * $> ./ip_validator 192.168.0.1
 * Valid
 * $> ./ip_validator 256.1.2.3
 * Invalid
 * $> ./ip_validator 192.168.0
 * Invalid
 * $> ./ip_validator 192.168.0.1 10.0.0.1
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

int	ft_atoi(char **str)
{
	int	num;

	num = 0;
	while (**str >= '0' && **str <= '9')
	{
		num = num * 10 + (**str - '0');
		(*str)++;
	}
	return (num);
}

int	is_valid_ip(char *ip)
{
	int	count;
	int	num;

	count = 0;
	while (*ip)
	{
		num = ft_atoi(&ip);
		if (num < 0 || num > 255)
			return (0);
		count++;
		if (count < 4 && *ip == '.')
			ip++;
		else if (count == 4 && *ip == '\0')
			return (1);
		else
			return (0);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_putstr("Error\n");
		return (1);
	}
	if (is_valid_ip(argv[1]))
		ft_putstr("Valid\n");
	else
		ft_putstr("Invalid\n");
	return (0);
}
