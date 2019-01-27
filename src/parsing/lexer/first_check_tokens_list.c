/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_check_tokens_list.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 00:10:05 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/27 05:59:31 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void		unexpected_token_error(char *token)
{
	ft_printf("syntax error near unexpected token : \"%s\"\n", token);
	quit_shell(EXIT_FAILURE, 0);
}

static void		not_terminal_type(t_list *lst)
{
	int		type;

	type = get_type_token(lst->content);
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
		type = get_type_token(lst->next->content);
		if (type == NUMBER_TYPE || type == WORD_TYPE)
		{
			set_type_token(lst->next->content, AGGREGATION_ARG_TYPE);
			return ;
		}
	}
	unexpected_token_error(get_token_token(lst->content));
}

static void		redirections(t_list *lst)
{
	int		type;

	if (lst->next)
	{
		type = get_type_token(lst->next->content);
		if (type == WORD_TYPE)
		{
			set_type_token(lst->next->content, REDIRECTION_ARG_TYPE);
			return ;
		}
	}
	unexpected_token_error(get_token_token(lst));
}

static void 	ft_lstremoveone(t_list	**lst)
{
	t_list	*tmp;

	tmp = *lst;
	if (!tmp)
		return ;
	if (tmp->prev)
		tmp->prev->next = tmp->next;
	if (tmp->next)
		tmp->next->prev = tmp->prev;
}

void	create_t_var(t_var **var, char *name, char *value)
{
	if (!(*var = ft_memalloc(sizeof(t_var))))
		quit_shell(EXIT_FAILURE, MALLOC_ERR);
	(*var)->name = ft_strdup(name);
	(*var)->value = ft_strdup(value);
	(*var)->value_is_expansion = FALSE;
}

// static void		variables(t_list *lst)
// {
// 	int		type;
// 	char	*value;
// 	t_list	*tmp;
// 	t_var	*var;
// 	t_list	*next;
// 	t_list	*del;
// 	t_list	*new;
//
// 	create_t_var(&var, get_token_token(lst->content), NULL);
// 	type = get_type_token(lst->next->content);
// 	if (type != WORD_TYPE)
// 		return ;
// 	tmp = lst->next;
// 	if (get_token_token(lst->next->content)[0] == '=')
// 	{
// 		value = get_token_token(lst->next->content);
// 		var->value = ft_strdup(&(value[1]));
// 		var->value_is_expansion = get_expansion_token(lst->next->content);
// 		del = lst->next;
// 		ft_lstremoveone(&lst->next);
// 		ft_lstdelone(&del, free_token);
// 	}
// 	new = ft_lstnew(&var, sizeof(t_var *));
// 	if (!get_var_list_token(lst->content))
// 		(*((t_var_token **)(lst->content)))->var_lst = new;
// 	else
// 		ft_lstaddend(&(*((t_var_token **)(lst->content)))->var_lst, new);
// 	// Boucle pour les var suivants
// 	tmp = lst->next;
// 	while (tmp)
// 	{
// 		// creation de la structure var
// 		if (get_type_token(tmp->content) != VAR_TYPE)
// 			break ;
// 		var = ft_memalloc(sizeof(t_var));
// 		// set du name
// 		var->name = ft_strdup((*((t_var_token **)(tmp->content)))->token);
// 		if (!tmp->next)
// 			break ;
// 		type = get_type_token(tmp->next->content);
// 		if (get_token_token(tmp->next->content)[0] == '=')
// 		{
// 			value = get_token_token(tmp->next->content);
// 			var->value = ft_strdup(&(value[1]));
// 			var->value_is_expansion = (*((t_var_token **)(tmp->next->content)))->is_expansion;
// 			// set_value_token(lst, ft_strdup(&(value[1])));
// 			del = tmp->next;
// 			ft_lstremoveone(&(tmp->next));
// 			ft_lstdelone(&del, free_token);
// 		}
// 		new = ft_lstnew(&var, sizeof(t_var *));
// 		ft_lstaddend(&(*((t_var_token **)(lst->content)))->var_lst, new);
// 		next = tmp->next;
// 		ft_lstremoveone(&tmp);
// 		ft_lstdelone(&tmp, free_token);
// 		tmp = next;
// 	}
// }

