#ifndef PARSE_H
# define PARSE_H

# include "../minishell.h"
# include <dirent.h>

// TOKEN OPTIONS
# define OR (1 << 0)
# define PIPE (1 << 1)
# define AND (1 << 2)
# define OUTPUT_REDIR_APPEND (1 << 3)
# define OUTPUT_REDIR (1 << 4)
# define HERE_DOC (1 << 5)
# define INPUT_REDIR (1 << 6)
# define OPEN_PARENTHESIS (1 << 7)
# define CLOSE_PARENTHESIS (1 << 8)

# define REDIR_OP (1 << 9)
# define PARENTHESIS (1 << 10)

# define WORD (1 << 11)
# define OPERATOR (1 << 12)
# define BUILTIN (1 << 13)
# define EMPTY_WORD (1 << 14)
# define REDIR_WORD (1 << 15)
# define HERE_DEL_WORD (1 << 16)
# define EXPANDED_WORD (1 << 17)

// FRAGMENT TYPES
# define SINGLE 1
# define DOUBLE 2
# define UNQUOTED 3
# define EMPTY 4

static DIR	*ft_opendir(char *path, DIR **directory)
{
	*directory = opendir(path);
	return (*directory);
}

typedef struct	s_fragment
{
	size_t	start;
	size_t	end;
	int		type;
	int		starts_with_space;
	int		ends_with_space;
}	t_fragment;

typedef struct	s_token
{
	char		*str;
	char		*redir_word;
	int			options;
	size_t		fragment_count;
	t_fragment	*fragments;
	size_t		fragment_i;
	int			*stars_arr;
}	t_token;

typedef struct	s_list
{
	t_token			*token;
	struct s_list	*next;
}	t_list;

typedef	struct	s_print_d
{
	char	**operators;
	t_token	*token;
	char	*line;
}	t_print_d;

typedef struct s_expansion_data
{
	t_parse_data	*d;
	t_list			*token_node;
	t_list			*target_node;
	size_t			i;
	int				is_redir_word;
}	t_expansion_data;

/* ft_lst */
void	ft_lstiter(t_list *lst, void (*f)(t_print_d *), t_print_d *data); // DELETE THIS <<
t_list	*ft_lstnew(t_token *token);
void	ft_lstadd_back(t_list **lst, t_list *nw);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
t_list	*ft_lstlast(t_list *lst);

/* parse.c */
t_btree	*parse(t_parse_data *d);
int		btoindex(int options);

/* tokenize.c */
t_list	*tokenize(t_parse_data *d);
/* utils */
size_t	count_fragments(char *line, ssize_t word_len, char **operators);
void	skip_spaces(char *line, size_t *i);
ssize_t	len_to_quote_or_delimiter(char *line, char **operators);
ssize_t	len_to_unquoted_delimiter(char *line, char **operators);
int		add_token(t_list **head, t_token *token);
t_token	*create_token(int is_redir_word);

/* validate_tokens.c */
int		validate_tokens(t_list *tokens, char **operators);
/* utils */
int		wrong_first_token(t_list *cur, char **operators);
int		validate_word(t_list *cur);
int		validate_open_paren(t_list *cur, long *paren_count, char **operators);
int		validate_close_paren(t_list *cur, long *paren_count);

/* expand.c */
int		expand(t_parse_data *d);

/* expand_fragment.c */
int		expand_fragment(t_expansion_data *xd);
/* utils */
int		mark_stars(t_list *target_node, size_t target_len, char *tmp);
char	*create_var_val(char *str, size_t *start, t_expansion_data *xd);
char	*safe_strjoin(char **str1, char *str2, int free_second_str);
int		append_substr(t_list *target_node, char *str, int free_second_str, int double_quote);

/* field_split.c */
int		field_split(char *fragment_str, char *expanded, t_expansion_data *xd);
int		create_split_tokens(t_list **head, char **split_arr,
	t_expansion_data *xd);
/* utils */
int		create_split_tokens(t_list **head, char **split_arr, t_expansion_data *xd);
int		insert_split_tokens(t_list **field_split_head, t_list *token_node,
	t_list **target_node, size_t fragment_i);

/* filename_expansion.c */
int		filename_expansion(t_list **head, char *line);

/* execution_tree.c */
t_btree	*create_exec_tree(t_parse_data *d);

/* redirections.c */
void	clear_redir_list(t_redir_list **redir_list);
void	clear_here_list(t_here_doc **here_list);
int		create_redirections(t_list **tokens, t_btree *bnode, t_here_doc **here_list);
int		open_write_here_docs(t_here_doc **here_list, t_parse_data *d);

/* parsing_utils.c */
void	del_tokens(t_list *tokens);
int		is_operator(char *cur_char, char **operators);
void	set_len_and_op(char *line_start, char **operators,
	size_t *substr_len, int *op_index);

/* fragment.c */
int		handle_fragments(char *line, char **operators, t_token *token, size_t *i);

#endif
