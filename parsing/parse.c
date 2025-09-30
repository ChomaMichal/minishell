#include "minishell.h"
// x &= ~(1 << 2)
// 000101
// 111011
//=000001

// DON't FORGET FUNCHECK

// #include <fcntl.h>
// void	signal_handler(int sig)
// {
// 	int fd = open("test", O_RDWR);
// 	write(fd, "sig recieved\n", 13);
// 	exit(1);
// 	// printf("sig recieved\n");
// }

// What if we have 2 bits of 2, and we want to check the 1 bit that is to the left?
// we read the one to the right first, which is an incorrect result.
// when calling it for token types, this function only works up to bit 8 (CLOSE_PAREN). Bigger is undefined.
//		||
//		||
//		\/
int	btoindex(int options)
{
	int	i;

	i = 0;
	while (!((options >> i) & 1))
		i++;
	return (i);
}

int	print_fragment_str(char *line, t_token *token, size_t fragment_i)
{
	char	*fragment_str;
	
	fragment_str = ft_substr(line, token->fragments[fragment_i].start,
		token->fragments[fragment_i].end - token->fragments[fragment_i].start + 1);
	if (!fragment_str)
		return (1);
	ft_printf(1, "expanded (%s) ", fragment_str);
	free(fragment_str);
	return (0);
}

void	del_token(void *ptr)
{
	free(((t_token *)ptr)->fragments);
	free(((t_token *)ptr)->str);
	free(ptr);
}

void	del_tokens(t_list *tokens)
{
	ft_lstclear(&tokens, del_token);
}

char	*create_env_var_value(char *str, size_t *start)
{
	size_t	j;
	char	*key;
	char	*value;

	j = 0;
	if (str[j] == '$')
		return (*start += 1, ft_strdup("$$"));
	if (str[j] == 0 || (!ft_isalpha(str[j]) && str[j] != '_'))
		return (ft_strdup("$"));
	while (ft_isalnum(str[j]) || str[j] == '_')
		j++;
	*start += j;
	key = ft_substr(str, 0, j);
	if (!key)
		return (NULL);
	value = getenv(key);
	free(key);
	if (!value)
		return (ft_strdup(""));
	value = ft_strdup(value);
	return (value);
}

int	append_substr(t_list *target_node, char *str, int free_second_str)
{
	char	*tmp;

	tmp = ft_strjoin(target_node->token->str, str);
	free(target_node->token->str);
	if (free_second_str)
		free(str);
	if (!tmp)
		return (1);
	target_node->token->str = tmp;
	return (0);
}

char	*safe_strjoin(char **str1, char *str2, int free_second_str)
{
	char	*tmp;

	tmp = ft_strjoin(*str1, str2);
	free(*str1);
	if (free_second_str)
		free(str2);
	if (!tmp)
		return (NULL);
	*str1 = tmp;
	return (*str1);
}

int	expand_double_quoted_fragment(char *fragment_str, t_list *target_node)
{
	char	*env_var_value;
	size_t	start;
	size_t	i;

	start = 0;
	i = 0;
	while (fragment_str[i])
	{
		if (fragment_str[i] == '$')
		{
			fragment_str[i] = 0;
			if (append_substr(target_node, &fragment_str[start], 0))
				return (1);
			start = i + 1;
			env_var_value = create_env_var_value(&fragment_str[start], &start);
			if (!env_var_value)
				return (1);
			if (append_substr(target_node, env_var_value, 1))
				return (1);
			i = start;
		}
		else
			i++;
	}
	return (append_substr(target_node, &fragment_str[start], 0));
}

