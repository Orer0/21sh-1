/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 05:41:20 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/13 18:56:25 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "st.h"

void			ft_ptree_create_node(t_ptree **tree, void *data, int type)
{
	static int	id = -1;

	id++;
	*tree = ft_memalloc(sizeof(t_ptree));
	(*tree)->id = id;
	(*tree)->data = data;
	(*tree)->type = type;
	(*tree)->childs_lst = NULL;
	(*tree)->nb_childs = 0;
	(*tree)->ast = NULL;
}

int				ft_ptree_add_child(t_ptree **tree, void *data, int type)
{
	t_list	*tmp;
	t_ptree	*child;

	if (!tree)
		return (FALSE);
	ft_ptree_create_node(&child, data, type);
	if (!(tmp = ft_lstnew(&child, sizeof(t_ptree *))))
	{
		ft_printf("erreur de lstnew dans add_child\n");
		return (FALSE);
	}
	if ((*tree)->nb_childs == 0)
	{
		(*tree)->childs_lst = tmp;
		(*tree)->nb_childs++;
		return (child->id);
	}
	ft_lstaddend(&(*tree)->childs_lst, tmp);
	(*tree)->nb_childs++;
	return (child->id);
}

t_ptree			**ft_ptree_get_node_with_id(t_ptree **tree, int id)
{
	t_list	*tmp;

	if (!tree)
		return (NULL);
	if ((*tree)->id == id)
		return (tree);
	tmp = (*tree)->childs_lst;
	while (tmp)
	{
		if ((*((t_ptree **)(tmp->content)))->id == id)
			return (((t_ptree **)(tmp->content)));
		ft_ptree_get_node_with_id(((t_ptree **)(tmp->content)), id);
		tmp = tmp->next;
	}
	return (NULL);
}

static void		ft_lstremoveone(t_list **lst)
{
	t_list	*tmp;

	tmp = *lst;
	if (!tmp)
		return ;
	if (tmp->prev)
		tmp->prev->next = tmp->next;
	if (tmp->next)
		tmp->next->prev = tmp->prev;
	ft_lstdelone(&tmp, del_ptree_node);
}

int				ft_ptree_remove_node_with_id(t_ptree **tree, int id)
{
	t_list	*tmp;
	t_list	*next;

	if (!tree)
		return (FALSE);
	tmp = (*tree)->childs_lst;
	while (tmp)
	{
		if ((*((t_ptree **)(tmp->content)))->id == id)
		{
			next = tmp->next;
			ft_lstremoveone(&tmp);
			(*tree)->nb_childs--;
			tmp = next;
			return (TRUE);
		}
		tmp = tmp->next;
	}
	return (FALSE);
}
