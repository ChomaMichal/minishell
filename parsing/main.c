#include "minishell.h"

void	set_operators(char **operators)
{
	operators[0] = "||";
	operators[1] = "|";
	operators[2] = "&&";
	operators[3] = ">>";
	operators[4] = ">";
	operators[5] = "<<";
	operators[6] = "<";
	operators[7] = "(";
	operators[8] = ")";
	operators[9] = NULL;
}

void	delete_bnode(void *ptr)
{
	t_btree	*node;

	node = (t_btree *)ptr;
	free_split(node->cmd_argv);
	free(node);
}

int	main(void)
{
	char	*line;
	t_btree	*cmds_tree;
	char	*operators[10];

	set_operators(operators);
	while (1)
	{
		line = readline("josef-shell-$ ");
		if (!line)
			break ;
		if (line[0])
		{
			add_history(line);
			rl_on_new_line();
			cmds_tree = create_exec_tree(line, operators);
			if (cmds_tree)
			{
				print_btree_pyramid(cmds_tree);
				btree_apply_suffix(cmds_tree, delete_bnode);
			// 	// execute(cmds_tree, env);
			}
		}
		free(line);
	}
	printf("exit\n");
	return (0);
}
