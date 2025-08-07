
#include "commands.h"
#include "../libft/libft.h"
#include "../minishell.h"

int main(int argc, char **argv, char **envp)
{
	char	*str = ft_strdup("");
	if (str == NULL)
		return (1);
	// char	*str2 = ft_strdup("PATH=hehe");
	t_data	data[1];
	data->env = ft_coppyarrstr(envp);
	if (data->env == NULL)
		return (free(str), 1);

	ft_pwd(data);
	ft_cd(data, str);
	ft_pwd(data);
	str  = ft_strdup("CDPATH=/tmp");
	if (str == NULL)
		return (free_arr((void ***)&data->env), 1);
	ft_export(data, str);
	str = ft_strdup("libft");
	if (str == NULL)
		return (free_arr((void ***)&data->env), 1);
	ft_cd(data, str);
	ft_pwd(data);
	str  = ft_strdup("ATH");
	if (str == NULL)
		return (free_arr((void ***)&data->env), 1);
	ft_unset(data, str);// ft_export(data, str2);
	// ft_env(data);
	printf("%i\n", data->rt);
	free_arr((void ***)&data->env);
}
