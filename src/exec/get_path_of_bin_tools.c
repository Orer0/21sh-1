/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_of_bin_tools.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 23:13:21 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/11 23:14:17 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void		del_data_path(char **new_path, char ***env_paths)
{
	ft_strdel(new_path);
	ft_strtab_del(env_paths);
}

void		*return_perm_denied(char *str)
{
	ft_printf("21sh: %s: Permission denied\n", str);
	return (NULL);
}

void		*return_cmd_not_found(char *str)
{
	ft_printf("21sh: command not found: %s\n", str);
	return (NULL);
}
