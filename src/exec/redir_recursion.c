/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_recursion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 23:01:07 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/08 05:28:22 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void 	redir_recursion(t_btree *tree)
{
	int fd;
	int arg;

	if (!tree->right)
	return ;
	// Si le noeud de droite est un argument de redirection, on le prend
	if (get_type_token(tree->right->data) == REDIRECTION_ARG_TYPE)
	{
		// ft_printf("OPEN DU FICHIER [%s]\n", get_token_token(tree->right->data));
		// OPEN LE FICHIER ARGUMENT
		if (get_type_token(tree->data) == OUT_RDIR_TYPE)
			fd = open(get_token_token(tree->right->data), O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		else if (get_type_token(tree->data) == IN_RDIR_TYPE)
			fd = open(get_token_token(tree->right->data), O_RDONLY);
		else if (get_type_token(tree->data) == OUT_ARDIR_TYPE)
			fd = open(get_token_token(tree->right->data), O_CREAT | O_WRONLY | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		else
			fd = 1;
		if (fd == -1)
		{
			ft_printf("21sh: open failed"); // a suprimer
			quit_shell(EXIT_FAILURE, 0);
		}
		if (ft_isdigit(get_token_token(tree->data)[0]))
		{
			arg = ft_atoi(get_token_token(tree->data));
			// ft_printf("atoi = %d\n", arg);
		}
		else
		{
			if (get_type_token(tree->data) == OUT_RDIR_TYPE || get_type_token(tree->data) == OUT_ARDIR_TYPE )
				arg = 1;
			else if (get_type_token(tree->data) == IN_RDIR_TYPE)
				arg = 0;
		}
		if (get_type_token(tree->data) == OUT_RDIR_TYPE || get_type_token(tree->data) == OUT_ARDIR_TYPE )
		{
			dup2(fd, arg);
			close(fd);
		}
		else if (get_type_token(tree->data) == IN_RDIR_TYPE)
		{
			dup2(fd, arg);
			close(fd);
		}
		return ;
	}
	// Sinon, l'argument est dans le noeud gauche du noeud de droite
	if (!tree->right->left)
		return ;
	if (get_type_token(tree->right->left->data) == REDIRECTION_ARG_TYPE)
	{
		// ft_printf("OPEN DU FICHIER [%s]\n", get_token_token(tree->right->left->data));
		// OPEN LE FICHIER ARGUMENT
		if (get_type_token(tree->data) == OUT_RDIR_TYPE)
			fd = open(get_token_token(tree->right->left->data), O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		else if (get_type_token(tree->data) == IN_RDIR_TYPE)
			fd = open(get_token_token(tree->right->left->data), O_RDONLY);
		else if (get_type_token(tree->data) == OUT_ARDIR_TYPE)
			fd = open(get_token_token(tree->right->left->data), O_CREAT | O_WRONLY | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		else
			fd = 1;
		if (fd == -1)
		{
			ft_printf("21sh: open failed"); // a suprimer
			quit_shell(EXIT_FAILURE, 0);
		}
		if (ft_isdigit(get_token_token(tree->data)[0]))
		{
			arg = ft_atoi(get_token_token(tree->data));
			ft_printf("atoi = %d\n", arg);
		}
		else
		{
			if (get_type_token(tree->data) == OUT_RDIR_TYPE || get_type_token(tree->data) == OUT_ARDIR_TYPE )
				arg = 1;
			else if (get_type_token(tree->data) == IN_RDIR_TYPE)
				arg = 0;
		}
		if (get_type_token(tree->data) == OUT_RDIR_TYPE || get_type_token(tree->data) == OUT_ARDIR_TYPE )
		{
			dup2(fd, arg);
			close(fd);
		}
		else if (get_type_token(tree->data) == IN_RDIR_TYPE)
		{
			dup2(arg, fd);
			close(fd);
		}
	}
	// Relance la bonne recursion sur le noeud de droite qui est un operateur
	if (is_redirection(get_type_token(tree->right->data)))
		redir_recursion(tree->right);
	else if (is_aggregation(get_type_token(tree->right->data)))
		aggr_recursion(tree->right);
}
