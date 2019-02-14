/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroblin <aroblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 14:09:14 by aroblin           #+#    #+#             */
/*   Updated: 2019/02/14 02:10:24 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_line.h"

/*
**	WAY - Manage tap key
**
**	params: cmd -> the keycode
**			t -> struct of the program term
**	return: the fonction that correspond at the keycode
**
**	Description:
**	- Send the cmd (keycode)
**	- Return the good fonction
*/

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

/*
**	GET_LINE - Open a promtp
**
**	params: promtp -> the prompt that will be print
**
**	return: the final line edit by the user and after the enter key
**
**	Description:
**	- Init termios - Set terminal in no canonical
**	- Analyse the tap key
**	- Return the final line
*/

char	*get_line(char *promtp)
{
	t_shell_data	*data;
	char			*line;
	char			*tmp;

	data = shell_data_singleton();
	if (!data->t)
	{
		if (!(data->t = ft_memalloc(sizeof(t_term))))
		{
			end_shell(&data->t, NULL);
			return (NULL);
		}
	}
	if (init_termios() == -1)
	{
		ft_memdel((void **)data->t);
		return (NULL);
	}
	set_terms(&data->t, promtp);
	write(0, data->t->promtp, ft_strlen(data->t->promtp));
	tmp = manag_way(&data->t);
	line = ft_strdup(tmp);
	ft_strdel(&tmp);
	clean_line(&data->t);
	reset_term();
	return (line);
}
