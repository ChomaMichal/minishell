/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoma <your@mail.com>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 19:04:26 by mchoma            #+#    #+#             */
/*   Updated: 2025/10/06 19:14:05 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/libft/libft.h"
#include "executor.h"

static void	pipe_command(t_btree *tree, t_data *data, int *fd)
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
	{
		close(fd);
		ft_execve(tree, data, path);
	}
	if (add_last_id(data->pids, pid))
		data->rt = 1;
	free(path);
	free_split(tree->cmd_argv);
	free(tree);
}

void	ft_pipe(t_btree *tree, t_data *data)
{
	int		fd[2];

	if (pipe(fd))
	{
		ft_putstrerr("Pipe has failed\n");
		data->rt = 1;
		//free rest of tree
		return ;
	}
	dup2(fd[1], stdout);
	pipe_command(tree->left, data, fd, 1);

}
