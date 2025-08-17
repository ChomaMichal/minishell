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
		return (perror("malloc: add_substr"), 1);
	ft_strlcpy(sub_str, line_start, len + 1);
	node = ft_lstnew(sub_str);
	if (!node)
		return (free(sub_str), perror("malloc: add_substr"), 1);
	ft_lstadd_back(head, node);
	return (0);
}

int	add_operator(t_list **head, char *line_start, char **splitter, int op_index)
{
	char	*sub_str;
	t_list	*node;
	size_t	len;

	len = ft_strlen(splitter[op_index]);
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

static t_list	*split_line_linked_list(char *line, char **splitter)
{
	t_list	*head;
	size_t	i;
	size_t	substr_len;
	int		op_index;

	i = 0;
	head = NULL;
	while (line[i])
	{
		substr_len = 0;
		op_index = 0;
		set_len_and_op(&line[i], splitter, &substr_len, &op_index);
		if (substr_len)
			if (add_command(&head, &line[i], substr_len))
				return (NULL);
		i += ((substr_len == 0) + substr_len - (op_index > -1));
		if (op_index > -1)
			if (add_operator(&head, &line[i], splitter, op_index))
				return (NULL);
		if (op_index == -1)
			i += 1;
		else
			i += ft_strlen(splitter[op_index]);
	}
	return (head);
}

void	print_strings(void *ptr)
{
	char *str;

	str = (char *)ptr;
	printf("%s\n", str);
}

void	free_str(void *ptr)
{
	free(ptr);
}

t_btree	*create_cmds_tree(char *line)
{
	// t_btree	*cmds_tree;
	t_list	*line_list;
	char	**splitter;

	if (create_splitter_arr(&splitter))
		return (perror("malloc: split_line"), NULL);
	line_list = split_line_linked_list(line, splitter);
	if (!line_list)
		return (free(splitter), perror("split_line"), NULL);
	ft_lstiter(line_list, print_strings);
	// cmds_tree = create_tree(line_list);
	// print_line_arr(line_list);
	ft_lstclear(&line_list, free_str);
	free_split(splitter);
	return (NULL);
	// return (cmds_tree);
}
