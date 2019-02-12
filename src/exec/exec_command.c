/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 02:21:06 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/11 23:08:44 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int		exec_command(char **command, char **env)
{
	int				status;
	char			*final_path;
	t_shell_data	*data;

	data = shell_data_singleton();
	if (!command[0][0] || !(final_path = get_path_of_bin(command[0])))
		return (FALSE);
	data->pid = fork();
	if (data->pid == 0)
	{
		if (!execve(final_path, command, env))
			exit(EXIT_FAILURE);
	}
	else if (data->pid < 0)
		quit_shell(EXIT_FAILURE, FORK_ERR);
	else if (data->pid > 0)
	{
		signal(SIGINT, catch_signal_kill);
		waitpid(data->pid, &status, 0);
		data->last_status = status;
	}
	ft_strdel(&final_path);
	return (TRUE);
}
