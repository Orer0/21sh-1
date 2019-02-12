/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_dollar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroblin <aroblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 02:35:39 by aroblin           #+#    #+#             */
/*   Updated: 2019/02/12 22:44:23 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	replace_dollar(char **tab, char **final)
{
	int		i;
	char	*tmp;

	tmp = NULL;
	i = 0;
	while (tab[i] != NULL)
	{
		tmp = get_env_var(tab[i]);
		if (!(*final) && tmp)
			*final = ft_strdup(tmp);
		else if (!(*final) && !(tmp))
			*final = ft_strdup(tab[i]);
		else if (tmp)
			*final = ft_strjoin_free_s1(final, &tmp);
		else
			*final = ft_strjoin_free_s1(final, &tab[i]);
		ft_strdel(&tmp);
		i++;
	}
}
