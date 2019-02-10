/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 01:54:20 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/10 06:01:11 by aroblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static void		export_intern_var(char *name)
{
	t_varenv		*var;
	t_shell_data	*data;

	data = shell_data_singleton();
	var = get_env_var_by_name(&data->intern_env_lst, name);
	if (var)
		change_env_var(&data->env_lst, var->name, var->content);
	else
		change_env_var(&data->env_lst, name, NULL);
}

int				export_builtin(char **args)
{
	int				i;
	t_shell_data 	*data;
	char			**tab;

	data = shell_data_singleton();
	if (args[0])
	{
		i = -1;
		while (args[++i])
		{
			if (ft_strchr(args[i], '='))
			{
				if (!(tab = ft_strsplit(args[i], '=')))
					quit_shell(EXIT_FAILURE, MALLOC_ERR);
				change_env_var(&data->env_lst, tab[0],
					&args[i][ft_strlen(tab[0]) + 1]);
				ft_strtab_del(&tab);
			}
			else
				export_intern_var(args[i]);
		}
	}
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
