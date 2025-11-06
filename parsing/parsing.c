/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 19:05:10 by jel-ghna          #+#    #+#             */
/*   Updated: 2025/11/06 15:23:28 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	btoindex(int options)
{
	int	i;

	i = 0;
	while (!((options >> i) & 1))
		i++;
	return (i);
}

t_btree	*parse(t_parse_data *d)
{
	t_print_d	print_data;

	print_data.line = d->line;
	print_data.operators = d->operators;
	d->tokens = tokenize(d);
	if (!d->tokens)
		return (free(d->line), parse_set_rt(d, 2), NULL);
	if (validate_tokens(d->tokens, d->operators))
		return (free(d->line), parse_set_rt(d, 2), del_tokens(d->tokens), NULL);
	if (expand(d))
		return (free(d->line), parse_set_rt(d, 2), del_tokens(d->tokens), NULL);
	d->exec_tree = create_exec_tree(d);
	del_tokens(d->tokens);
	clear_here_list(&d->here_list);
	if (!d->exec_tree)
		parse_set_rt(d, 2);
	return (free(d->line), d->exec_tree);
}
