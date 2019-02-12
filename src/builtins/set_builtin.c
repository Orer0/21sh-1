/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 21:03:19 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/12 05:27:47 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static void		print_intern_env(t_list *lst)
{
	t_list	*tmp;

	tmp = lst;
	while (tmp)
	{
		ft_printf("%s=%s\n", ((t_varenv *)(tmp->content))->name,
			((t_varenv *)(tmp->content))->content);
		tmp = tmp->next;
	}
}

int				set_builtin(char **args)
{
	int				i;
	t_shell_data	*data;
	char			**tab;

	data = shell_data_singleton();
	if (args[0])
	{
		i = -1;
		while (args[++i])
		{
			if (!(tab = ft_strsplit(args[i], '=')))
				quit_shell(EXIT_FAILURE, MALLOC_ERR);
			change_env_var(&data->intern_env_lst, tab[0],
				&args[i][ft_strlen(tab[0]) + 1]);
			if (get_env_var_by_name(&data->env_lst, tab[0]))
				change_env_var(&data->env_lst, tab[0],
					&args[i][ft_strlen(tab[0]) + 1]);
			ft_strtab_del(&tab);
		}
	}
	else
		print_intern_env(data->intern_env_lst);
	return (EXIT_SUCCESS);
}
