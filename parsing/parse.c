#include "minishell.h"
// x &= ~(1 << 2)
// 000101
// 111011
//=000001

// DON'T STORE " " (strings with spaces) in res
// DON't FORGET FUNCHECK

int	ft_isblank(char c)
{
	return (c == ' ' || c == '	');
}

static void	skip_blank(char *line, size_t *i)
{
	while (ft_isblank(line[*i]))
		*i += 1;
}

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

// int	add_command(t_list **head, char *line_start, size_t len)
// {
// 	char	*sub_str;
// 	t_list	*node;

// 	if (len == 0)
// 		return (1);
// 	sub_str = malloc(sizeof(char) * (len + 1));
// 	if (!sub_str)
// 		return (perror("malloc: add_command"), 1);
// 	ft_strlcpy(sub_str, line_start, len + 1);
// 	node = ft_lstnew(sub_str);
// 	if (!node)
// 		return (free(sub_str), perror("malloc: add_command"), 1);
// 	ft_lstadd_back(head, node);
// 	return (0);
// }

size_t	len_to_delimiter(char *line, char **operators)
{
	size_t	len;
	size_t	op;

	len = 0;
	while (line[len])
	{
		op = 0;
		if (line[len] == ' '|| line[len] == '	')
			return (len);
		while (operators[op])
		{
			if (!ft_strncmp(&line[len], operators[op], ft_strlen(operators[op])))
				return (len);
			op++;
		}
		len++;
	}
	return (len);
}

// int	handle_quotes(t_list **head, char *line, char quote, size_t *i)
// {
// 	size_t	j;

// 	j = 0;
// 	while (line[j])
// 	{
// 		j++;
// 		if (line[j] == 0)
// 			return (perror("unclosed quote"), 1);
// 		if (line[j] == quote)
// 			break ;
// 	}
// 	if (add_command(head, &line[0], j + 1))
// 		return (perror("add_command-handle_quotes failed"), 1);
// 	*i += (j + 1);
// 	return (0);
// }

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
	token->options |= (1 << op_index);
	token->options |= OPERATOR;
	if (add_token(head, token))
		return (free(token), perror("malloc: add_token"), 1);
	*i += ft_strlen(operators[op_index]);
	skip_blank(line, i);
	op_index = is_operator(&line[*i], operators);
	if (op_index > -1)
		return (handle_operator(head, line, operators, i));
	return (0);
}

// int	add_fragment(t_fragment fragment, t_token *token)
// {
// 	if (resize_fragments_arr(token->fragments))
// 		return (1);
// 	token->fragments[token->fragment_count] = fragment;
// 	token->fragment_count++;
// }

// t_fragment	*make_fragment(char *line, size_t start, size_t i)
// {
// 	t_fragment	*fragment;

// 	fragment = malloc(sizeof(t_fragment));
// 	if (!fragment)
// 		return (NULL);
// 	if (line[start] == '\"' && line[i] == '\"')
// 	{
// 		fragment->str = ft_substr(line, start + 1, i - start);
// 		fragment->type = DOUBLE_QUOTE_FRAGM;
// 	}
// 	else if (line[start] == '\'' && line[i] == '\'')
// 	{
// 		fragment->str = ft_substr(line, start + 1, i - start);
// 		fragment->type = SINGLE_QUOTE_FRAGM;
// 	}
// 	else
// 	{
// 		fragment->str = ft_substr(line, start, i - start);
// 		fragment->type = LITERAL_FRAGM;
// 	}
// 	if (!fragment->str)
// 		return (1);
// }

// int	make_add_fragment(char *line, t_token *token, size_t start, size_t i)
// {
// 	t_fragment	*fragment;

// 	fragment = make_fragment(line, start, i);
// 	if (!fragment)
// 		return (1);
// 	if (add_fragment(fragment))
// 		return (1);
// 	return (0);
// }

// int	close_double_quote(size_t *start, size_t *i, char *line, t_token *token)
// {
// 	t_fragment	*fragment;

// 	fragment = malloc(sizeof(fragment));
// 	if (!fragment)
// 		return (perror("malloc: close_double_quote"), 1);
	
// }

