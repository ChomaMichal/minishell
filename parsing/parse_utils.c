#include "minishell.h"

int	create_splitter_arr(char ***splitter_arr)
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
	(*splitter_arr)[11] = NULL;
	// (*splitter_arr)[11] = ft_strdup("{");
	// (*splitter_arr)[12] = ft_strdup("}");
	// (*splitter_arr)[13] = ft_strdup("$");
	return (0);
}

void	free_split(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

int	is_splitter(char *line_start, char **splitter)
{
	size_t	i;

	i = 0;
	while (splitter[i])
	{
		if (ft_strncmp(line_start, splitter[i], ft_strlen(splitter[i])) == 0)
			return (i);
		i++;
	}
	return (-1);
}

void	set_len_and_op(char *line_start, char **splitter,
	size_t *cmd_len, int *op_index)
{
	size_t	len;

	len = 0;
	*op_index = is_splitter(&line_start[len], splitter);
	while (line_start[len] && *op_index == -1)
	{
		len += 1;
		*op_index = is_splitter(&line_start[len], splitter);
	}
	*cmd_len = len;
}

void	print_line_arr(char **line_arr)
{
	size_t	i;

	i = 0;
	while (line_arr[i])
		ft_printf("\"%s\"\n", line_arr[i++]);
}
