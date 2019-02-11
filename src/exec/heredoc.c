/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 23:09:55 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/11 23:11:55 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static int	heredoc_name(char **path)
{
	static int	id = 52;
	char		*tmp;
	int			fd;

	id++;
	if (!(tmp = ft_itoa(id)))
		quit_shell(EXIT_FAILURE, 0);
	if (!(*path = ft_strjoin("/tmp/.21sh_heredoc_", tmp)))
		quit_shell(EXIT_FAILURE, 0);
	ft_strdel(&tmp);
	fd = open(*path, O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (fd == -1)
		quit_shell(EXIT_FAILURE, 0);
	return (fd);
}

void		heredoc(t_btree *node, int arg)
{
	char	*argument;
	int		fd_h;
	char	*path;

	fd_h = heredoc_name(&path);
	argument = get_token_token(node->data);
	write(fd_h, argument, ft_strlen(argument));
	close(fd_h);
	fd_h = open(path, O_RDONLY);
	ft_strdel(&path);
	dup2(fd_h, arg);
	close(fd_h);
}
