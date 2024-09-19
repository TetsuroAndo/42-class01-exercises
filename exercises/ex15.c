/* class01/ex15.c
 * 課題名：atoi_date_calculator
 * 使用可能な関数：write
 * ------------------------------------------*
 * コマンドライン引数として日付（YYYY-MM-DD形式）と日数を受け取り、
 * 指定された日数後の日付を計算して出力するプログラムを書きなさい。
 * うるう年も考慮してください。
 * 引数が2つでない場合、または無効な入力の場合は、"Error"と出力してください。
 *
 * 例：
 * $> ./date_calculator 2023-03-15 10
 * 2023-03-25
 * $> ./date_calculator 2024-02-28 2
 * 2024-03-01
 * $> ./date_calculator 2023-13-01 5
 * Error
 * $> ./date_calculator 2023-01-01
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

int	is_leap_year(int year)
{
	return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}

int	days_in_month(int year, int month)
{
	int	days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	if (month == 2 && is_leap_year(year))
		return (29);
	return (days[month - 1]);
}

void	print_date(int year, int month, int day)
{
	ft_putchar(year / 1000 + '0');
	ft_putchar((year / 100) % 10 + '0');
	ft_putchar((year / 10) % 10 + '0');
	ft_putchar(year % 10 + '0');
	ft_putchar('-');
	ft_putchar(month / 10 + '0');
	ft_putchar(month % 10 + '0');
	ft_putchar('-');
	ft_putchar(day / 10 + '0');
	ft_putchar(day % 10 + '0');
	ft_putchar('\n');
}

int	is_valid_date(int year, int month, int day)
{
	if (year < 1 || month < 1 || month > 12 || day < 1)
		return (0);
	return (day <= days_in_month(year, month));
}

void	calculate_date(int year, int month, int day, int days)
{
	int	days_in_current_month;

	while (days > 0)
	{
		days_in_current_month = days_in_month(year, month);
		if (day + days <= days_in_current_month)
		{
			day += days;
			break ;
		}
		days -= (days_in_current_month - day + 1);
		month++;
		day = 1;
		if (month > 12)
		{
			year++;
			month = 1;
		}
	}
	print_date(year, month, day);
}

int	main(int argc, char **argv)
{
	int		year;
	int		month;
	int		day;
	int		days;
	char	*date;

	if (argc != 3)
	{
		ft_putstr("Error\n");
		return (1);
	}
	date = argv[1];
	year = ft_atoi(&date);
	if (*date++ != '-')
		return (1);
	month = ft_atoi(&date);
	if (*date++ != '-')
		return (1);
	day = ft_atoi(&date);
	if (!is_valid_date(year, month, day))
	{
		ft_putstr("Error\n");
		return (1);
	}
	days = ft_atoi(&argv[2]);
	if (days < 0)
	{
		ft_putstr("Error\n");
		return (1);
	}
	calculate_date(year, month, day, days);
	return (0);
}