char	*create_expanded_fragment(char *fragment_str, char **target_str)
{
	char	*env_var_value;
	size_t	start;
	size_t	i;

	start = 0;
	i = 0;
	while (fragment_str[i])
	{
		if (fragment_str[i] == '$')
		{
			fragment_str[i] = 0;
			if (!safe_strjoin(target_str, &fragment_str[start], 0))
				return (NULL);
			start = i + 1;
			env_var_value = create_env_var_value(&fragment_str[start], &start);
			if (!env_var_value)
				return (NULL);
			if (!safe_strjoin(target_str, env_var_value, 1))
				return (NULL);
			i = start;
		}
		else
			i++;
	}
	return (safe_strjoin(target_str, &fragment_str[start], 0));
}

int	create_field_split_tokens(t_list **head, char **split_arr)
{
	t_token	*new_token;
	size_t	arr_counter;

	arr_counter = 0;
	while (split_arr[arr_counter])
	{
		new_token = create_token();
		if (!new_token)
			return (1);
		new_token->fragment_count = 1;
		new_token->fragments = NULL;
		new_token->options |= WORD;
		new_token->options |= EXPANDED_WORD;
		new_token->str = ft_strdup(split_arr[arr_counter]);
		if (!new_token->str)
			return (free(new_token), 1);
		if (add_token(head, new_token))
			return (free(new_token->str), free(new_token), 1);
		arr_counter++;
	}
	return (0);
}

// int	handle_splitter_expansion(t_list **target_node)
// {
// 	t_token	*new_token;

// 	new_token = create_token();
// 	if (!new_token)
// 		return (1);
// 	new_token->fragment_count = 1;
// 	new_token->fragments = ;
// 	new_token
// }

int	insert_field_split_tokens(t_list **field_split_head, t_list *token_node, t_list **target_node, size_t fragment_i)
{
	t_list	*tmp;

	// NEXT CHECK MEANS THE EXPANDED STRING RESULTED IN ONLY SPACES (I ONLY ENTER THIS FUNCTION IF THE EXPANSION HAS SPACES),
	// IN THIS CASE WE NEED TO HANDLE IT AS A SPLITTER OF THE WORD.
	if (!*field_split_head)
		return (0);
	tmp = (token_node)->next;
	if (!(token_node)->token->fragments[fragment_i].starts_with_space
	|| fragment_i == 0)
	{
		(token_node)->next = (*field_split_head)->next;
		if (append_substr(*target_node, (*field_split_head)->token->str, 1))
			return (1);
		(free((*field_split_head)->token), free(*field_split_head));
		*field_split_head = (token_node)->next;
	}
	else if ((token_node)->token->fragments[fragment_i].starts_with_space)
	{
		(token_node)->next = *field_split_head;
	}
	*target_node = ft_lstlast(*field_split_head);
	// printf("target_node now is (%s)\n", ((*target_node)->token->str));
	ft_lstlast(*field_split_head)->next = tmp;
	return (0);
}

int	field_split(char *expanded, t_list *token_node, t_list **target_node, size_t fragment_i)
{
	t_list	*head;
	char	**split_arr;

	head = NULL;
	split_arr = ft_split(expanded, " 	");
	if (!split_arr)
		return (1);
	// printf("doing field split on (%s):\n", expanded);
	// for (int i = 0; split_arr[i]; i++)
	// 	printf("		%i:(%s)\n",i , split_arr[i]);
	if (create_field_split_tokens(&head, split_arr))
		return (del_tokens(head), free_split(split_arr), 1);
	free_split(split_arr);
	if (insert_field_split_tokens(&head, token_node, target_node, fragment_i))
		return (del_tokens(head), 1);
	printf("nodes are now:");
	for (t_list *cur = token_node; cur; cur = cur->next)
	{
		printf("(%s)->", cur->token->str);
	}
	printf("\n");
	return (0);
}