static void		variables(t_list *lst)
{
	// int		type;
	// char	*value;
	t_list	*tmp;
	// t_var	*var;
	t_list	*next;
	// t_list	*del;
	t_list	*new;

	// create_t_var(&var, get_token_token(lst->content), NULL);
	// type = get_type_token(lst->next->content);
	// if (type != WORD_TYPE)
	// 	return ;
	// tmp = lst->next;
	// if (get_token_token(lst->next->content)[0] == '=')
	// {
	// 	value = get_token_token(lst->next->content);
	// 	var->value = ft_strdup(&(value[1]));
	// 	var->value_is_expansion = get_expansion_token(lst->next->content);
	// 	del = lst->next;
	// 	ft_lstremoveone(&lst->next);
	// 	ft_lstdelone(&del, free_token);
	// }
	set_type_token(lst->content, VAR_TYPE);
	new = ft_lstnew(((t_var_token **)(lst->content)), sizeof(t_var_token *));
	if (!get_var_list_token(lst->content))
		(*((t_var_token **)(lst->content)))->var_lst = new;
	else
		ft_lstaddend(&(*((t_var_token **)(lst->content)))->var_lst, new);
	// Boucle pour les var suivants
	tmp = lst->next;
	while (tmp)
	{
		if (!ft_strchr(get_token_token(tmp->content), '='))
			break ;
		new = ft_lstnew(((t_var_token **)(lst->content)), sizeof(t_var_token *));
		ft_lstaddend(&(*((t_var_token **)(lst->content)))->var_lst, new);
		// // creation de la structure var
		// if (get_type_token(tmp->content) != VAR_TYPE)
		// 	break ;
		// var = ft_memalloc(sizeof(t_var));
		// // set du name
		// var->name = ft_strdup((*((t_var_token **)(tmp->content)))->token);
		if (!tmp->next)
			break ;
		// type = get_type_token(tmp->next->content);
		// if (get_token_token(tmp->next->content)[0] == '=')
		// {
		// 	value = get_token_token(tmp->next->content);
		// 	var->value = ft_strdup(&(value[1]));
		// 	var->value_is_expansion = (*((t_var_token **)(tmp->next->content)))->is_expansion;
		// 	// set_value_token(lst, ft_strdup(&(value[1])));
		// 	del = tmp->next;
		// 	ft_lstremoveone(&(tmp->next));
		// 	ft_lstdelone(&del, free_token);
		// }
		// new = ft_lstnew(&var, sizeof(t_var *));
		// ft_lstaddend(&(*((t_var_token **)(lst->content)))->var_lst, new);
		next = tmp->next;
		ft_lstremoveone(&tmp);
		// ft_lstdelone(&tmp, free_token);
		tmp = next;
	}
}

static void		operators(t_list *lst)
{
	int		type;

	if (lst->next)
	{
		type = get_type_token(lst->next);
		if (is_operator(type))
			unexpected_token_error(get_token_token(lst->content));
	}
	else
	{
		if (is_operator(get_type_token(lst->content)))
			unexpected_token_error(get_token_token(lst->content));
	}
}



void 	first_check_tokens_list(t_list *lst)
{
	t_list		*tmp;
	int			t;

	tmp = lst;
	if (lst == NULL)
		return ;
	t = get_type_token(tmp->content);
	if (t == DOTCOMMA_TYPE || t == PIPE_TYPE || t == AND_TYPE || t == OR_TYPE)
		return (unexpected_token_error(get_token_token(tmp->content)));
	while (tmp)
	{
		is_aggregation(get_type_token(tmp->content)) ? aggregations(tmp) : 0;
		is_redirection(get_type_token(tmp->content)) ? redirections(tmp) : 0;
		is_operator(get_type_token(tmp->content)) ? operators(tmp) : 0;
		if (ft_strchr(get_token_token(tmp->content), '='))
			variables(tmp);
		// if (get_type_token(tmp->content) == VAR_TYPE)
		// if (get_token_token(tmp->content)[0] == '~')
		// 	set_expansion_token(tmp->content, TRUE);
		if (get_type_token(tmp->content) == NUMBER_TYPE)
			set_type_token(tmp->content, WORD_TYPE);
		if (tmp->next == NULL)
			return (not_terminal_type(tmp));
		tmp = tmp->next;
	}
}
