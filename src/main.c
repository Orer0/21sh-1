/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 18:30:34 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/28 07:39:48 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

int		main(int ac, char **av)
{
	if (ac != 2)
		return (EXIT_SUCCESS);
	shell_parser(av[1]);
	quit_shell(EXIT_SUCCESS, 0);
	return (EXIT_SUCCESS);
}
