/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_dollar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroblin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 02:35:39 by aroblin           #+#    #+#             */
/*   Updated: 2019/02/07 02:42:31 by aroblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void	replace_dollar(char **tab, char **final) // utilse dans get_var_tab aussi
{
	int		i;
	char	*tmp;

	tmp = NULL;
	i = 0;
	while (tab[i] != NULL)
	{
		tmp = get_env_var(tab[i]);
		if (!(final) && tmp)
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
