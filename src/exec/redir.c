/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroblin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 01:40:48 by aroblin           #+#    #+#             */
/*   Updated: 2019/02/05 01:51:56 by aroblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "tokens.h"

void	out_redir(t_cmd_token *cmd, t_token *name, t_token *redir)
{
	int		fd;
	int		fd_op;

	fd = open(name->token, O_CREAT | O_WRONLY | O_TRUNC); // ajouter mode
	redir->token 
	dup2(redir->
	
