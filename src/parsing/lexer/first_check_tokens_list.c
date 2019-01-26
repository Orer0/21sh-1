/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_check_tokens_list.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 00:10:05 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/26 18:41:14 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void		unexpected_token_error(char *token)
{
	ft_printf("syntax error near unexpected token : \"%s\"\n", token);
	quit_shell(EXIT_FAILURE, 0);
}

static void		not_terminal_type(t_list *lst)
{
	int		type;

	type = get_type_token(lst);
	if (type == PIPE_TYPE
		|| type == D_QUOTE_TYPE
		|| type == S_QUOTE_TYPE
		|| type == AND_TYPE
		|| type == OR_TYPE)
		unexpected_token_error(get_token_token(lst));
}

static void		aggregations(t_list *lst)
{
	int		type;

	if (lst->next)
	{
		type = get_type_token(lst->next);
		if (type == NUMBER_TYPE || type == WORD_TYPE)
		{
			set_type_token(lst->next, AGGREGATION_ARG_TYPE);
			return ;
		}
	}
	unexpected_token_error(get_token_token(lst));
}

static void		redirections(t_list *lst)
{
	int		type;

	if (lst->next)
	{
		type = get_type_token(lst->next);
		if (type == WORD_TYPE)
		{
			set_type_token(lst->next, REDIRECTION_ARG_TYPE);
			return ;
		}
	}
	unexpected_token_error(get_token_token(lst));
}

void 	ft_lstremoveone(t_list	**lst)
{
	t_list	*tmp;

	tmp = *lst;
	if (!tmp)
		return ;
	if (tmp->prev)
		tmp->prev->next = tmp->next;
	if (tmp->next)
		tmp->next->prev = tmp->prev;
	// tmp->prev = NULL;
	// tmp->next = NULL;
	// (void)del;
	// ft_lstdelone(&tmp, free_token);
}

static void		variables(t_list *lst)
{
	int		type;
	char	*value;
	t_list	*tmp;
	t_var	*var;
	t_list	*next;
	t_list	*del;
	t_list	*new;
	// t_list	*new_lst;

	// new_lst = NULL;
	// creation de la structure var
	var = ft_memalloc(sizeof(t_var));
	// set du name
	var->name = ft_strdup((*((t_var_token **)(lst->content)))->token);
	// if (!lst->next)
	// 	return ;
	type = get_type_token(lst->next);
	if (type != WORD_TYPE)
		return ;
	tmp = lst->next;
	if (get_token_token(lst->next)[0] == '=')
	{
		value = get_token_token(lst->next);
		var->value = ft_strdup(&(value[1]));
		var->value_is_expansion = (*((t_var_token **)(lst->next->content)))->is_expansion;
		// set_value_token(lst, ft_strdup(&(value[1])));
		del = lst->next;
		ft_lstremoveone(&lst->next);
		ft_lstdelone(&del, free_token);
	}
	// ft_printf("Apres la premiere value, lst = %s, lst next = %s\n", get_token_token(lst), lst->next);
	new = ft_lstnew(&var, sizeof(t_var *));
	if (!(*((t_var_token **)(lst->content)))->vars)
		(*((t_var_token **)(lst->content)))->vars = new;
	else
		ft_lstaddend(&(*((t_var_token **)(lst->content)))->vars, new);
	// Boucle pour les var suivants
	tmp = lst->next;
	while (tmp)
	{
		// if (!tmp)
			// return ;
		// creation de la structure var
		if (get_type_token(tmp) != VAR_TYPE)
			break ;
		var = ft_memalloc(sizeof(t_var));
		// set du name
		var->name = ft_strdup((*((t_var_token **)(tmp->content)))->token);
		if (!tmp->next)
			break ;
		type = get_type_token(tmp->next);
		if (get_token_token(tmp->next)[0] == '=')
		{
			value = get_token_token(tmp->next);
			var->value = ft_strdup(&(value[1]));
			var->value_is_expansion = (*((t_var_token **)(tmp->next->content)))->is_expansion;
			// set_value_token(lst, ft_strdup(&(value[1])));
			del = tmp->next;
			ft_lstremoveone(&(tmp->next));
			ft_lstdelone(&del, free_token);
		}
		new = ft_lstnew(&var, sizeof(t_var *));
		ft_lstaddend(&(*((t_var_token **)(lst->content)))->vars, new);
		next = tmp->next;
		ft_lstremoveone(&tmp);
		ft_lstdelone(&tmp, free_token);
		tmp = next;
	}
	// (*((t_var_token **)(lst->content)))->vars = new_lst;
}

static void		operators(t_list *lst)
{
	int		type;

	if (lst->next)
	{
		type = get_type_token(lst->next);
		if (is_operator(type))
			unexpected_token_error(get_token_token(lst));
	}
	else
	{
		if (is_operator(get_type_token(lst)))
			unexpected_token_error(get_token_token(lst));
	}
}



void 	first_check_tokens_list(t_list *lst)
{
	t_list		*tmp;
	int			t;

	tmp = lst;
	if (lst == NULL)
		return ;
	t = get_type_token(tmp);
	if (t == DOTCOMMA_TYPE || t == PIPE_TYPE || t == AND_TYPE || t == OR_TYPE)
		return (unexpected_token_error(get_token_token(tmp)));
	while (tmp)
	{
		!is_aggregation(get_type_token(tmp)) ?0: aggregations(tmp);
		!is_redirection(get_type_token(tmp)) ?0: redirections(tmp);
		// !(get_type_token(tmp) == VAR_TYPE) ?0: (void)variables(tmp);
		if (get_type_token(tmp) == VAR_TYPE)
			variables(tmp);
		!is_operator(get_type_token(tmp)) ?0: operators(tmp);
		!(get_token_token(tmp)[0] == '~') ?0: set_expansion_token(tmp, TRUE);
		!(get_type_token(tmp) == NUMBER_TYPE) ?0: set_type_token(tmp, WORD_TYPE);
		if (tmp->next == NULL)
			return (not_terminal_type(tmp));
		tmp = tmp->next;
	}
}
