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

// What if we have 2 bits of 2, and we want to check the 1 bit that is to the left?
// we read the one to the right first, which is an incorrect result.
// when calling it for token types, this function only works up to bit 8 (CLOSE_PAREN). Bigger is undefined.
//		||
//		||
//		\/
int	btoindex(int options)
{
	int	i;

	i = 0;
	while (!((options >> i) & 1))
		i++;
	return (i);
}

int	parse_tokens(t_list *tokens, char *line, char **operators)
{
	return (0);
}

void	delete_token(void *ptr)
{
	free(((t_token *)ptr)->fragments);
	free(((t_token *)ptr)->str);
	free(ptr);
}

void	free_tokens(t_list *tokens)
{
	ft_lstclear(&tokens, delete_token);
}

t_btree	*create_exec_tree(char *line, char **operators)
{
	t_btree		*cmds_tree;
	t_list		*tokens;
	t_print_d	data;

	data.line = line;
	data.operators = operators;
	tokens = tokenize(line, operators);
	if (!tokens)
		return (ft_printf(2, "minishell: tokenize() failed\n"), NULL);
	if (validate_tokens(tokens, operators))
		return (ft_printf(2, "minishell: validate_tokens() failed\n"), free_tokens(tokens), NULL);
	if (parse_tokens(tokens, line, operators))
		return (ft_printf(2, "minishell: parse() failed\n"), free_tokens(tokens), NULL);
	// ft_lstiter(tokens, print_tokens, &data);
	cmds_tree = create_tree(tokens);
	free_tokens(tokens);
	return (cmds_tree);
	// return (cmds_tree);
}
