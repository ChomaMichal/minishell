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

int	btoindex(int options)
{
	int	i;

	i = 0;
	while (!((options >> i) & 1))
		i++;
	return (i);
}

int	parse(t_list *tokens, char *line, char **operators)
{
	if (validate_tokens(tokens, operators))
		return (1);
	return (0);
}

void	free_token(void *ptr)
{
	free(((t_token *)ptr)->fragments);
	free(((t_token *)ptr)->str);
	free(ptr);
}
t_btree	*create_cmds_tree(char *line, char **operators)
{
	// t_btree	*cmds_tree;
	t_list		*tokens;
	t_print_d	data;

	data.line = line;
	data.operators = operators;
	tokens = tokenize(line, operators);
	if (!tokens)
		return (/* perror("minishell: tokenize() failed"),  */NULL);
	if (parse(tokens, line, operators))
		return (/* perror("minishell: parse() failed"),  */ft_lstclear(&tokens, free_token), NULL);
	ft_lstiter(tokens, print_tokens, &data); // REMEMBER, THIS FREES THE FRAGMENTS. COMMENT IT IF YOU NEED THEM
	// cmds_tree = create_tree(tokens);
	ft_lstclear(&tokens, free_token);
	return (NULL);
	// return (cmds_tree);
}
