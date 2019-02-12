/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_tilde.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 20:49:11 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/12 23:11:12 by ndubouil         ###   ########.fr       */
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

int				new_tilde_value(char **str, int s, char *home)
{
	char	*tmp;

	tmp = NULL;
	if ((*str) && (*str)[1] == '/')
		tmp = ft_strsub(*str, 1, ft_strlen(*str) - 1);
	else if ((*str) && s > 1 && (*str)[s - 1] == '/')
		tmp = ft_strdup("/");
	else
		tmp = ft_strdup("");
	if (!tmp)
		quit_shell(EXIT_FAILURE, 0);
	ft_strdel(str);
	if (!(*str = ft_strjoin(home, tmp)))
	{
		ft_strdel(&tmp);
		quit_shell(EXIT_FAILURE, 0);
	}
	ft_strdel(&tmp);
	return (TRUE);
}

int				replace_tilde(char **str)
{
	char			*home;
	int				s;

	s = ft_strlen(*str);
	if (s > 1 && !ft_strequ("~/", (*str)))
	{
		if (!(home = get_home_of_user(&(*str)[1])))
			home = getenv("HOME");
	}
	else
	{
		home = getenv("HOME");
		if (!home)
			home = get_home_of_user(getenv("USER"));
	}
	if (home)
		return (new_tilde_value(str, s, home));
	return (FALSE);
}
