/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_check_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 23:34:04 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/15 23:47:13 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void		get_the_new_line(char *argument, char **line, char **final_str)
{
	char			*tmp;

	*line = get_line(PROMPT_MIN, argument);
	if (final_str && !ft_strequ(*line, "\n"))
	{
		tmp = *final_str;
		*final_str = ft_strjoin(tmp, "\n");
		ft_strdel(&tmp);
	}
	if (!ft_strequ(*line, argument))
	{
		if (!(*final_str))
			*final_str = ft_strdup(*line);
		else
		{
			tmp = *final_str;
			*final_str = ft_strjoin(tmp, *line);
			ft_strdel(&tmp);
		}
	}
}

int				first_check_heredoc(t_list **lst)
{
	char			*final_str;
	char			*line;
	char			*argument;
	int				ret;
	t_shell_data	*data;

	data = shell_data_singleton();
	ret = TRUE;
	final_str = NULL;
	line = NULL;
	argument = get_token_token((*lst)->next->content);
	while (!ft_strequ(line, argument))
	{
		ft_strdel(&line);
		get_the_new_line(argument, &line, &final_str);
		if (ft_strequ(line, "\n") && data->ctrl_c)
		{
			ret = FALSE;
			break ;
		}
	}
	ft_strdel(&line);
	ft_strdel(&(*((t_token **)((*lst)->next->content)))->token);
	set_token_token((*lst)->next->content, final_str);
	return (ret);
}
