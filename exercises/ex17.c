/* class01/ex17.c
 * 課題名：atoi_morse_code
 * 使用可能な関数：write
 * ------------------------------------------*
 * コマンドライン引数として英数字の文字列を受け取り、それをモールス信号に変換して出力するプログラムを書きなさい。
 * モールス信号では、文字間は1つのスペース、単語間は3つのスペースで区切ります。
 * 大文字と小文字は区別しません。
 * 引数が1つでない場合、または無効な文字が含まれる場合は、"Error"と出力してください。
 *
 * 例：
 * $> ./morse_code "SOS"
 * ... --- ...
 * $> ./morse_code "HELLO WORLD"
 * .... . .-.. .-.. ---   .-- --- .-. .-.. -..
 * $> ./morse_code "H3llo"
 * .... ...-- .-.. .-.. ---
 * $> ./morse_code "Invalid@"
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

char	*get_morse(char c)
{
	char	*morse[] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....",
			"..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-",
			".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..",
			"-----", ".----", "..---", "...--", "....-", ".....", "-....",
			"--...", "---..", "----."};

	if (c >= 'A' && c <= 'Z')
		return (morse[c - 'A']);
	if (c >= 'a' && c <= 'z')
		return (morse[c - 'a']);
	if (c >= '0' && c <= '9')
		return (morse[c - '0' + 26]);
	return (NULL);
}

int	is_valid_char(char c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0'
			&& c <= '9') || c == ' ');
}

void	print_morse(char *str)
{
	char	*morse;
	int		first_word;

	first_word = 1;
	while (*str)
	{
		if (*str == ' ')
		{
			if (!first_word)
				ft_putstr("  ");
			str++;
			continue ;
		}
		if (!first_word)
			ft_putchar(' ');
		morse = get_morse(*str);
		ft_putstr(morse);
		first_word = 0;
		str++;
	}
	ft_putchar('\n');
}

int	main(int argc, char **argv)
{
	char	*str;

	if (argc != 2)
	{
		ft_putstr("Error\n");
		return (1);
	}
	str = argv[1];
	while (*str)
	{
		if (!is_valid_char(*str))
		{
			ft_putstr("Error\n");
			return (1);
		}
		str++;
	}
	print_morse(argv[1]);
	return (0);
}
