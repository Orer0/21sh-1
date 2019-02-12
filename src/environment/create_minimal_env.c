/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_minimal_env.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 23:48:25 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/03 00:02:44 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void		create_minimal_env(void)
{
	t_shell_data	*data;

	data = shell_data_singleton();
	change_env_var(&data->env_lst, "SHLVL", "0");
	change_env_var(&data->env_lst, "PWD", getcwd(NULL, sizeof(char *)));
	change_env_var(&data->env_lst, "PATH", "/bin:/usr/bin");
	change_env_var(&data->env_lst, "TERM", "xterm");
}
