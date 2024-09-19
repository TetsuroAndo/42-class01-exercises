/* class01/ex20.c
 * 課題名：atoi_big_integer
 * 使用可能な関数：write, malloc, free
 * ------------------------------------------*
 * コマンドライン引数として2つの非常に大きな整数（文字列形式）を受け取り、その和を計算して出力するプログラムを書きなさい。
 * 整数は100桁以上の桁数を持つ可能性があるため、通常のint型では扱えません。
 * 独自のbig integer構造体を実装し、文字列から変換、加算、そして結果を文字列に戻す処理を行ってください。
 * 引数が2つでない場合、または無効な入力の場合は、"Error"と出力してください。
 *
 * 例：
 * $> ./big_integer_add 12345678901234567890 98765432109876543210
 * 111111111011111111100
 * $> ./big_integer_add 999999999999999999999 1
 * 1000000000000000000000
 * $> ./big_integer_add 123 abc
 * Error
 */

#include <stdlib.h>
#include <unistd.h>

#define MAX_DIGITS 1000

typedef struct
{
	int	digits[MAX_DIGITS];
	int	length;
}		BigInteger;

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
}

int	is_valid_number(char *str)
{
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

void	string_to_big_integer(char *str, BigInteger *num)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[len])
		len++;
	num->length = len;
	for (i = 0; i < len; i++)
		num->digits[i] = str[len - 1 - i] - '0';
}

void	add_big_integers(BigInteger *a, BigInteger *b, BigInteger *result)
{
	int	carry;
	int	i;
	int	max_len;
	int	sum;

	carry = 0;
	max_len = (a->length > b->length) ? a->length : b->length;
	for (i = 0; i < max_len || carry; i++)
	{
		sum = carry;
		if (i < a->length)
			sum += a->digits[i];
		if (i < b->length)
			sum += b->digits[i];
		result->digits[i] = sum % 10;
		carry = sum / 10;
	}
	result->length = i;
}

void	print_big_integer(BigInteger *num)
{
	int	i;

	for (i = num->length - 1; i >= 0; i--)
		ft_putchar(num->digits[i] + '0');
	ft_putchar('\n');
}

int	main(int argc, char **argv)
{
	BigInteger a, b, result;
	if (argc != 3 || !is_valid_number(argv[1]) || !is_valid_number(argv[2]))
	{
		ft_putstr("Error\n");
		return (1);
	}
	string_to_big_integer(argv[1], &a);
	string_to_big_integer(argv[2], &b);
	add_big_integers(&a, &b, &result);
	print_big_integer(&result);
	return (0);
}
