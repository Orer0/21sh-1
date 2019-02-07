/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 18:30:34 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/07 05:55:09 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include <errno.h>

static int		set_options(char *ops, int *options, int pos)
{
	if (ops[pos] == '\0')
		return (FALSE);
	if (is_valid_option(ops[pos], SHELL_OPT))
		*(options) |= (1 << (ops[pos] - 'a'));
	else
	{
		ft_printf("21sh: illegal option -- %c\n" , ops[pos]);
		ft_printf("valid options: [-%s]\n" , SHELL_OPT);
		quit_shell(EXIT_FAILURE, 0);
	}
	set_options(ops, options, (pos + 1));
	return (TRUE);
}

void 	exec_ast(t_btree *tree, int exec_next);
void 	aggr_recursion(t_btree *tree, int fd_tab[256], int i);

void 	redir_recursion(t_btree *tree, int fd_tab[256], int i)
{
	int fd;

	if (!tree->right)
	return ;
	// Si le noeud de droite est un argument de redirection, on le prend
	if (get_type_token(tree->right->data) == REDIRECTION_ARG_TYPE)
	{
		ft_printf("OPEN DU FICHIER [%s]\n", get_token_token(tree->right->data));
		// OPEN LE FICHIER ARGUMENT
		fd = open(get_token_token(tree->right->data), O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if (fd == -1)
		{
			ft_printf("21sh: open failed"); // a suprimer
			quit_shell(EXIT_FAILURE, 0);
		}
		fd_tab[i] = fd;
		ft_printf("fd apres open = %d, i[%d]\n", fd, i);
		i++;
		if (get_type_token(tree->data) == OUT_RDIR_TYPE)
		{
			int new;
			int nem = dup(1);
			if ((new = dup2(fd, nem)) < 0)
				ft_printf("ERREUR DE DUP2\n");
			ft_fd_printf(nem, "yyyyyyyyyy");
			//close(fd);
			// close(new);
			// close(nem);
		}
		return ;
	}
	// Sinon, l'argument est dans le noeud gauche du noeud de droite
	if (!tree->right->left)
		return ;
	if (get_type_token(tree->right->left->data) == REDIRECTION_ARG_TYPE)
	{
		ft_printf("OPEN DU FICHIER [%s]\n", get_token_token(tree->right->left->data));
		// OPEN LE FICHIER ARGUMENT
		fd = open(get_token_token(tree->right->left->data), O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if (fd == -1)
		{
			ft_printf("21sh: open failed"); // a suprimer
			quit_shell(EXIT_FAILURE, 0);
		}
		fd_tab[i] = fd;
		ft_printf("fd apres open = %d i[%d]\n", fd, i);
		i++;
		if (get_type_token(tree->data) == OUT_RDIR_TYPE)
		{
		//	if (dup2(fd, 1) < 0)
		//		ft_printf("ERREUR DE DUP2\n");
		//	ft_printf("yyyyyyyyyy");
		//	close(fd);
			// close(fd);
		}
	}
	// Relance la bonne recursion sur le noeud de droite qui est un operateur
	if (is_redirection(get_type_token(tree->right->data)))
		redir_recursion(tree->right, fd_tab, i);
	else if (is_aggregation(get_type_token(tree->right->data)))
		aggr_recursion(tree->right, fd_tab, i);
}

void 	aggr_recursion(t_btree *tree, int fd_tab[256], int i)
{
	if (!tree->right)
	return ;
	// Si le noeud de droite est un argument d'aggregation, on le prend
	if (get_type_token(tree->right->data) == AGGREGATION_ARG_TYPE)
	{
		ft_printf("Argument d'aggregation = %s\n", get_token_token(tree->right->data));
		return ;
	}
	// Sinon, l'argument est dans le noeud gauche du noeud de droite
	if (!tree->right->left)
		return ;
	if (get_type_token(tree->right->left->data) == AGGREGATION_ARG_TYPE)
	{
		ft_printf("Argument d'aggregation = %s\n", get_token_token(tree->right->left->data));
	}
	// Relance la bonne recursion sur le noeud de droite qui est un operateur
	if (is_redirection(get_type_token(tree->right->data)))
		redir_recursion(tree->right, fd_tab, i);
	else if (is_aggregation(get_type_token(tree->right->data)))
		aggr_recursion(tree->right, fd_tab, i);
}

void	aggr_redir_execution(t_btree *tree)
{
	int		fd_tab[256];
	int		i;

	ft_bzero(fd_tab, 256);
	i = 0;

	if (is_redirection(get_type_token(tree->data)))
		redir_recursion(tree, fd_tab, i);
	else if (is_aggregation(get_type_token(tree->data)))
		aggr_recursion(tree, fd_tab, i);
	// Si le noeud de gauche est une command ou une variable
	if (get_type_token(tree->left->data) == CMD_TYPE || get_type_token(tree->left->data) == VAR_TYPE)
	{
		char	**tab;
		t_shell_data	*data;
		t_list	*old_intern_env;
		t_list	*tmp_intern_env;

		data = shell_data_singleton();
		// EXECUTER LE NOEUD DE GAUCHE
		ft_printf("EXECUTION NOEUD GAUCHE = %s\n", get_token_token(tree->left->data));
		if (get_type_token(tree->left->data) == CMD_TYPE)
		{
			if (get_var_token_in_cmd_token(tree->left->data))
			{
				old_intern_env = data->intern_env_lst;
				tmp_intern_env = ft_lstcpy(data->intern_env_lst, &tmp_intern_env);
				data->intern_env_lst = tmp_intern_env;
				tab = get_var_tab(((t_var_token **)(tree->left->data)));
				set_builtin(tab);
				ft_strtab_del(&tab);
			}
			tab = get_cmd_tab(((t_cmd_token **)(tree->left->data)));
			if (!manage_builtins(tab))
				exec_command(tab, data->env_tab);
			ft_strtab_del(&tab);
			if (get_var_token_in_cmd_token(tree->left->data))
			{
				ft_lstdel(&data->intern_env_lst, del_env_var);
				data->intern_env_lst = old_intern_env;
			}
		}
		// VARIABLES
		else if (get_type_token(tree->left->data) == VAR_TYPE)
		{
			tab = get_var_tab(((t_var_token **)(tree->left->data)));
			set_builtin(tab);

		// exec_ast(tree->left, TRUE);
		}
	}

	ft_printf("CLOSE TABLEAU DE FD\n");
	i = 0;
	while (fd_tab[i])
	{
		ft_printf("fd[%d] = %d\n", i, fd_tab[i]);
		if (!close(fd_tab[i]))
			ft_printf("fail close [%s]\n", strerror(errno));
		i++;
	}
}

void 	pipe_execution(t_btree *tree)
{
	// creer le pipe
	// exectuer le noeud de gauche
	exec_ast(tree->left, TRUE);
	exec_ast(tree->right, TRUE);
}

void 	exec_ast(t_btree *tree, int exec_next)
{
	char	**tab;
	t_shell_data	*data;
	t_list	*old_intern_env;
	t_list	*tmp_intern_env;
	int			exec;

	data = shell_data_singleton();
	if (tree == NULL)
		return ;
	exec = TRUE;
	if (get_type_token(tree->data) == PIPE_TYPE && exec_next)
	{
		pipe_execution(tree);
		return ;
	}
	// > >&
	else if ((is_redirection(get_type_token(tree->data)) || is_aggregation(get_type_token(tree->data))) && exec_next)
	{
		aggr_redir_execution(tree);
		return ;
	}
	else
		if (exec_next)
			if (tree->left != NULL)
				exec_ast(tree->left, exec);
	// &&
	if (get_type_token(tree->data) == AND_TYPE)
	{
		if (WEXITSTATUS(data->last_status) != EXIT_SUCCESS)
			exec = FALSE;
		// if (tree->right != NULL)
		// 	exec_ast(tree->right, exec);
	}
	// ||
	else if (get_type_token(tree->data) == OR_TYPE)
	{
		if (WEXITSTATUS(data->last_status) == EXIT_SUCCESS)
			exec = FALSE;
		// if (tree->right != NULL)
		// 	exec_ast(tree->right, exec);
	}
	// COMMANDE
	else if (get_type_token(tree->data) == CMD_TYPE && exec_next)
	{
		if (get_var_token_in_cmd_token(tree->data))
		{
			old_intern_env = data->intern_env_lst;
			tmp_intern_env = ft_lstcpy(data->intern_env_lst, &tmp_intern_env);
			data->intern_env_lst = tmp_intern_env;
			tab = get_var_tab(((t_var_token **)(tree->data)));
			set_builtin(tab);
			ft_strtab_del(&tab);
		}
		tab = get_cmd_tab(((t_cmd_token **)(tree->data)));
		if (!manage_builtins(tab))
			exec_command(tab, data->env_tab);
		ft_strtab_del(&tab);
		if (get_var_token_in_cmd_token(tree->data))
		{
			ft_lstdel(&data->intern_env_lst, del_env_var);
			data->intern_env_lst = old_intern_env;
		}
		// if (tree->right != NULL)
		// 	exec_ast(tree->right, exec);
	}
	// VARIABLES
	else if (get_type_token(tree->data) == VAR_TYPE && exec_next)
	{
		tab = get_var_tab(((t_var_token **)(tree->data)));
		set_builtin(tab);
		ft_strtab_del(&tab);
		// if (tree->right != NULL)
		// 	exec_ast(tree->right, exec);
	}
	if (tree->right != NULL)
		exec_ast(tree->right, exec);
}

void 	ft_minimal_shell(void)
{
	char	*line;
	t_shell_data *data;

	data = shell_data_singleton();
	while (666)
	{
		clean_parsing();
		ft_printf("%s", PROMPT);
		if (!read_prompt(0, &line))
			quit_shell(EXIT_FAILURE, 0);
		if (!line || line[0] == -1)
			quit_shell(EXIT_FAILURE, 0);
		if (shell_parser(&line))
			exec_ast(data->ast, 1);
	}
}

void	ft_shell(void)
{
	t_shell_data	*data;
	char			*line;

	line = NULL;
	data = shell_data_singleton();
	if (data->term)
	{
		while (666)
		{
			clean_parsing();
			if (!(line = get_line(PROMPT)))
				return (ft_minimal_shell());
			if (shell_parser(&line))
				exec_ast(data->ast, 1);
		}
	}
	else
	{
		ft_printf("21sh: warning: the variable TERM not found\n");
		quit_shell(EXIT_FAILURE, 0);
	}
}

void 	init_shell(char **environ)
{
	t_shell_data	*data;
	t_varenv		*envshlvl;
	char			*tmp;
	int				shlvl;
	t_varenv		*term;

	data = shell_data_singleton();
	if (!env_tab_to_lst(&data->env_lst, environ))
		create_minimal_env();
	term = get_env_var_by_name(&data->env_lst, "TERM");
	if (term && isatty(0))
		data->term = term->content;
	else
	{
		change_env_var(&data->env_lst, "TERM", "xterm");
		change_env_var(&data->intern_env_lst, "TERM", "xterm");
		data->term = get_env_var_by_name(&data->env_lst, "TERM")->content;
	}
	if (!(envshlvl = get_env_var_by_name(&data->env_lst, "SHLVL")))
		shlvl = 0;
	else
		shlvl = ft_atoi(envshlvl->content);
	tmp = ft_itoa(shlvl + 1);
	change_env_var(&data->env_lst, "SHLVL", tmp);
	change_env_var(&data->intern_env_lst, "SHLVL", tmp);
	ft_strdel(&tmp);
	env_lst_to_tab(&data->env_lst, &data->env_tab);
	env_tab_to_lst(&data->intern_env_lst, data->env_tab);
}

int		main(int ac, char **av, char **environ)
{
	t_shell_data	*data;
	int				pos_args;
	char			*line;

	(void)ac;
	pos_args = 0;
	data = shell_data_singleton();
	options_parser(av, &data->options, &pos_args, set_options);
	init_shell(environ);
	// OPTION C executer la commande directement et quitter
	if ((data->options & OPT_C))
	{
		if (pos_args > 1)
		{
			line = ft_strdup(av[pos_args]);
			shell_parser(&line);
		}
		// executer la commande
	}
	else
	{
		ft_shell();
	}
	quit_shell(EXIT_SUCCESS, 0);
	return (EXIT_SUCCESS);
}
