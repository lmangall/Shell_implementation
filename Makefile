# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/09 18:29:39 by lmangall          #+#    #+#              #
#    Updated: 2024/01/04 12:51:58 by lmangall         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
SRCDIR = src
INCDIR = include
LIBFTDIR = lib/libft
OBJDIR = obj

SRCS = parser/parser.c \
		parser/parser_operators.c \
		parser/parser_root_node.c \
		lexer_expander/lexer.c \
		lexer_expander/lexer_quotes.c \
		lexer_expander/expander.c \
		executor.c \
		main.c \
		node.c \
		errors.c \
		signals.c \
		free.c \
		pipe.c \
		redirect.c \
		builtins/builtins.c \
		builtins/cd.c \
		builtins/echo.c  \
		builtins/pwd.c \
		builtins/env.c \
		vars/export_var.c \
		vars/unset_var.c \
		vars/set_var.c \
		vars/utils_var.c \
		vars/utils_var_dev.c \
		vars/vars.c \
		extra.c

OBJS = $(patsubst %.c, $(OBJDIR)/%.o, $(SRCS))

CC = gcc
CFLAGS = -I$(INCDIR) -Wall -Wextra -Werror #-fsanitize=address
LIBS = -L$(LIBFTDIR) -lft
READLINE_LIBS = -lreadline
READLINE_INC = -I /Users/$(USER)/.brew/opt/readline/include
#READLINE = -L /Users/$(USER)/.brew/opt/readline/lib
# //add back -Werror -Wall -Wextra 
NAME = minishell

all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -C $(LIBFTDIR)
	@$(CC) $(OBJS) $(CFLAGS) $(LIBS) $(READLINE_LIBS) -o $(NAME)
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
	@$(MAKE) all READLINE_LIBS="$(READLINE_LIBS)" READLINE_INC="$(READLINE_INC)"

readline: install_readline

.PHONY: install_readline readline