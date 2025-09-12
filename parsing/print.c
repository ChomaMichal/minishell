#include "minishell.h"

void	rec_print_bits(int x, int i)
{
	if (i < 31)
		rec_print_bits(x, i + 1);
	if ((x >> i) & 1)
		write(1, "1", 1);
	else
		write(1, "0", 1);
	if (!(i % 8) && i != 0)
		write(1, ",", 1);
	if (!(i % 4) && i != 0)
		write(1, " ", 1);
	if (i == 32)
		write(1, "\n", 1);
}

void	print_bits(int x, int i)
{
	printf("options: ");
	fflush(NULL);
	printf("\n");
	rec_print_bits(x, i);
}

void	print_fragment_type(t_fragment *fragment)
{
	if (fragment->type == SINGLE)
		write(1, "	SINGLE QUOTE", 14);
	else if (fragment->type == DOUBLE)
		write(1, "	DOUBLE QUOTE", 14);
	else if (fragment->type == UNQUOTED)
		write(1, "	UNQUOTED", 10);
}

int	token_count = 0;
void	print_tokens(t_print_d *data)
{
	char		**operators;
	t_token		*token;
	char		*line;
	t_fragment	fragment;
	size_t		i;
	size_t		len;

	i = 0;
	operators = data->operators;
	token = data->token;
	line = data->line;
	if (token->options & WORD)
	{
		printf("token (%d) type: (WORD)\n", token_count++);
		if (token->fragment_count == 0)
			printf("[%s] EMPTY TOKEN\n", token->str);
		while (i < token->fragment_count)
		{
			fragment = (token->fragments)[i];
			len = fragment.end - fragment.start + 1;
			write(1, "[", 1);
			write(1, &line[fragment.start], len);
			write(1, "]", 1);
			if (len)
				print_fragment_type(&fragment);
			write(1, "\n", 1);
			i++;
		}
	}
	else if (token->options & OPERATOR)
	{
		printf("token (%d) type: (OPERATOR)\n", token_count++);		
		printf("[%s]\n", operators[btoindex(token->options)]);
	}
	print_bits(token->options, 0);
	printf("\n\n");
	// free(token->fragments);
}
