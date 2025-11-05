/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_buildins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 15:00:31 by mchoma            #+#    #+#             */
/*   Updated: 2025/10/30 16:41:33 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/idlist.h"
#include "executor.h"
#include "../commands/commands.h"
#include <stdio.h>

int	echo_maker(t_btree *tree, t_data *data)
{
	size_t	i;
	int		flag;
	char	*str;

	flag = 0;
	i = 1;
	str = NULL;
	
	if ((tree->cmd_argv)[0] && (tree->cmd_argv)[i] != 0)
		if (ft_strncmp(tree->cmd_argv[i], "-n", 3) == 0 && ++flag)
			i++;
	while (tree->cmd_argv[i])
	{
		if (!(i == 1 || (i == 2 && flag == 1)))
		{
			str = ft_strjoinf1(str, " ");
			if (str == NULL)
				return (ft_putstrerr("fail\n"), add_last_id(&data->pids, -1));
		}
		str = ft_strjoinf1(str, tree->cmd_argv[i]);
		if (str == NULL)
			return (ft_putstrerr("fail\n"), add_last_id(&data->pids, -1));
		i ++;
	}
	return (ft_echo(data, str, flag), free(str), add_last_id(&data->pids, -1));
}

void	echo_wrap(t_btree *tree, t_data *data)
{
	redit_buildin(tree->redir_list, 0);
	echo_maker(tree, data);
	redit_buildin(tree->redir_list, 1);
}

void	cd_wrap(t_btree *tree, t_data *data)
{
	redit_buildin(tree->redir_list, 0);
	if (!tree->cmd_argv[1])
		ft_cd(data, ft_strdup(""));
	else
		ft_cd(data, tree->cmd_argv[1]);
	redit_buildin(tree->redir_list, 1);
}

void	export_wrap(t_btree *tree, t_data *data)
{
	redit_buildin(tree->redir_list, 0);
	if (!tree->cmd_argv[1])
		ft_export(data, "");
	else
		ft_export(data, tree->cmd_argv[1]);
	redit_buildin(tree->redir_list, 1);
}

void	unset_wrap(t_btree *tree, t_data *data)
{
	redit_buildin(tree->redir_list, 0);
	if (!tree->cmd_argv[1])
		ft_unset(data, "");
	else
		ft_unset(data, tree->cmd_argv[1]);
	redit_buildin(tree->redir_list, 1);
}
