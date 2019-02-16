# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/15 18:38:22 by ndubouil          #+#    #+#              #
#    Updated: 2019/02/16 02:42:57 by ndubouil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include sources.mk

# Binaries and Flags

CC		=	/usr/bin/gcc
RM		=	/bin/rm
CFLAGS	=	-Wall -Wextra -Werror -g3# -fsanitize=address
TERMCAP =	-ltermcap

# Directories

LIBFT	=	./libft/
ILIBFT	=	./$(LIBFT)include/
H		=	./include/

#  Files

HFILES	=	$(H)sh21.h														\
			$(H)lexer.h														\
			$(H)ast.h														\
			$(H)tokens.h													\
			$(H)shell_data.h												\
			$(H)get_line.h													\
			$(H)st.h

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
		@$(CC) $(CFLAGS) $(TERMCAP) $(OBJ) -I$(H) -I$(ILIBFT) -L$(LIBFT) -lft -o $(NAME)
		@echo "I'm READY"

%.o:		%.c $(HFILES)
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
