#include "../lib/libft/src/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include "../include/shell.h"
#include "../include/pipe.h"
#include "../include/redirect.h"
#include "../include/node.h"
#include "../include/executor.h"
#include "../include/builtins.h"
#include "../include/free.h"