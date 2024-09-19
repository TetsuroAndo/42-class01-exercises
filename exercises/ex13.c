/* class01/ex13.c
 * 課題名：atoi_calculator
 * 使用可能な関数：write
 * ------------------------------------------*
 * コマンドライン引数として簡単な数式を受け取り、その結果を計算して出力するプログラムを書きなさい。
 * 数式は整数と +, -, *, / の四則演算子のみを含むものとします。
 * 括弧や小数点、べき乗などは考慮しません。
 * 引数が1つでない場合、または無効な数式の場合は、"Error"と出力してください。
 *
 * 例：
 * $> ./calculator "5 + 3 * 2"
 * 11
 * $> ./calculator "10 - 4 / 2"
 * 8
 * $> ./calculator "2 + 2 *"
 * Error
 * $> ./calculator "3.14 + 2"
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

int	ft_atoi(char **str)
{
	int	result;

	result = 0;
	while (**str >= '0' && **str <= '9')
	{
		result = result * 10 + (**str - '0');
		(*str)++;
	}
	return (result);
}

int	eval_expr(char *str)
{
	int		result;
	int		num;
	char	op;

	result = ft_atoi(&str);
	while (*str)
	{
		while (*str == ' ')
			str++;
		op = *str;
		str++;
		while (*str == ' ')
			str++;
		num = ft_atoi(&str);
		if (op == '+')
			result += num;
		else if (op == '-')
			result -= num;
		else if (op == '*')
			result *= num;
		else if (op == '/')
		{
			if (num == 0)
				return (0);
			result /= num;
		}
		else
			return (0);
	}
	return (result);
}

int	main(int argc, char **argv)
{
	int	result;

	if (argc != 2)
	{
		ft_putstr("Error\n");
		return (1);
	}
	result = eval_expr(argv[1]);
	ft_putnbr(result);
	ft_putchar('\n');
	return (0);
}
