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

void	print_command(t_btree *node)
{
	size_t	i;

	i = 0;
	printf("node (");
	while (node->cmd_argv[i])
	{
		printf("%s-", node->cmd_argv[i]);
		i++;
	}
	printf(")\n");
}

void	print_node(t_btree *node)
{
	if (node->type == BNODE_COMMAND)
		print_command(node);
	else if (node->type == BNODE_AND)
		printf("node (&&)\n");
	else if (node->type == BNODE_OR)
		printf("node (||)\n");
	else if (node->type == BNODE_PIPE)
		printf("node (|)\n");
	else if (node->type == BNODE_SUBSHELL)
		printf("node (())\n");

}

void	print_node_info(void *node)
{
	t_btree	*left;
	t_btree	*right;
	t_btree	*node_data;
	char	*str;

	node_data = (t_btree *)node;
	left = node_data->left;
	right = node_data->right;
	print_node(node_data);
	if (left)
	{
		printf("left: ");
		print_node(left);
	}
	if (right)
	{
		printf("right: ");
		print_node(right);
	}
	printf("\n\n");
}

// t_bitem	*create_item(char *str, int index)
// {
// 	t_bitem	*item;

// 	item = malloc(sizeof(t_bitem));
// 	if (!item)
// 		return (NULL);
// 	item->str = ft_strdup(str);
// 	if (!item->str)
// 		return (free(item), NULL);
// 	item->index = index;
// 	return (item);
// }

// void	free_item(t_bitem *item)
// {
// 	free(item->str);
// 	free(item);
// }

// t_btree	*create_cmds_tree_test(t_bitem *item[5])
// {
// 	t_btree *cmds_tree;

// 	cmds_tree = NULL;
// 	item[0] = create_item("|", 3);			// Function btree_insert_data compares the indices of items
// 	item[1] = create_item("&&", 2);			// 	and puts lower index to left, and equal or higher
// 	item[2] = create_item("ls -l", 1);		//	to right. hence similar indices 2 and 3.
// 	item[3] = create_item("grep .c", 2);
// 	item[4] = create_item("wc -l", 3);
// 	for (int i = 0; i < 5; i++)
// 		btree_insert_data(&cmds_tree, item[i], has_bigger_index);
// 	return (cmds_tree);
// }

void	free_btree_node(void *ptr)
{
	free(ptr);
}
