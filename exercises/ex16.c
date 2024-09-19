/* class01/ex16.c
 * 課題名：atoi_parse_csv
 * 使用可能な関数：write, malloc, free
 * ------------------------------------------*
 * コマンドライン引数としてCSV形式の文字列を受け取り、各フィールドを解析して出力するプログラムを書きなさい。
 * フィールドにカンマが含まれる場合、そのフィールドは二重引用符で囲まれているものとします。
 * 各フィールドを新しい行に出力し、フィールド間に空行を入れてください。
 * 引数が1つでない場合、または無効なCSV形式の場合は、"Error"と出力してください。
 *
 * 例：
 * $> ./parse_csv "apple,banana,cherry"
 * apple
 *
 * banana
 *
 * cherry
 * $> ./parse_csv "1,\"2,3\",4"
 * 1
 *
 * 2,3
 *
 * 4
 * $> ./parse_csv "invalid""csv"
 * Error
 */

#include <stdlib.h>
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

int	is_valid_csv(char *str)
{
	int	in_quotes;

	in_quotes = 0;
	while (*str)
	{
		if (*str == '"')
			in_quotes = !in_quotes;
		else if (*str == ',' && !in_quotes)
			return (1);
		str++;
	}
	return (!in_quotes);
}

void	print_field(char **str)
{
	int	in_quotes;

	in_quotes = 0;
	while (**str && (**str != ',' || in_quotes))
	{
		if (**str == '"')
		{
			in_quotes = !in_quotes;
			(*str)++;
			continue ;
		}
		ft_putchar(**str);
		(*str)++;
	}
	ft_putchar('\n');
	ft_putchar('\n');
	if (**str == ',')
		(*str)++;
}

void	parse_csv(char *str)
{
	while (*str)
		print_field(&str);
}

int	main(int argc, char **argv)
{
	if (argc != 2 || !is_valid_csv(argv[1]))
	{
		ft_putstr("Error\n");
		return (1);
	}
	parse_csv(argv[1]);
	return (0);
}
