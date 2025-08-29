#include "minishell.h"
// x &= ~(1 << 2)
// 000101
// 111011
//=000001

// DON'T STORE " " (strings with spaces) in res
// DON't FORGET FUNCHECK

int	add_command(t_list **head, char *line_start, size_t len)
{
	char	*sub_str;
	t_list	*node;

	if (len == 0)
		return (1);
	sub_str = malloc(sizeof(char) * (len + 1));
	if (!sub_str)
		return (perror("malloc: add_command"), 1);
	ft_strlcpy(sub_str, line_start, len + 1);
	node = ft_lstnew(sub_str);
	if (!node)
		return (free(sub_str), perror("malloc: add_command"), 1);
	ft_lstadd_back(head, node);
	return (0);
}

size_t	len_to_delimiter(char *line, char **operators)
{
	size_t	len;
	size_t	op;

	len = 0;
	while (line[len])
	{
		op = 0;
		while (operators[op])
		{
			if (!ft_strncmp(&line[len], operators[op], ft_strlen(operators[op])))
				return (len);
			op++;
		}
		if (line[len] == ' '|| line[len] == '	')
			return (len);
		len++;
	}
	return (len);
}

int	ft_isblank(char c)
{
	return (c == ' ' || c == '	');
}

int	handle_quotes(t_list **head, char *line, char quote, size_t *i)
{
	size_t	j;

	j = 0;
	while (line[j])
	{
		j++;
		if (line[j] == 0)
			return (perror("unclosed quote"), 1);
		if (line[j] == quote)
			break ;
	}
	if (add_command(head, &line[0], j + 1))
		return (perror("add_command-handle_quotes failed"), 1);
	*i += (j + 1);
	return (0);
}

int	add_operator_token(t_list **head, int op_index)
{
	t_token	*token;
	t_list	*node;

	token = malloc(sizeof(t_token));
	if (!token)
		return (perror("malloc: add_operator_token"), 1);
	token->fragment_count = 0;
	token->fragments = NULL;
	token->options = 0;
	token->str = NULL;
	token->options = token->options | (1 << op_index);
	node = ft_lstnew(token);
	if (!node)
		return (free(token), perror("malloc: add_operator_token"), 1);
	ft_lstadd_back(head, node);
	return (0);
}

int	handle_operator(t_list **head, char **operators, int op_index, size_t *i)
{
	int	op_index;

	if (add_operator_token(head, op_index))
		return (1);
	*i += ft_strlen(operators[op_index]);
	return (0);
}

int	handle_command(t_list **head, char *line, char **operators, size_t *i)
{
	size_t	word_len;

	// if (line[*i] == '\'' || line[*i] == '\"')
	// {
	// 	if (handle_quotes(head, &line[*i], line[*i], i))
	// 		return (perror("handle_quotes failed"), 1);
	// }
	// else
	// {
	word_len = len_to_delimiter(&line[*i], operators);
	if (add_command(head, &line[*i], word_len))
		return (perror("add_command failed"), 1);
	*i += word_len;
	// }
	return (0);
}

static void	skip_blank(char *line, size_t *i)
{
	while (ft_isblank(line[*i]))
		*i += 1;
}

static t_list	*tokenize(char *line, char **operators)
{
	t_list	*head;
	size_t	i;
	int		op_res;
	int		op_index;

	i = 0;
	head = NULL;
	while (line[i])
	{
		skip_blank(line, &i);
		op_index = is_operator(&line[i], operators);
		if (op_index > -1)
		{
			if (handle_operator(&head, operators, op_index, &i));
				return (NULL);
		}
		else if (handle_command(&head, line, operators, &i))
			return (NULL);
		skip_blank(line, &i);
	}
	return (head);
}

void	print_string(void *ptr)
{
	char	*str;

	str = (char *)ptr;
	printf("%s$\n", str);
}

// void	trim_spaces(void *ptr)
// {
// 	char	*str;
// 	size_t	i;
// 	size_t	len;

// 	i = 0;
// 	str = (char *)ptr;
// 	len = ft_strlen(str);
// 	while (ft_isspace(str[i]))
// 		i++;
// }

void	free_str(void *ptr)
{
	free(ptr);
}

t_btree	*create_cmds_tree(char *line, char **operators)
{
	// t_btree	*cmds_tree;
	t_list	*line_list;
	char	**operators;

	line_list = tokenize(line, operators);
	if (!line_list)
		return (ft_lstclear(&line_list, free_str), perror("split_line failed"), NULL);
	ft_lstiter(line_list, print_string);
	// ft_lstnodeiter(line_list, trim_spaces);
	// cmds_tree = create_tree(line_list);
	// print_line_arr(line_list);
	ft_lstclear(&line_list, free_str);
	return (NULL);
	// return (cmds_tree);
}
