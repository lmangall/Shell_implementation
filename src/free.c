

#include "../lib/libft/src/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include "../include/shell.h"
#include "../include/node.h"
#include "../include/executor.h"
#include "../include/builtins.h"
#include "../include/free.h"


// void free_command_str(struct node_s *node)
// {
//     if (node == NULL)
//     {
//         return;
//     }

//     if (node->type == NODE_COMMAND)
//     {
//         free(node->str);
//     }

//     struct node_s *child = node->first_child;
//     while (child != NULL)
//     {
//         free_command_str(child);
//         child = child->next_sibling;
//     }
// }

// void free_master_command_str(struct node_type_master *master_node)
// {
//     if (master_node == NULL)
//     {
//         return;
//     }

//     for (int i = 0; i < master_node->nbr_root_nodes; i++)
//     {
//         free_command_str(master_node->root_nodes[i]);
//     }
// }



void free_argv(int argc, char **argv)
{
	if(!argc)
		return;
	while(argc--)
	free(argv[argc]);
}