int	fragment_double_quote(char *line, t_token *token, size_t *i)
{
	char		*match;

	match = ft_strchr(&line[*i + 1], '\"');
	if (!match)
		return (perror("unclosed double quote"), 1);
	if (match == &line[*i + 1])
		return (0);
	token->fragments[token->fragment_count].start = *i + 1;
	token->fragments[token->fragment_count].end = *i + 1
		+ (match - &line[*i] - 1);
	token->fragments[token->fragment_count].type = DOUBLE;
	token->fragment_count += 1;
	return (0);
}

int	fragment_single_quote(char *line, t_token *token, size_t *i)
{
	char		*match;

	match = ft_strchr(&line[*i + 1], '\'');
	if (!match)
		return (perror("unclosed single quote"), 1);
	if (match == &line[*i + 1])
		return (0);
	token->fragments[token->fragment_count].start = *i + 1;
	token->fragments[token->fragment_count].end = *i + 1
		+ (match - &line[*i] - 1);
	token->fragments[token->fragment_count].type = SINGLE;
	token->fragment_count += 1;
	return (0);
}

size_t	len_to_quote_or_delimiter(char *line, size_t i, char **operators)
{
	size_t	len;
	size_t	op;

	len = 0;
	while (line[len])
	{
		op = 0;
		if (line[len] == ' '|| line[len] == '	'
			|| line[len] == '\'' || line[len] == '\"')
				return (len);
		while (operators[op])
		{
			if (!ft_strncmp(&line[len], operators[op], ft_strlen(operators[op])))
				return (len);
			op++;
		}
		len++;
	}
	return (len);
}

int	fragment_unquoted(char *line, t_token *token, size_t *i, char **operators)
{
	size_t	unquoted_len;

	unquoted_len = len_to_quote_or_delimiter(line, *i, operators);
	token->fragments[token->fragment_count].start = *i;
	token->fragments[token->fragment_count].end = *i + unquoted_len - 1;
	token->fragments[token->fragment_count].type = UNQUOTED;
	token->fragment_count += 1;
	return (0);
}

int	handle_fragments(char *line, char **operators, t_token *token, size_t *i)
{
	while(line[*i])
	{
		if (line[*i] == '\"')
		{
			if (fragment_double_quote(line, token, i))
				return (1);
		}
		else if (line[*i] == '\'')
		{
			if (fragment_single_quote(line, token, i))
				return (1);
		}
		else
		{
			if (fragment_unquoted(line, token, i, operators))
				return (1);
		}
	}
	return (0);
}

int	handle_word(t_list **head, char *line, char **operators, size_t *i)
{
	t_token		*token;
	size_t		word_len;
	t_fragment	*fragments;

	skip_blank(line, i);
	token = create_token();
	if (!token)
		return (perror("malloc: create_token"), 1);
	token->options |= WORD;
	word_len = len_to_delimiter(&line[*i], operators);
	if (word_len == 0)
		return (free(token), 0);
	token->fragments = malloc(sizeof(t_fragment) * ((word_len / 2) + 1));
	if (!fragments)
		return (free(token), perror("malloc: handle_word"), 1);
	if (handle_fragments(line, operators, token, i))
		return (free(token), free(fragments), 1);
	// if (add_token(head, token))
	// 	return (free(token), perror("malloc: handle_word"), 1);
	*i += word_len;
	return (0);
}

static t_list	*tokenize(char *line, char **operators)
{
	t_list	*head;
	size_t	i;

	i = 0;
	head = NULL;
	while (line[i])
	{
		if (handle_operator(&head, line, operators, &i))
			return (NULL);
		if (handle_word(&head, line, operators, &i))
			return (NULL);
	}
	return (head);
}

void	print_string(void *ptr)
{
	char	*str;

	str = (char *)ptr;
	printf("%s$\n", str);
}

void	free_str(void *ptr)
{
	free(ptr);
}

t_btree	*create_cmds_tree(char *line, char **operators)
{
	// t_btree	*cmds_tree;
	t_list	*line_list;

	line_list = tokenize(line, operators);
	if (!line_list)
		return (ft_lstclear(&line_list, free_str), perror("split_line failed"), NULL);
	ft_lstiter(line_list, print_string);
	// ft_lstnodeiter(line_list, trim_spaces);
	// cmds_tree = create_tree(line_list);
	// print_line_arr(line_list);
	ft_lstclear(&line_list, free_str);
	return (NULL);
	// return (cmds_tree);
}
