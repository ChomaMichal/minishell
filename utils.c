/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 15:08:59 by mchoma            #+#    #+#             */
/*   Updated: 2025/11/04 18:54:03 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <signal.h>
#include "minishell.h"
#include "libft/idlist.h"

int	ms_signal_event_hook(void)
{
	write(0, "^C\n", 3);
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	signal_parent_sigint(int sig)
{
<<<<<<< HEAD
	int		i;

	i = sig;
	// C Standards: we should not use readline functions in signal handlers
	// write(STDIN_FILENO, "\n", 1);
=======
	(void)(sig);
	sgnl = 1;
	(void)write(STDIN_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
>>>>>>> 5c012d97ef026f77ccd46fdfc156fb1f2dee24a7
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
		free(node->ambig);
		clear_redir_list(&node->redir_list);
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
		free(node->ambig);
		clear_redir_list_unlink(&node->redir_list);
		free(node);
	}
}

void	cleanup(t_data *data)
{
	data->rt = wait_and_get_exit_value(data->pids);
<<<<<<< HEAD
=======
	free_pids(&data->pids);
>>>>>>> 5c012d97ef026f77ccd46fdfc156fb1f2dee24a7
	if (data->subshell == 1)
		btree_apply_suffix(data->head, delete_bnode);
	if (data->subshell == 0)
		btree_apply_suffix(data->head, delete_bnode_unlink);
	data->head = NULL;
<<<<<<< HEAD
=======
}

char	*shlvl(char *org)
{
	return (ft_strjoinf2("SHLVL=", ft_itoa(ft_atoi(org + 6) + 1)));
}

char **init_env(char **envp)
{
	size_t	i;
	char	**rt;
	
	i = 0;
	while (envp[i])
		i ++;
	rt = ft_calloc (i, sizeof(char *) + 1);
	if (rt  == NULL)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "SHLVL=", 6) == 0)
			rt[i] = shlvl(envp[i]);
		else 
			rt[i] = ft_strdup(envp[i]);
		if (rt[i] == NULL)
			return (free_arr((void ***)&rt), NULL);
		i ++;
	}
	return (rt);
>>>>>>> 5c012d97ef026f77ccd46fdfc156fb1f2dee24a7
}

int	init_main(t_data *data, char **envp, t_parse_data *d)
{
	rl_signal_event_hook = ms_signal_event_hook;
	d->here_list = NULL;
	// d->line_count = 0;
	d->exec_tree = NULL;
	d->tokens = NULL;
	d->line = NULL;
	d->data = data;
	set_operators(d->operators);
	data->env = init_env(envp);
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
