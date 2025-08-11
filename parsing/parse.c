#include "minishell.h"

static void	free_split(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

static int	create_splitter_arr(char ***splitter_arr)
{
	*splitter_arr = malloc(sizeof(char **) * 13);
	if (!*splitter_arr)
		return (perror("malloc error: split_line"), 1);
	(*splitter_arr)[0] = ft_strdup("\'");
	(*splitter_arr)[1] = ft_strdup("\"");
	(*splitter_arr)[2] = ft_strdup("||");
	(*splitter_arr)[3] = ft_strdup("|");
	(*splitter_arr)[4] = ft_strdup("&&");
	(*splitter_arr)[5] = ft_strdup(">>");
	(*splitter_arr)[6] = ft_strdup(">");
	(*splitter_arr)[7] = ft_strdup("<<");
	(*splitter_arr)[8] = ft_strdup("<");
	(*splitter_arr)[9] = ft_strdup("(");
	(*splitter_arr)[10] = ft_strdup(")");
	(*splitter_arr)[11] = ft_strdup("{");
	(*splitter_arr)[12] = NULL;
	// (*splitter_arr)[12] = ft_strdup("}");
	// (*splitter_arr)[13] = ft_strdup("$");
	return (0);
}

static int	is_splitter(char *cur_char, char **splitter)
{
	size_t	i;

	i = 0;
	while (splitter[i])
	{
		if (ft_strncmp(cur_char, splitter[i], ft_strlen(splitter[i])) == 0)
			return (i);
		i++;
	}
	return (-1);
}

static size_t	len_till_splitter(char *cur_char, char **splitter)
{
	size_t	len;

	len = 0;
	if (!cur_char)
		return (0);
	// ft_printf("%s\n", cur_char);
	while (cur_char[len] && is_splitter(&cur_char[len], splitter) == -1)
		len++;
	return (len);
}

int	resize_res(char ***res)
{
	char	**new_res;
	char	**tmp;
	size_t	new_size;

	new_size = 0;
	while ((*res)[new_size++])
		;
	new_res = ft_calloc(sizeof(char *) * (new_size + 1), 1);
	if (!new_res)
		return (free_split(*res), perror("malloc: split_line"), 1);
	new_size = 0;
	while ((*res)[new_size])
	{
		new_res[new_size] = (*res)[new_size];
		new_size++;
	}
	new_res[new_size + 1] = NULL;
	tmp = *res;
	*res = new_res;
	free(tmp);
	return (0);
}

int	add_substr(char *line_start, size_t len, char **res)
{
	char	*sub_str;
	size_t	i;

	if (len == 0)
		return (1);
	sub_str = malloc(sizeof(char) * (len + 1));
	if (!sub_str)
		return (perror("malloc: split_line"), 1);
	ft_strlcpy(sub_str, line_start, len + 1);
	i = 0;
	while (res[i])
		i++;
	res[i] = sub_str;
	return (0);
}

size_t	add_operator(char *line_start, char **splitter, char **res)
{
	char	*sub_str;
	int		op_index;
	int		op_len;
	size_t	i;

	if (!line_start || !*line_start)
		return (0);
	// printf("line is %s\n", line_start);
	op_index = is_splitter(line_start, splitter);
	// printf("op_index is %d\n", op_index);
	op_len = ft_strlen(splitter[op_index]);
	sub_str = malloc(sizeof(char) * (op_len + 1));
	if (!sub_str)
		return (perror("malloc: split_line"), 0);
	ft_strlcpy(sub_str, line_start, op_len + 1);
	i = 0;
	while (res[i])
		i++;
	res[i] = sub_str;
	return (op_len);
}

void	print_line_arr(char **line_arr)
{
	size_t	i;

	i = 0;
	while (line_arr[i])
		ft_printf("\"%s\"\n", line_arr[i++]);
}

// DON'T STORE " " (strings with spaces) in res
// DON't FORGET FUNCHECK
static char	**split_line(char *line, char **splitter)
{
	char	**res;
	size_t	i;
	size_t	sub_len;

	i = 0;
	res = malloc(sizeof(char *));
	if (!res)
		return (perror("malloc: split_line"), NULL);
	res[0] = NULL;
	while (line[i])
	{
		if (resize_res(&res))
			return (NULL);
		sub_len = len_till_splitter(&line[i], splitter);
		// printf("for char %c\nsub_len is %zu\n", line[i], sub_len);
		if (sub_len)
		{
			add_substr(&line[i], sub_len, res);
			i += ((sub_len == 0) + sub_len); // if 0 increment 1 else increment sub_len
		}
		if (resize_res(&res))
			return (NULL);
		i += add_operator(&line[i], splitter, res);
	}
	return (res);
}

t_btree	*create_cmds_tree(char *line)
{
	// t_btree	*cmds_tree;
	char	**line_arr;
	char	**splitter;

	if (create_splitter_arr(&splitter))
		return (perror("malloc: split_line"), NULL);
	line_arr = split_line(line, splitter);
	if (!line_arr)
		return (free(splitter), NULL);
	print_line_arr(line_arr);
	free_split(line_arr);
	free_split(splitter);
	return (NULL);
	// return (cmds_tree);
}
