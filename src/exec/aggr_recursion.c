/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aggr_recursion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 23:02:27 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/12 21:45:47 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static int		fd_to_dup(t_btree *tree)
{
	int		fd_dup;

	fd_dup = 0;
	if (ft_isdigit(get_token_token(tree->data)[0]))
		fd_dup = ft_atoi(get_token_token(tree->data));
	else
	{
		if (get_type_token(tree->data) == DUP_OUT_FD_TYPE)
			fd_dup = 1;
		else if (get_type_token(tree->data) == DUP_IN_FD_TYPE)
			fd_dup = 0;
	}
	return (fd_dup);
}

static void		aggr_dup(int close_fd, int adup, char *argument)
{
	if (close_fd)
		close(adup);
	else
	{
		if (dup2(ft_atoi(argument), adup) == -1)
		{
			ft_fd_printf(2, "21sh: %s: bad file descriptor\n", argument);
			exit(EXIT_FAILURE);
		}
	}
}

static void		aggr_recursion_node(t_btree *tree, t_btree *node)
{
	int		adup;
	int		close_fd;
	int		i;
	char	*argument;

	argument = get_token_token(node->data);
	close_fd = FALSE;
	adup = fd_to_dup(tree);
	if (ft_strequ(argument, "-"))
		close_fd = TRUE;
	else
	{
		i = -1;
		while (argument[++i])
		{
			if (!ft_isdigit(argument[i]))
			{
				ft_fd_printf(2, "21sh: %s: bad file unit number\n", argument);
				exit(EXIT_FAILURE);
			}
		}
	}
	aggr_dup(close_fd, adup, argument);
	return ;
}

void			aggr_recursion(t_btree *tree)
{
	if (!tree->right)
		return ;
	if (get_type_token(tree->right->data) == AGGREGATION_ARG_TYPE)
	{
		aggr_recursion_node(tree, tree->right);
		return ;
	}
	if (!tree->right->left)
		return ;
	if (get_type_token(tree->right->left->data) == AGGREGATION_ARG_TYPE)
		aggr_recursion_node(tree, tree->right->left);
	if (is_redirection(get_type_token(tree->right->data)))
		redir_recursion(tree->right);
	else if (is_aggregation(get_type_token(tree->right->data)))
		aggr_recursion(tree->right);
}
