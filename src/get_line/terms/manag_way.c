/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manag_way.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroblin <aroblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 05:06:01 by aroblin           #+#    #+#             */
/*   Updated: 2019/02/16 03:29:14 by aroblin          ###   ########.fr       */
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

static int		basic_cmd(t_term **t, char *cmd, void (*fonct)(t_term **t))
{
	struct winsize	ws;

	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1)
		return (-1);
	(*t)->col = ws.ws_col;
	(*t)->nb_line = (((*t)->max_cur + (*t)->len_p) / (*t)->col);
	fonct = way(cmd);
	cmd_way(fonct, t, cmd);
	fonct = NULL;
	ft_bzero(&cmd, sizeof(char[8]));
	return (1);
}

char			*check_end_cmd(char *cmd, t_term **t)
{
	if (cmd[0] == 10 && cmd[1] == 0)
	{
		if (ft_end_line(t, cmd))
			return ((*t)->line);
	}
	else if (cmd[0] == 3)
	{
		ctrl_c(t);
		ft_bzero(&cmd, sizeof(char) * 8);
		return ((*t)->line);
	}
	return (NULL);
}

/*
**	MANAG_WAY - read the tap keycode
**
**	params: t -> struct whit all curses and final line
**
**	return: the final line tap / edit by the user
**
**	Description:
**	- free the line if the curse is in position 0
**	- read of 7 for catch all keycode
**	- detec if key enter is tap and lauch a enter fonction if is TRUE
**		and return the final line
**	- detec if CRTL + d is tap and lauch end_shell for exit if is TRUE
**	- if is not CTRL + d or enter keycode, the fonction
**		lauch other detection of keycode
**	- return final line
*/

char			*manag_way(t_term **t, char *end_of_file)
{
	char			cmd[8];
	void			(*fonct)(t_term **t);

	fonct = NULL;
	while (666)
	{
		ft_bzero(&cmd, sizeof(char) * 8);
		check_line(t);
		read(0, cmd, 7);
		if ((cmd[0] == 10 && cmd[1] == 0) || cmd[0] == 3)
			return (check_end_cmd(cmd, t));
		else if (cmd[0] == 4)
		{
			ft_strequ((*t)->promtp, PROMPT) ? end_shell(t, cmd) : 0;
			if (ft_strequ((*t)->promtp, PROMPT_MIN))
				if ((*t)->line == NULL)
					return (end_quoting_heredoc(t, end_of_file));
		}
		else
		{
			if (basic_cmd(t, cmd, fonct) == -1)
				return (NULL);
		}
	}
	return ((*t)->line);
}
