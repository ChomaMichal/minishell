/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoma <your@mail.com>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 14:17:53 by mchoma            #+#    #+#             */
/*   Updated: 2025/11/06 14:22:17 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
#include <sys/ioctl.h>

void	signal_parent_sigint(int sig)
{
	g_sgnl = sig;
}

char	*shlvl(char *org)
{
	return (ft_strjoinf2("SHLVL=", ft_itoa(ft_atoi(org + 6) + 1)));
}

char	**init_env(char **envp)
{
	size_t	i;
	char	**rt;

	i = 0;
	while (envp[i])
		i ++;
	rt = ft_calloc (i + 1, sizeof(char *));
	if (rt == NULL)
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

int	rlhook(void)
{
	if (ioctl(STDIN_FILENO, TIOCSTI, "\n") == -1)
		ft_putstrerr("oictl error\n");
	rl_replace_line("", 0);
	return (0);
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
	data->env = init_env(envp);
	if (data->env == NULL)
		return (-1);
	data->rt = 0;
	data->subshell = 0;
	data->pids = NULL;
	data->head = NULL;
	rl_signal_event_hook = rlhook;
	signal(SIGINT, signal_parent_sigint);
	signal(SIGQUIT, SIG_IGN);
	return (0);
}
