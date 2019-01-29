/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 18:30:34 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/29 08:38:24 by ndubouil         ###   ########.fr       */
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


void 	exec_ast(t_btree *tree)
{
	char	**tab;
	t_shell_data	*data;

	data = shell_data_singleton();
	if (tree == NULL)
		return ;
	if (tree->left != NULL)
		exec_ast(tree->left);
	// &&
	if (get_type_token(tree->data) == AND_TYPE)
	{
		// if (tree->left != NULL)
		// 	exec_ast(tree->left);
		if (WEXITSTATUS(data->last_status) == EXIT_SUCCESS)
		{
			if (tree->right != NULL)
				exec_ast(tree->right);
		}
	}
	// ||
	else if (get_type_token(tree->data) == OR_TYPE)
	{
		// if (tree->left != NULL)
		// 	exec_ast(tree->left);
		if (WEXITSTATUS(data->last_status) == EXIT_FAILURE)
		{
			if (tree->right != NULL)
				exec_ast(tree->right);
		}
	}
	// COMMANDE
	else if (get_type_token(tree->data) == CMD_TYPE)
	{
		tab = get_cmd_tab((*((t_cmd_token **)(tree->data))));
		if (!manage_builtins(tab))
		exec_command(tab, data->env_tab);
		// ft_printf("retour de la cmd [%d]\n", WEXITSTATUS(data->last_status));
		ft_strtab_del(&tab);
	}
	else
	{
		// if (tree->left != NULL)
		// 	exec_ast(tree->left);
		if (tree->right != NULL)
			exec_ast(tree->right);
	}
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
		if (!read_prompt(0, &line) || line[0] == -1)
			quit_shell(EXIT_FAILURE, 0);
		shell_parser(line);
		// Executer
		exec_ast(data->ast);
		ft_strdel(&line);
	}
}

void	ft_shell(void)
{
	t_shell_data	*data;

	data = shell_data_singleton();
	// if (data->shell)
	// 	ft_printf("J'attends readline !\n");
	// else
	// {
		ft_printf("21sh: warning: the variable TERM is not set, this is a minimal shell\n");
		ft_minimal_shell();
	// }
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
	ft_printf("tty = %s, TERM = %s\n", ttyname(0), term->content);
	if (term || !isatty(0))
		data->shell = term->content;
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

	(void)ac;
	pos_args = 0;
	data = shell_data_singleton();
	options_parser(av, &data->options, &pos_args, set_options);
	init_shell(environ);
	// OPTION C executer la commande directement et quitter
	if ((data->options & OPT_C))
	{
		if (pos_args > 1)
			shell_parser(av[pos_args]);
		// executer la commande
	}
	else
	{
		ft_shell();
	}
	quit_shell(EXIT_SUCCESS, 0);
	return (EXIT_SUCCESS);
}
