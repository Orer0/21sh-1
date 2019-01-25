/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 23:58:18 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/25 05:58:39 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/*
**	Free un token
*/

void 	free_token(void *content, size_t size)
{
	int type;
	t_var_token *tmp;
	t_var_token *next;

	type = (*((t_token **)(content)))->type;
	(void)size;
	ft_strdel(&((*((t_token **)(content)))->token));
	if (type == CMD_TYPE)
	{
		ft_lstdel(&(*((t_cmd_token **)(content)))->args, free_token);
		if ((*((t_cmd_token **)(content)))->variables)
		{
			tmp = (*((t_cmd_token **)(content)))->variables;
			while (tmp)
			{
				next = tmp->next;
				ft_strdel(&tmp->value);
				ft_memdel((void **)((t_token **)(tmp)));
				// free_token(tmp, 0);
				tmp = next;
			}
		}
		ft_strdel(&(*((t_cmd_token **)(content)))->variables->value);
		ft_memdel(((void **)&((*((t_cmd_token **)(content)))->variables)));
		// ft_lstdel(&(*((t_cmd_token **)(content)))->assign, free_token);
	}
	else if (type == VAR_TYPE)
	{
		ft_strdel(&(*((t_var_token **)(content)))->value);
		ft_memdel((void **)((t_token **)(content)));
		// if ((*((t_var_token **)(content)))->next)
		// 	free_token(&(*((t_var_token **)(content)))->next, 0);
		// ft_memdel((void **)((t_token **)(content)));
		// return ;
		// free_token(&(*((t_var_token **)(content)))->next, 0);
	}
	// ft_memdel((void **)((t_token **)(content)));
	ft_memdel(&content);
}
