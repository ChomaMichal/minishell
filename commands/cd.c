#include "../minishell.h"
#include "../libft/libft.h"

int	cd_path(t_data *data, char **path)
{
	char	*str;
	char	**arr;
	size_t	i;

	str = ft_get_env_value(data->env,"CDPATH");
	if (str == NULL)
		return (free(path), 0);
	arr = ft_split(str, ':');
	if (arr == NULL)
		return (free(str), 0);
	str = ft_strjoin("/", *path);
	while (arr[i])
	{
		if (ft_strnstr(arr[i] + ft_strlen(arr[i]) - ft_strlen(str), str, ft_strlen(str)))
		{
			free(*path);
			*path = str;
			return (1);
		}
		i++;
	}
	return (1);
}

int	ft_cd(t_data *data, char *path)
{
	char	*str;

	if (*path != '/')
	{
		if (cd_path(data, &path) == 0)
			return (free(path), 0);
	}
	if (*path == 0)
	{
		free(path);
		path = ft_get_env_value(data->env,"HOME");
		if (path == NULL)
			return (0);
	}
	if (chdir(path) == -1)
	{
		data->rt = 1;
		ft_putstr_fd("bash: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory", 2);
		return (free(path), 0);
	}
	data->rt = 0;
	return (free(path), 1);
}


