/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 18:23:54 by mchoma            #+#    #+#             */
/*   Updated: 2025/10/08 18:53:56 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	star_forward(size_t *i, size_t *j, char *match, char *str)
{
	size_t	tmp;

	tmp = 0;
	if (str[(*i)] != 0 && match[(*j)] == '*' && match[((*j)) + 1] == 0)
	{
		while (str[(*i)])
			(*i)++;
		while (match[(*j)])
			(*j)++;
		return ;
	}
	while (str[(*i) + tmp] == match[(*j) + 1 + tmp] && str[(*i) + tmp]
		&& match[(*j) + 1 + tmp])
		tmp ++;
	if ((match[(*j) + 1 + tmp] == '*' || match[(*j) + 1 + tmp] == 0) && tmp != 0)
	{
		(*j) = (*j) + tmp + 1;
		(*i) = (*i) + tmp;
	}
	else
		((*i)) ++;
}

int		star_match(char *match, char *str)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while(1)
	{
		if (match[j] == '*' && match[j + 1] == '*')
			j ++;
		if (match[j] == '*' &&  str[i])
			star_forward(&i, &j, match, str);
		else if (match[j] == str[i] && match[j] && str[i])
		{
			i ++;
			j ++;
		}
		else
		{
			if (str[i] == 0 && match[j] == 0)
				return (1);
			if (match[j] == '*' && match[j + 1] == 0)
				return (1);
			return (0);
		}
	}
}
