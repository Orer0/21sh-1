/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_data.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 02:22:51 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/14 01:13:16 by aroblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_DATA_H
# define SHELL_DATA_H

# include "libft.h"
# include "get_line.h"
/*
typedef struct		s_cur
{
	int				x;
	int				y;
}					t_cur;

typedef struct		s_term
{
	int				index_his;
	int				max_cur;
	int				col;
	int				nb_line;
	int				rel_line;
	int				hist_line;
	int				len_p;
	char			*line;
	char			*promtp;
	char			*sel;
	char			*selec;
	char			*current_line;
	char			*cmd;
	t_list			*history;
	t_cur			cur;
	struct termios	term;
}					t_term;
*/
typedef struct		s_ptree
{
	int				id;
	char			*data;
	int				type;
	t_list			*childs_lst;
	int				nb_childs;
	t_btree			*ast;
}					t_ptree;

/*
**	Main structure
*/

typedef struct		s_shell_data
{
	pid_t			pid;
	int				last_status;
	int				exec_next;
	char			*term;
	//char			*selec;
	int				options;
	t_list			*env_lst;
	char			**env_tab;
//	char			*current_line;
	t_list			*intern_env_lst;
	t_list			*tokens_list;
	t_ptree			*parse_tree;
	t_btree			*ast;
	t_term			*t;
//	t_list			*history;
}					t_shell_data;

t_shell_data		*shell_data_singleton();
void				quit_shell(int status, int err);

#endif
