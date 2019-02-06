/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 04:27:56 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/06 05:48:53 by aroblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "tokens.h"

static char		*get_env_var(char *name)
{
	t_varenv	*var;
	char	*content;
	t_shell_data	*data;

	data = shell_data_singleton();
	var = get_env_var_by_name(&data->intern_env_lst, name);
	if (var)
		content = ft_strdup(var->content);
	else
		content = ft_strdup("");
	if (!content)
		quit_shell(EXIT_FAILURE, MALLOC_ERR);
	return (content);
}

static void	manage_dollar_var(char **str, int pos)
{
	(void)pos;
	char	*before_equal;
	char	*after_equal;
	char	**tab;
	int i = 0;
	char	*tmp;
	char	*final;

	final = NULL;
	tmp = NULL;
	tab = NULL;
	before_equal = ft_strsub(*str, 0, ft_strpos(*str, '='));
	after_equal = ft_strsub(*str, ft_strpos(*str, '=') + 1, ft_strlen(*str) - ft_strpos(*str, '='));
	ft_printf("before = [%s] after = [%s]\n", before_equal, after_equal);
	tab = ft_strsplit(before_equal, '$');
	while (tab[i] != NULL)
	{
		tmp = get_env_var(tab[i]);
		if (final == NULL)
			final = ft_strdup(tmp);
		else
			final = ft_strjoin_free_s1(&final, &tmp);
		ft_strdel(&tmp);
		i++;
	}
	if (final == NULL)
		final = ft_strdup(before_equal);
	ft_strtab_del(&tab);
	tab = ft_strsplit(after_equal, '$');
	while (tab[i] != NULL)
	{
		tmp = get_env_var(tab[i]);
		if (final == NULL)
			final = ft_strdup(tmp);
		else
			final = ft_strjoin_free_s1(&final, &tmp);
		ft_strdel(&tmp);
		i++;
	}
	final = ft_strjoin_add(after_equal, final, '=');
	ft_strdel(str);
	ft_strtab_del(&tab);
	*str = ft_strdup(final);
	ft_strdel(&final);
	ft_strdel(&before_equal);
	ft_strdel(&after_equal);
}

static void	manage_expansion_var(char **str, int pos)
{
	char	*after_equal;
	char	*before_equal;
	char	*equal;
	char	*final;

	equal = ft_strchr(*str, '=');
	equal[0] = 0;
	before_equal = ft_strdup(*str);
	equal[0] = '=';
	after_equal = ft_strdup(ft_strchr(*str, '=') + 1);
	//ft_printf("before = [%s] after = [%s]\n", before_equal, after_equal);
//	ft_printf("%d = pos\n", pos);
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
	else
	{
		manage_dollar_var(str, pos);
	}
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
		manage_expansion_var(&(*token)->token, (*token)->is_expansion);
//	ft_printf("%d = token_len", (*token)->is_expansion);
//	ft_printf("   %s = token", (*token)->token);
	tab[0] = ft_strdup((*token)->token);
	tab[1] = NULL;
	tmp = (*token)->var_lst;
	while (tmp)
	{
		if (get_expansion_token(tmp->content))
			manage_expansion_var(&(*((t_cmd_token **)(tmp->content)))->token, (*token)->is_expansion);
		ft_strtab_addend(&tab, get_token_token(tmp->content));
		tmp = tmp->next;
	}
	return (tab);
}
