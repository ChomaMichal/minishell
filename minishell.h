#ifndef MINISHELL_H
# define MINISHELL_H

//global
extern volatile int sgnl; 

typedef struct s_list t_list;

//this contains ids of the child processes that are currently running
typedef struct s_ids
{
	struct s_ids	*next;
	int				pid;
}	t_ids;

typedef struct s_data
{
	char			**env;
	int				rt;
	t_ids			*pids;
	struct s_btree	*head;
	int				subshell;
}	t_data;

typedef enum	e_bnode_type
{
	BNODE_COMMAND,
	BNODE_PIPE,
	BNODE_AND,
	BNODE_OR,
	BNODE_SUBSHELL
}	t_bnode_type;

typedef enum	e_redir_type
{
	REDIR_OUT,
	REDIR_OUT_APP,
	REDIR_IN,
	REDIR_HERE
}	t_redir_type;

typedef struct	s_redir_list
{
	t_redir_type		type;
	char				*file_name;
	struct s_redir_list	*next;
}	t_redir_list;

typedef struct	s_btree
{
	struct s_btree	*left;
	struct s_btree	*right;
	char			**cmd_argv;
	t_bnode_type	type;
	t_redir_list	*redir_list;
	char			*ambig;
	int				empty_cmd;
}	t_btree;

typedef struct	s_here_doc
{
	char				*delimiter;
	t_btree				*bnode;
	char				*file_name;
	struct s_here_doc	*next;
}	t_here_doc;

typedef struct	s_parse_data
{
	char			*line;
	char			*operators[10];
	t_list			*tokens;
	unsigned long	line_count;
	t_here_doc		*here_list;
	t_btree			*exec_tree;
	t_data			*data;
}	t_parse_data;

# include "libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>


/* DEV print.c */
void	btree_apply_prefix(t_btree *root, void (*applyf)(void *));
void	btree_apply_suffix(t_btree *root, void (*applyf)(void *));
void	print_btree_pyramid(const t_btree *node);

/* parsing/parsing.c */
t_btree	*parse(t_parse_data *d);
/* parsing/redirections.c */
void	clear_redir_list(t_redir_list **redir_list);
void	clear_here_list(t_here_doc **here_list);

// int		btoindex(int options);

// execute
void	execute(t_btree *tree, t_data *data);

//utils
int		wait_and_get_exit_value(t_ids *list);
void	delete_bnode(void *ptr);
int		ft_exit(t_data *data, char *arg);
void	set_operators(char **operators);
void	delete_bnode(void *ptr);
void	delete_bnode_unlink(void *ptr);
void	print_env(char **envp);
void	cleanup(t_data *data);
void	clear_redir_list_unlink(t_redir_list **redir_list);
int		init_main(t_data *data, char **envp, t_parse_data *d);

#endif
