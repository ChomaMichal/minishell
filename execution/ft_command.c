/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoma <your@mail.com>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 19:02:13 by mchoma            #+#    #+#             */
/*   Updated: 2025/10/10 15:35:44 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "executor.h"
#include "../commands/commands.h"
#include "../libft/libft.h"
char	*ft_strdup(const char *s);

//todo implement build ins
//if it is not found exit with 127 
//if found and not executable exit with 126

void	ft_execve(t_btree *tree, t_data *data)
{
	char	*path;

	path = get_path(data->env, tree->cmd_argv[0]);
	if (path == NULL)
	{
		data->rt = 1;
		free_split(tree->cmd_argv);
		free(tree);
		return ;
	}
	execve(path, tree->cmd_argv, data->env);
	free(tree->cmd_argv);
	free(tree);
	free(path);
	//ft_exit();
}

void	echo_wrap(t_btree *tree, t_data *data)
{
	size_t	i;
	int		flag;
	char	*str;

	flag = 0;
	i = 1;
	if (tree->cmd_argv[i] && ft_strncmp(tree->cmd_argv[1], "-n", 3)
		&& ++flag)
		i++;
	while (tree->cmd_argv[i])
	{
		str = ft_strjoinf1(str, tree->cmd_argv[i]);
		if (str == NULL)
			return ;//error handle
		i ++;
	}
	ft_echo(data, str, flag);
	
}

void	cd_wrap(t_btree *tree, t_data *data)
{
	if (!tree->cmd_argv[1])
		ft_cd(data, ft_strdup(""));
	else
		ft_cd(data, tree->cmd_argv[1]);
}

void	cd_export(t_btree *tree, t_data *data)
{
	if (!tree->cmd_argv[1])
		ft_export(data, ft_strdup(""));
	else
		ft_export(data, tree->cmd_argv[1]);
}

void	cd_unset(t_btree *tree, t_data *data)
{
	if (!tree->cmd_argv[1])
		ft_unset(data, ft_strdup(""));
	else
		ft_unset(data, tree->cmd_argv[1]);
}

void	env_wrap(t_btree *tree, t_data *data)
{
	ft_env(data);
}

void	export_wrap(t_btree *tree, t_data *data)
{

}

void	unset_wrap(t_btree *tree, t_data *data)
{

}


void	pwd_wrap(t_btree *tree, t_data *data)
{

}


void	env_pwd(t_btree *tree, t_data *data)
{
	ft_pwd(data);
}



int	is_buildin(t_btree *tree, t_data *data)
{
	if (tree->cmd_argv[0] == NULL)
		ft_putstrerr("null passed to cmd_argv\n");

	if (ft_strncmp(tree->cmd_argv[0], "cd", 3))
		return (cd_wrap(tree, data), 1);
	if (ft_strncmp(tree->cmd_argv[0], "pwd", 4))
		return (pwd_wrap(tree, data), 1);
	if (ft_strncmp(tree->cmd_argv[0], "echo", 5))
		return (echo_wrap(tree, data), 1);
	if (ft_strncmp(tree->cmd_argv[0], "env", 4))
		return (env_wrap(tree, data), 1);
	if (ft_strncmp(tree->cmd_argv[0], "unset", 6))
		return (unset_wrap(tree, data), 1);
	if (ft_strncmp(tree->cmd_argv[0], "export", 7))
		return (export_wrap(tree, data), 1);
	if (ft_strncmp(tree->cmd_argv[0], "exit", 5))
		return (ft_exit(0));
		
		

}


void	ft_command(t_btree *tree, t_data *data)
{
	int		pid;

	
	pid = fork();
	if (pid == 0)
		ft_execve(tree, data);
	if (add_last_id(&data->pids, pid))
		data->rt = 1;
	free_split(tree->cmd_argv);
	free(tree);
}
