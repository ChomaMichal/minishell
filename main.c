/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 18:43:42 by mchoma            #+#    #+#             */
/*   Updated: 2025/10/21 15:21:00 by mchoma           ###   ########.fr       */
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
	char	*line;
	char	*operators[10];
	t_data	data;
	int		line_count;

	if (init_main(&data, envp, &line_count, operators))
		return (ft_putstrerr("Malloc fail in initialization\n"), 1);
	while (1)
	{
		line = readline("<>minishell<>");
		if (line && line[0] && ++line_count)
		{
			add_history(line);
			data.head = create_exec_tree(line, operators, &data, &line_count);
			if (data.head)
			{
				execute(data.head, &data);
				cleanup(&data);
			}
			rl_on_new_line();
		}
		free(line);
	}
	ft_exit(&data, NULL);
	return (0);
}
