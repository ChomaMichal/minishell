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

int	in_dup_open(char *filename, int *original)
{
	int		rt;
	int		fd;

	if (original[0] <= -1)
	{
		rt = dup(STDIN_FILENO);
		if (rt == -1)
			return (ft_putstrerr("redirection failed\n"), -2);
	}
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (ft_putstrerr("redirection failed\n"), -2);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (ft_putstrerr("redirection failed\n"), -2);
	return (rt);
}

int	out_dup_app(char *filename, int *original)
{
	int		rt;
	int		fd;

	if (original[1] <= -1)
	{
		rt = dup(STDOUT_FILENO);
		if (rt == -1)
			return (ft_putstrerr("redirection failed\n"), -2);
	}
	fd = open(filename, O_WRONLY | O_APPEND);
	if (fd == -1)
		return (ft_putstrerr("opeining file failed\n"), -2);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (ft_putstrerr("redirection failed\n"), -2);
	return (rt);
}

int	out_dup_trunc(char *filename, int *original)
{
	int		rt;
	int		fd;

	if (original[1] <= -1)
	{
		rt = dup(STDOUT_FILENO);
		if (rt == -1)
			return (ft_putstrerr("dup redirection failed\n"), -2);
	}
	fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (fd == -1)
		return (ft_putstrerr("opening file failed\n"), -2);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (ft_putstrerr("dup 2 redirection failed\n"), -2);
	return (rt);
}

int	ft_revert(int *original)
{
	if (original[0] != -1)
	{
		if (dup2(original[0], STDIN_FILENO) == -1)
			return (-2);
		close (original[0]);
	}
	if (original[1] != -1)
	{
		if (dup2(original[1], STDOUT_FILENO) == -1)
			return (-2);
		close(original[1]);
	}
	original[1] = -1;
	original[0] = -1;
	return (1);
}

//dup original fd than dup 2 a new one to the original 
//place than after the funcion dup 2 the dupped original back 
//original[0] == std in
//original[1] == std out
int	redit_buildin(t_redir_list *list, int revert)
{
	static int	original[2] = {-1, -1};

	if (revert == 1)
		return (ft_revert(original));
	while (list && original[1] != -2 && original[0] != -2)
	{
		if (list->type == REDIR_OUT)
			original[1] = out_dup_trunc(list->file_name, original);
		if (list->type == REDIR_OUT_APP)
			original[1] = out_dup_app(list->file_name, original);
		if (list->type == REDIR_IN)
			original[0] = in_dup_open(list->file_name, original);
		if (list->type == REDIR_HERE)
			original[0] = in_dup_open(list->file_name, original);
		list = list->next;
	}
	if (original[0] == -2 || original[1] == -2)
		return (ft_revert(original), -1);
	return (1);
}
