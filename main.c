/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 18:43:42 by mchoma            #+#    #+#             */
/*   Updated: 2025/10/21 20:56:32 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	if (init_main(&data, envp, &d))
		return (ft_putstrerr("Malloc fail in initialization\n"), 1);
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
			{
				execute(data.head, &data);
				cleanup(&data);
			}
			rl_on_new_line();
		}
		free(d.line);
	}
	ft_exit(&data, NULL);
	return (0);
}
