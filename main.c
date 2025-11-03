/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 18:43:42 by mchoma            #+#    #+#             */
/*   Updated: 2025/11/03 21:03:43 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data			data;
	t_parse_data	d;

	rl_catch_signals = 0;
	if (init_main(&data, envp, &d))
		return (ft_putstrerr("minishell: allocation error in init\n"), 1);
	d.line_count = 0;
	int x = 0;
	while (1 && x < 3)
	{
		if (x == 0)
			d.line = ft_strdup("echo \'ooo\'\"hello$HOME\"xD > output | cat main.c && /echo SUCCESS && (echo hey)"); //readline("<>minishell<>");
		if (x == 1)
		{
			free(d.line);
			d.line = ft_strdup("echo \'ooo\'\"hello\"xD"); //readline("<>minishell<>");
		}
		if (x == 2)
		{
			free(d.line);
			d.line = NULL;//ft_strdup("");
		}
		x++;
		if (!d.line)
			break ;
		if (d.line[0] && ++d.line_count)
		{
			// add_history(d.line);
			data.head = parse(&d);
			if (data.head)
				(execute(data.head, &data), cleanup(&data), clear_here_list(&d.here_list));
			// rl_on_new_line();
		}
		// free(d.line);
	}
	free(d.line);
	ft_exit(&data, NULL);
	return (0);
}
