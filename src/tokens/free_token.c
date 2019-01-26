/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 23:58:18 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/26 06:03:08 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void 	free_t_var(void *content, size_t size)
{
	// ft_printf(" dans free t var\n");
	(void)size;
	ft_strdel(&(*((t_var **)(content)))->value);
	ft_strdel(&(*((t_var **)(content)))->name);
	ft_memdel((void **)((t_var **)(content)));
	// ft_memdel(&content);
}

void 	free_var(void *content, size_t size)
{
	t_list *tmp;
	t_list	*next;

	(void)size;
	// ft_strdel(&(*((t_var_token **)(content)))->value);
	if ((*((t_var_token **)(content)))->vars)
	{
		tmp = (*((t_var_token **)(content)))->vars;
		// ft_lstdel(&(*((t_var_token **)(content)))->vars, free_t_var);
		while (tmp)
		{
			ft_strdel(&(*((t_var **)(tmp->content)))->value);
			ft_strdel(&(*((t_var **)(tmp->content)))->name);
			ft_memdel((void **)((t_var **)(tmp->content)));
			next = tmp->next;
			ft_memdel((void **)&tmp);
			tmp = next;
		}
		// ft_memdel((void **)&(*((t_var_token **)(content)))->vars);
	}
	// ft_memdel((void **)&(*((t_var_token **)(content))));
	ft_memdel((void **)((t_token **)(content)));
	ft_memdel(&content);
}

/*
**	Free un token
*/

void 	free_token(void *content, size_t size)
{
	int type;
	// t_list *tmp;
	// t_list *next;

	if (!content)
		return ;
	type = (*((t_token **)(content)))->type;
	(void)size;
	ft_strdel(&((*((t_token **)(content)))->token));
	if (type == CMD_TYPE)
	{
		ft_lstdel(&(*((t_cmd_token **)(content)))->args, free_token);
		// if (*((t_cmd_token **)(content)))->variables)
		// {
		// free_var((*((t_cmd_token **)(content)))->variables, 0);
			// ft_lstdel(&(*((t_cmd_token **)(content)))->variables, free_var);
			// free_var((*((t_cmd_token **)(content)))->variables);
			// ft_strdel(&((*((t_token **)(content)))->token));
			// ft_strdel(&(*((t_var_token **)(content)))->value);
			// ft_memdel((void **)(*((t_cmd_token **)(content)))->variables);

			// free_token((*((t_cmd_token **)(content)))->variables, 0);
			// tmp = (*((t_cmd_token **)(content)))->variables;
			// while (tmp)
			// {
			// 	next = tmp->next;
			// 	ft_strdel(&tmp->value);
			// 	ft_memdel((void **)((t_token **)(tmp)));
			// 	// free_token(tmp, 0);
			// 	tmp = next;
			// }
		// }
		// if ((*((t_cmd_token **)(content)))->variables)
		// 	ft_strdel(&(*((t_cmd_token **)(content)))->variables->value);
		// ft_memdel(((void **)&((*((t_cmd_token **)(content)))->variables)));
		ft_memdel((void **)((t_cmd_token **)(content)));
		// ft_memdel(&content);
		// ft_lstdel(&(*((t_cmd_token **)(content)))->assign, free_token);
	}
	else if (type == VAR_TYPE)
	{
		free_var(content, 0);
		// if ((*((t_var_token **)(content)))->next_vars)
		// {
		// 	tmp = (*((t_var_token **)(content)))->next_vars;
		// 	while (tmp)
		// 	{
		// 		next = tmp->next;
		// 		ft_strdel(&(*((t_var_token **)(content)))->value);
		// 		ft_memdel((void **)((t_token **)(tmp)));
		// 		// free_token(tmp, 0);
		// 		tmp = next;
		// 	}
		// }
		// ft_strdel(&(*((t_var_token **)(content)))->value);
		// ft_memdel((void **)((t_token **)(content)));
		// if ((*((t_var_token **)(content)))->next)
		// 	free_token(&(*((t_var_token **)(content)))->next, 0);
		// ft_memdel((void **)((t_token **)(content)));
		// return ;
		// free_token(&(*((t_var_token **)(content)))->next, 0);
		// ft_memdel((void **)((t_token **)(content)));
		return;
	}
	ft_memdel((void **)((t_token **)(content)));
	ft_memdel(&content);
}
