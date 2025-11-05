/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildinredit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoma <your@mail.com>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 15:31:11 by mchoma            #+#    #+#             */
/*   Updated: 2025/10/29 15:32:04 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "executor.h"
#include <unistd.h>

int	in_dup_open(char *filename, int *in)
{
	int		fd;

	if (*in <= -1)
	{
		*in = dup(STDIN_FILENO);
		if (*in == -1)
			return (ft_putstrerr("redirection failed\n"), -2);
	}
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (ft_putstrerr("open in redirection failed\n"), -2);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (close(fd), ft_putstrerr("redirection failed\n"), -2);
	close (fd);
	return (1);
}

int	out_dup_app(char *filename, int *out)
{
	int		fd;

	if (*out <= -1)
	{
		*out = dup(STDOUT_FILENO);
		if (*out == -1)
			return (ft_putstrerr("redirection failed\n"), -2);
	}
	fd = open(filename, O_WRONLY | O_APPEND);
	if (fd == -1)
		return (ft_putstrerr("opeining file failed\n"), -2);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (close(fd), ft_putstrerr("redirection failed\n"), -2);
	close (fd);
	return (1);
}

int	out_dup_trunc(char *filename, int *out)
{
	int		fd;

	if (*out <= -1)
	{
		*out = dup(STDOUT_FILENO);
		if (*out == -1)
			return (ft_putstrerr("dup redirection failed\n"), -2);
	}
	fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (fd == -1)
		return (ft_putstrerr("opening file failed\n"), -2);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (close(fd), ft_putstrerr("dup 2 redirection failed\n"), -2);
	close (fd);
	return (1);
}

int	ft_revert(int *in, int *out)
{
	if (*in != -1)
	{
		if (dup2(*in, STDIN_FILENO) == -1)
			return (ft_printf(2, "Error dup2\n"), -1);
		close (*in);
	}
	if (*out != -1)
	{
		if (dup2(*out, STDOUT_FILENO) == -1)
			return (ft_printf(2, "Error dup2\n"), -1);
		close(*out);
	}
	*out = -1;
	*in = -1;
	return (1);
}

//dup original fd than dup 2 a new one to the original 
//place than after the funcion dup 2 the dupped original back 
//in == std in
//out == std out
int	redit_buildin(t_redir_list *list, int revert)
{
	static int	in = -1;
	static int	out = -1;
	int			err;

	err = 1;
	if (revert == 1)
		return (ft_revert(&in, &out));
	while (list && err == 1)
	{
		if (list->type == REDIR_OUT)
			err = out_dup_trunc(list->file_name, &out);
		if (list->type == REDIR_OUT_APP)
			err = out_dup_app(list->file_name, &out);
		if (list->type == REDIR_IN)
			err = in_dup_open(list->file_name, &in);
		if (list->type == REDIR_HERE)
			err = in_dup_open(list->file_name, &in);
		list = list->next;
	}
	if (err <= -1)
		return (ft_revert(&in, &out), -1);
	return (1);
}
