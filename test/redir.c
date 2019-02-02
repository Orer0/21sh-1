/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroblin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 05:52:22 by aroblin           #+#    #+#             */
/*   Updated: 2019/02/02 06:02:25 by aroblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <fcntl.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

int		main(int ac, char **av)
{
	pid_t pid;
	int status;
	char	*command = "ls";
	int		ret;

	ret = open("out", O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
	status = 0;
//	pid = fork();
//	if (pid == -1)
//	{
//		return (-1);
//	}
//	else if (pid == 0)
//	{
		dup2(ret, 1);
		if (execve(command, NULL, NULL) < 0)
		{
			printf("test\n");
			exit(0);
		}
//	}
//	else
//		wait(&status);
	return (0);
}
