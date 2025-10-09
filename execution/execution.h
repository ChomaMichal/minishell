/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 16:14:01 by mchoma            #+#    #+#             */
/*   Updated: 2025/10/08 18:11:15 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "../minishell.h"

char	*get_path(char**envp, char *command);
void	ft_execve(t_btree *tree, t_data *data, char  *path);
int		wait_and_get_exit_value(t_ids *list);
void	ft_subshell(t_btree *tree, t_data *data);
void	ft_and(t_btree *tree, t_data *data);
void	ft_or(t_btree *tree, t_data *data);
void	ft_command(t_btree *tree, t_data *data);
void	ft_pipe(t_btree *tree, t_data *data);

#endif
