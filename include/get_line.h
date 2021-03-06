/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroblin <aroblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/12 15:13:42 by aroblin           #+#    #+#             */
/*   Updated: 2019/02/16 02:05:35 by aroblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_LINE_H
# define GET_LINE_H

# include "libft.h"
# include <sys/ioctl.h>
# include "shell_data.h"

# define LE		1
# define ND		2

int					init_termios(void);
int					reset_term(void);
void				reset_curse(t_term **t);

void				set_terms(t_term **t, char *promtp);

char				*manag_way(t_term **t, char *end_of_file);
void				*way(char *cmd);
void				cmd_way(void (*fonct)(t_term **), t_term **t, char *cmd);
void				*set_cmd_his(char *cmd);
void				*set_cmd_mouv(char *cmd);
void				*set_cmd_edit(char *cmd);

void				ft_right(t_term **t);
void				ft_left(t_term **t);
void				word_left(t_term **t);
void				word_right(t_term **t);

char				*enter(t_term **t);
char				*ctrl_c(t_term **t);

void				clean_line(t_term **t);
int					end_shell(t_term **t, char *cmd);
char				*end_quoting_heredoc(t_term **t, char *end_of_file);

void				multi_up(t_term **t);
void				multi_down(t_term **t);

void				selec(t_term **t);
int					selec_right(t_term **t, int rel_cur, int tmp_cur);
int					selec_left(t_term **t, int rel_cur);
void				paste(t_term **t);
void				cut(t_term **t, int rel_cur, int tmp);
int					mode_inver(t_term **t, int tmp_cur);

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
