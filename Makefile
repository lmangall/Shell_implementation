# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/09 18:29:39 by lmangall          #+#    #+#              #
#    Updated: 2023/08/24 11:58:01 by lmangall         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
SRCDIR = src
INCDIR = include
LIBFTDIR = lib/libft
OBJDIR = obj

SRCS = lexer.c \
		parser.c \
		executor.c \
		source.c \
		main.c \
		node.c \
		errors.c \
		expander.c \
		vars.c \

OBJS = $(patsubst %.c, $(OBJDIR)/%.o, $(SRCS))

CC = gcc
CFLAGS = -I$(INCDIR)
# CFLAGS = -I$(INCDIR) -Wall -Wextra -Werror
READLINE = -L./lib/libft -lft -lreadline
READLINE_INC = -I /Users/$(USER)/.brew/opt/readline/include
#READLINE = -L /Users/$(USER)/.brew/opt/readline/lib
# //add back -Werror -Wall -Wextra 
NAME = minishell

all: install_readline $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -C $(LIBFTDIR)
	@$(CC) $(OBJS) $(READLINE) $(READLINE_INC) $(CFLAGS) -L$(LIBFTDIR) -lft -o $(NAME)
	@echo "\033[32mCompilation succeeded!\033[0m"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR) # Create the object directory if it doesn't exist
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(MAKE) -C $(LIBFTDIR) clean
	@$(RM) -r $(OBJDIR) # Remove the object directory

fclean: clean
	@$(MAKE) -C $(LIBFTDIR) fclean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

install_readline:
	apt-get install libreadline-dev
	# add sudo to line above

