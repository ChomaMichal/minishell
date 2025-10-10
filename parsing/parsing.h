#ifndef PARSE_H
# define PARSE_H


#include "../minishell.h"
#include <stddef.h>
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
# define EXPANDED_WORD (1 << 15)

// FRAGMENT TYPES
# define SINGLE 1
# define DOUBLE 2
# define UNQUOTED 3
# define EMPTY 4

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
	char				*str;
	int					options;
	size_t				fragment_count;
	t_fragment			*fragments;
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

/* ft_lst */
t_list	*ft_lstnew(t_token *token);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
t_list	*ft_lstlast(t_list *lst);

/* tokenize_utils.c */
int		is_blank(char c);
void	skip_blank(char *line, size_t *i);
size_t	len_to_delimiter(char *line, char **operators);
size_t	len_to_quote_or_delimiter(char *line, char **operators);
size_t	len_to_unquoted_delimiter(char *line, char **operators);

/* TEMP print.c */
// void	print_tokens(t_print_d *data);
void	ft_lstiter(t_list *lst, void (*f)(t_print_d *), t_print_d *data);

/* parse.c */
t_btree	*create_exec_tree(char *line, char **operators);
int		btoindex(int options);

/* validate_tokens.c */
int		validate_tokens(t_list *tokens, char **operators);
	
/* parse_utils.c */
int		create_operators(char ***operators);
void	free_split(char **arr);
int		is_operator(char *cur_char, char **operators);
void	print_line_arr(char **line_arr);
void	set_len_and_op(char *line_start, char **operators,
	size_t *substr_len, int *op_index);

/* tokenize.c */
int		add_token(t_list **head, t_token *token);
t_token	*create_token(void);
t_list	*tokenize(char *line, char **operators);

/* fragment.c */
int		fragment_double_quote(char *line, t_token *token, size_t *i);
int		fragment_single_quote(char *line, t_token *token, size_t *i);
int		fragment_unquoted(char *line, t_token *token, size_t *i, char **operators);
int		handle_fragments(char *line, char **operators, t_token *token, size_t *i);

/* execution_tree.c */
t_btree	*create_tree(t_list *tokens);

#endif
