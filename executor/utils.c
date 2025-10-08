/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoma <your@mail.com>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 18:59:46 by mchoma            #+#    #+#             */
/*   Updated: 2025/10/06 19:40:06 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/libft/libft.h"
#include "executor.h"

//if it is not found exit with 127 
//if found and not executable exit with 126
void	ft_execve(t_btree *tree, t_data *data, char  *path)
{
	path = get_path(data->env, tree->cmd_argv[0]); 
	if (path == NULL)
	{
		data->rt = 1;
		free_split(tree->cmd_argv);
		free(tree);
		return ;
	}
	execve(path, tree->cmd_argv, data->env);
	free(tree->cmd_argv);
	free(tree);
	free(path);
	//ft_exit();
}

int		wait_and_get_exit_value(t_ids *list)
{
	int	rt;

	if (list->next == NULL)
	{
		waitpid(list->pid, &rt, 0);
		if (WIFSIGNALED(rt))
			return (WTERMSIG(rt) + 128);
		WEXITSTATUS(rt);
		return (WEXITSTATUS(rt));
	}
	waitpid(list->pid, NULL, 0);
	return (wait_and_get_exit_value(list->next));
}
