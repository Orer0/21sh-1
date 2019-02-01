/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroblin <aroblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 14:09:14 by aroblin           #+#    #+#             */
/*   Updated: 2019/02/01 23:29:19 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_line.h"

void	*way(t_term **t, char *cmd)
{
	void	(*fonct)(t_term **);

	fonct = NULL;
	if ((*t)->index_his <= -1)
		fonct = set_cmd_mouv(cmd);
	if (fonct == NULL && (*t)->index_his <= -1)
		fonct = set_cmd_edit(cmd);
	if (fonct == NULL)
		fonct = set_cmd_his(cmd);
	return (fonct);
}

void	cmd_way(void (*fonct)(t_term **), t_term **t, char *cmd)
{
	char	*tmp;

	tmp = NULL;
	if (fonct != NULL)
	{
		fonct(t);
		ft_bzero(&cmd, sizeof(char[6]));
		fonct = NULL;
	}
	else if (fonct == NULL && cmd[0] > 0 && cmd[0] < 127
		&& cmd[0] != 27 && (*t)->index_his <= -1)
	{
		if (!(tmp = ft_strdup(cmd)))
		{
			printf("ereur malloc\n");
			return ;
		}
		if ((*t)->cur.x == (*t)->max_cur)
			print_buf_end(tmp, t);
		else if ((*t)->line != NULL)
			print_insertion(t, tmp);
	}
}

int		manag_way(t_term **t)
{
	struct winsize	ws;
	char			cmd[6];
	void			(*fonct)(t_term **t);

	fonct = NULL;
	ft_bzero(&cmd, sizeof(char[6]));
	while (1)
	{
		if ((*t)->cur.x == 0 && (*t)->max_cur == 0)
		{
			if ((*t)->line != NULL)
				ft_strdel(&(*t)->line);
		}
		read(0, cmd, 6);
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
		(*t)->col = ws.ws_col;
		(*t)->nb_line = (((*t)->max_cur + (*t)->len_p) / (*t)->col);
		fonct = way(t, cmd);
		cmd_way(fonct, t, cmd);
		fonct = NULL;
		ft_bzero(&cmd, sizeof(char[6]));
	}
	return (0);
}

int		get_line(char *promtp)
{
	t_term			*t;
	struct termios	term;

	if (!(t = ft_memalloc(sizeof(t_term))))
	{
		printf("erreur malloc");
		return (-1);
	}
	set_terms(&t, promtp);
	ft_putstr(t->promtp);
	init_termios(&term);
	manag_way(&t);
	reset_term(&term);
	return (0);
}
