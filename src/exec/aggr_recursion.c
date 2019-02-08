/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aggr_recursion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 23:02:27 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/08 05:26:20 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void 	aggr_recursion(t_btree *tree)
{
	// int arg;
	int adup;
	int closee;

	closee = FALSE;
	if (!tree->right)
	return ;
	// Si le noeud de droite est un argument d'aggregation, on le prend
	if (get_type_token(tree->right->data) == AGGREGATION_ARG_TYPE)
	{
		// RECUPERE LE FD A DUP
		if (ft_isdigit(get_token_token(tree->data)[0]))
		{
			adup = ft_atoi(get_token_token(tree->data));
			// ft_printf("atoi = %d\n", adup);
		}
		else
		{
			if (get_type_token(tree->data) == DUP_OUT_FD_TYPE )
				adup = 1;
			else if (get_type_token(tree->data) == DUP_IN_FD_TYPE)
				adup = 0;
		}

		int i;
		char	*argument = get_token_token(tree->right->data);
		if (ft_strequ(argument, "-"))
			closee = TRUE;
		else
		{
			i = -1;
			while (argument[++i])
			{
				if (!ft_isdigit(argument[i]))
				{
					ft_fd_printf(2, "21sh: %s: bad file unit number", argument);
					return ;
				}
			}
		}
		if (closee)
		{
			close(adup);
		}
		else
		{
			dup2(ft_atoi(argument), adup);
		}
		return ;
	}
	// Sinon, l'argument est dans le noeud gauche du noeud de droite
	if (!tree->right->left)
		return ;
	if (get_type_token(tree->right->left->data) == AGGREGATION_ARG_TYPE)
	{
		// RECUPERE LE FD A DUP
		if (ft_isdigit(get_token_token(tree->data)[0]))
		{
			adup = ft_atoi(get_token_token(tree->data));
			// ft_printf("atoi = %d\n", adup);
		}
		else
		{
			if (get_type_token(tree->data) == DUP_OUT_FD_TYPE )
				adup = 1;
			else if (get_type_token(tree->data) == DUP_IN_FD_TYPE)
				adup = 0;
		}

		int i;
		char	*argument = get_token_token(tree->right->left->data);
		if (ft_strequ(argument, "-"))
			closee = TRUE;
		else
		{
			i = -1;
			while (argument[++i])
			{
				if (!ft_isdigit(argument[i]))
				{
					ft_fd_printf(2, "21sh: %s: bad file unit number", argument);
					return ;
				}
			}
		}
		if (closee)
		{
			close(adup);
		}
		else
		{
			dup2(ft_atoi(argument), adup);
		}
	}
	// Relance la bonne recursion sur le noeud de droite qui est un operateur
	if (is_redirection(get_type_token(tree->right->data)))
		redir_recursion(tree->right);
	else if (is_aggregation(get_type_token(tree->right->data)))
		aggr_recursion(tree->right);
}
