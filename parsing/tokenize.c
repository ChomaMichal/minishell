#include "minishell.h"

int	add_token(t_list **head, t_token *token)
{
	t_list	*node;

	node = ft_lstnew(token);
	if (!node)
		return (free(token), perror("malloc: add_operator_token"), 1);
	ft_lstadd_back(head, node);
	return (0);
}

t_token	*create_token(void)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->fragment_count = 0;
	token->fragments = NULL;
	token->options = 0;
	token->str = NULL;
	return (token);
}

void	set_operator_options(int *options, int op)
{
	*options |= (1 << op);
	*options |= OPERATOR;
	if (op == 3 || op == 4 || op == 5 || op == 6)
		*options |= REDIR_OP;
	else if (7 == op || op == 8)
		*options |= PARENTHESIS;
}

int	handle_operator(t_list **head, char *line, char **operators, size_t *i)
{
	t_token	*token;
	int		op_index;

	skip_blank(line, i);
	op_index = is_operator(&line[*i], operators);
	if (op_index == -1)
		return (0);
	token = create_token();
	if (!token)
		return (perror("malloc: create_token"), 1);
	set_operator_options(&token->options, op_index);
	if (add_token(head, token))
		return (free(token), perror("malloc: add_token"), 1);
	*i += ft_strlen(operators[op_index]);
	skip_blank(line, i);
	op_index = is_operator(&line[*i], operators);
	if (op_index > -1)
		return (handle_operator(head, line, operators, i));
	return (0);
}

int	handle_word(t_list **head, char *line, char **operators, size_t *i)
{
	t_token		*token;
	size_t		word_len;

	skip_blank(line, i);
	token = create_token();
	if (!token)
		return (perror("malloc: create_token"), 1);
	token->options |= WORD;
	word_len = len_to_unquoted_delimiter(&line[*i], operators);
	if (word_len == 0)
		return (free(token), 0);
	token->fragments = malloc(sizeof(t_fragment) * ((word_len / 2) + 1));
	if (!token->fragments)
		return (free(token), perror("malloc: handle_word"), 1);
	if (handle_fragments(line, operators, token, i))
		return (free(token->fragments), free(token), 1);
	if (add_token(head, token))
		return (free(token->fragments), free(token),
		perror("malloc: handle_word"), 1);
	// *i += word_len;
	return (0);
}

static void	free_token(void *ptr)
{
	free(((t_token *)ptr)->fragments);
	free(ptr);
}

// TODO: change the variable line's name depending on how you use it, from the start or from the middle of the line
t_list	*tokenize(char *line, char **operators)
{
	t_list		*head;
	size_t		i;

	i = 0;
	head = NULL;
	while (line[i])
	{
		if (handle_operator(&head, line, operators, &i))
			return (ft_lstclear(&head, free_token),
			perror("handle_operator failed"), NULL);
		if (handle_word(&head, line, operators, &i))
			return (ft_lstclear(&head, free_token),
			perror("handle_word failed"), NULL);
	}
	return (head);
}
