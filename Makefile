# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/15 18:38:22 by ndubouil          #+#    #+#              #
#    Updated: 2019/02/09 05:00:32 by ndubouil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Binaries and Flags

CC		=	/usr/bin/gcc
RM		=	/bin/rm
CFLAGS	=	-Wall -Wextra -Werror -g3 -fsanitize=address
TERMCAP =	-ltermcap

# Directories

LIBFT	=	./libft/
ILIBFT	=	./$(LIBFT)include/
H		=	./include/
SRC		=	./src/
ENV		=	$(SRC)environment/
EXE		=	$(SRC)exec/
DEBUG	=	$(SRC)debug/
PARS	=	$(SRC)parsing/
LEX		=	$(PARS)lexer/
ST		=	$(PARS)syntax_tree/
AST		=	$(PARS)ast/
TK		=	$(SRC)tokens/
BT		=	$(SRC)builtins/
CD		=	$(BT)cd/
GTL		=	$(SRC)get_line/

#  Files

HFILES	=	$(H)21sh.h														\
			$(H)lexer.h														\
			$(H)ast.h														\
			$(H)tokens.h													\
			$(H)shell_data.h												\
			$(H)get_line.h													\
			$(H)st.h

MAIN	=	$(SRC)main.c
SRCS	=	$(MAIN)															\
			$(SRC)/minimal_shell/read_prompt.c								\
			$(PARS)parser.c													\
			$(LEX)lexer.c													\
			$(LEX)lexer_tools.c												\
			$(LEX)stack.c													\
			$(LEX)is_acceptor.c												\
			$(LEX)is_ignored.c												\
			$(LEX)get_index_from_char.c										\
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
			$(ST)b_rule.c													\
			$(ST)c_rule.c													\
			$(AST)ast.c														\
			$(AST)delete_ast.c												\
			$(AST)procedures.c												\
			$(TK)free_token.c												\
			$(TK)tokens.c													\
			$(TK)get_cmd_tab.c												\
			$(TK)get_var_tab.c												\
			$(TK)replace_tilde.c											\
			$(TK)replace_dollar.c											\
			$(TK)get_env_var.c												\
			$(TK)get_var_tab_for_unset.c									\
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
			$(EXE)exec_ast.c												\
			$(EXE)catch_signal_kill.c										\
			$(EXE)aggr_redir_execution.c									\
			$(EXE)redir_recursion.c											\
			$(EXE)aggr_recursion.c											\
			$(EXE)pipe_execution.c											\
			$(EXE)get_path_of_bin.c											\
			$(SRC)quit_shell.c												\
			$(SRC)shell_data_singleton.c									\
			$(SRC)clean_shell_data.c										\
			$(BT)exit_builtin.c												\
			$(BT)set_builtin.c												\
			$(BT)export_builtin.c											\
			$(BT)unset_builtin.c											\
			$(BT)echo_builtin.c												\
			$(SRC)options.c													\
			$(SRC)ft_lstcpy.c												\
			$(BT)manage_builtins.c											\
			$(CD)get_final_path.c											\
			$(CD)get_pwd_for_cd.c											\
			$(CD)check_path_errors.c										\
			$(CD)ft_stringtab_len.c											\
			$(CD)ft_strjointab.c											\
			$(CD)ft_realloc_addend_tab.c									\
			$(CD)build_pwd_tab.c											\
			$(CD)cd_builtin.c												\
			$(GTL)get_line.c												\
			$(GTL)terms/history.c											\
			$(GTL)terms/init_term.c											\
			$(GTL)terms/utils.c												\
			$(GTL)terms/mouv.c												\
			$(GTL)terms/home_end.c											\
			$(GTL)terms/set_terms.c											\
			$(GTL)terms/supp.c												\
			$(GTL)terms/mouv_word.c											\
			$(GTL)terms/print.c												\
			$(GTL)terms/enter.c												\
			$(GTL)terms/multi.c												\
			$(GTL)terms/set_key.c											\
			$(GTL)terms/clean_line.c										\
			$(GTL)terms/del.c												\
			$(GTL)terms/manag_way.c											\
			$(GTL)terms/selec/selec_mouv.c									\
			$(GTL)terms/selec/selec.c										\
			$(GTL)terms/selec/cut.c											\
			$(GTL)terms/selec/paste.c										\
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
