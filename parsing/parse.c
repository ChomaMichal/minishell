#include "minishell.h"
// x &= ~(1 << 2)
// 000101
// 111011
//=000001

// DON't FORGET FUNCHECK

// #include <fcntl.h>
// void	signal_handler(int sig)
// {
// 	int fd = open("test", O_RDWR);
// 	write(fd, "sig recieved\n", 13);
// 	exit(1);
// 	// printf("sig recieved\n");
// }

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
	printf("\n\n");
	rec_print_bits(x, i);
}

int token_count = 0;
void	print_fragments(void *ptr, char *line)
{
	t_fragment	fragment;
	t_token		*token;
	size_t		i;
	size_t		len;

	i = 0;
	token = (t_token *)ptr;
	char *type;
	if (token->options & WORD)
		type = "WORD";
	else if (token->options & OPERATOR)
		type = "OPERATOR";
	printf("token (%d) type: (%s)\n", token_count++, type);
	while (i < token->fragment_count)
	{
		fragment = (token->fragments)[i];
		len = fragment.end - fragment.start + 1;
		write(1, "\"", 1);
		write(1, &line[fragment.start], len);
		write(1, "\"", 1);
		write(1, "\n", 1);
		i++;
	}
	print_bits(token->options, 0);
	printf("\n");
	free(token->fragments);
}

int	btoindex(int options)
{
	int	i;

	i = 0;
	while (!((options >> i) & 1))
		i++;
	return (i);
}

int	validate_parentheses(t_list *tokens) // THIS DOESN'T WORK, NEED TO MAKE A STACK AND POP WHEN 2 PARENS MATCH
{
	t_list	*cur;
	long	count;

	count = 0;
	cur = tokens;
	while (cur)
	{
		if (cur->token->options & OPEN_PARENTHESIS)
			count++;
		else if (cur->token->options & CLOSE_PARENTHESIS)
			count--;
		cur = cur->next;
	}
	if (count)
		ft_printf(2, "minishell: syntax error: unmatched parentheses\n");
	return (count);
}

int	validate_tokens(t_list *tokens, char **operators)
{
	t_list	*cur;
	t_list	*prev;
	int		options;

	cur = tokens;
	options = cur->token->options;
	if ((options & OR) || (options & AND) || (options & PIPE))
	{
		ft_printf(2,"minishell: syntax error near unexpected token `%s'\n",
			operators[btoindex(options)]);
		return (1);
	}
	if ((options & REDIR_OP) && cur->next == NULL)
	{
		ft_printf(2,
			"minishell: syntax error near unexpected token `newline'\n");
		return (1);
	}
	if (validate_parentheses(tokens))
		return (1);
	// prev = cur;
	// cur = cur->next;
	// while (cur)
	// {
		
	// }
}

int	parse(t_list *tokens, char *line, char **operators)
{
	size_t	i;
	t_list	*cur;
	int		options;

	cur = tokens;
	options = cur->token->options;
	if (validate_tokens(tokens, operators))
		return (1);
	// while (cur)
	// {
			
	// 	cur = cur->next;
	// }
}

void	free_token(void *ptr)
{
	free(((t_token *)ptr)->fragments);
	free(ptr);
}

t_btree	*create_cmds_tree(char *line, char **operators)
{
	// t_btree	*cmds_tree;
	t_list	*tokens;

	tokens = tokenize(line, operators);
	if (!tokens)
		return (perror("tokenize() failed"), NULL);
	// ft_lstiter(tokens, print_fragments, line); // REMEMBER, THIS FREES THE FRAGMENTS. COMMENT IT IF YOU NEED THEM
	if (parse(tokens, line, operators))
		return (ft_lstclear(&tokens, free_token), NULL);
	// ft_lstnodeiter(tokens, trim_spaces);
	// cmds_tree = create_tree(tokens);
	// print_line_arr(tokens);
	ft_lstclear(&tokens, free_token);
	return (NULL);
	// return (cmds_tree);
}
