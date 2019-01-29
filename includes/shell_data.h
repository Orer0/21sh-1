/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_data.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 02:22:51 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/29 06:09:42 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_DATA_H
# define SHELL_DATA_H

# include "st.h"
# include "libft.h"

/*
**	Main structure
*/

typedef struct		s_shell_data
{
	pid_t			pid;
	int				last_status;
	char			*shell;
	int				options;
	t_list			*env_lst;
	char			**env_tab;
	t_list			*intern_env_lst;
	t_list			*tokens_list;
	t_ptree			*parse_tree;
	t_btree			*ast;
}					t_shell_data;

t_shell_data		*shell_data_singleton();
void				quit_shell(int status, int err);

#endif
