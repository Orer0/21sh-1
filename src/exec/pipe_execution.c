/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 23:03:35 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/16 02:41:55 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "ast.h"

static void		run_pipe(t_btree *tree)
{
	int		arr[2];
	pid_t	pid;
	int		fd;

	pipe(arr);
	pid = fork();
	if (pid == 0)
	{
		fd = dup2(arr[WRITE_END], 1);
		close(arr[READ_END]);
		exec_ast(tree->left, TRUE);
		close(arr[WRITE_END]);
		close(fd);
		exit(EXIT_SUCCESS);
	}
	else if (pid < 0)
		quit_shell(EXIT_FAILURE, FORK_ERR);
	signal(SIGINT, catch_signal_kill);
	fd = dup2(arr[READ_END], 0);
	close(arr[WRITE_END]);
	exec_ast(tree->right, TRUE);
	kill(pid, SIGTERM);
	close(arr[READ_END]);
	close(fd);
	wait(NULL);
}

void			pipe_execution(t_btree *tree)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		run_pipe(tree);
		exit(EXIT_SUCCESS);
	}
	else if (pid < 0)
		quit_shell(EXIT_FAILURE, FORK_ERR);
	else if (pid > 0)
	{
		wait(NULL);
	}
}
