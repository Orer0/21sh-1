/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroblin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 22:18:22 by aroblin           #+#    #+#             */
/*   Updated: 2019/02/05 22:36:42 by aroblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "tokens.h"
#include "21sh.h"

int		main(int ac, char **av)
{
	pid_t pid_fils;
	int fd[2];
	char *messg;

	pipe(fd);
	pid_fils = fork();
	if (pid_fils != 0) /* Processus père */
	{
		messg = ft_strdup("bonjour");
		write(fd[1], messg, ft_strlen(messg));
	}
	return EXIT_SUCCESS;
}
