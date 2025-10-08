#include "libft.h"
#include <stdio.h>

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

void	print_str_and_index(void *item)
{
	printf("item (%d) is: (%s)\n",
		((t_bitem *)item)->index,
		((t_bitem *)item)->str);
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

// void	print_node_info(void *node)
// {
// 	t_btree	*left;
// 	t_btree	*right;
// 	t_btree	*node_data;
// 	t_bitem	*item;

// 	node_data = (t_btree *)node;
// 	left = node_data->left;
// 	right = node_data->right;
// 	item = node_data->item;
// 	printf("node (%d)(%s) children are\n", item->index, item->str);
// 	if (left)
// 		printf("\tlefft:(%d)(%s)\n", left->item->index, left->item->str);
// 	if (right)
// 		printf("\tright:(%d)(%s)\n", right->item->index, right->item->str);
// }

// void	delete_bnode(t_btree *node)
// {

// }

// TODO: Check inserting

int main(void)
{
	t_btree	*root;
	t_bitem	*items[5];

	// items = malloc(sizeof(t_bitem *) * 5);
	// if (!items)
	// 	return (1);
	items[0] = create_item("is", 20);
	items[1] = create_item("hello, ", 0);
	items[2] = create_item("name", 6);
	items[3] = create_item("my", 4);
	items[4] = create_item("josef", 25);
	// printf("%s == %zi\n", node->str, (size_t)node->index);
	root = NULL;
	// new_node = btree_create_node("hi");
	int i = -1;
	while (++i < 5)
	{
		btree_insert_data(&root, items[i], has_bigger_index);
		// printf("added (%s)(%d) to the tree\n", items[i]->str, items[i]->index);
	}
	btree_apply_prefix(root, print_node_info);
	i = -1;
	while (++i < 5)
		free_item(items[i]);
	return (0);
}
