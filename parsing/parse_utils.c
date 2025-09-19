#include "minishell.h"

void	free_split(char **arr)
{
	size_t	i;

	i = 0;
	if (!arr)
		return ;
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
