/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 19:02:13 by mchoma            #+#    #+#             */
/*   Updated: 2025/10/13 19:54:39 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "../commands/commands.h"
#include "../libft/libft.h"
#include <signal.h>

//todo implement build ins
//if it is not found exit with 127 
//if found and not executable exit with 126

static int	redirection(t_btree *tree)
{
	int		in;
	int		out;

	if (tree->redir.in)
	{
		in = open(tree->redir.in, O_RDONLY);
		if (in > 0)
			return (ft_putstrerr("failed to open file in redirection\n"), -1);
		dup2(in, STDIN_FILENO);
		close(in);
	}
	if (tree->redir.out)
	{
		if (tree->redir.append)
			out = open(tree->redir.out, O_WRONLY | O_CREAT | O_APPEND, 0777);
		else
			out = open(tree->redir.out, O_WRONLY | O_CREAT, 0777);
		if (out == -1)
			return (ft_putstrerr("failed to open file in redirection\n"), -1);
		dup2(out, STDOUT_FILENO);
		close(out);
	}
	return (0);
}
void	ft_execve(t_btree *tree, t_data *data)
{
	char	*path;
	int		out;
	int		in;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	if (redirection(tree))
		ft_exit(data, "1");
	path = get_path(data->env, tree->cmd_argv[0]);
	if (path == NULL)
	{
		ft_putstrerr("Binary ");
		ft_putstrerr(tree->cmd_argv[0]);
		ft_putstrerr(" not found\n");
		ft_exit(data, "127");
	}
	execve(path, tree->cmd_argv, data->env);
	ft_putstrerr("Binary ");
	ft_putstrerr(path);
	ft_putstrerr(" not executable\n");
	free(path);
	ft_exit(data, "126");
}

#include <stdio.h>

int 	echo_maker(t_btree *tree, t_data *data)
{
	size_t	i;
	int		flag;
	char	*str;

	flag = 0;
	i = 1;
	str = NULL;
	if ((tree->cmd_argv)[i] != 0)
		if (ft_strncmp(tree->cmd_argv[i], "-n", 3) == 0 && ++flag)
			i++;
	while (tree->cmd_argv[i])
	{
		if (!(i == 1 || (i == 2 && flag == 1)))
		{
			str = ft_strjoinf1(str, " ");
			if (str == NULL)
				return 1;//error handle
		}
		str = ft_strjoinf1(str, tree->cmd_argv[i]);
		if (str == NULL)
			return 1;//error handle
		i ++;
	}
	return (ft_echo(data, str, flag), free(str), add_last_id(&data->pids, -1));
}

void	echo_wrap(t_btree *tree, t_data *data)
{
	int		pid;

	pid = -1;
	if (tree->redir.in || tree->redir.out)
	{
		pid = fork();
		if (pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_IGN);
			redirection(tree);
		}
	}
	if (pid <= 0)
		echo_maker(tree, data);
	if (pid == 0)
		ft_exit(data, NULL);
	if (pid   != 0)
		add_last_id(&data->pids, pid);
}


void	cd_wrap(t_btree *tree, t_data *data)
{
	int		pid;

	pid = -1;
	if (tree->redir.in || tree->redir.out)
	{
		pid = fork();
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
		redirection(tree);
	}
	if (pid <= 0)
	{
		if (!tree->cmd_argv[1])
			ft_cd(data, ft_strdup(""));
		else
			ft_cd(data, tree->cmd_argv[1]);
	}
	if (pid == 0)
		ft_exit(data, NULL);
	if (pid   != 0)
		add_last_id(&data->pids, pid);
}

void	export_wrap(t_btree *tree, t_data *data)
{
	int		pid;

	pid = -1;
	if (tree->redir.in || tree->redir.out)
	{
		pid = fork();
		if (pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_IGN);
			redirection(tree);
		}
	}
	if (pid <= 0)
	{
		if (!tree->cmd_argv[1])
			ft_export(data, "");
		else
			ft_export(data, tree->cmd_argv[1]);
	}
	if (pid == 0)
		ft_exit(data, NULL);
	if (pid   != 0)
		add_last_id(&data->pids, pid);
}

void	unset_wrap(t_btree *tree, t_data *data)
{
	int		pid;

	pid = -1;
	if (tree->redir.in || tree->redir.out)
	{
		pid = fork();
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
		redirection(tree);
	}
	if (pid <= 0)
	{
		if (!tree->cmd_argv[1])
			ft_unset(data, ft_strdup(""));
		else
			ft_unset(data, tree->cmd_argv[1]);
	}
	if (pid == 0)
		ft_exit(data, NULL);
	if (pid   != 0)
		add_last_id(&data->pids, pid);
}

void	env_wrap(t_btree *tree, t_data *data)
{
	int		pid;

	pid = -1;
	if (tree->redir.in || tree->redir.out)
	{
		pid = fork();
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
		redirection(tree);
	}
	if (pid <= 0)
		ft_env(data);
	if (pid == 0)
		ft_exit(data, NULL);
	if (pid   != 0)
		add_last_id(&data->pids, pid);
}

void	pwd_wrap(t_btree *tree, t_data *data)
{
	int		pid;

	pid = -1;
	if (tree->redir.in || tree->redir.out)
	{
		pid = fork();
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
		redirection(tree);
	}
	if (pid <= 0)
		ft_pwd(data);
	if (pid == 0)
		ft_exit(data, NULL);
	if (pid   != 0)
		add_last_id(&data->pids, pid);
}

void	exit_wrap(t_btree *tree, t_data *data)
{
	ft_exit(data, tree->cmd_argv[1]);
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
