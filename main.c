/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 18:43:42 by mchoma            #+#    #+#             */
/*   Updated: 2025/10/13 20:28:30 by jel-ghna         ###   ########.fr       */
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

void	print_env(char **envp)
{
	size_t	i;

	i = 0;
	while (envp[i++])
		printf("%s\n", envp[i - 1]);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_btree	*cmds_tree;
	char	*operators[10];
	t_data	data;
	int		line_count;

	line_count = 0;
	argc = 0;
	argv  = NULL;
	data.env = ft_coppyarrstr(envp);
	data.rt = 0;
	data.subshell = 0;
	data.pids = NULL;
	data.head = NULL;
	// print_env(envp);
	set_operators(operators);
	signal(SIGINT, signal_parent_sigint);
	while (1)
	{
		line = readline("<>minishell<>");
		if (!line)
			break ;
		if (line[0])
		{
			line_count++;
			add_history(line);
			cmds_tree = create_exec_tree(line, operators, &data, &line_count);
			if (cmds_tree)
			{
				// print_btree_pyramid(cmds_tree);
				data.head = cmds_tree;
				execute(cmds_tree, &data);
				btree_apply_suffix(cmds_tree, delete_bnode);
				data.rt = wait_and_get_exit_value(data.pids);
			}
			rl_on_new_line();
		}
		free(line);
	}
	ft_exit(&data, NULL);
	return (0);
}
