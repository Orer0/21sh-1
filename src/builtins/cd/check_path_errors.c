/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path_errors.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 19:37:05 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/29 08:30:31 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

int		check_path_errors(char *path)
{
	struct stat st;

	if ((stat(path, &st)) < 0)
	{
		ft_printf("21sh: cd: no such file or directory: %s\n", path);
		return (FALSE);
	}
	else
	{
		if (!S_ISDIR(st.st_mode))
		{
			ft_printf("21sh: cd: not a directory: %s\n", path);
			return (FALSE);
		}
	}
	return (TRUE);
}
