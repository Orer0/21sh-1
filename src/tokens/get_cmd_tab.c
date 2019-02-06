/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 06:19:59 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/06 23:44:37 by aroblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "tokens.h"
#include "lexer.h"
/*
static char		*get_env_var(char *name) // enlever static)
{
 	t_varenv	*var;
	char	*content;
	t_shell_data	*data;

	data = shell_data_singleton();
	var = get_env_var_by_name(&data->intern_env_lst, name);
	if (var)
		content = ft_strdup(var->content);
	else
		return (NULL);
	if (!content)
		quit_shell(EXIT_FAILURE, MALLOC_ERR);
	return (content);
}
*/
/*
static char	*get_dollar(char *line)
{
	int		i;
	char	stack[STACK_SIZE];

	while (line[++i])
	{
		if (is_(line[i]))
		{
			(line->i)--;
			return (get_env_var(stack));
		}
		else
		{
			if (!is_ignored(state, next_state))
				put_char_in_stack(&stack, line->line[line->i]);
		}
		state = next_state;
	}
	(line->i)--;
	return (get_env_var(stack));
}
*/
static void	manage_expansion_cmd(char **str)
{
	int		i;
//	char	*var;

	if ((*str)[0] == '~')
		replace_tilde(str);
	i = -1;
	while ((*str)[++i])
	{
		if ((*str)[i] == '$')
		{
//			var = get_dollar(&(*str)[i + 1]);
		}
	}
}

char 	**get_cmd_tab(t_cmd_token **token)
{
	char	**tab;
	t_list	*tmp;

	if (!(tab = ft_memalloc(sizeof(char *) * 2)))
		quit_shell(EXIT_FAILURE, MALLOC_ERR);
	if ((*token)->is_expansion)
		manage_expansion_cmd(&(*token)->token);
	tab[0] = ft_strdup((*token)->token);
	tab[1] = NULL;
	tmp = (*token)->args;
	while (tmp)
	{
		if (get_expansion_token(tmp->content))
			manage_expansion_cmd(&(*((t_cmd_token **)(tmp->content)))->token);
		ft_strtab_addend(&tab, get_token_token(tmp->content));
		tmp = tmp->next;
	}
	return (tab);
}
