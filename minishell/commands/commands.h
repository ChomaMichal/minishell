/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 18:10:58 by jel-ghna          #+#    #+#             */
/*   Updated: 2025/10/08 18:10:58 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

# include "../minishell.h"

void	set_rt(int *rt, int num);
// changes working directory to given path
// works with absolute and relative paths
// in case of no arguments given pass ft_strdup("") as a path
int		ft_cd(t_data *data, char *path);
//prints current directory to stdout
int		ft_pwd(t_data *data);
// takes null terminated formated string
// the string has to be joined can't accept mutible strings
// frees it after using dont give NULL
// flag == 0 no flag is given
// flag == 1 -n flag is given
// prints the given strint to stdout
int		ft_echo(t_data *data, char *str, int flag);
// prints given environment
int		ft_env(t_data *data);
// takes adres of alocated array of alocated strings copies all of 
// the env variables except the given one which will be freed
// and modifies the given argument 
int		ft_unset(t_data *data, char *variable);
//takes malloced string as argument changes the env is string is correctly formated 
//sets exit value in struct
int		ft_export(t_data *data, char *arg);
#endif
