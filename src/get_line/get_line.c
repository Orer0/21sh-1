/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroblin <aroblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 14:09:14 by aroblin           #+#    #+#             */
/*   Updated: 2019/02/09 03:47:53 by aroblin          ###   ########.fr       */
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
		ft_bzero(&cmd, sizeof(char[8]));
		fonct = NULL;
	}
	else if (fonct == NULL && cmd[0] > 0 && cmd[0] < 127
		&& cmd[0] != 27 && (*t)->index_his <= -1)
	{
		if (!(tmp = ft_strdup(cmd)))
			end_shell(t, cmd);
		if ((*t)->cur.x == (*t)->max_cur)
			print_buf_end(tmp, t);
		else if ((*t)->line != NULL)
			print_insertion(t, tmp);
	}
}

char	*get_line(char *promtp)
{
	t_term			*t;
	char			*line;
	char			*tmp;

	t = NULL;
	if (!(t = ft_memalloc(sizeof(t_term))))
	{
		end_shell(&t, NULL);
		return (NULL);
	}
	if (init_termios() == -1)
	{
		ft_memdel((void **)t);
		return (NULL);
	}
	set_terms(&t, promtp);
	ft_putstr(t->promtp);
	tmp = manag_way(&t);
	ft_strdel(&tmp);
	clean_line(&t);
	reset_term();
	return (line);
}
