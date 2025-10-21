/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoma <your@mail.com>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 15:08:59 by mchoma            #+#    #+#             */
/*   Updated: 2025/10/21 15:20:34 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
#include <signal.h>

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

void	cleanup(t_data *data)
{
	btree_apply_suffix(data->head, delete_bnode);
	data->head = NULL;
	data->rt = wait_and_get_exit_value(data->pids);
}

int	init_main(t_data *data, char **envp, int *line_count, char **operators)
{
	set_operators(operators);
	data->env = ft_coppyarrstr(envp);
	if (data->env == NULL)
		return (-1);
	data->rt = 0;
	data->subshell = 0;
	data->pids = NULL;
	data->head = NULL;
	signal(SIGINT, signal_parent_sigint);
	*line_count = 0;
	return (0);
}
