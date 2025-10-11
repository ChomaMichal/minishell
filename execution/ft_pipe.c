/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoma <your@mail.com>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 19:04:26 by mchoma            #+#    #+#             */
/*   Updated: 2025/10/10 15:25:40 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "../ids/idlist.h"
#include "../libft/libft.h"

void	ft_putstrerr(char *str);

void	read_pipe(t_btree *tree, t_data *data, int *fd)
{
	data->subshell = 1;
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	free_pids(&data->pids);
	execute(tree->right, data);
}

void	write_pipe(t_btree *tree, t_data *data, int *fd)
{
	data->subshell = 1;
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	free_pids(&data->pids);
	execute(tree->left, data);
}

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
	{
		read_pipe(tree, data, fd);
		exit(0);
	}
	if (add_last_id(&data->pids, pid))
	{
		fprintf(stderr, "error add_last_id\n");
		return ;//error handle
	}
	pid = fork();
	if (pid == 0)
	{
		write_pipe(tree, data, fd);
		exit(0);
	}
	if (add_last_id(&data->pids, pid))
	{
		fprintf(stderr, "error add_last_id\n");
		return ;//error handle
	}
	data->rt = wait_and_get_exit_value(data->pids);
	free_pids(&data->pids);
}

