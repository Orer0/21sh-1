/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manag_way.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroblin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 05:06:01 by aroblin           #+#    #+#             */
/*   Updated: 2019/02/08 06:06:32 by aroblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_line.h"

static int		ft_end_line(t_term **t, char *cmd)
{
	enter(t);
	if ((*t)->line != NULL)
		return (1);
	else
		ft_bzero(&cmd, sizeof(char[8]));
	return (0);
}

static void		check_line(t_term **t)
{
	if ((*t)->cur.x == 0 && (*t)->max_cur == 0)
	{
		if ((*t)->line != NULL)
			ft_strdel(&(*t)->line);
	}
}

int		end_shell(t_term **t, char *cmd)
{
	if (t == NULL)
	{
		reset_term(&(*t)->term);
		quit_shell(EXIT_SUCCESS, 0);
		return (0);
	}
	else if ((*t)->line == NULL)
	{
		clean_line(t);
		reset_term(&(*t)->term);
		quit_shell(EXIT_SUCCESS, 0);
		return (0);
	}
	ft_bzero(&cmd, sizeof(char[8]));
	return (1);

}

static void		basic_cmd(t_term **t, char *cmd, void (*fonct)(t_term **t))
{
	struct winsize	ws;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
	(*t)->col = ws.ws_col;
	(*t)->nb_line = (((*t)->max_cur + (*t)->len_p) / (*t)->col);
	fonct = way(t, cmd);
	cmd_way(fonct, t, cmd);
	fonct = NULL;
	ft_bzero(&cmd, sizeof(char[8]));
}

char			*manag_way(t_term **t)
{
	char			cmd[8];
	void			(*fonct)(t_term **t);

	fonct = NULL;
	ft_bzero(&cmd, sizeof(char) * 8);
	while (666)
	{
		check_line(t);
		read(0, cmd, 7);
		if (cmd[0] == 10 && cmd[1] == 0)
		{
			if (ft_end_line(t, cmd))
				return ((*t)->line);
		}
		else if (cmd[0] == 4)
			end_shell(t, cmd);
		else
			basic_cmd(t, cmd, fonct);
		ft_bzero(&cmd, sizeof(char) * 8);
	}
	return ((*t)->line);
}
