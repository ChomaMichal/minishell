/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_buildins2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 15:17:42 by mchoma            #+#    #+#             */
/*   Updated: 2025/10/23 08:38:33 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../commands/commands.h"
#include "executor.h"

void	env_wrap(t_btree *tree, t_data *data)
{
	if (redit_buildin(tree->redir_list, 0) == 1)
		ft_env(data);
	else
		data->rt = 1;
	redit_buildin(tree->redir_list, 1);
}

void	pwd_wrap(t_btree *tree, t_data *data)
{
	if (redit_buildin(tree->redir_list, 0) == 1)
		ft_pwd(data);
	else
		data->rt = 1;
	redit_buildin(tree->redir_list, 1);
}

void	exit_wrap(t_btree *tree, t_data *data)
{
	if (redit_buildin(tree->redir_list, 0) == 1)
		ft_exit(data, tree->cmd_argv[1]);
	else
		data->rt = 1;
	redit_buildin(tree->redir_list, 1);
}

int	is_buildin(t_btree *tree, t_data *data)
{
	if (ft_strncmp(tree->cmd_argv[0], "cd", 3) == 0)
		return (cd_wrap(tree, data), 1);
	if (ft_strncmp(tree->cmd_argv[0], "pwd", 4) == 0)
		return (pwd_wrap(tree, data), 1);
	if (ft_strncmp(tree->cmd_argv[0], "echo", 5) == 0)
		return (echo_wrap(tree, data), 1);
	if (ft_strncmp(tree->cmd_argv[0], "env", 4) == 0)
		return (env_wrap(tree, data), 1);
	if (ft_strncmp(tree->cmd_argv[0], "unset", 6) == 0)
		return (unset_wrap(tree, data), 1);
	if (ft_strncmp(tree->cmd_argv[0], "export", 7) == 0)
		return (export_wrap(tree, data), 1);
	if (ft_strncmp(tree->cmd_argv[0], "exit", 5) == 0)
		return (exit_wrap(tree, data), 1);
	return (0);
}
