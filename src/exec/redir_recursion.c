/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_recursion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 23:01:07 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/09 05:43:12 by aroblin          ###   ########.fr       */
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

static int	here_name(char **path)
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

static void add_in_file(char **str, char *argument, char **line)
{
	char	*tmp;

	tmp = NULL;
	while (!ft_strequ(*line, argument))
	{
		ft_strdel(line);
		*line = get_line(PROMPT_MIN);
		if (*str && !ft_strequ(*line, "\n"))
		{
			tmp = *str;
			*str = ft_strjoin(tmp, "\n");
			ft_strdel(&tmp);
		}
		if (!ft_strequ(*line, argument))
		{
			if (!*str)
				*str = ft_strdup(*line);
			else
			{
				tmp = *str;
				*str = ft_strjoin(tmp, *line);
				ft_strdel(&tmp);
			}
		}
	}
}

static void	heredoc(t_btree *node, int arg)
{
	char	*str;
	char	*argument;
	int		fd_h;
	char	*path;
	char	*line;

	line = NULL;
	str = NULL;
	fd_h = here_name(&path);
	argument = get_token_token(node->data);
	add_in_file(&str, argument, &line);
	write(fd_h, str, ft_strlen(str));
	close(fd_h);
	ft_strdel(&str);
	fd_h = open(path, O_RDONLY);
	ft_strdel(&path);
	dup2(fd_h, arg);
	close(fd_h);
}

static void	redir_recursion_node(t_btree *tree, t_btree *node)
{
	int		arg;
	int		fd;

	fd = fd_to_dup(tree, node);
	if (ft_isdigit(get_token_token(tree->data)[0]))
		arg = ft_atoi(get_token_token(tree->data));
	else
	{
		if (get_type_token(tree->data) == OUT_RDIR_TYPE || get_type_token(tree->data) == OUT_ARDIR_TYPE )
			arg = 1;
		else if (get_type_token(tree->data) == IN_RDIR_TYPE || get_type_token(tree->data) == HEREDOC_TYPE)
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
	else if (get_type_token(tree->data) == HEREDOC_TYPE)
		heredoc(node, arg);
}

void 	redir_recursion(t_btree *tree)
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
