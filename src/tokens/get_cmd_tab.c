/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 06:19:59 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/02 23:08:33 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "tokens.h"

static void	manage_expansion(char **str)
{
	// int		i;

	if ((*str)[0] == '~')
		replace_tilde(str);
	// i = -1;
	// while (after_equal[++i])
	// {
	// 	if (after_equal[++i] == '$')
	// 		// replace dollar
	// }
}

char 	**get_cmd_tab(t_cmd_token **token)
{
	char	**tab;
	t_list	*tmp;

	if (!(tab = ft_memalloc(sizeof(char *) * 2)))
		quit_shell(EXIT_FAILURE, MALLOC_ERR);
	if ((*token)->is_expansion)
		manage_expansion(&(*token)->token);
	tab[0] = ft_strdup((*token)->token);
	tab[1] = NULL;
	tmp = (*token)->args;
	while (tmp)
	{
		if (get_expansion_token(tmp->content))
			manage_expansion(&(*((t_cmd_token **)(tmp->content)))->token);
		ft_strtab_addend(&tab, get_token_token(tmp->content));
		tmp = tmp->next;
	}
	return (tab);
}
