/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 23:03:35 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/10 04:04:19 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "ast.h"
#define READ_END	0
#define WRITE_END	1

void 	run_pipe(t_btree *tree)
{
	int		tab[2];
	pid_t	pid;

	pipe(tab);
	pid = fork();
	if (pid == 0)
	{
		dup2(tab[WRITE_END], 1);
		close(tab[READ_END]);
		exec_ast(tree->left, TRUE);
		exit(EXIT_SUCCESS);
	}
	else if (pid < 0)
		ft_printf("fail fork\n");
	else if (pid > 0)
	{
		signal(SIGINT, catch_signal_kill);
		dup2(tab[READ_END], 0);
		close(tab[WRITE_END]);
		exec_ast(tree->right, TRUE);
		kill(pid, SIGTERM);
		wait(NULL);
	}
}

void 	pipe_execution(t_btree *tree)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		run_pipe(tree);
		exit(EXIT_SUCCESS);
	}
	else if (pid < 0)
		ft_printf("fail fork\n");
	else if (pid > 0)
	{
		wait(NULL);
	}
}
