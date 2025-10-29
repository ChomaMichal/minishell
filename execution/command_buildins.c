/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_buildins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 15:00:31 by mchoma            #+#    #+#             */
/*   Updated: 2025/10/23 12:44:06 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/idlist.h"
#include "executor.h"
#include "../commands/commands.h"

int	echo_maker(t_btree *tree, t_data *data)
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
				return (ft_putstrerr("fail\n"), add_last_id(&data->pids, -1));
		}
		str = ft_strjoinf1(str, tree->cmd_argv[i]);
		if (str == NULL)
			return (ft_putstrerr("fail\n"), add_last_id(&data->pids, -1));
		i ++;
	}
	return (ft_echo(data, str, flag), free(str), add_last_id(&data->pids, -1));
}

void	echo_wrap(t_btree *tree, t_data *data)
{
	int		pid;

	echo_maker(tree, data);
}

void	cd_wrap(t_btree *tree, t_data *data)
{
	int		pid;

	pid = -1;
	if (tree->redir_list)
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
	if (pid != 0)
		add_last_id(&data->pids, pid);
}

void	export_wrap(t_btree *tree, t_data *data)
{
	int		pid;

	pid = -1;
	if (tree->redir_list)
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
	if (pid != 0)
		add_last_id(&data->pids, pid);
}

void	unset_wrap(t_btree *tree, t_data *data)
{
	int		pid;

	pid = -1;
	if (tree->redir_list)
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
	if (pid != 0)
		add_last_id(&data->pids, pid);
}


int		in_dup_open()
{
	int		rt;
	int		fd;

	rt = dup(STDIN_FILENO);
	if (rt == -1)
		return (ft_putstrerr("redirection failed\n"), -1);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (ft_putstrerr("redirection failed\n"), -1);
	if (dup2(fd, STDIN_FILENO))
		return (ft_putstrerr("redirection failed\n"), -1);
	
	return (rt);
}


//dup original fd than dup 2 a new one to the original 
//place than after the funcion dup 2 the dupped original back 
//original[0] == std in
//original[1] == std out
int		redit_buildin(t_redir_list list)
{
	int	i;
	static int original[2];

	while (list.next)
	{
		if (list.type  == REDIR_OUT)
			original[1] = ft_open(list.file_name, O_WRONLY | O_TRUNC);
		if (list.type  == REDIR_OUT_APP)
			original[1] = ft_open(list.file_name, O_WRONLY | O_APPEND);
		if (list.type  == REDIR_IN)
			original[0] = ft_open()

		if (list.type  == REDIR_HERE)
				
	}
}
