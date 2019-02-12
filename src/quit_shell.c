/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 17:41:36 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/12 21:30:30 by aroblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "lexer.h"
#include "ast.h"

void	del_history(void *content, size_t size)
{
	(void)size;
	ft_memdel(&content);
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
	if (data->history)
		ft_lstdel(&data->history, &del_history);
	ft_strdel(&data->term);
	ft_strdel(&data->selec);
	ft_strtab_del(&data->env_tab);
	ft_lstdel(&data->env_lst, del_env_var);
	ft_lstdel(&data->intern_env_lst, del_env_var);
	ft_memdel((void **)&data);
	exit(status);
}
