/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 18:30:34 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/16 03:01:47 by aroblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static int	set_options(char *ops, int *options, int pos)
{
	if (ops[pos] == '\0')
		return (FALSE);
	if (is_valid_option(ops[pos], SHELL_OPT))
		*(options) |= (1 << (ops[pos] - 'a'));
	else
	{
		ft_fd_printf(2, "21sh: illegal option -- %c\n", ops[pos]);
		ft_fd_printf(2, "valid options: [-%s]\n", SHELL_OPT);
		quit_shell(EXIT_FAILURE, 0);
	}
	set_options(ops, options, (pos + 1));
	return (TRUE);
}

void		ft_minimal_shell(void)
{
	char			*line;
	t_shell_data	*data;

	data = shell_data_singleton();
	ft_strdel(&data->term);
	while (666)
	{
		clean_parsing();
		ft_fd_printf(0, "%s", PROMPT);
		if (!read_prompt(0, &line))
			quit_shell(EXIT_FAILURE, 0);
		if (!line || line[0] == -1)
			quit_shell(EXIT_FAILURE, 0);
		if (shell_parser(&line))
			exec_ast(data->ast, 1);
	}
}

void		ft_shell(void)
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
			signal(SIGINT, catch_signal_kill);
			if (!(line = get_line(PROMPT, NULL)))
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

int			main(int ac, char **av, char **environ)
{
	t_shell_data	*data;
	int				pos_args;
	char			*line;

	(void)ac;
	ft_printf("MAIN\n");
	pos_args = 0;
	data = shell_data_singleton();
	options_parser(av, &data->options, &pos_args, set_options);
	init_shell(environ);
	if ((data->options & OPT_C))
	{
		if (pos_args > 1)
		{
			ft_strdel(&data->term);
			line = ft_strdup(av[pos_args]);
			if (shell_parser(&line))
				exec_ast(data->ast, 1);
		}
	}
	else
		ft_shell();
	quit_shell(EXIT_SUCCESS, 0);
	return (EXIT_SUCCESS);
}
