/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 18:31:39 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/22 03:19:25 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TWENTYONE_SH_H
# define TWENTYONE_SH_H

# include "libft.h"
# include "libftprintf.h"
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <limits.h>
# include <fcntl.h>

# include "tokens.h"
# include "st.h"

/*
** Errors
*/

enum	e_err
{
	MALLOC_ERR = -999,
};

/*
**	Main structure
*/

typedef struct		s_shell_data
{
	t_list			*tokens_list;
	t_ptree			*parse_tree;
	t_btree			*ast;
}					t_shell_data;

/*
** quit_shell
*/

t_shell_data		*shell_data_singleton();
void				quit_shell(int status, int err);


/*
** PARSER functions
*/

int		shell_parser(char *line);


#endif
