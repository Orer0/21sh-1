/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var_tab_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 03:29:28 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/18 22:44:31 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "tokens.h"

static void	del_all_str(char ***arr, char **final, char **bef_do, char **af_do)
{
	ft_strtab_del(arr);
	ft_strdel(final);
	ft_strdel(bef_do);
	ft_strdel(af_do);
}

static void	build_new_str(char **div_str, char *final, int equal)
{
	char	*bef_do;
	char	**arr;
	char	*af_do;

	if (!(bef_do = ft_strsub(*div_str, 0, ft_strpos(*div_str, '$'))))
		quit_shell(EXIT_FAILURE, MALLOC_ERR);
	if (!(af_do = ft_strsub(*div_str, ft_strpos(*div_str, '$'),
					ft_strlen(*div_str) - ft_strpos(*div_str, '$'))))
		quit_shell(EXIT_FAILURE, MALLOC_ERR);
	final = ft_strdup(bef_do);
	if (!(arr = ft_strsplit(af_do, '$')))
		quit_shell(EXIT_FAILURE, MALLOC_ERR);
	replace_dollar(arr, &final);
	if ((!final))
		quit_shell(EXIT_FAILURE, MALLOC_ERR);
	ft_strdel(div_str);
	if (equal == 1)
		*div_str = ft_strjoin(final, "=");
	else
		*div_str = ft_strdup(final);
	if (*div_str == NULL)
		quit_shell(EXIT_FAILURE, MALLOC_ERR);
	del_all_str(&arr, &final, &bef_do, &af_do);
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

static void	manag_tild_var(char **str, char **after_equal, char **before_equal)
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

void		manage_expansion_var(char **str)
{
	char	*after_equal;
	char	*before_equal;
	char	*equal;

	equal = ft_strchr(*str, '=');
	if (!equal)
		return ;
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
