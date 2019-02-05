/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroblin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 01:40:48 by aroblin           #+#    #+#             */
/*   Updated: 2019/02/05 04:03:19 by aroblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "tokens.h"

void	out_redir(t_cmd_token *cmd, t_token *name, t_token *redir)
{
	int				fd;
	int				fd_op;
	char			**tab;
	t_shell_data	*data;

	data = shell_data_singleton();
	tab = get_cmd_tab(&cmd);
	fd_op = ft_atoi(redir->token);
	if ((fd = open(name->token, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR
		| S_IWUSR | S_IRGRP | S_IROTH) < 0))
	{
		ft_printf("erreur open in out_redir"); // a suprimer
		quit_shell(EXIT_SUCCESS, 1);
	}
	dup2(fd_op, fd);
	exec_command(tab, data->env_tab);
	close(fd);
}

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
	if ((fd = open(name->token, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR
		| S_IWUSR | S_IRGRP | S_IROTH) < 0))
	{
		ft_printf("erreur open in out_redir"); // a suprimer
		quit_shell(EXIT_SUCCESS, 1);
	}
	dup2(fd, fd_op);
	exec_command(tab, data->env_tab);
	close(fd);
}
