/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 18:30:34 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/03 01:44:46 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

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
	// ft_printf("noeud [%s], exec next [%d]\n", get_token_token(tree->data), exec_next);
	if (exec_next)
		if (tree->left != NULL)
			exec_ast(tree->left, exec);
	// &&
	if (get_type_token(tree->data) == AND_TYPE)
	{
		if (WEXITSTATUS(data->last_status) != EXIT_SUCCESS)
			exec = FALSE;
	}
	// ||
	else if (get_type_token(tree->data) == OR_TYPE)
	{
		if (WEXITSTATUS(data->last_status) == EXIT_SUCCESS)
			exec = FALSE;
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
	}
	// VARIABLES
	else if (get_type_token(tree->data) == VAR_TYPE && exec_next)
	{
		tab = get_var_tab(((t_var_token **)(tree->data)));
		set_builtin(tab);
		ft_strtab_del(&tab);
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
		shell_parser(&line);
		// Executer
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
			shell_parser(&line);
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
