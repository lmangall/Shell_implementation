#ifndef NODE_H
#define NODE_H

enum node_type_e
{
    NODE_COMMAND,           /* simple command */
    NODE_VAR,               /* variable name (or simply, a word) */
};

struct node_s
{
    enum   node_type_e type;    /* type of this node */
    char	*str;        /* value of this node */
    int    children;            /* number of child nodes */
    struct node_s *first_child; /* first child node */
    struct node_s *next_sibling, *prev_sibling;
                                /*
                                 * if this is a child node, keep
                                 * pointers to prev/next siblings
                                 */
};
/**
 * @brief  creates a new node and sets it's type field.
 */
struct  node_s *new_node(enum node_type_e type);
/**
 * @brief expands the AST of a simple command by adding a new child node
 *  and incrementing the root node's children field. 
 * If the root node has no children,
 * the new child is assigned to the first_child field of the root node. 
 * Otherwise, the child is appended to the end of the children's list.
 */
void    add_child_node(struct node_s *parent, struct node_s *child);
/**
 * @brief 
 * 
 * @param type 
 * @return struct node_s* 
 */
void    free_node_tree(struct node_s *node);
/**
 * @brief sets a node's value to the given string. 
 * It copies the string to a newly allocated memory space, 
 * then sets the val_type and val.str fields accordingly. 
 */
void    set_node_str(struct node_s *node, char *val);
#endif