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
		write(1, &line[fragment.start], len);
		write(1, "\n", 1);
		i++;
	}
}

void	free_str(void *ptr)
{
	free(ptr);
}

void	parse(t_list *tokens, char *line, char **operators)
{
	;
}

t_btree	*create_cmds_tree(char *line, char **operators)
{
	// t_btree	*cmds_tree;
	t_list		*tokens;

	tokens = tokenize(line, operators);
	if (!tokens)
		return (perror("split_line failed"), NULL);
	ft_lstiter(tokens, print_fragments, line);
	// parse(tokens, line, operators);
	// ft_lstnodeiter(tokens, trim_spaces);
	// cmds_tree = create_tree(tokens);
	// print_line_arr(tokens);
	ft_lstclear(&tokens, free_str);
	return (NULL);
	// return (cmds_tree);
}
