/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filename_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 16:26:33 by jel-ghna          #+#    #+#             */
/*   Updated: 2025/11/03 19:07:11 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	insert_expanded_filenames(t_list **files_list, t_list **node)
{
	free((*node)->token->fragments);
	free((*node)->token->stars_arr);
	free((*node)->token->str);
	free((*node)->token);
	ft_lstlast(*files_list)->next = (*node)->next;
	(*node)->token = (*files_list)->token;
	(*node)->next = (*files_list)->next;
	free(*files_list);
}

static int	create_files_tokens(t_list **head, char **split_arr,
	size_t fragment_i, t_list *token_node)
{
	t_token	*new_token;
	size_t	arr_counter;

	arr_counter = 0;
	while (split_arr[arr_counter++])
	{
		new_token = create_token(0);
		if (!new_token)
			return (1);
		new_token->fragment_i = fragment_i;
		new_token->fragments = malloc(sizeof (t_fragment));
		if (!new_token->fragments)
			return (free(new_token), 1);
		ft_memmove(new_token->fragments, token_node->token->fragments,
			sizeof(t_fragment));
		new_token->options = new_token->options | WORD | EXPANDED_WORD
			| (token_node->token->options & REDIR_WORD);
		new_token->str = ft_strdup(split_arr[arr_counter - 1]);
		if (!new_token->str)
			return (free(new_token->fragments), free(new_token), 1);
		if (add_token(head, new_token))
			return (free(new_token->fragments), free(new_token->str),
				free(new_token), 1);
	}
	return (0);
}

static int	expand_filename(t_list **node, size_t fragment_i)
{
	char	**files_arr;
	t_list	*files_list;

	files_arr = NULL;
	files_list = NULL;
	files_arr = expand_star_append((*node)->token->str, &files_arr,
			(*node)->token->stars_arr);
	if (!files_arr)
		return (0);
	if (create_files_tokens(&files_list, files_arr, fragment_i, *node))
		return (free_split(files_arr), del_tokens(files_list), 1);
	free_split(files_arr);
	insert_expanded_filenames(&files_list, node);
	return (0);
}

int	filename_expansion(t_list **head, char *line)
{
	t_list	*node;

	node = *head;
	while (node)
	{
		if (node->token->options & WORD
			&& !(node->token->options & EXPANDED_WORD))
		{
			if (expand_filename(&node, node->token->fragment_i))
				return (1);
		}
		node = node->next;
	}
	return (0);
}
