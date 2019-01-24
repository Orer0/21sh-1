/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_command_token.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 23:55:46 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/24 02:46:30 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void		add_command_in_tab(char ***tab, t_list *tmp)
{
	if (!(ft_strtab_addend(tab, get_token_token(tmp))))
		quit_shell(EXIT_FAILURE, MALLOC_ERR);
	if (tmp->prev)
		tmp->prev->next = tmp->next;
	if (tmp->next)
		tmp->next->prev = tmp->prev;
}

static void		manage_commands(t_list *lst)
{
	char **tab;
	t_list	*tmp;
	t_cmd_token *token;
	t_list	*next;

	tmp = lst;
	if (!(tab = ft_memalloc(sizeof(char *) * 2))
		|| !(tab[0] = ft_strdup(get_token_token(tmp))))
		quit_shell(EXIT_FAILURE, MALLOC_ERR);
	tmp = tmp->next;
	while (tmp)
	{
		if (is_aggregation(get_type_token(tmp)) || get_type_token(tmp) == HEREDOC_TYPE)
		{
			tmp = tmp->next->next;
			continue ;
		}
		if (get_type_token(tmp) == WORD_TYPE)
		{
			add_command_in_tab(&tab, tmp);
			next = tmp->next;
			ft_lstdelone(&tmp, free_token);
			tmp = next;
		}
		else
			break ;
	}
	token_constructor(get_token_token(lst), CMD_TYPE, (t_token **)&token);
	free_token(lst->content, 0);
	lst->content = ft_memalloc(sizeof(&token) * sizeof(t_cmd_token));
	ft_memcpy(lst->content, &token, sizeof(t_cmd_token));
	lst->content_size = sizeof(t_cmd_token);
	set_tab_token(lst, tab);
}

void 	build_command_token(void)
{
	t_list			*tmp;
	t_shell_data 	*data;
	t_var_token			*t;
	t_list			*del;
	t_list			*tmpp;
	t_list			*new;

	data = shell_data_singleton();
	tmp = data->tokens_list;
	if (tmp == NULL)
		return ;
	while (tmp)
	{
		// ft_printf("tout debut [%s]\n", get_token_token(tmp));

		if (get_type_token(tmp) == WORD_TYPE)
		{
			manage_commands(tmp);
			// ft_printf("sortant de manage command [%s]\n", get_token_token(tmp));
			if (tmp->prev)
			{
				if (get_type_token(tmp->prev) == VAR_TYPE)
				{
					tmpp = tmp->prev;
					while (tmpp && get_type_token(tmpp) == VAR_TYPE)
					{
						token_constructor((*((t_token **)(tmpp->content)))->token, (*((t_token **)(tmpp->content)))->type, (t_token **)&t);
						new = ft_lstnew(&t, sizeof(t_var_token));
						set_value_token(new, ft_strdup((*((t_var_token **)(tmpp->content)))->value));
						if (!(*((t_cmd_token **)(tmp->content)))->assign)
							(*((t_cmd_token **)(tmp->content)))->assign = new;
						else
							ft_lstadd(&((*((t_cmd_token **)(tmp->content)))->assign), new);
						// ft_printf("PREV = %s\n", get_token_token(tmpp));
						if (!tmpp->prev)
							break ;
						if (tmpp->prev)
							tmpp->prev->next = tmpp->next;
						if (tmpp->next)
							tmpp->next->prev = tmpp->prev;
						del = tmpp;
						tmpp = tmpp->prev;
						// ft_printf("PREV fin = %s\n", get_token_token(tmpp));
						ft_lstdelone(&del, free_token);
					}
					if (tmpp == data->tokens_list)
					{
						del = data->tokens_list;
						data->tokens_list = data->tokens_list->next;
						ft_lstdelone(&del, free_token);
					}

						// ft_printf("TEST [%s]\n", get_token_token(data->tokens_list->next));
						// if (!data->tokens_list)
							// ft_printf("LAAAAAA\n");
						// data->tokens_list = data->tokens_list->next;
					// ft_printf("tmpp : %s\n", );
					// ft_printf("tmpp : %s\n", get_token_token(tmpp));
					// ft_printf("tmp prev = %s\n", get_token_token(tmp->prev));
					// ft_printf("tmp = %s\n", get_token_token(tmp));
					tmp->prev = NULL;
				}
			}
		}
		tmp = tmp->next;
	}
}
