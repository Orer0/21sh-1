/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_tilde.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 20:49:11 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/01 01:40:46 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static char		*get_home_of_user(char *name)
{
	struct passwd	*p;
	char			*tmp;
	int				size;

	tmp = ft_strdup(name);
	size = ft_strlen(name);
	if (tmp[size - 1] == '/')
		tmp[size - 1] = 0;
	if ((p = getpwnam(tmp)))
	{
		ft_strdel(&tmp);
		return (p->pw_dir);
	}
	else
	{
		ft_strdel(&tmp);
		return (NULL);
	}
}

/*
**	TODO Remplacer getenv par notre getenv
*/

int				replace_tilde(char **str)
{
	char			*home;
	char			*tmp;
	int				s;

	s = ft_strlen(*str);
	if (s > 1 && !ft_strequ("~/", (*str)))
		home = get_home_of_user(&(*str)[1]);
	else
	{
		home = getenv("HOME");
		if (!home)
			home = get_home_of_user(getenv("USER"));
	}
	if (home)
	{
		if ((*str)[s - 1] == '/')
			tmp = ft_strdup(&(*str)[s - 1]);
		else
			tmp = ft_strdup("");
		ft_strdel(str);
		if (!(*str = ft_strjoin(home, tmp)))
		{
			ft_strdel(&tmp);
			return (FALSE);
		}
		ft_strdel(&tmp);
		return (TRUE);
	}
	return (FALSE);
}
