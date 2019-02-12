/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 06:19:59 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/10 01:02:35 by aroblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "tokens.h"

static void		get_dollar(char **str)
{
	char	*bef_do;
	char	**tab;
	char	*af_do;
	char	*final;

	final = NULL;
	if (!(bef_do = ft_strsub(*str, 0, ft_strpos(*str, '$'))))
		quit_shell(EXIT_FAILURE, MALLOC_ERR);
	if (!(af_do = ft_strsub(*str, ft_strpos(*str, '$'),
					ft_strlen(*str) - ft_strpos(*str, '$'))))
		quit_shell(EXIT_FAILURE, MALLOC_ERR);
	final = ft_strdup(bef_do);
	if (!(tab = ft_strsplit(af_do, '$')))
		quit_shell(EXIT_FAILURE, MALLOC_ERR);
	replace_dollar(tab, &final);
	if ((!final))
		quit_shell(EXIT_FAILURE, MALLOC_ERR);
	ft_strdel(str);
	*str = ft_strdup(final);
	if (*str == NULL)
		quit_shell(EXIT_FAILURE, MALLOC_ERR);
	ft_strtab_del(&tab);
	ft_strdel(&final);
	ft_strdel(&bef_do);
	ft_strdel(&af_do);
}

static void		manage_expansion_cmd(char **str)
{
	if ((*str)[0] == '~')
		replace_tilde(str);
	else if (ft_strchr(*str, '$'))
		get_dollar(str);
}

char			**get_cmd_tab(t_cmd_token **token)
{
	char	**tab;
	t_list	*tmp;

	if (!(tab = ft_memalloc(sizeof(char *) * 2)))
		quit_shell(EXIT_FAILURE, MALLOC_ERR);
	if ((*token)->is_expansion)
		manage_expansion_cmd(&(*token)->token);
	tab[0] = ft_strdup((*token)->token);
	tab[1] = NULL;
	tmp = (*token)->args;
	while (tmp)
	{
		if (get_expansion_token(tmp->content))
			manage_expansion_cmd(&(*((t_cmd_token **)(tmp->content)))->token);
		ft_strtab_addend(&tab, get_token_token(tmp->content));
		tmp = tmp->next;
	}
	return (tab);
}
