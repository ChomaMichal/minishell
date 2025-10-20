/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 18:43:42 by mchoma            #+#    #+#             */
/*   Updated: 2025/10/15 19:36:43 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

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

void	free_here_docs(t_here_doc **here_list)
{
	t_here_doc	*cur;
	t_here_doc	*next;

	if (!*here_list)
		return ;
	cur = *here_list;
	while (cur)
	{
		free(cur->delimiter);
		if (cur->file_name && access(cur->file_name, F_OK) == 0)
			unlink(cur->file_name);
		free(cur->file_name);
		next = cur->next;
		free(cur);
		cur = next;
	}
}

void	signal_parent_sigint(int sig)
{
	write(STDIN_FILENO, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
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
		free(node);
	}
}

void	init_parse_data(t_parse_data *d)
{
	d->here_list = NULL;
	d->line_count = 0;
	d->cmds_tree = NULL;
	d->line = NULL;
	set_operators(d->operators);
}

void	init_data(t_data *data, int argc, char **argv, char **envp)
{
	data->env = ft_coppyarrstr(envp);
	data->rt = 0;
	data->subshell = 0;
	data->pids = NULL;
	data->head = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_parse_data	d;
	t_data			data;

	init_parse_data(&d);
	init_data(&data, envp, argc, argv);
	signal(SIGINT, signal_parent_sigint);
	while (1)
	{
		d.line = readline("<>minishell<>");
		if (!d.line)
			break ;
		if (d.line[0] && ++d.line_count)
		{
			
			add_history(d.line);
			d.cmds_tree = create_exec_tree(&d, &data);
			if (d.cmds_tree)
			{
				// print_btree_pyramid(cmds_tree);
				data.head = d.cmds_tree;
				execute(d.cmds_tree, &data);
				free_here_docs(&d.here_list);
				btree_apply_suffix(d.cmds_tree, delete_bnode);
				data.rt = wait_and_get_exit_value(data.pids);
			}
			rl_on_new_line();
		}
		free(d.line);
	}
	ft_exit(&data, NULL);
	return (0);
}
