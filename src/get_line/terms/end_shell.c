/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_shell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroblin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 03:57:48 by aroblin           #+#    #+#             */
/*   Updated: 2019/02/15 04:46:19 by aroblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_line.h"

int				end_shell(t_term **t, char *cmd)
{
	if (t == NULL)
	{
		reset_term();
		quit_shell(EXIT_SUCCESS, 0);
		return (0);
	}
	else if ((*t)->line == NULL)
	{
		clean_line(t);
		reset_term();
		quit_shell(EXIT_SUCCESS, 0);
		return (0);
	}
	ft_bzero(&cmd, sizeof(char[8]));
	return (1);
}

char			*end_quoting_heredoc(t_term **t, char *end_of_file)
{
	char	*tmp;

	tmp = NULL;
	clean_line(t);
	reset_term();
	if (end_of_file)
		if (!(tmp = ft_strdup(end_of_file)))
			quit_shell(EXIT_FAILURE, MALLOC_ERR);
	return (tmp);
}
