# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/09 18:29:39 by lmangall          #+#    #+#              #
#    Updated: 2023/08/10 12:00:58 by lmangall         ###   ########.fr        #
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

OBJS = $(patsubst %.c, $(OBJDIR)/%.o, $(SRCS))

CC = gcc
CC = gcc
CFLAGS = -I$(INCDIR)
# //add back -Werror -Wall -Wextra 
NAME = minishell

all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -C $(LIBFTDIR)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L$(LIBFTDIR) -lft

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
