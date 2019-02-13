/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 22:29:09 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/13 18:16:17 by aroblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static void		print_env(t_list *lst)
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

int				setenv_builtin(char **args, t_shell_data **data)
{
	int				i;
	char			**tab;

	if (args[0])
	{
		i = -1;
		while (args[++i])
		{
			if (!(tab = ft_strsplit(args[i], '=')))
				quit_shell(EXIT_FAILURE, MALLOC_ERR);
			if (tab[1])
				change_env_var(&(*data)->env_lst, tab[0]
					, &args[i][ft_strlen(tab[0]) + 1]);
			else
				change_env_var(&(*data)->env_lst, tab[0], NULL);
			if (get_env_var_by_name(&(*data)->intern_env_lst, tab[0]))
				change_env_var(&(*data)->intern_env_lst, tab[0]
					, &args[i][ft_strlen(tab[0]) + 1]);
			ft_strtab_del(&tab);
		}
	}
	else
		print_env((*data)->env_lst);
	return (EXIT_SUCCESS);
}
