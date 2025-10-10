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
	close(STDIN_FILENO);
	if (dup2(fd[0], STDIN_FILENO))
		ft_putstrerr("dup2 failed\n");
	close(fd[1]);
	execute(tree->right, data);
	free_arr((void ***)&tree->cmd_argv);
	free(tree);
}

void	write_pipe(t_btree *tree, t_data *data, int *fd)
{
	close(STDOUT_FILENO);
	if (dup2(fd[1], STDOUT_FILENO))
		ft_putstrerr("dup2 failed\n");
	close(fd[0]);
	execute(tree->left, data);
	free_arr((void ***)&tree->cmd_argv);
	free(tree);
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
		read_pipe(tree, data, fd);
	if (add_last_id(&data->pids, pid))
		return ;//error handle
	pid = fork();
	if (pid == 0)
		write_pipe(tree, data, fd);
	if (add_last_id(&data->pids, pid))
		return ;//error handle
	data->rt = wait_and_get_exit_value(data->pids);
}

