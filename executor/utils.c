/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoma <your@mail.com>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 18:59:46 by mchoma            #+#    #+#             */
/*   Updated: 2025/10/06 19:00:17 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/libft/libft.h"
#include "executor.h"

void	ft_execve(t_btree *tree, t_data *data, char  *path)
{
	execve(path, tree->cmd_argv, data->env);
	free(tree->cmd_argv);
	free(tree);
	free(path);
	//ft_exit();
	exit(1);
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
