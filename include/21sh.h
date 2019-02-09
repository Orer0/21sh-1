/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 18:31:39 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/09 04:23:15 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TWENTYONE_SH_H
# define TWENTYONE_SH_H

# include "../libft/include/libft.h"
# include "../libft/include/libftprintf.h"
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <limits.h>
# include <fcntl.h>

# include "tokens.h"
# include "shell_data.h"

# define PROMPT "21sh $> "
# define PROMPT_MIN "> "

# define OPTIONS_CD		"LP"
# define OPTIONS_ENV	"i"
# define OPTIONS_ECHO	"n"
# define OPT_L 			(1 << 27)
# define OPT_P 			(1 << 28)
# define OPT_I			(1 << ('i' - 'a'))
# define OPT_N			(1 << ('n' - 'a'))
# define OPT_C			(1 << ('c' - 'a'))
# define SHELL_OPT		"c"

/*
**	Main structure
*/

// typedef struct		s_shell_data
// {
// 	t_list			*tokens_list;
// 	t_ptree			*parse_tree;
// 	t_btree			*ast;
// }					t_shell_data;

typedef struct		s_varenv
{
	char			*name;
	char			*content;
}					t_varenv;

// t_shell_data		*shell_data_singleton(void);
// void				quit_shell(int status, int err);
void 				clean_parsing(void);

/*
** Errors
*/

enum	e_err
{
	MALLOC_ERR = -999,
};

t_list		*ft_lstcpy(t_list *src, t_list **dest);


/*
** PARSER functions
*/

int		shell_parser(char **line);

/*
**	Environement
*/

int				add_env_var(t_list **lst, char *name, char *content);
int				change_env_var(t_list **lst, char *name, char *newcontent);
t_varenv		*create_varenv(char *name, char *content);
void			del_env_var(void *content, size_t size);
int				env_lst_to_tab(t_list **lst, char ***tab);
int				env_tab_to_lst(t_list **lst, char **environ);
t_varenv		*get_env_var_by_name(t_list **lst, char *name);
void			create_minimal_env(void);
int				remove_env_var(t_list **lst, char *name);

/*
**	Options
*/

void	options_parser(char **args, int *options, int *pos_args,
			int (*set_options)(char *, int *, int));
int		is_valid_option(char c, char *options);


int			read_prompt(const int fd, char **line);

/*
**	EXECUTION
*/

char			*get_path_of_bin(char *path);
int				exec_command(char **command, char **env);
void 			exec_ast(t_btree *tree, int exec_next);
void	aggr_redir_execution(t_btree *tree);
void 	redir_recursion(t_btree *tree);
void 	aggr_recursion(t_btree *tree);
void 	pipe_execution(t_btree *tree);
void		catch_signal_kill(int signal);


/*
**		BUILTINS
*/

int					unset_builtin(char **args);
int					manage_builtins(char **command);
int					echo_builtin(char **args);
int					is_valid_option(char c, char *options);
void				options_parser(char **args, int *options, int *pos_args,
						int (*set_options)(char *, int *, int));
int					env_builtin(char **args);
int					export_builtin(char **args);
int					set_builtin(char **args);
void				exit_builtin(char **args);

/*
**	ENV
*/

t_list				*ft_lstcpy(t_list *src, t_list **dest);
int					manage_envvar_args(int options, t_list **env_lst_cpy,
						char **args, int *pos_args);

/*
**	CD
*/

char				*get_pwd_for_cd(int pos_args, char **args);
int					ft_realloc_addend_tab(char ***tab, char *elem);
char				*ft_strjointab(char **tab, char sep);
int					ft_stringtab_len(char **tab);
int					check_path_errors(char *path);
char				*get_final_path(char **path);
int					build_pwd_tab(char ***arg_tab, char ***pwd_tab,
						int pwd_tab_len);
int					cd_builtin(char **args);


char				*get_line(char *promtp);

#endif
