/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 15:16:38 by mchoma            #+#    #+#             */
/*   Updated: 2025/10/30 15:16:03 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "../commands/commands.h"
#include "../libft/libft.h"
#include "../libft/idlist.h"
#include <signal.h>

void	ft_execve(t_btree *tree, t_data *data)
{
	char	*path;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (tree->ambig)
		ft_printf(2, "idk abigous redirection i guess \n skill issue UwU\n");
	if (!tree->ambig && redir_dup2(tree) == -1)
		ft_exit(data, "1");
	if (tree->empty_cmd)
		ft_exit(data, "0");
	path = get_path(data->env, tree->cmd_argv[0]);
	if (path == NULL)
	{
		ft_printf(2, "Binary %s not found\n", tree->cmd_argv[0]);
		ft_exit(data, "127");
	}
	execve(path, tree->cmd_argv, data->env);
	ft_printf(2, "Binary %s not executable\n", path);
	free(path);
	ft_exit(data, "126");
}

void	ft_command(t_btree *tree, t_data *data)
{
	int		pid;

	if (!tree->empty_cmd && is_buildin(tree, data) == 1)
		return ;
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
