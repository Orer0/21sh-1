/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 17:41:36 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/21 18:12:22 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "lexer.h"

void	quit_shell(int status, int err)
{
	t_shell_data *data;

	if (err == MALLOC_ERR)
		write(2, "21sh: malloc failed", 19);
	data = shell_data_singleton();
	delete_list_tokens();
	ft_memdel((void **)&data);
	exit(status);
}
