/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoma <your@mail.com>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 19:04:26 by mchoma            #+#    #+#             */
/*   Updated: 2025/10/09 19:03:26 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/libft/libft.h"
#include "executor.h"
#include "../ids/idlist.h"

void	ft_putstrerr(char *str);

void	read_pipe(t_btree tree, data, fd)


void	ft_pipe(t_btree *tree, t_data *data)
{
	int		fd[2];
	int		pid;

	if (pipe(fd))
	{
		ft_putstrerr("Pipe has failed\n");
		data->rt = 1;
		//free rest of tree
		return ;
	}
	pid = fork();
	if (pid == 0)
		read_pipe(tree->left, data, fd);
	if (add_last_id(data->pids, pid))
		return ;//error handle
	pid = fork();
	if (pid == 0)
		write_pipe(tree->right, data, fd);
	if (add_last_id(data->pids, pid))
		return ;//error handle
	data->rt = wait_and_get_exit_value(data->pids);
}

