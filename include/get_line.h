/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroblin <aroblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/12 15:13:42 by aroblin           #+#    #+#             */
/*   Updated: 2019/02/08 22:15:45 by aroblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_LINE_H
# define GET_LINE_H

// # include <fcntl.h>
// # include <dirent.h>
// # include <sys/types.h>
// # include <sys/stat.h>
// # include <grp.h>
// # include <uuid/uuid.h>
# include "../libft/include/libft.h"
// # include <limits.h>
# include <stdio.h> // a sup
// # include <curses.h>
# include <term.h>
// # include <termcap.h>
# include <sys/ioctl.h>
# include "shell_data.h"

# define LE 1
# define ND 2
# define ON 1
# define OFF 0

typedef struct		s_cur
{
	int				x;
	int				y;
}					t_cur;

typedef struct		s_term
{
	t_cur			cur;
	int				index_his;
	int				max_cur;
	int				col;
	int				nb_line;
	int				rel_line;
	int				hist_line;
	struct termios	term;
	char			*line;
	char			*promtp;
	char			*sel;
	int				len_p;
}					t_term;

int					init_termios(void);
int					reset_term(void);

void				set_terms(t_term **t, char *promtp);

char				*manag_way(t_term **t);
void				*way(t_term **t, char *cmd);
void				cmd_way(void (*fonct)(t_term **), t_term **t, char *cmd);
void				*set_cmd_his(char *cmd);
void				*set_cmd_mouv(char *cmd);
void				*set_cmd_edit(char *cmd);

void				ft_right(t_term **t);
void				ft_left(t_term **t);
void				word_left(t_term **t);
void				word_right(t_term **t);

char				*enter(t_term **t);

void				clean_line(t_term **t);
int					end_shell(t_term **t, char *cmd);

void				multi_up(t_term **t);
void				multi_down(t_term **t);

void				selec(t_term **t);
int					selec_right(t_term **t, int rel_cur, int tmp_cur);
int					selec_left(t_term **t, int rel_cur);
void				paste(t_term **t);
void				cut(t_term **t, int rel_cur, int tmp);

void				print_buf_end(char *buf, t_term **t);
void				print_insertion(t_term **t, char *buf);

void				cur_begin_line(t_term **t);
void				cur_end_line(t_term **t);
void				go_way(t_term **t, int nb, int way);

int					supp(t_term **t);
void				del(t_term **t);
void				new_line(t_term **t, int len, int size);

int					history_up(t_term **t);
int					history_down(t_term **t);

void				delete_all(int len, t_term **t);

int					ft_is_space(int c);
int					put(int c);
int					putst(char *c);

#endif
