# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/15 18:38:22 by ndubouil          #+#    #+#              #
#    Updated: 2019/01/31 04:29:09 by ndubouil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Binaries and Flags

CC		=	/usr/bin/gcc
RM		=	/bin/rm
CFLAGS	=	-Wall -Wextra -Werror -g3 -fsanitize=address

# Directories

LIBFT	=	./libft/
ILIBFT	=	./$(LIBFT)includes/
H		=	./includes/
SRC		=	./src/
ENV		=	$(SRC)environment/
EXE		=	$(SRC)exec/
MIN		=	$(SRC)minimal_shell/
DEBUG	=	$(SRC)debug/
PARS	=	$(SRC)parsing/
LEX		=	$(PARS)lexer/
ST		=	$(PARS)syntax_tree/
AST		=	$(PARS)ast/
TK		=	$(SRC)tokens/
BT		=	$(SRC)builtins/
CD		=	$(BT)cd/

#  Files

HFILES	=	$(H)21sh.h														\
			$(H)lexer.h														\
			$(H)ast.h														\
			$(H)tokens.h													\
			$(H)shell_data.h												\
			$(H)st.h

MAIN	=	$(SRC)main.c
SRCS	=	$(MAIN)															\
			$(PARS)parser.c													\
			$(LEX)lexer.c													\
			$(LEX)lexer_tools.c												\
			$(LEX)replace_tilde.c											\
			$(LEX)stack.c													\
			$(LEX)is_acceptor.c												\
			$(LEX)is_ignored.c												\
			$(LEX)get_index_from_char.c										\
			$(LEX)get_dollar.c												\
			$(LEX)build_command_token.c										\
			$(LEX)build_command_token_tools.c								\
			$(LEX)get_type_of_token.c										\
			$(LEX)first_check_tokens_list.c									\
			$(LEX)first_check_tokens_list_tools.c							\
			$(LEX)delete_list_tokens.c										\
			$(LEX)token_constructor.c										\
			$(LEX)unexpected_token_error.c									\
			$(LEX)automaton_transition.c									\
			$(ST)syntax_tree.c												\
			$(ST)delete_parsing_tree.c										\
			$(ST)ft_ptree.c													\
			$(ST)test_current_token.c										\
			$(ST)s_rule.c													\
			$(ST)t_rule.c													\
			$(ST)u_rule.c													\
			$(ST)v_rule.c													\
			$(ST)f_rule.c													\
			$(ST)a_rule.c													\
			$(AST)ast.c														\
			$(AST)delete_ast.c												\
			$(AST)procedures.c												\
			$(TK)free_token.c												\
			$(TK)tokens.c													\
			$(TK)get_cmd_tab.c												\
			$(TK)get_var_tab.c												\
			$(ENV)get_env_var_by_name.c										\
			$(ENV)env_lst_to_tab.c											\
			$(ENV)env_tab_to_lst.c											\
			$(ENV)change_env_var.c											\
			$(ENV)remove_env_var.c											\
			$(ENV)add_env_var.c												\
			$(ENV)create_varenv.c											\
			$(ENV)del_env_var.c												\
			$(ENV)create_minimal_env.c										\
			$(EXE)exec_command.c											\
			$(EXE)get_path_of_bin.c											\
			$(MIN)read_prompt.c												\
			$(SRC)quit_shell.c												\
			$(SRC)shell_data_singleton.c									\
			$(SRC)clean_shell_data.c										\
			$(BT)exit_builtin.c												\
			$(BT)set_builtin.c												\
			$(BT)export_builtin.c											\
			$(BT)unset_builtin.c											\
			$(BT)echo_builtin.c												\
			$(SRC)options.c													\
			$(BT)manage_builtins.c											\
			$(CD)get_final_path.c											\
			$(CD)get_pwd_for_cd.c											\
			$(CD)check_path_errors.c										\
			$(CD)ft_stringtab_len.c											\
			$(CD)ft_strjointab.c											\
			$(CD)ft_realloc_addend_tab.c									\
			$(CD)build_pwd_tab.c											\
			$(CD)cd_builtin.c												\
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
