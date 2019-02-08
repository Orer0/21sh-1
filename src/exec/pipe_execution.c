/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 23:03:35 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/08 04:42:57 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#define READ_END	0
#define WRITE_END	1

void 	run_pipe(t_btree *tree)
{
	// creer le pipe
	// exectuer le noeud de gauche
	int		tab[2];
	pid_t	pid;
	// int status;
	t_shell_data *data;

	data = shell_data_singleton();
	pipe(tab);

	pid = fork();
	// enfant
	if (pid == 0)
	{
		dup2(tab[WRITE_END], 1);
		close(tab[READ_END]);
		// ft_fd_printf(2, "dans le fils\n");
		// execve("/bin/ls", ["/bin/ls", "-l"], NULL);
		exec_ast(tree->left, TRUE);
		exit(0);
	}
	else if (pid < 0)
		ft_printf("fail fork\n");
	// pere
	else if (pid > 0)
	{
		// signal(SIGINT, catch_signal_kill);
		dup2(tab[READ_END], 0);
		close(tab[WRITE_END]);
		// ft_fd_printf(2, "dans le pere avant le wait\n");
		// char buff[512];
		wait(NULL);
		// ft_fd_printf(2, "dans le pere apres le wait\n");
		// read(0, buff, 100);
		// ft_printf("buffer du read = %s\n", buff);
		exec_ast(tree->right, TRUE);
	}
}

void 	pipe_execution(t_btree *tree)
{
	// creer le pipe
	// exectuer le noeud de gauche
	int		tab[2];
	pid_t	pid;
	// int status;
	t_shell_data *data;

	(void)tree;
	data = shell_data_singleton();
	pipe(tab);

	pid = fork();
	// enfant
	if (pid == 0)
	{
		run_pipe(tree);
		exit(0);
	}
	else if (pid < 0)
		ft_printf("fail fork\n");
	// pere
	else if (pid > 0)
	{
		wait(NULL);
	}
}