int	expand_unquoted_fragment(char *fragment_str, t_list *token_node, t_list **target_node, size_t i)
{
	t_token	*token;
	char	*expanded;

	token = token_node->token;
	expanded = ft_strdup("");
	if (!expanded)
		return (1);
	expanded = create_expanded_fragment(fragment_str, &expanded);
	if (!expanded)
		return (1);
	if (!ft_strchr(expanded, ' ') && !ft_strchr(expanded, '	'))
		return (append_substr(*target_node, expanded, 1), 0);
	// NEED TO SEE IF I HAVE SPACE ONLY STRING!! HOW TO HANDLE IT?
	token->fragments[i].starts_with_space = (ft_strchr(" 	", expanded[0])
		!= NULL);
	token->fragments[i].ends_with_space = (*expanded
		&& ft_strchr(" 	", expanded[ft_strlen(expanded) - 1]));
	if (field_split(expanded, token_node, target_node, i))
		return (free(expanded), 1);
	return (free(expanded), 0);
}

int	expand_single_quoted_fragment(char *fragment_str, t_list *target_node)
{
	char	*tmp;

	tmp = ft_strjoin(target_node->token->str, fragment_str);
	if (!tmp)
		return (1);
	free(target_node->token->str);
	target_node->token->str = tmp;
	return (0);
}

int	expand_fragment(char *line, t_list *token_node, t_list **target_node, size_t i)
{
	t_token	*token;
	int		res;
	char	*fragment_str;

	token = token_node->token;
	fragment_str = ft_substr(line, token->fragments[i].start,
		token->fragments[i].end - token->fragments[i].start + 1);
	// while ((*target_node) &&(*target_node)->token->options & EXPANDED_WORD)
		// *target_node = (*target_node)->next;
	if (!fragment_str)
		return (1);
	if (token->fragments[i].type == SINGLE)
		res = expand_single_quoted_fragment(fragment_str, *target_node);
	else if (token->fragments[i].type == DOUBLE)
		res = expand_double_quoted_fragment(fragment_str, *target_node);
	else if (token->fragments[i].type == UNQUOTED)
		res = expand_unquoted_fragment(fragment_str, token_node, target_node, i);
	free(fragment_str);
	return (res);
}

int	expand_word(char *line, t_list *target_node)
{
	size_t	fragment_i;
	t_list	*token_node;

	fragment_i = 0;
	token_node = target_node;
	free(token_node->token->str);
	token_node->token->str = ft_strdup("");
	if (!token_node->token->str)
		return (1);
	while (fragment_i < token_node->token->fragment_count)
	{
		if (token_node->token->fragments[fragment_i].type == EMPTY)
		{
			fragment_i++;
			continue ;
		}
		// print_fragment_str(line, token_node->token, fragment_i);
		if(expand_fragment(line, token_node, &target_node, fragment_i))
			return (1);
		fragment_i++;
	}
	// ft_printf(1, "to (%s)\n", token_node->token->str);
	if (!*token_node->token->str && token_node->token->fragments && token_node->token->fragments[0].type == UNQUOTED && token_node->token->fragment_count == 1)
		return (token_node->token->options |= EMPTY_WORD, 0);
	return (0);
}

int	expand(t_list *head, char *line)
{
	t_list	*node;

	node = head;
	while (node)
	{
		if (node->token->options & WORD
			&& !(node->token->options & EXPANDED_WORD))
			{
				if (expand_word(line, node))
					return (ft_printf(2, "malloc failed in expand_token() token: (%s)\n", node->token->str), 1);
			}
		node = node->next;
	}
	return (0);
}

t_btree	*create_exec_tree(char *line, char **operators)
{
	t_btree		*exec_tree;
	t_list		*head;
	t_print_d	data;

	data.line = line;
	data.operators = operators;
	head = tokenize(line, operators);
	if (!head)
		return (ft_printf(2, "minishell: tokenize() returned NULL\n"), NULL);
	if (validate_tokens(head, operators))
		return (ft_printf(2, "minishell: validate_tokens() failed\n"), del_tokens(head), NULL);
	if (expand(head, line))
		return (ft_printf(2, "minishell: parse() failed\n"), del_tokens(head), NULL);
	ft_lstiter(head, print_tokens, &data);
	exec_tree = create_tree(head);
	del_tokens(head);
	return (exec_tree);
}
