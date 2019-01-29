/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_minimal_env.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 23:48:25 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/28 23:51:29 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void		create_minimal_env(void)
{
	t_shell_data	*data;

	data = shell_data_singleton();
	change_env_var(&data->env_lst, "SHLVL", "0");
	change_env_var(&data->env_lst, "PWD", getcwd(NULL, sizeof(char *)));
	change_env_var(&data->env_lst, "PATH", "/bin:/usr/bin");
}
