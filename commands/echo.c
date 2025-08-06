#include "commands.h"
#include "../minishell.h"

int	ft_echo(t_data *data, char *str, int flag)
{
	if (flag == 0 && printf("%s\n", str) == -1)
	{
		data->rt = 1;
		return (free(str) ,0);
	}
	if (flag == 1 && printf("%s", str) == -1)
	{
		data->rt = 1;
		return (free(str) ,0);
	}
	data->rt = 0;
	return (free(str), 1);
}
