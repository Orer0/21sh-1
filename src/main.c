/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 18:30:34 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/21 20:39:24 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

t_shell_data	*shell_data_singleton()
{
	static t_shell_data *data;

	if (!data)
	{
		if (!(data = ft_memalloc(sizeof(t_shell_data))))
			quit_shell(EXIT_SUCCESS, MALLOC_ERR);
	}
	return (data);
}

int		main(int ac, char **av)
{
	if (ac != 2)
		return (EXIT_SUCCESS);
	shell_parser(av[1]);
	quit_shell(EXIT_SUCCESS, 0);
	return (EXIT_SUCCESS);
}
