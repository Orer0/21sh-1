/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_pwd_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 19:34:08 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/29 08:34:59 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static int		dotdot_case(char ***pwd_tab, int *pwd_tab_len)
{
	if (*pwd_tab_len <= 0)
		return (TRUE);
	ft_strdel(&(*pwd_tab)[(*pwd_tab_len) - 1]);
	(*pwd_tab)[(*pwd_tab_len) - 1] = NULL;
	if (!(*pwd_tab)[0])
	{
		if (!(ft_realloc_addend_tab(pwd_tab, "")))
			return (FALSE);
	}
	else
		(*pwd_tab_len)--;
	return (TRUE);
}

static int		check_validity_path(char ***pwd_tab)
{
	char *tmp;

	if (!(tmp = ft_strjointab(*pwd_tab, '/')))
		return (FALSE);
	if (!check_path_errors(tmp))
	{
		ft_strdel(&tmp);
		return (FALSE);
	}
	ft_strdel(&tmp);
	return (TRUE);
}

int				build_pwd_tab(char ***arg_tab, char ***pwd_tab, int pwd_tab_len)
{
	int		i;

	i = -1;
	while ((*arg_tab)[++i])
	{
		if (ft_strcmp((*arg_tab)[i], "..") == 0)
		{
			if (!dotdot_case(pwd_tab, &pwd_tab_len))
				return (FALSE);
		}
		else if (ft_strcmp((*arg_tab)[i], ".") == 0)
			continue;
		else
		{
			if (!(ft_realloc_addend_tab(pwd_tab, (*arg_tab)[i])))
				return (FALSE);
			pwd_tab_len++;
		}
		if (!check_validity_path(pwd_tab))
			return (FALSE);
	}
	return (TRUE);
}
