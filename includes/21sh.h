/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 18:31:39 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/21 03:35:58 by ndubouil         ###   ########.fr       */
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

/*
** PARSER
*/

int		shell_parser(char *line);

/*
**	LEXER
*/

// int lexer(char *line, t_list **tokens_list);
// int 	first_check_tokens_list(t_list *lst);
// int 	build_command_token(t_list *lst);
// void 	delete_list_tokens(t_list **tokens_list);

/*
**	DEBUG
*/
void 	ft_print_tokens(t_list *tokens_list);

#endif
