#include "minishell.h"

// int	resize_res(char ***res)
// {
// 	char	**new_res;
// 	char	**tmp;
// 	size_t	new_size;

// 	new_size = 0;
// 	while ((*res)[new_size++])
// 		;
// 	new_res = ft_calloc(sizeof(char *) * (new_size + 1), 1);
// 	if (!new_res)
// 		return (free_split(*res), perror("malloc: split_line"), 1);
// 	new_size = 0;
// 	while ((*res)[new_size])
// 	{
// 		new_res[new_size] = (*res)[new_size];
// 		new_size++;
// 	}
// 	new_res[new_size + 1] = NULL;
// 	tmp = *res;
// 	*res = new_res;
// 	free(tmp);
// 	return (0);
// }

// x &= ~(1 << 2)
// 000101
// 111011
//=000001

// size_t	add_operator(char *line_start, char **splitter, char **res)
// {
// 	char	*sub_str;
// 	int		op_index;
// 	int		op_len;
// 	size_t	i;

// 	if (!line_start || !*line_start)
// 		return (0);
// 	// printf("line is %s\n", line_start);
// 	op_index = is_splitter(line_start, splitter);
// 	// printf("op_index is %d\n", op_index);
// 	op_len = ft_strlen(splitter[op_index]);
// 	sub_str = malloc(sizeof(char) * (op_len + 1));
// 	if (!sub_str)
// 		return (perror("malloc: split_line"), 0);
// 	ft_strlcpy(sub_str, line_start, op_len + 1);
// 	i = 0;
// 	while (res[i])
// 		i++;
// 	res[i] = sub_str;
// 	return (op_len);
// }

// DON'T STORE " " (strings with spaces) in res
// DON't FORGET FUNCHECK
// static char	**split_line_str_arr(char *line, char **splitter)
// {
// 	char	**res;
// 	size_t	i;
// 	size_t	sub_len;

// 	i = 0;
// 	res = malloc(sizeof(char *));
// 	if (!res)
// 		return (perror("malloc: split_line"), NULL);
// 	res[0] = NULL;
// 	while (line[i])
// 	{
// 		if (resize_res(&res))
// 			return (NULL);
// 		sub_len = command_len(&line[i], splitter);
// 		// printf("for char %c\nsub_len is %zu\n", line[i], sub_len);
// 		if (sub_len)
// 		{
// 			add_substr(&line[i], sub_len, res);
// 			i += ((sub_len == 0) + sub_len); // if 0 increment 1 else increment sub_len
// 		}
// 		if (resize_res(&res))
// 			return (NULL);
// 		i += add_operator(&line[i], splitter, res);
// 	}
// 	return (res);
// }

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

int	add_operator(t_list **head, char *line_start, char **operators, int op_index)
{
	char	*sub_str;
	t_list	*node;
	size_t	len;

	len = ft_strlen(operators[op_index]);
	sub_str = malloc(sizeof(char) * (len + 1));
	if (!sub_str)
		return (perror("malloc: add_operator"), 1);
	ft_strlcpy(sub_str, line_start, len + 1);
	node = ft_lstnew(sub_str);
	if (!node)
		return (free(sub_str), perror("malloc: add_operator"), 1);
	node->options |= (1 << op_index);
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
	while (line[j + 1])
	{
		if (line[j + 1] == quote)
			break ;
		else if (line[j + 1] == 0)
			return (perror("unclosed quote"), 1);
		j++;
	}
	if (add_command(head, &line[1], j))
		return (perror("add_command failed"), 1);
	*i += (j + 2);
	return (0);
}

int	handle_operator(t_list **head, char *line, char **operators, size_t *i)
{
	int	op_index;

	// printf("reading (%s) from line\n", &line[*i]);
	op_index = is_operator(&line[*i], operators);
	// printf("adding operator (%d)\n", op_index);
	if (op_index == -1)
		return (0);
	if (add_operator(head, &line[*i], operators, op_index))
		return (perror("add_operator failed"), 1);
	*i += ft_strlen(operators[op_index]);
	return (0);
}

int	handle_command(t_list **head, char *line, char **operators, size_t *i)
{
	size_t	word_len;

	if (line[*i] == '\'' || line[*i] == '\"')
	{
		if (handle_quotes(head, line, line[*i], i))
			return (perror("handle_quotes failed"), 1);
	}
	else
	{	
		word_len = len_to_delimiter(&line[*i], operators);
		if (add_command(head, &line[*i], word_len))
			return (perror("add_command failed"), 1);
		*i += word_len;
	}
	return (0);
}

static t_list	*tokenize(char *line, char **operators)
{
	t_list	*head;
	size_t	i;

	i = 0;
	head = NULL;
	while (line[i])
	{
		// printf("at (%s)\n", &line[i]);
		while (ft_isblank(line[i]))
			i++;
		if (handle_operator(&head, line, operators, &i))
			return (NULL);
		while (ft_isblank(line[i]))
			i++;
		if (handle_command(&head, line, operators, &i))
			return (NULL);
	}
	return (head);
}

void	print_string(void *ptr)
{
	char	*str;

	str = (char *)ptr;
	printf("%s\n", str);
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

t_btree	*create_cmds_tree(char *line)
{
	// t_btree	*cmds_tree;
	t_list	*line_list;
	char	**operators;

	if (create_operators(&operators))
		return (perror("create_operators failed"), NULL);
	line_list = tokenize(line, operators);
	if (!line_list)
		return (free(operators), perror("split_line failed"), NULL);
	ft_lstiter(line_list, print_string);
	// ft_lstnodeiter(line_list, trim_spaces);
	// cmds_tree = create_tree(line_list);
	// print_line_arr(line_list);
	ft_lstclear(&line_list, free_str);
	free_split(operators);
	return (NULL);
	// return (cmds_tree);
}
