/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 04:27:56 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/10 04:03:53 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "tokens.h"

static void build_new_str(char **div_str, char *final, int equal)
{
	char	*bef_do;
	char	**tab;
	char	*af_do;

	if (!(bef_do = ft_strsub(*div_str, 0, ft_strpos(*div_str, '$'))))
		quit_shell(EXIT_FAILURE, MALLOC_ERR);
	if (!(af_do = ft_strsub(*div_str, ft_strpos(*div_str, '$'),
					ft_strlen(*div_str) - ft_strpos(*div_str, '$'))))
		quit_shell(EXIT_FAILURE, MALLOC_ERR);
	final = ft_strdup(bef_do);
	if (!(tab = ft_strsplit(af_do, '$')))
		quit_shell(EXIT_FAILURE, MALLOC_ERR);
	replace_dollar(tab, &final);
	if ((!final))
		quit_shell(EXIT_FAILURE, MALLOC_ERR);
	ft_strdel(div_str);
	if (equal == 1)
		*div_str = ft_strjoin(final, "=");
	else
		*div_str = ft_strdup(final);
	if (*div_str == NULL)
		quit_shell(EXIT_FAILURE, MALLOC_ERR);
	ft_strtab_del(&tab);
	ft_strdel(&final);
	ft_strdel(&bef_do);
	ft_strdel(&af_do);
}

static void	manage_dollar_var(char **str)
{
	char	*before_equal;
	char	*after_equal;
	char	*final;

	final = NULL;
	if (!(before_equal = ft_strsub(*str, 0, ft_strpos(*str, '='))))
		quit_shell(EXIT_FAILURE, MALLOC_ERR);
	if (!(after_equal = ft_strsub(*str, ft_strpos(*str, '=')
		+ 1, ft_strlen(*str) - ft_strpos(*str, '='))))
		quit_shell(EXIT_FAILURE, MALLOC_ERR);
	build_new_str(&before_equal, final, 1);
	build_new_str(&after_equal, final, 0);
	ft_strdel(str);
	if (!(*str = ft_strjoin(before_equal, after_equal)))
		quit_shell(EXIT_FAILURE, MALLOC_ERR);
	ft_strdel(&before_equal);
	ft_strdel(&after_equal);
}

static void manag_tild_var(char **str, char **after_equal, char **before_equal)
{
	char	*final;

	replace_tilde(after_equal);
	ft_strdel(str);
	if (!(final = ft_strnew(ft_strlen(*before_equal)
		+ ft_strlen(*after_equal) + 1)))
		quit_shell(EXIT_FAILURE, MALLOC_ERR);
	final = ft_strcat(final, *before_equal);
	final = ft_strcat(final, "=");
	final = ft_strcat(final, *after_equal);
	ft_strdel(str);
	*str = final;
}

static void	manage_expansion_var(char **str)
{
	char	*after_equal;
	char	*before_equal;
	char	*equal;

	equal = ft_strchr(*str, '=');
	equal[0] = 0;
	if (!(before_equal = ft_strdup(*str)))
		quit_shell(EXIT_FAILURE, MALLOC_ERR);
	equal[0] = '=';
	if (!(after_equal = ft_strdup(ft_strchr(*str, '=') + 1)))
		quit_shell(EXIT_FAILURE, MALLOC_ERR);
	if (after_equal[0] == '~')
		manag_tild_var(str, &after_equal, &before_equal);
	else if (ft_strchr(*str, '$'))
		manage_dollar_var(str);
	ft_strdel(&after_equal);
	ft_strdel(&before_equal);
}

char 	**get_var_tab(t_var_token **token)
{
	char	**tab;
	t_list	*tmp;

	if (get_type_token(token) == VAR_TYPE)
	{
		if (!(tab = ft_memalloc(sizeof(char *) * 2)))
			quit_shell(EXIT_FAILURE, MALLOC_ERR);
		if ((*token)->is_expansion)
			manage_expansion_var(&(*token)->token);
		tab[0] = ft_strdup((*token)->token);
		// tab[1] = NULL;
	}
	else
	{
		if (!(tab = ft_memalloc(sizeof(char *))))
			quit_shell(EXIT_FAILURE, MALLOC_ERR);
		// tab[0] = NULL;
	}
	// ft_printf("tab[0] = %s\n", tab[0]);
	tmp = (*token)->var_lst;
	while (tmp)
	{
		if (((t_var_token *)(tmp->content))->is_expansion)
			manage_expansion_var(&(*((t_var_token **)(tmp->content)))->token);
		ft_strtab_addend(&tab, ((t_var_token *)(tmp->content))->token);
		tmp = tmp->next;
	}
	return (tab);
}
