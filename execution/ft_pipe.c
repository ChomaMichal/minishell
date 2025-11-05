/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 19:04:26 by mchoma            #+#    #+#             */
/*   Updated: 2025/10/23 12:57:38 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "../libft/libft.h"
#include "../libft/idlist.h"

void	ft_putstrerr(char *str);

void	read_pipe(t_btree *tree, t_data *data, int *fd)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	data->subshell = 1;
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	execute(tree->right, data);
	ft_exit(data, NULL);
}

void	write_pipe(t_btree *tree, t_data *data, int *fd)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	data->subshell = 1;
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	execute(tree->left, data);
	ft_exit(data, NULL);
}

void	ft_pipe(t_btree *tree, t_data *data)
{
	int		fd[2];
	int		pid[2];

	if (pipe(fd))
	{
		ft_putstrerr("Pipe has failed\n");
		data->rt = 1;
		return ;
	}
	pid[0] = fork();
	if (pid[0] == 0)
		read_pipe(tree, data, fd);
	pid[1] = fork();
	if (pid[1] == 0)
		write_pipe(tree, data, fd);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid[0], &data->rt, 0);
	waitpid(pid[1], &data->rt, 0);
	data->pids = NULL;
}
