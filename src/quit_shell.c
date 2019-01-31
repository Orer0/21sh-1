/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 17:41:36 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/29 01:32:42 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "lexer.h"
#include "ast.h"

void	quit_shell(int status, int err)
{
	t_shell_data *data;

	if (err == MALLOC_ERR)
		write(2, "21sh: malloc failed", 19);
	data = shell_data_singleton();
	delete_list_tokens(&data->tokens_list);
	if (data->parse_tree)
		delete_parsing_tree(&data->parse_tree);
	if (data->ast)
		delete_ast(&data->ast);
	ft_strtab_del(&data->env_tab);
	ft_lstdel(&data->env_lst, del_env_var);
	ft_lstdel(&data->intern_env_lst, del_env_var);
	ft_memdel((void **)&data);
	exit(status);
}