/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_term.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroblin <aroblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 02:00:55 by aroblin           #+#    #+#             */
/*   Updated: 2019/02/03 05:00:55 by aroblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_line.h"

int		reset_term(struct termios *term)
{
	if (tcgetattr(0, term) == -1)
		return (-1);
	term->c_lflag = (ICANON | ECHO);
	if (tcsetattr(0, TCSANOW, term) == -1)
		return (-1);
	return (0);
}

int		init_termios(t_term **t)
{
	t_shell_data	*data;

	data = shell_data_singleton();
	if (tgetent(NULL, data->term) <= 0)
		return (-1);
	if (tcgetattr(STDIN_FILENO, &(*t)->term) == -1)
		return (-1);
	else
	{
		(*t)->term.c_lflag &= ~(ICANON | ECHO);
		(*t)->term.c_cc[VMIN] = 1;
		(*t)->term.c_cc[VTIME] = 0;
		if (tcsetattr(0, TCSADRAIN, &(*t)->term) == -1)
			return (-1);
	}
	return (0);
}
