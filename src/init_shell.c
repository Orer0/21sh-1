/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 04:48:20 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/20 23:40:08 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static void		manage_shell_level(void)
{
	t_shell_data	*data;
	t_varenv		*env_shlvl;
	int				shlvl;
	char			*tmp;

	data = shell_data_singleton();
	if (!(env_shlvl = get_env_var_by_name(&data->env_lst, "SHLVL")))
		shlvl = 0;
	else
		shlvl = ft_atoi(env_shlvl->content);
	tmp = ft_itoa(shlvl + 1);
	change_env_var(&data->env_lst, "SHLVL", tmp);
	change_env_var(&data->intern_env_lst, "SHLVL", tmp);
	ft_strdel(&tmp);
	env_lst_to_tab(&data->env_lst, &data->env_tab);
	env_tab_to_lst(&data->intern_env_lst, data->env_tab);
}

void			init_shell(char **environ)
{
	t_shell_data	*data;
	t_varenv		*term;

	data = shell_data_singleton();
	if (!env_tab_to_lst(&data->env_lst, environ))
		create_minimal_env();
	term = get_env_var_by_name(&data->env_lst, "TERM");
	if ((term && term->content[0]) && isatty(0))
		data->term = ft_strdup(term->content);
	else
	{
		change_env_var(&data->env_lst, "TERM", "xterm");
		change_env_var(&data->intern_env_lst, "TERM", "xterm");
		data->term = ft_strdup("xterm");
	}
	manage_shell_level();
}
