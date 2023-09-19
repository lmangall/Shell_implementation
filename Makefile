# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/09 18:29:39 by lmangall          #+#    #+#              #
#    Updated: 2023/09/19 11:22:15 by lmangall         ###   ########.fr        #
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
		main.c \
		node.c \
		errors.c \
		expander.c \
		vars.c \
		signals.c \
		free.c \
		pipe.c \
		redirect.c \
		builtins/utils.c \
		builtins/cd.c \
		builtins/echo.c  \
		builtins/pwd.c \
		builtins/env.c \
		extra.c

OBJS = $(patsubst %.c, $(OBJDIR)/%.o, $(SRCS))

CC = gcc
CFLAGS = -I$(INCDIR) -Wall -Wextra -Werror
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
	@mkdir -p $(dir $@) # Create the subdirectories
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

