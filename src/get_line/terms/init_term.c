/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_term.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroblin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 02:00:55 by aroblin           #+#    #+#             */
/*   Updated: 2019/02/01 22:18:31 by aroblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_line.h"

int		reset_term(struct termios *term)
{
	if (tcgetattr(0, term) == -1)
		return (-1);
	term->c_lflag = (ICANON | ECHO);
	if (tcsetattr(0, 0, term) == -1)
		return (-1);
	return (0);
}

void	init_termios(struct termios *term)
{
	char	*name;

	name = NULL;
	if ((name = getenv("TERM")) == NULL) // a revoir
	{
		if (!(name = ft_strdup("xterm-256color")))
			exit(0);// erruer mallox
	}
	if (tgetent(NULL, name) <= 0)
	{
		printf("erruer tgetent\n");
		return ;
	}
	if (tcgetattr(0, term) == -1)
	{
		printf("21sh error: no termios.");
		exit(-1);
	}
	term->c_lflag &= ~(ICANON | ECHO);
	term->c_cc[VMIN] = 1;
	term->c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, term) == -1)
		return ;
}
