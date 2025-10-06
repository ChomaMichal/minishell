/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoma <your@mail.com>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 16:14:01 by mchoma            #+#    #+#             */
/*   Updated: 2025/10/06 19:01:42 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H
# include "../parsing/minishell.h"

char	*get_path(char**envp, char *command);
void	ft_execve(t_btree *tree, t_data *data, char  *path);
int		wait_and_get_exit_value(t_ids *list);
void	ft_subshell(t_btree *tree, t_data *data);
void	ft_and(t_btree *tree, t_data *data);
void	ft_or(t_btree *tree, t_data *data);
void	ft_command(t_btree *tree, t_data *data);
void	ft_pipe(t_btree *tree, t_data *data);

#endif
