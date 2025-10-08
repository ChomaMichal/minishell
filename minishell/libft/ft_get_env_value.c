#include "libft.h"

char	*ft_get_env_value(char **arr, char *key)
{
	size_t	i;
	char	*tmp;

	tmp = ft_strjoin(key, "=");
	if (tmp == NULL)
		return (NULL);
	i = 0;
	while(arr[i])
	{
		if (ft_strnstr(arr[i], tmp, ft_strlen(tmp)))
			return (free(tmp), ft_substr(arr[i],
				(size_t)(ft_strchr(arr[i], '=') - arr[i]) + 1, ft_strlen(arr[i])));
		i++;
	}
	return (free(tmp), ft_strdup(""));
}
