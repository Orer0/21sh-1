/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 20:58:16 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/11 22:37:00 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static void			reset_env_tab(void)
{
	t_shell_data	*data;

	data = shell_data_singleton();
	ft_strtab_del(&data->env_tab);
	if (!env_lst_to_tab(&data->env_lst, &data->env_tab))
		quit_shell(EXIT_FAILURE, MALLOC_ERR);
}

static void			give_data(char **cmd)
{
	t_shell_data	*data;

	data = shell_data_singleton();
	if (ft_strequ(cmd[0], "cd"))
		data->last_status = cd_builtin(cmd);
	else if (ft_strequ(cmd[0], "set"))
		data->last_status = set_builtin(&cmd[1]);
	else if (ft_strequ(cmd[0], "setenv"))
		data->last_status = setenv_builtin(&cmd[1]);
	else if (ft_strequ(cmd[0], "export"))
		data->last_status = export_builtin(&cmd[1]);
	else if (ft_strequ(cmd[0], "unset"))
		data->last_status = unset_builtin(&cmd[1]);
	else if (ft_strequ(cmd[0], "unsetenv"))
		data->last_status = unsetenv_builtin(&cmd[1]);
	reset_env_tab();
}

int					manage_builtins(char **cmd)
{
	t_shell_data	*data;

	data = shell_data_singleton();
	if (ft_strequ(cmd[0], "exit"))
		exit_builtin(cmd);
	else if (ft_strequ(cmd[0], "cd") || ft_strequ(cmd[0], "set")
		|| ft_strequ(cmd[0], "export") || ft_strequ(cmd[0], "unset")
		|| ft_strequ(cmd[0], "setenv") || ft_strequ(cmd[0], "unsetenv"))
		give_data(cmd);
	else if (ft_strequ(cmd[0], "echo"))
		data->last_status = echo_builtin(cmd);
	else
		return (FALSE);
	return (TRUE);
}
