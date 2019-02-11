/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_recursion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 23:01:07 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/11 23:12:00 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include <sys/types.h>

static int	fd_to_dup(t_btree *tree, t_btree *node)
{
	int		fd;

	if (get_type_token(tree->data) == OUT_RDIR_TYPE)
		fd = open(get_token_token(node->data), O_CREAT
			| O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else if (get_type_token(tree->data) == IN_RDIR_TYPE)
		fd = open(get_token_token(node->data), O_RDONLY);
	else if (get_type_token(tree->data) == OUT_ARDIR_TYPE)
		fd = open(get_token_token(node->data), O_CREAT
			| O_WRONLY | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else
		fd = 1;
	if (fd == -1)
		quit_shell(EXIT_FAILURE, 0);
	return (fd);
}

static int	define_arg_redir(t_btree *tree)
{
	if (get_type_token(tree->data) == OUT_RDIR_TYPE
		|| get_type_token(tree->data) == OUT_ARDIR_TYPE)
		return (1);
	else if (get_type_token(tree->data) == IN_RDIR_TYPE
		|| get_type_token(tree->data) == HEREDOC_TYPE)
		return (0);
	return (-1);
}

static void	redir_recursion_node(t_btree *tree, t_btree *node)
{
	int		arg;
	int		fd;

	fd = fd_to_dup(tree, node);
	if (ft_isdigit(get_token_token(tree->data)[0]))
		arg = ft_atoi(get_token_token(tree->data));
	else
		arg = define_arg_redir(tree);
	if (get_type_token(tree->data) == OUT_RDIR_TYPE
		|| get_type_token(tree->data) == OUT_ARDIR_TYPE)
	{
		dup2(fd, arg);
		close(fd);
	}
	else if (get_type_token(tree->data) == IN_RDIR_TYPE)
	{
		dup2(fd, arg);
		close(fd);
	}
	else if (get_type_token(tree->data) == HEREDOC_TYPE)
		heredoc(node, arg);
}

void		redir_recursion(t_btree *tree)
{
	if (!tree->right)
		return ;
	if (get_type_token(tree->right->data) == REDIRECTION_ARG_TYPE)
	{
		redir_recursion_node(tree, tree->right);
		return ;
	}
	if (!tree->right->left)
		return ;
	if (get_type_token(tree->right->left->data) == REDIRECTION_ARG_TYPE
		&& get_type_token(tree->right->data) != HEREDOC_TYPE)
		redir_recursion_node(tree, tree->right->left);
	if (is_redirection(get_type_token(tree->right->data)))
		redir_recursion(tree->right);
	else if (is_aggregation(get_type_token(tree->right->data)))
		aggr_recursion(tree->right);
}
