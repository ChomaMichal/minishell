/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoma <your@mail.com>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 19:02:13 by mchoma            #+#    #+#             */
/*   Updated: 2025/10/06 19:02:25 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../parsing/libft/libft.h"
#include "executor.h"

void	ft_command(t_btree *tree, t_data *data)
{
	char	*path;
	int		pid;

	path = get_path(data->env, tree->cmd_argv[0]); 
	if (path == NULL)
	{
		data->rt = 1;
		free_split(tree->cmd_argv);
		free(tree);
		return ;
	}
	pid = fork();
	if (pid == 0)
		ft_execve(tree, data, path);
	if (add_last_id(data->pids, pid))
		data->rt = 1;
	free(path);
	free_split(tree->cmd_argv);
	free(tree);
}
