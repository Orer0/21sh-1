/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 04:27:56 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/03 01:21:25 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "tokens.h"

static void	manage_expansion_var(char **str)
{
	// int		i;
	char	*after_equal;
	char	*before_equal;
	char	*equal;
	char	*final;

	equal = ft_strchr(*str, '=');
	equal[0] = 0;
	before_equal = ft_strdup(*str);
	equal[0] = '=';
	after_equal = ft_strdup(ft_strchr(*str, '=') + 1);
	ft_printf("before = [%s] after = [%s]\n", before_equal, after_equal);
	if (after_equal[0] == '~')
	{
		replace_tilde(&after_equal);
		ft_strdel(str);
		final = ft_strnew(ft_strlen(before_equal) + ft_strlen(after_equal) + 1);
		final = ft_strcat(final, before_equal);
		final = ft_strcat(final, "=");
		final = ft_strcat(final, after_equal);
		ft_strdel(str);
		*str = final;
	}
	// i = -1;
	// while (after_equal[++i])
	// {
	// 	if (after_equal[++i] == '$')
	// 		// replace dollar
	// }
	ft_strdel(&after_equal);
	ft_strdel(&before_equal);
}

char 	**get_var_tab(t_var_token **token)
{
	char	**tab;
	t_list	*tmp;

	if (!(tab = ft_memalloc(sizeof(char *) * 2)))
		quit_shell(EXIT_FAILURE, MALLOC_ERR);
	if ((*token)->is_expansion)
		manage_expansion_var(&(*token)->token);
	tab[0] = ft_strdup((*token)->token);
	tab[1] = NULL;
	tmp = (*token)->var_lst;
	while (tmp)
	{
		if (get_expansion_token(tmp->content))
			manage_expansion_var(&(*((t_cmd_token **)(tmp->content)))->token);
		ft_strtab_addend(&tab, get_token_token(tmp->content));
		tmp = tmp->next;
	}
	return (tab);
}
