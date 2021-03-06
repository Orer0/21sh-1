/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 23:58:18 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/12 03:24:03 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	free_var(void *content, size_t size)
{
	t_list	*tmp;
	t_list	*next;

	(void)size;
	ft_strdel(&(*((t_var_token **)(content)))->token);
	if ((*((t_var_token **)(content)))->var_lst)
	{
		tmp = (*((t_var_token **)(content)))->var_lst;
		while (tmp)
		{
			ft_strdel(&(*((t_var_token **)(tmp->content)))->token);
			ft_memdel((void **)((t_var_token **)(tmp->content)));
			ft_memdel((void **)&tmp->content);
			next = tmp->next;
			ft_memdel((void **)&tmp);
			tmp = next;
		}
	}
	ft_memdel((void **)((t_token **)(content)));
	ft_memdel(&content);
}

/*
**	Free un token
*/

void	free_token(void *content, size_t size)
{
	int	type;

	if (!content)
		return ;
	type = (*((t_token **)(content)))->type;
	(void)size;
	ft_strdel(&((*((t_token **)(content)))->token));
	if (type == CMD_TYPE)
	{
		ft_lstdel(&(*((t_cmd_token **)(content)))->args, free_token);
		if ((*((t_cmd_token **)(content)))->var_token)
			free_var((*((t_cmd_token **)(content)))->var_token, 0);
		ft_memdel((void **)((t_cmd_token **)(content)));
	}
	else if (type == VAR_TYPE)
	{
		free_var(content, 0);
		return ;
	}
	ft_memdel((void **)((t_token **)(content)));
	ft_memdel(&content);
}
