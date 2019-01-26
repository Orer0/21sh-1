/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 23:58:18 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/26 18:50:25 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void 	free_t_var(void *content, size_t size)
{
	// ft_printf(" dans free t var\n");
	(void)size;
	ft_strdel(&(*((t_var **)(content)))->value);
	ft_strdel(&(*((t_var **)(content)))->name);
	// ft_memdel((void **)(*((t_var **)(content))));
	// ft_memdel((void **)((t_var **)(content)));
	ft_memdel(&content);
}

void 	free_var(void *content, size_t size)
{
	t_list *tmp;
	t_list	*next;

	(void)size;
	ft_strdel(&(*((t_var_token **)(content)))->token);
	if ((*((t_var_token **)(content)))->vars)
	{
		tmp = (*((t_var_token **)(content)))->vars;
		// ft_lstdel(&(*((t_var_token **)(content)))->vars, free_t_var);
		while (tmp)
		{
			ft_strdel(&(*((t_var **)(tmp->content)))->value);
			ft_strdel(&(*((t_var **)(tmp->content)))->name);
			ft_memdel((void **)((t_var **)(tmp->content)));
			ft_memdel((void **)&tmp->content);
			next = tmp->next;
			ft_memdel((void **)&tmp);
			tmp = next;
		}
		// ft_memdel((void **)&(*((t_var_token **)(content)))->vars);
	}
	// ft_memdel((void **)&(*((t_var_token **)(content)))->vars);
	// ft_memdel(&(*((t_var_token **)(content)))->vars->content);
	ft_memdel((void **)((t_token **)(content)));
	ft_memdel(&content);
}

/*
**	Free un token
*/

void 	free_token(void *content, size_t size)
{
	int type;

	if (!content)
		return ;
	type = (*((t_token **)(content)))->type;
	(void)size;
	ft_strdel(&((*((t_token **)(content)))->token));
	if (type == CMD_TYPE)
	{
		// liste d'arguments
		ft_lstdel(&(*((t_cmd_token **)(content)))->args, free_token);
		// token variables
		if ((*((t_cmd_token **)(content)))->variables)
		{
			free_var((*((t_cmd_token **)(content)))->variables, 0);

		}

		ft_memdel((void **)((t_cmd_token **)(content)));
	}
	else if (type == VAR_TYPE)
	{
		free_var(content, 0);

		return;
	}
	ft_memdel((void **)((t_token **)(content)));
	ft_memdel(&content);
}
