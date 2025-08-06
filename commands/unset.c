/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoma <mchoma@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 15:07:09 by mchoma            #+#    #+#             */
/*   Updated: 2025/08/06 16:30:43 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"
#include "../libft/libft.h"

static int	check_for_var(char ***envp, char **variable)
{
	size_t	i;
	char	*tmp;

	i = 0;
	tmp = ft_strjoin(*variable, "=");
	if (tmp == NULL)
		return (0);
	while ((*envp)[i])
	{
		if (ft_strnstr((*envp)[i], tmp, ft_strlen(tmp)) == NULL)
			i ++;
		else
			return (free(tmp), 1);
	}
	return (free(tmp), 0);
}

int		ft_unset(t_data *data, char *variable)
{
	size_t	i;
	size_t	j;
	char	*tmp;
	char	**new;

	j = check_for_var(&data->env, &variable);
	i = 0;
	// printf("%lu == len of new\n", j);
	tmp = ft_strjoin(variable, "=");
	if (tmp == NULL)
		return (free(variable), set_rt(&data->rt, 1), 0);
	new = ft_calloc(sizeof(char*), ft_arrlen((void **)data->env) - j + 1);
	if (new == NULL)
		return (free(tmp), free(variable), set_rt(&data->rt, 1), 0);
	j = 0;
	while ((data->env)[i])
	{
		// printf("%lu == i\n", i);
		if (ft_strnstr((data->env)[i], variable, ft_strlen(variable)) == NULL)
		{
			new[j] = (data->env)[i];
			j ++;
		}
		else
			free((data->env)[i]);
		i ++;
	}
	free(data->env);
	data->env = new;
	return (free(variable), free(tmp), set_rt(&data->rt, 0), 1);
}


