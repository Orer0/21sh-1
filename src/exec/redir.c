/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroblin <aroblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 01:40:48 by aroblin           #+#    #+#             */
/*   Updated: 2019/02/08 04:42:32 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
/*
#include "tokens.h"


void	app_out_redir(t_cmd_token *cmd, t_token *name, t_token *redir)
{
	int				fd;
	int				fd_op;
	char			**tab;
	t_shell_data	*data;

	data = shell_data_singleton();
	tab = get_cmd_tab(&cmd);
	fd_op = ft_atoi(redir->token);
	if ((fd = open(name->token, O_APPEND | O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR
		| S_IWUSR | S_IRGRP | S_IROTH) < 0))
	{
		ft_printf("erreur open in out_redir"); // a suprimer
		quit_shell(EXIT_SUCCESS, 1);
	}
	dup2(fd_op, fd);
	exec_command(tab, data->env_tab);
	close(fd);
}

void	in_redir(t_cmd_token *cmd, t_token *name, t_token *redir)
{
	int				fd;
	int				fd_op;
	char			**tab;
	t_shell_data	*data;

	data = shell_data_singleton();
	tab = get_cmd_tab(&cmd);
	fd_op = ft_atoi(redir->token);
	if ((fd = open(name->token, O_APPEND | O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) < 0))
	{
		ft_printf("erreur open in out_redir"); // a suprimer
		quit_shell(EXIT_SUCCESS, 1);
	}
	dup2(fd, fd_op);
	exec_command(tab, data->env_tab);
	close(fd);
}
*/
#include <stdio.h>
int		main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	int				fd;
	char			**tab;
	char			*cmd;
	char			*out;

	out = ft_strdup("file");
	cmd = ft_strdup("/bin/ls");
	tab = ft_memalloc(sizeof(char *) * 1);
	tab[0] = ft_strdup("/bin/ls");
	if ((fd = open(out, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR
		| S_IWUSR | S_IRGRP | S_IROTH)) < 0)
	{
		ft_printf("erreur open in out_redir"); // a suprimer
	}
	dup2(fd, 2);
	if (execve(cmd, tab, env) < 0)
		printf("coucou\n");
	//close(fd);
	return (0);
}
