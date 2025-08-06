#include "libft.h"
char **ft_append_arr_str(char ***arr, char *str)
{
	size_t	i;
	char	**new;
	
	i = 0;
	while ((*arr)[i])
		i++;
	new = ft_calloc(i + 2, sizeof(char*));
	if (new == NULL)
		return (NULL);
	i = 0;
	while ((*arr)[i])
	{
		new[i] = (*arr)[i];
		i ++;
	}
	new[i] = str;
	new[i + 1] = NULL;
	free(*arr);
	*arr = new;
	return (new);
}
