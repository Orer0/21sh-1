/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 21:03:19 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/13 18:11:10 by aroblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

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

int				set_builtin(char **args, t_shell_data **data)
{
	int				i;
	char			**arr;

	if (args[0])
	{
		i = -1;
		while (args[++i])
		{
			if (!(arr = ft_strsplit(args[i], '=')))
				quit_shell(EXIT_FAILURE, MALLOC_ERR);
			if (arr[1])
				change_env_var(&(*data)->intern_env_lst, arr[0]
					, &args[i][ft_strlen(arr[0]) + 1]);
			else
				change_env_var(&(*data)->intern_env_lst, arr[0], NULL);
			if (get_env_var_by_name(&(*data)->env_lst, arr[0]))
				change_env_var(&(*data)->env_lst, arr[0]
					, &args[i][ft_strlen(arr[0]) + 1]);
			ft_strtab_del(&arr);
		}
	}
	else
		print_intern_env((*data)->intern_env_lst);
	return (EXIT_SUCCESS);
}
