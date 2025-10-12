/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoma <your@mail.com>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 19:02:13 by mchoma            #+#    #+#             */
/*   Updated: 2025/10/12 17:22:19 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "executor.h"
#include "../commands/commands.h"
#include "../libft/libft.h"
#include <signal.h>

//todo implement build ins
//if it is not found exit with 127 
//if found and not executable exit with 126

void	ft_execve(t_btree *tree, t_data *data)
{
	char	*path;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	path = get_path(data->env, tree->cmd_argv[0]);
	if (path == NULL)
	{
		data->rt = 1;
		free_split(tree->cmd_argv);
		free(tree);
		return ;
	}
	execve(path, tree->cmd_argv, data->env);
	free(path);
	ft_exit(data, NULL);
}

#include <stdio.h>

void	echo_wrap(t_btree *tree, t_data *data)
{
	size_t	i;
	int		flag;
	char	*str;

	flag = 0;
	i = 1;
	if (tree->cmd_argv[i] && ft_strncmp(tree->cmd_argv[1], "-n", 3) == 0
		&& ++flag)
		i++;
	str = ft_strdup(tree->cmd_argv[i]);
	if (str == NULL)
		return ; //error handle
	i ++;
	while (tree->cmd_argv[i])
	{
		str = ft_strjoinf1(str, " ");
		if (str == NULL)
			return ;//error handle
		str = ft_strjoinf1(str, tree->cmd_argv[i]);
		if (str == NULL)
			return ;//error handle

		i ++;
	}
	ft_echo(data, str, flag);
	free(str);
	add_last_id(&data->pids, -1);
}

void	cd_wrap(t_btree *tree, t_data *data)
{
	if (!tree->cmd_argv[1])
		ft_cd(data, ft_strdup(""));
	else
		ft_cd(data, tree->cmd_argv[1]);
	add_last_id(&data->pids, -1);
}

void	export_wrap(t_btree *tree, t_data *data)
{
	if (!tree->cmd_argv[1])
		ft_export(data, "");
	else
		ft_export(data, tree->cmd_argv[1]);
	add_last_id(&data->pids, -1);
}

void	unset_wrap(t_btree *tree, t_data *data)
{
	if (!tree->cmd_argv[1])
		ft_unset(data, ft_strdup(""));
	else
		ft_unset(data, tree->cmd_argv[1]);
	add_last_id(&data->pids, -1);
}

void	env_wrap(t_btree *tree, t_data *data)
{
	tree = NULL;
	ft_env(data);
	add_last_id(&data->pids, -1);
}

void	pwd_wrap(t_btree *tree, t_data *data)
{
	tree = NULL;
	ft_pwd(data);
	add_last_id(&data->pids, -1);
}

void	exit_wrap(t_btree *tree, t_data *data)
{
	ft_exit(data, tree->cmd_argv[0]);
	add_last_id(&data->pids, -1);
}



int	is_buildin(t_btree *tree, t_data *data)
{
	/*
	if (tree->cmd_argv[0] == NULL)
	{
		ft_putstrerr("null passed to cmd_argv\n");
		return 0;
	}
	*/
	if (ft_strncmp(tree->cmd_argv[0], "cd", 3) == 0)
		return (cd_wrap(tree, data), 1);
	if (ft_strncmp(tree->cmd_argv[0], "pwd", 4) == 0)
		return (pwd_wrap(tree, data), 1);
	if (ft_strncmp(tree->cmd_argv[0], "echo", 5) == 0)
		return (echo_wrap(tree, data), 1);
	if (ft_strncmp(tree->cmd_argv[0], "env", 4) == 0)
		return (env_wrap(tree, data), 1);
	if (ft_strncmp(tree->cmd_argv[0], "unset", 6) == 0)
		return (unset_wrap(tree, data), 1);
	if (ft_strncmp(tree->cmd_argv[0], "export", 7) == 0)
		return (export_wrap(tree, data), 1);
	if (ft_strncmp(tree->cmd_argv[0], "exit", 5) == 0)
		return (exit_wrap(tree, data), 1);
	return (0);
}


void	ft_command(t_btree *tree, t_data *data)
{
	int		pid;

	if (is_buildin(tree, data) == 1)
		return;
	pid = fork();
	if (pid == 0)
		ft_execve(tree, data);
	else if (add_last_id(&data->pids, pid))
		data->rt = 1;
	if (data->subshell == 1)
	{
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		exit(wait_and_get_exit_value(data->pids));
	}
}
