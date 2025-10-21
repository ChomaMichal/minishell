/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 15:08:59 by mchoma            #+#    #+#             */
/*   Updated: 2025/10/21 21:01:43 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "minishell.h"

void	signal_parent_sigint(int sig)
{
	int		i;

	i = sig;
	write(STDIN_FILENO, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	set_operators(char **operators)
{
	operators[0] = "||";
	operators[1] = "|";
	operators[2] = "&&";
	operators[3] = ">>";
	operators[4] = ">";
	operators[5] = "<<";
	operators[6] = "<";
	operators[7] = "(";
	operators[8] = ")";
	operators[9] = NULL;
}

void	delete_bnode(void *ptr)
{
	t_btree	*node;

	if (ptr)
	{
		node = (t_btree *)ptr;
		free_split(node->cmd_argv);
		free(node->redir.in);
		free(node->redir.out);
		if (node->redir.here)
			unlink(node->redir.here);
		free(node->redir.here);
		node->redir.here = NULL;
		free(node);
	}
}

void	delete_bnode_unlink(void *ptr)
{
	t_btree	*node;

	if (ptr)
	{
		node = (t_btree *)ptr;
		free_split(node->cmd_argv);
		free(node->redir.in);
		free(node->redir.out);
		if (node->redir.here)
			unlink(node->redir.here);
		free(node->redir.here);
		node->redir.here = NULL;
		free(node);
	}
}

void	cleanup(t_data *data)
{
	if (data->subshell == 1)
		btree_apply_suffix(data->head, delete_bnode);
	if (data->subshell == 0)
		btree_apply_suffix(data->head, delete_bnode_unlink);
	data->head = NULL;
	data->rt = wait_and_get_exit_value(data->pids);
}

int	init_main(t_data *data, char **envp, t_parse_data *d)
{
	d->here_list = NULL;
	d->line_count = 0;
	d->exec_tree = NULL;
	d->tokens = NULL;
	d->line = NULL;
	d->data = data;
	set_operators(d->operators);
	data->env = ft_coppyarrstr(envp);
	if (data->env == NULL)
		return (-1);
	data->rt = 0;
	data->subshell = 0;
	data->pids = NULL;
	data->head = NULL;
	signal(SIGINT, signal_parent_sigint);
	signal(SIGQUIT, SIG_IGN);
	return (0);
}
