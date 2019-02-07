/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 06:19:59 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/07 02:31:32 by aroblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "tokens.h"
#include "lexer.h"

static char		*get_env_var(char *name) // enlever static)
{
 	t_varenv	*var;
	char	*content;
	t_shell_data	*data;

	data = shell_data_singleton();
	var = get_env_var_by_name(&data->intern_env_lst, name);
	if (var)
		content = ft_strdup(var->content);
	else
		return (NULL);
	if (!content)
		quit_shell(EXIT_FAILURE, MALLOC_ERR);
	return (content);
}

static void replace_dollar(char **tab, char **final) // utilse dans get_var_tab aussi
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
