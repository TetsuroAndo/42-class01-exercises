/* class01/ex19.c
 * 課題名：atoi_rpn_calculator
 * 使用可能な関数：write, atoi, malloc, free
 * ------------------------------------------*
 * コマンドライン引数として逆ポーランド記法（RPN）の数式を受け取り、その結果を計算して出力するプログラムを書きなさい。
 * 演算子は +, -, *, / の四則演算のみを扱います。
 * 各要素（数値や演算子）はスペースで区切られているものとします。
 * スタックを使用して計算を行ってください。
 * 引数が1つでない場合、または無効な式の場合は、"Error"と出力してください。
 *
 * 例：
 * $> ./rpn_calculator "3 4 +"
 * 7
 * $> ./rpn_calculator "5 2 3 + *"
 * 25
 * $> ./rpn_calculator "3 4 + -"
 * Error
 * $> ./rpn_calculator "3 4 ++ 5"
 * Error
 */

#include <stdlib.h>
#include <unistd.h>

#define STACK_SIZE 1000

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
	if (n < 0)
	{
		ft_putchar('-');
		n = -n;
	}
	if (n >= 10)
		ft_putnbr(n / 10);
	ft_putchar(n % 10 + '0');
}

int	is_operator(char c)
{
	return (c == '+' || c == '-' || c == '*' || c == '/');
}

int	calculate(int a, int b, char op)
{
	if (op == '+')
		return (a + b);
	if (op == '-')
		return (a - b);
	if (op == '*')
		return (a * b);
	if (op == '/' && b != 0)
		return (a / b);
	return (0);
}

int	rpn_calculator(char *expr)
{
	int	stack[STACK_SIZE];
	int	top;

	top = -1;
	int a, b;
	while (*expr)
	{
		if (*expr == ' ')
		{
			expr++;
			continue ;
		}
		if (*expr >= '0' && *expr <= '9')
		{
			stack[++top] = atoi(expr);
			while (*expr >= '0' && *expr <= '9')
				expr++;
		}
		else if (is_operator(*expr))
		{
			if (top < 1)
				return (0);
			b = stack[top--];
			a = stack[top--];
			stack[++top] = calculate(a, b, *expr);
			expr++;
		}
		else
			return (0);
	}
	return (top == 0 ? stack[top] : 0);
}

int	main(int argc, char **argv)
{
	int	result;

	if (argc != 2)
	{
		ft_putstr("Error\n");
		return (1);
	}
	result = rpn_calculator(argv[1]);
	if (result == 0 && argv[1][0] != '0')
	{
		ft_putstr("Error\n");
		return (1);
	}
	ft_putnbr(result);
	ft_putchar('\n');
	return (0);
}
