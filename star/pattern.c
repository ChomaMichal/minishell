/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 14:51:15 by mchoma            #+#    #+#             */
/*   Updated: 2025/11/04 19:15:00 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	star_match_recur(char *match, char *str);

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
		&& match[(*j) + 1 + tmp] && !(match[0] == '*' && i == 0))
		tmp ++;
	if ((match[(*j) + 1 + tmp] == '*'
			|| match[(*j) + 1 + tmp] == 0) && tmp != 0)
	{
		(*j) = (*j) + tmp + 1;
		(*i) = (*i) + tmp;
	}
}


int	star_forward_wrap(char *match, char *str)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (match[0] != '*' || match[0] == 0 || str[0] == 0)
		return (0);
	if (match[0] == '*' && str[0])
		star_forward(&i, &j, match, str);
	if (i != 0 && star_match_recur(match + j, str + i) == 1)
		return (1);
	return (star_forward_wrap(match, str + 1));
}


int	star_match_recur(char *match, char *str)
{
	if ((str[0] != 0 && match[0]  == 0) || (str[0] == 0 && match[0]  != 0))
		return (0);
	if (str[0] == 0 && match[0] == 0)
		return (1);
	if (str[0] != 0 && match[0] == '*' && match[1] == 0)
		return (1);
	else if (match[0] == str[0] && match[0] && str[0])
		return (star_match_recur(match + 1, str + 1));
	else if (match[0] == '*' && str[0])
		return (star_forward_wrap(match, str));
	return (0);
}