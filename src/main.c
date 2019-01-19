/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 18:30:34 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/19 03:39:36 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

int		main(int ac, char **av)
{
	t_list		*tokens_list;

	if (ac != 2)
		return (EXIT_SUCCESS);
	ft_printf("chaine recu : %s\n", av[1]);
	lexer(av[1], &tokens_list);
	ft_print_tokens(tokens_list);
	delete_list_tokens(&tokens_list);
	return (EXIT_SUCCESS);
}
