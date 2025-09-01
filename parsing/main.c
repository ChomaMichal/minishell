#include "minishell.h"

/*
	final test tree:

            ___"|"____
	       |          |
	  ___"&&"__     "wc -l"
	 |         |
    "ls -l"  "grep .c"
*/

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
	// (*splitter_arr)[11] = ft_strdup("{");
	// (*splitter_arr)[12] = ft_strdup("}");
	// (*splitter_arr)[13] = ft_strdup("$");
}

int	main(void)
{
	char	*line;
	t_btree	*cmds_tree;
	char	*operators[10];
	// t_bitem	*item[5];

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
			cmds_tree = create_cmds_tree(line, operators);
			// execute(cmds_tree, env);
		}
		// cmds_tree = create_cmds_tree_test(item);			// Custom tree function for testing
		// btree_apply_prefix(cmds_tree, print_node_info);		// Print all nodes' info
		// btree_apply_suffix(cmds_tree, free_btree_node);		// Free btree nodes
		// for (int i = 0; i < 5; i++)							// Free custom items
		// 	free_item(item[i]);
		free(line);
	}
	printf("exit\n");
	return (0);
}
