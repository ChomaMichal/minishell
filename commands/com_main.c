
#include "commands.h"
#include "../libft/libft.h"
#include "../minishell.h"

int main(int argc, char **argv, char **envp)
{
	// char	*str = ft_strdup("PATH");
	char	*str2 = ft_strdup("PATH=hehe");
	t_data	data[1];


	// ft_pwd();
	// ft_cd("/tmp");
	// ft_pwd();
	data->env = ft_coppyarrstr(envp);
	// free(env[1]);
	ft_export(data, str2);
	ft_env(data);
	free_arr((void ***)&data->env);
}
