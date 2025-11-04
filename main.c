/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoma <your@mail.com>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 16:21:03 by mchoma            #+#    #+#             */
/*   Updated: 2025/10/30 16:21:05 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
volatile int sgnl = 0;

void	print_env(char **envp)
{
	size_t	i;

	i = 0;
	while (envp[i++])
		printf("%s\n", envp[i - 1]);
}

int	main(int argc, char **argv, char **envp)
{
	t_data			data;
	t_parse_data	d;

	(void) argc;
	(void) argv;
	if (init_main(&data, envp, &d))
		return (ft_putstrerr("Malloc fail in initialization\n"), 1);
	d.line_count = 0;
	while (1)
	{
		d.line = readline("<>minishell<>");
		if (!d.line)
			break ;
		if (d.line[0] && ++d.line_count)
		{
			add_history(d.line);
			data.head = parse(&d);
			if (data.head)
				execute(data.head, &data);
		}
		cleanup(&data);
		free(d.line);
		rl_on_new_line();
	}
	ft_exit(&data, NULL);
	return (0);
}
