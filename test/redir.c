/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroblin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 05:52:22 by aroblin           #+#    #+#             */
/*   Updated: 2019/02/02 20:21:57 by aroblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <fcntl.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "../libft/include/libft.h"

int		main(int ac, char **av, char **env)
{
	pid_t pid;
	int status;
	char	*command = "/bin/cat";
	int		ret;
	int		fd;
	char	**tab;
	int		fd_pip[2];

	char	mess[100] = "bonjour";

	tab  = ft_strsplit(command, ' ');

	//fd = open("out", O_WRONLY | O_CREAT | O_APPEND, S_IRWXU); // double redr droite
	//fd = open("out", O_WRONLY | O_CREAT, S_IRWXU);// simple redir == ecrase
	fd = open("out", O_RDONLY, S_IRWXU);// lecture depuis fichier
	status = 0;
//	dup2(fd, 1);// redir standar droite
//	dup2(fd, 2);// redir erreur droite
//	dup2(fd, 0);// redir entre standard
	if (execve(command, tab, env) < 0)
	{
		printf("test\n");
		exit(0);
	}
	close(fd);
	return (0);
}
