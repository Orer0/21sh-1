/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_var_by_name.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 19:56:05 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/29 02:18:53 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

t_varenv		*get_env_var_by_name(t_list **lst, char *name)
{
	t_list	*tmp;

	tmp = *lst;
	while (tmp)
	{
		if (ft_strcmp(((t_varenv *)(tmp->content))->name, name) == 0)
			return (((t_varenv *)(tmp->content)));
		tmp = tmp->next;
	}
	return (NULL);
}
