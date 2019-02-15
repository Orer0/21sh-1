/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manag_way.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroblin <aroblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 05:06:01 by aroblin           #+#    #+#             */
/*   Updated: 2019/02/15 01:56:23 by aroblin          ###   ########.fr       */
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

int				end_shell(t_term **t, char *cmd)
{
	if (t == NULL)
	{
		reset_term();
		quit_shell(EXIT_SUCCESS, 0);
		return (0);
	}
	else if ((*t)->line == NULL)
	{
		clean_line(t);
		reset_term();
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
	fonct = way(cmd);
	cmd_way(fonct, t, cmd);
	fonct = NULL;
	ft_bzero(&cmd, sizeof(char[8]));
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

char				*end_quoting_heredoc(t_term **t, char *cmd
		, char *end_of_file)
{
	char *tmp;

	tmp = NULL;
	if ((*t)->line == NULL)
	{
		clean_line(t);
		reset_term();
		if (!(tmp = ft_strdup(end_of_file)))
			quit_shell(EXIT_FAILURE, MALLOC_ERR);
		return (tmp);
	}
	ft_bzero(&cmd, sizeof(char[8]));
	return (NULL);
}

char			*manag_way(t_term **t, char *end_of_file)
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
		{
			if (ft_strequ((*t)->promtp, PROMPT))
				end_shell(t, cmd);
			else if (ft_strequ((*t)->promtp, PROMPT_MIN))
			{
				if ((*t)->line == NULL)
					return (end_quoting_heredoc(t, cmd, end_of_file));
			}
		}
		else
			basic_cmd(t, cmd, fonct);
		ft_bzero(&cmd, sizeof(char) * 8);
	}
	return ((*t)->line);
}
