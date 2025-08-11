#include "minishell.h"

int	has_bigger_index(void *cur_item, void *inserted_item)
{
	// printf("inserted_item's index (%s)\ncur_item's index (%s)",
	// 	((t_bitem *)inserted_item)->str,
	// 	((t_bitem *)cur_item)->str);
	if (((t_bitem *)inserted_item)->index < ((t_bitem *)cur_item)->index)
		return (1);
	else
		return (-1);
}

void	print_node_info(void *node)
{
	t_btree	*left;
	t_btree	*right;
	t_btree	*node_data;
	t_bitem	*item;

	node_data = (t_btree *)node;
	left = node_data->left;
	right = node_data->right;
	item = node_data->item;
	printf("node (%d)(%s) children are\n", item->index, item->str);
	if (left)
		printf("\tlefft:(%d)(%s)\n", left->item->index, left->item->str);
	if (right)
		printf("\tright:(%d)(%s)\n", right->item->index, right->item->str);
}

t_bitem	*create_item(char *str, int index)
{
	t_bitem	*item;

	item = malloc(sizeof(t_bitem));
	if (!item)
		return (NULL);
	item->str = ft_strdup(str);
	if (!item->str)
		return (free(item), NULL);
	item->index = index;
	return (item);
}

void	free_item(t_bitem *item)
{
	free(item->str);
	free(item);
}

/*
	final test tree:

            ___"|"____
	       |          |
	  ___"&&"__     "wc -l"
	 |         |
    "ls -l"  "grep .c"
*/

t_btree	*create_cmds_tree_test(t_bitem *item[5])
{
	t_btree *cmds_tree;

	cmds_tree = NULL;
	item[0] = create_item("|", 3);			// Function btree_insert_data compares the indices of items
	item[1] = create_item("&&", 2);			// 	and puts lower index to left, and equal or higher
	item[2] = create_item("ls -l", 1);		//	to right. hence similar indices 2 and 3.
	item[3] = create_item("grep .c", 2);
	item[4] = create_item("wc -l", 3);
	for (int i = 0; i < 5; i++)
		btree_insert_data(&cmds_tree, item[i], has_bigger_index);
	return (cmds_tree);
}

void	free_btree_node(void *ptr)
{
	free(ptr);
}

// Currently there's nothing in the tree's nodes to
//	indicate what is operator and what is command.
int	main(void)
{
	char	*line;
	t_btree	*cmds_tree;
	t_bitem	*item[5];

	while (1)
	{
		line = readline("josef-shell-$ ");
		if (!line)
			break ;
		if (line[0])
			add_history(line);
		rl_on_new_line();
		// cmds_tree = create_cmds_tree(line);
		cmds_tree = create_cmds_tree_test(item);			// Custom tree function for testing
		btree_apply_prefix(cmds_tree, print_node_info);		// Print all nodes' info
		btree_apply_suffix(cmds_tree, free_btree_node);		// Free btree nodes
		for (int i = 0; i < 5; i++)							// Free custom items
			free_item(item[i]);
		free(line);
	}
	printf("exit\n");
	return (0);
}
