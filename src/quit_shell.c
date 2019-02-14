/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 17:41:36 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/14 02:03:47 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "lexer.h"
#include "ast.h"

static void	del_history(void *content, size_t size)
{
	(void)size;
	ft_memdel(&content);
}

static void	clean_line(t_term **t)
{
	ft_strdel(&(*t)->selec);
	ft_strdel(&(*t)->current_line);
	ft_strdel(&(*t)->promtp);
	if ((*t)->history)
		ft_lstdel(&(*t)->history, &del_history);
	if ((*t)->sel != NULL)
	ft_strdel(&(*t)->sel);
	ft_memdel((void **)t);
}

void	quit_shell(int status, int err)
{
	t_shell_data	*data;

	if (err == MALLOC_ERR)
		ft_fd_printf(2, "21sh: allocation critical fail\n");
	else if (err == FORK_ERR)
		ft_fd_printf(2, "21sh: fork critical fail\n");
	data = shell_data_singleton();
	delete_list_tokens(&data->tokens_list);
	if (data->parse_tree)
		delete_parsing_tree(&data->parse_tree);
	if (data->ast)
		delete_ast(&data->ast);
	clean_line(&data->t);
	ft_strdel(&data->term);
	ft_strtab_del(&data->env_tab);
	ft_lstdel(&data->env_lst, del_env_var);
	ft_lstdel(&data->intern_env_lst, del_env_var);
	ft_memdel((void **)&data);
	exit(status);
}
