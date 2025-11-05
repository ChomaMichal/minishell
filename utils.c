/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josefelghnam <josefelghnam@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 15:08:59 by mchoma            #+#    #+#             */
/*   Updated: 2025/11/05 01:43:05 by josefelghna      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/idlist.h"

void	signal_parent_sigint(int sig)
{
	(void)(sig);
	sgnl = 1;
	(void)write(STDIN_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
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
	int		rt;

	rt = wait_and_get_exit_value(data->pids);
	if (rt != -1)
		data->rt = rt;
	free_pids(&data->pids);
	if (data->subshell == 1)
		btree_apply_suffix(data->head, delete_bnode);
	if (data->subshell == 0)
		btree_apply_suffix(data->head, delete_bnode_unlink);
	data->head = NULL;
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
}

int	init_main(t_data *data, char **envp, t_parse_data *d)
{
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
