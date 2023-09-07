#include "../../lib/libft/src/libft.h"
#include "../../include/builtins.h"
#include "../../include/parser.h"
#include "../../include/expander.h"
#include "../../include/node.h"
#include "../../include/parser.h"

void do_echo_builtin(char **argv)
{
    int print_newline = 1; // 1 entspricht true, 0 entspricht false
    int i = 1;

    // it checks for -n and if it finds it, it sets print_newline to 0
    // if it finds after that -nn or -nnnnn it leaves print_newline to 0 and it will not print -nn or -nnnnn
    // so basically, it will print everything after the first -n except following -nn -nnnn and so on.
    while (argv[i] && ft_strncmp(argv[i], "-n", 2) == 0) {
        print_newline = 0;
        i++;
    }

    while (argv[i]) {
        ft_putstr_fd(argv[i], 1);

        if (argv[i + 1]) {
            ft_putstr_fd(" ", 1);
        }

        i++;    
    }

    if (print_newline) {
        ft_putstr_fd("\n", 1);
    }

    // return EXIT_SUCCESS;
    
}