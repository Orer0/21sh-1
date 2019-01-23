# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/15 18:38:22 by ndubouil          #+#    #+#              #
#    Updated: 2019/01/23 03:52:27 by ndubouil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Binaries and Flags

CC		=	/usr/bin/gcc
RM		=	/bin/rm
CFLAGS	=	-Wall -Wextra -Werror -g3 #-fsanitize=address

# Directories

LIBFT	=	./libft/
ILIBFT	=	./$(LIBFT)includes/
H		=	./includes/
SRC		=	./src/
DEBUG	=	$(SRC)debug/
PARS	=	$(SRC)parsing/
LEX		=	$(PARS)lexer/
ST		=	$(PARS)syntax_tree/
AST		=	$(PARS)ast/
TK		=	$(SRC)tokens/

#  Files

HFILES	=	$(H)21sh.h														\
			$(H)lexer.h														\
			$(H)ast.h														\
			$(H)tokens.h													\
			$(H)st.h

MAIN	=	$(SRC)main.c
SRCS	=	$(MAIN)															\
			$(PARS)parser.c													\
			$(LEX)lexer.c													\
			$(LEX)replace_tilde.c											\
			$(LEX)stack.c													\
			$(LEX)is_acceptor.c												\
			$(LEX)is_ignored.c												\
			$(LEX)get_index_from_char.c										\
			$(LEX)get_dollar.c												\
			$(LEX)build_command_token.c										\
			$(LEX)get_type_of_token.c										\
			$(LEX)first_check_tokens_list.c									\
			$(LEX)delete_list_tokens.c										\
			$(LEX)token_constructor.c										\
			$(ST)syntax_tree.c												\
			$(TK)free_token.c												\
			$(TK)tokens.c													\
			$(AST)ast.c														\
			$(SRC)quit_shell.c												\
			$(DEBUG)debug.c

OBJ		=	$(patsubst %.c,%.o,$(SRCS))

# Name of the project

NAME	=	21sh

.PHONY: all clean fclean re

# Rules

all:		$(NAME)
		@true

$(NAME):	Makefile $(OBJ) $(MAIN) $(HFILES) $(LIBFT)
		@echo "Compiling Libft ..."
		@make -C $(LIBFT)
		@echo "Building $(NAME) ..."
		@$(CC) $(CFLAGS) $(OBJ) -I$(H) -I$(ILIBFT) -L$(LIBFT) -lft -o $(NAME)
		@echo "I'm READY"

%.o: 		%.c
		@echo "Creating $@ ..."
		@$(CC) $(CFLAGS) -I$(H) -I$(ILIBFT) -c $< -o $@

clean:
		@echo "Cleaning Objs ..."
		@$(RM) -f $(OBJ)
		@echo "Cleaning Libft Objs ..."
		@make clean -C $(LIBFT)

fclean:		clean
		@echo "Cleaning $(NAME) exec"
		@$(RM) -f $(NAME)
		@echo "Cleaning libft exec"
		@make fclean -C $(LIBFT)

re:			fclean all
