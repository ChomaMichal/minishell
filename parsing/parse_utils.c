#include "minishell.h"

int	create_operators(char ***arr)
{
	*arr = malloc(sizeof(char **) * 13);
	if (!*arr)
		return (1);
	(*arr)[0] = ft_strdup("\'");
	(*arr)[1] = ft_strdup("\"");
	(*arr)[2] = ft_strdup("||");
	(*arr)[3] = ft_strdup("|");
	(*arr)[4] = ft_strdup("&&");
	(*arr)[5] = ft_strdup(">>");
	(*arr)[6] = ft_strdup(">");
	(*arr)[7] = ft_strdup("<<");
	(*arr)[8] = ft_strdup("<");
	(*arr)[9] = ft_strdup("(");
	(*arr)[10] = ft_strdup(")");
	(*arr)[11] = NULL;
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

int	is_operator(char *line_start, char **operators)
{
	size_t	i;

	i = 0;
	while (operators[i])
	{
		if (ft_strncmp(line_start, operators[i], ft_strlen(operators[i])) == 0)
			return (i);
		i++;
	}
	return (-1);
}

void	set_len_and_op(char *line_start, char **operators,
	size_t *substr_len, int *op_index)
{
	size_t	len;

	len = 0;
	*op_index = is_operator(&line_start[len], operators);
	while (line_start[len] && *op_index == -1)
	{
		len += 1;
		*op_index = is_operator(&line_start[len], operators);
	}
	*substr_len = len;
}

void	print_line_arr(char **line_arr)
{
	size_t	i;

	i = 0;
	while (line_arr[i])
		ft_printf("\"%s\"\n", line_arr[i++]);
}
