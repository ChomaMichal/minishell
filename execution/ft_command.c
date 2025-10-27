/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 15:16:38 by mchoma            #+#    #+#             */
/*   Updated: 2025/10/23 12:44:42 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "../commands/commands.h"
#include "../libft/libft.h"
#include "../libft/idlist.h"
#include <signal.h>

//todo implement build ins
//if it is not found exit with 127 
//if found and not executable exit with 126

int	redirection(t_btree *tree)
{
	int				in;
	int				out;
	t_redir_list	*cur;

	in = -1;
	out = -1;
	cur = tree->redir_list;
	while (cur)
	{
		if (cur->type == REDIR_HERE || cur->type == REDIR_IN)
		{
			if (in > -1)
				close(in);
			in = open(cur->file_name, O_RDONLY);
			if (in == -1)
				return (ft_printf(2, "open failed in redirection() REDIR_HERE|REDIR_IN\n"), -1);
		}
		else if (cur->type == REDIR_OUT)
		{
			if (out > -1)
				close(out);
			out = open(cur->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
			if (out == -1)
				return (ft_printf(2, "open failed in redirection() REDIR_OUT\n"), -1);
		}
		else if (cur->type == REDIR_OUT_APP)
		{
			if (out > -1)
				close(out);
			out = open(cur->file_name, O_WRONLY | O_CREAT | O_APPEND, 0777);
			if (out == -1)
				return (ft_printf(2, "open failed in redirection() REDIR_OUT_APP\n"), -1);
		}
		cur = cur->next;
	}
	if (in > -1)
		dup2(in, STDIN_FILENO);
	if (out > -1)
		dup2(out, STDOUT_FILENO);
	return (0);
}

void	ft_execve(t_btree *tree, t_data *data)
{
	char	*path;
	int		out;
	int		in;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	if (tree->ambig)
	{
		ft_putstrerr("minishell: ");
		ft_putstrerr(tree->ambig);
		ft_putstrerr(" ambiguous redirection\n");
		ft_exit(data, "1");
	}
	if (tree->empty_cmd)
		ft_exit(data, "0");
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

void	ft_command(t_btree *tree, t_data *data)
{
	int		pid;

	if (tree->ambig)
		printf("ambig caught in execution\n");
	if (tree->empty_cmd)
		printf("empty cmd caught in execution\n");
	if (is_buildin(tree, data) == 1)
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
