/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroblin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 02:10:58 by aroblin           #+#    #+#             */
/*   Updated: 2019/02/09 22:38:40 by aroblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_line.h"

void	delete_all(int len, t_term **t)
{
	size_t		k;

	k = ft_strlen((*t)->promtp);
	if (len > 0)
	{
		while (len > 0)
		{
			tputs(tgetstr("up", NULL), 0, &put);
			len--;
		}
	}
	tputs(tgetstr("cr", NULL), 0, &put);
	while (k > 0)
	{
		tputs(tgetstr("nd", NULL), 0, &put);
		k--;
	}
	tputs(tgetstr("cd", NULL), 0, &put);
}

void	go_way(t_term **t, int nb, int way)
{
	(void)t;
	while (nb > 0)
	{
		if (way == LE)
			tputs(tgetstr("le", NULL), 0, &put);
		if (way == ND)
			tputs(tgetstr("nd", NULL), 0, &put);
		nb--;
	}
}

int		ft_is_space(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\0')
		return (1);
	return (0);
}

int		put(int c)
{
	return ((int)write(STDIN_FILENO, &c, 1));
}

int		putst(char *c)
{
	int		i;

	i = 0;
	while (c[i] != '\0')
	{
		put(c[i]);
		i++;
	}
	return (i);
}
