/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 18:26:03 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/11 00:41:07 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static int		set_options(char *ops, int *options, int pos)
{
	if (ops[pos] == '\0')
		return (FALSE);
	if (is_valid_option(ops[pos], OPTIONS_CD))
	{
		if (ops[pos] == 'L')
			*options |= OPT_L;
		else if (ops[pos] == 'P')
			*options |= OPT_P;
	}
	else
	{
		ft_printf("21sh: cd: illegal option -- %c\nusage: cd [-%s] [dir]\n"
			, ops[pos], OPTIONS_CD);
		return (FALSE);
	}
	set_options(ops, options, (pos + 1));
	return (TRUE);
}

static int		manage_pwd(char *oldpwd, char *pwd, int options)
{
	t_shell_data	*data;

	data = shell_data_singleton();
	if (!(change_env_var(&data->env_lst, "OLDPWD", oldpwd)))
		return (FALSE);
	if (options & OPT_P)
	{
		if (!(change_env_var(&data->env_lst, "PWD", getcwd(NULL, 0))))
			return (FALSE);
	}
	else
	{
		if (!(change_env_var(&data->env_lst, "PWD", pwd)))
			return (FALSE);
	}
	return (TRUE);
}

int				change_directory(char *pwd, char *oldpwd, int options)
{
	if (!check_path_errors(pwd))
		return (FALSE);
	if ((chdir(pwd)) < 0)
	{
		ft_printf("21sh: cd: %s: Permission denied\n", pwd);
		return (FALSE);
	}
	return (manage_pwd(oldpwd, pwd, options));
}

static void		manag_oldpwd(char **oldpwd)
{
	t_varenv		*tmp;
	t_shell_data	*data;

	data = shell_data_singleton();
	if (!(tmp = get_env_var_by_name(&data->env_lst, "PWD")))
	{
		change_env_var(&data->env_lst, "PWD", getcwd(NULL, sizeof(char *)));
		tmp = get_env_var_by_name(&data->env_lst, "PWD");
	}
	*oldpwd = tmp->content;
}

int				cd_builtin(char **args)
{
	char			*oldpwd;
	char			*pwd;
	int				pos_args;
	int				options;

	oldpwd = NULL;
	options = 0;
	pos_args = 0;
	options_parser(args, &options, &pos_args, set_options);
	manag_oldpwd(&oldpwd);
	if (!(pwd = get_pwd_for_cd(pos_args, args)))
		return (EXIT_FAILURE);
	if (!change_directory(pwd, oldpwd, options))
	{
		ft_strdel(&pwd);
		return (EXIT_FAILURE);
	}
	ft_strdel(&pwd);
	return (EXIT_SUCCESS);
}
