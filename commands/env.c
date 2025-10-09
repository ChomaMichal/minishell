#include "commands.h"

int	ft_env(t_data *data)
{
	size_t	i;

	i = 0;
	if (data->env == NULL)
		return (set_rt(&data->rt, 0), 1);
	while(data->env[i] != NULL)
	{
		if (printf("%s\n", data->env[i]) == -1)
		{
			data->rt = 1;
			return  (set_rt(&data->rt, 1), 0);
		}
		i ++;
	}
	return (set_rt(&data->rt, 0), 1);
}
