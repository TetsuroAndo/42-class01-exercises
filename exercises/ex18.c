/* class01/ex18.c
 * 課題名：atoi_isbn_validator
 * 使用可能な関数：write
 * ------------------------------------------*
 * コマンドライン引数としてISBN-13の文字列を受け取り、その有効性を検証するプログラムを書きなさい。
 * 有効なISBN-13の場合は"Valid"を、無効な場合は"Invalid"を出力してください。
 * ISBNは13桁の数字で構成され、最後の1桁はチェックディジットです。
 * ハイフンは無視してください。
 * 引数が1つでない場合は、"Error"と出力してください。
 *
 * 例：
 * $> ./isbn_validator 9780306406157
 * Valid
 * $> ./isbn_validator 978-0-306-40615-7
 * Valid
 * $> ./isbn_validator 9780306406158
 * Invalid
 * $> ./isbn_validator 978030640615
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

int	is_valid_isbn(char *isbn)
{
	int	sum;
	int	digit_count;
	int	multiplier;

	sum = 0;
	digit_count = 0;
	multiplier = 1;
	while (*isbn)
	{
		if (*isbn >= '0' && *isbn <= '9')
		{
			sum += (*isbn - '0') * multiplier;
			multiplier = (multiplier == 1) ? 3 : 1;
			digit_count++;
		}
		else if (*isbn != '-')
			return (0);
		isbn++;
	}
	if (digit_count != 13)
		return (0);
	return (sum % 10 == 0);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_putstr("Error\n");
		return (1);
	}
	if (ft_strlen(argv[1]) < 13)
	{
		ft_putstr("Error\n");
		return (1);
	}
	if (is_valid_isbn(argv[1]))
		ft_putstr("Valid\n");
	else
		ft_putstr("Invalid\n");
	return (0);
}
