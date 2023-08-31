#include "../../lib/libft/src/libft.h"
#include "../../include/builtins.h"
#include "../../include/parser.h"
#include "../../include/expander.h"
#include "../../include/node.h"
#include "../../include/parser.h"

int contains_echo(struct node_s *node) {
    int i = 0;

    while (node->str[i] != '\0') {
        if (ft_strncmp(node->str + i, "echo", 4) == 0) {
            return 1;
        }
        i++;
    }
    
    return 0;
}

#if 0
int do_echo_builtin(struct node_s *node) {
    int print_newline = 0;
    struct node_s *arg_node = node;

    if (arg_node && strcmp(arg_node->str, "echo") != 0) {
        return EXIT_FAILURE;
    }

    arg_node = arg_node->next_sibling;
    if (arg_node && strcmp(arg_node->str, "-n") == 0) {
        print_newline = 1;
        arg_node = arg_node->next_sibling;
    }

    while (arg_node) {
        printf("%s", arg_node->str);

        if (arg_node->next_sibling) {
            printf(" ");
        }

        arg_node = arg_node->next_sibling;
    }

    if (print_newline) {
        printf("\n");
    }

    return EXIT_SUCCESS;
}
#endif

int do_echo_builtin(struct node_s *node) {
    int print_newline = 1; // 1 entspricht true, 0 entspricht false
    struct node_s *arg_node = node;

    if (arg_node && strcmp(arg_node->str, "echo") != 0) {
        return EXIT_FAILURE;
    }

    arg_node = arg_node->next_sibling;
    if (arg_node && strcmp(arg_node->str, "-n") == 0) {
        print_newline = 0;
        arg_node = arg_node->next_sibling;
    }

    while (arg_node) {
        printf("%s", arg_node->str);

        if (arg_node->next_sibling) {
            printf(" ");
        }

        arg_node = arg_node->next_sibling;
    }

    if (print_newline) {
        printf("\n");
    }

    return EXIT_SUCCESS;
}