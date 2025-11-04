int	create_redirections(t_list **tokens, t_btree *bnode, t_here_doc **here_list)
{
	t_list	*cur;

	cur = *tokens;
	while (cur && (cur->token->options & WORD
		|| cur->token->options & REDIR_OP))
	{
		if (cur->token->options & REDIR_OP)
		{
			if (is_ambiguous_redir(cur->next))
			{
				bnode->ambig = ft_strdup(cur->token->redir_word);
				if (!bnode->ambig)
					return (clear_all_redirs(bnode, here_list), 1);
			}
			if (add_redir_node(&bnode->redir_list, cur->token->options,
				cur->next->token->str))
				return (clear_all_redirs(bnode, here_list), 1);
			if (cur->token->options & HERE_DOC)
				if (add_here_node(here_list, cur->next->token->str, bnode))
					return (clear_all_redirs(bnode, here_list), 1);
			cur = cur->next;
		}
		cur = cur->next;
	}
	return (0);
}