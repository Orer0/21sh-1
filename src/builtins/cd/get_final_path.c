/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_final_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 19:33:08 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/10 05:59:47 by aroblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static char		*get_complete_path(char *parent, char *name)
{
	char	*tmp;
	char	*result;

	if (parent == NULL || name == NULL)
		return (NULL);
	if (name[0] == '/')
		return (name);
	if (name[0] == '.' && name[1] == '/')
	{
		if (!(tmp = ft_strdup(&name[2])))
			return (NULL);
		ft_strdel(&name);
		name = tmp;
	}
	if (parent[ft_strlen(parent) - 1] == '/')
		tmp = ft_strdup(parent);
	else
		tmp = ft_strjoin(parent, "/");
	if (!tmp)
		return (NULL);
	if (!(result = ft_strjoin(tmp, name)))
		return (NULL);
	ft_strdel(&tmp);
	return (result);
}

static void		clean_absolute_path(char **path)
{
	char **pwd_tab;
	char *str;

	if ((*path)[0] == '/' && (*path)[1] != '.')
	{
		if (!(pwd_tab = ft_strsplit(*path, '/')))
			return ;
		if (!(str = ft_strjointab(pwd_tab, '/')))
		{
			ft_strtab_del(&pwd_tab);
			return ;
		}
		ft_strtab_del(&pwd_tab);
		ft_strdel(path);
		*path = ft_strdup(str);
		ft_strdel(&str);
	}
}

static void		del_tab(char ***arg_tab, char ***pwd_tab)
{
	ft_strtab_del(arg_tab);
	ft_strtab_del(pwd_tab);
}

char			*get_final_path(char **path)
{
	char			**arg_tab;
	char			**pwd_tab;
	char			*pwd;
	char			*str;
	t_shell_data	*data;

	data = shell_data_singleton();
	if (!(pwd = get_env_var_by_name(&data->env_lst, "PWD")->content))
		getcwd(pwd, sizeof(char *));
	clean_absolute_path(path);
	if ((*path)[0] == '/' && (*path)[1] != '.')
		return (ft_strdup(get_complete_path(pwd, *path)));
	if (!(arg_tab = ft_strsplit(*path, '/')))
		return (NULL);
	if (!(pwd_tab = ft_strsplit(pwd, '/')))
		return (NULL);
	if (!build_pwd_tab(&arg_tab, &pwd_tab, ft_stringtab_len(pwd_tab)))
	{
		del_tab(&arg_tab, &pwd_tab);
		return (NULL);
	}
	if (!(str = ft_strjointab(pwd_tab, '/')))
		return (NULL);
	del_tab(&arg_tab, &pwd_tab);
	return (str);
}
