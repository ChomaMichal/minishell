#include "libft.h"

void	free_arr(void ***arr)
{
	size_t	i;

	i = 0;
	if (arr == NULL)
		return ;
	if (*arr == NULL)
		return ;
	while ((*arr)[i])
	{
		free((*arr)[i]);
		i ++;
	}
	free(*arr);
	*arr = NULL;
}
