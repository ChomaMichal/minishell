#include "minishell.h"

/*
	final test tree:

            ___"|"____
	       |          |
	  ___"&&"__     "wc -l"
	 |         |
    "ls -l"  "grep .c"
*/

// Currently there's nothing in the tree's nodes to
//	indicate what is operator and what is command.
int	main(void)
{
	char	*line;
	t_btree	*cmds_tree;
	// t_bitem	*item[5];

	while (1)
	{
		line = readline("josef-shell-$ ");
		if (!line)
			break ;
		if (line[0])
		{
			add_history(line);
			rl_on_new_line();
			cmds_tree = create_cmds_tree(line);
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
