/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 20:47:47 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/22 03:58:22 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "st.h"

static void 	del_ptree_node(void *content, size_t size);

/*
**	FREE
*/

static void 	free_ptree_node(t_ptree **tree)
{
	ft_lstdel(&((*tree)->childs_lst), del_ptree_node);
	ft_memdel((void **)tree);
}


static void 	del_ptree_node(void *content, size_t size)
{
	(void)size;
	if (!content)
		return ;
	// Free un child
	ft_lstdel(&(*((t_ptree **)(content)))->childs_lst, del_ptree_node);
	free_ptree_node(((t_ptree **)(content)));
	ft_memdel(&content);
}

/*
**	Creer noeud d'arbre de parsing
*/

void 	ft_ptree_create_node(t_ptree **tree, void *data, int type)
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

/*
**	Ajoute un noeud enfant au noeud passe
*/

int		ft_ptree_add_child(t_ptree **tree, void *data, int type)
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

/*
**	Retourne un noeud de l'arbre grace a son id
*/

t_ptree		**ft_ptree_get_node_with_id(t_ptree **tree, int id)
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

/*
**	Recherche et supprime un noeud dans l'arbre grace a son id
*/

int		ft_ptree_remove_node_with_id(t_ptree **tree, int id)
{
	t_list	*tmp;
	t_list	*prev;

	if (!tree)
		return (FALSE);
	tmp = (*tree)->childs_lst;
	if (tmp && (*((t_ptree **)(tmp->content)))->id == id)
	{
		prev = tmp;
		(*tree)->childs_lst = tmp->next;
		ft_lstdelone(&prev, del_ptree_node);
		(*tree)->nb_childs--;
		return (TRUE);
	}
	while (tmp)
	{
		if (tmp->next && (*((t_ptree **)(tmp->next->content)))->id == id)
		{
			prev = tmp->next;
			tmp->next = tmp->next->next;
			ft_lstdelone(&prev, del_ptree_node);
			free(prev);
			(*tree)->nb_childs--;
			return (TRUE);
		}
		ft_ptree_remove_node_with_id(((t_ptree **)(tmp->content)), id);
		tmp = tmp->next;
	}
	return (FALSE);
}

////////////////////////////////////////////////////////////////////////////////
//////////////													////////////////
//////////////				REGLES DE GRAMMAIRE					////////////////
//////////////													////////////////
////////////////////////////////////////////////////////////////////////////////

/*
**	Compare le type du token avec le type entre et creer un noeud si OK
*/

int		test_current_token(t_tokens_list **tokens_list_struct, int type, t_ptree **subtree)
{
	t_list	*good_token;

	good_token = ft_lsti((*tokens_list_struct)->tokens_list, (*tokens_list_struct)->index);
	if ((*tokens_list_struct)->index + 1 > (*tokens_list_struct)->size)
		return (FALSE);
	if (type_cmp((*((t_token **)(good_token->content)))->type, type))
	{
		ft_ptree_add_child(subtree, (*((t_token **)(good_token->content)))->token, (*((t_token **)(good_token->content)))->type);
		(*tokens_list_struct)->index++;
		return (TRUE);
	}
	return (FALSE);
}

static int		S_function(t_tokens_list **tokens_list_struct, t_ptree **tree);
static int		S_prime_function(t_tokens_list **tokens_list_struct, t_ptree **tree);
static int		T_function(t_tokens_list **tokens_list_struct, t_ptree **tree);
static int		U_prime_function(t_tokens_list **tokens_list_struct, t_ptree **tree);

/*
**	Regle F
*/

static int		F_function(t_tokens_list **tokens_list_struct, t_ptree **tree)
{
	int		id;
	int		save_index;
	t_ptree		**tmp;

	// Ajout a l'arbre d'un noeud correspond a cette regle et recupere son id
	id = ft_ptree_add_child(tree, NULL, F_RULE);
	// Recupere ce noeud
	tmp = ft_ptree_get_node_with_id(tree, id);
	// Retient l'index de la liste des tokens avant de commencer
	save_index = (*tokens_list_struct)->index;
	// Premiere regle de la grammaire
	if (test_current_token(tokens_list_struct, CMD_TYPE, tmp))
	{
		return (TRUE);
	}
	// La regle a rate -> retourne sur l'index d'avant
	(*tokens_list_struct)->index = save_index;
	// Supprime l'arbre faux qui a ete cree
	ft_ptree_remove_node_with_id(tree, id);
	return (FALSE);
}

/*
**	Regle V prime -> pas de noeud et toujours true (epsilon)
*/

static int		V_prime_function(t_tokens_list **tokens_list_struct, t_ptree **tree)
{
	int		save_index;

	// Retient l'index de la liste des tokens avant de commencer
	save_index = (*tokens_list_struct)->index;
	// Premiere regle de la grammaire
	if (test_current_token(tokens_list_struct, AGGREGATION_TYPE, tree) && test_current_token(tokens_list_struct, AGGREGATION_ARG_TYPE, tree)  && V_prime_function(tokens_list_struct, tree))
	{
		return (TRUE);
	}
	// La regle a rate -> retourne sur l'index d'avant
	(*tokens_list_struct)->index = save_index;
	// Deuxieme regle de la grammaire
	if (test_current_token(tokens_list_struct, AGGREGATION_TYPE, tree)  && V_prime_function(tokens_list_struct, tree))
	{
		return (TRUE);
	}
	// La regle a rate -> retourne sur l'index d'avant
	(*tokens_list_struct)->index = save_index;
	return (TRUE);
}

/*
**	Regle V
*/

static int		V_function(t_tokens_list **tokens_list_struct, t_ptree **tree)
{
	int		id;
	int		save_index;
	t_ptree		**tmp;

	// Ajout a l'arbre d'un noeud correspond a cette regle et recupere son id
	id = ft_ptree_add_child(tree, NULL, V_RULE);
	// Recupere ce noeud
	tmp = ft_ptree_get_node_with_id(tree, id);
	// Retient l'index de la liste des tokens avant de commencer
	save_index = (*tokens_list_struct)->index;
	// Premiere regle de la grammaire
	if (F_function(tokens_list_struct, tmp) && V_prime_function(tokens_list_struct, tmp))
	{
		return (TRUE);
	}
	// La regle a rate -> retourne sur l'index d'avant
	(*tokens_list_struct)->index = save_index;
	// Supprime l'arbre faux qui a ete cree
	ft_ptree_remove_node_with_id(tree, id);
	return (FALSE);
}

/*
**	Regle U prime -> pas de noeud et toujours true (epsilon)
*/

static int		U_prime_function(t_tokens_list **tokens_list_struct, t_ptree **tree)
{
	int		save_index;

	// Retient l'index de la liste des tokens avant de commencer
	save_index = (*tokens_list_struct)->index;
	// Premiere regle de la grammaire
	if (test_current_token(tokens_list_struct, REDIRECTION_TYPE, tree) && test_current_token(tokens_list_struct, REDIRECTION_ARG_TYPE, tree)  && U_prime_function(tokens_list_struct, tree))
	{
		return (TRUE);
	}
	// La regle a rate -> retourne sur l'index d'avant
	(*tokens_list_struct)->index = save_index;
	return (TRUE);
}

/*
**	Regle U
*/

static int		U_function(t_tokens_list **tokens_list_struct, t_ptree **tree)
{
	int		id;
	int		save_index;
	t_ptree		**tmp;

	// Ajout a l'arbre d'un noeud correspond a cette regle et recupere son id
	id = ft_ptree_add_child(tree, NULL, U_RULE);
	// Recupere ce noeud
	tmp = ft_ptree_get_node_with_id(tree, id);
	// Retient l'index de la liste des tokens avant de commencer
	save_index = (*tokens_list_struct)->index;
	// Premiere regle de la grammaire
	if (V_function(tokens_list_struct, tmp) && U_prime_function(tokens_list_struct, tmp))
	{
		return (TRUE);
	}
	// La regle a rate -> retourne sur l'index d'avant
	(*tokens_list_struct)->index = save_index;
	// Supprime l'arbre faux qui a ete cree
	ft_ptree_remove_node_with_id(tree, id);
	return (FALSE);
}

/*
**	Regle T prime -> pas de noeud et toujours true (epsilon)
*/

static int		T_prime_function(t_tokens_list **tokens_list_struct, t_ptree **tree)
{
	int		save_index;

	// Retient l'index de la liste des tokens avant de commencer
	save_index = (*tokens_list_struct)->index;
	// Premiere regle de la grammaire
	if (test_current_token(tokens_list_struct, PIPE_TYPE, tree) && T_function(tokens_list_struct, tree) && T_prime_function(tokens_list_struct, tree))
	{
		return (TRUE);
	}
	// La regle a rate -> retourne sur l'index d'avant
	(*tokens_list_struct)->index = save_index;
	return (TRUE);
}

/*
**	Regle T
*/

static int		T_function(t_tokens_list **tokens_list_struct, t_ptree **tree)
{
	int		id;
	int		save_index;
	t_ptree		**tmp;

	// Ajout a l'arbre d'un noeud correspond a cette regle et recupere son id
	id = ft_ptree_add_child(tree, NULL, T_RULE);
	// Recupere ce noeud
	tmp = ft_ptree_get_node_with_id(tree, id);
	// Retient l'index de la liste des tokens avant de commencer
	save_index = (*tokens_list_struct)->index;
	// Premiere regle de la grammaire
	if (U_function(tokens_list_struct, tmp) && T_prime_function(tokens_list_struct, tmp))
	{
		return (TRUE);
	}
	// La regle a rate -> retourne sur l'index d'avant
	(*tokens_list_struct)->index = save_index;
	// Supprime l'arbre faux qui a ete cree
	ft_ptree_remove_node_with_id(tree, id);
	return (FALSE);
}

/*
**	Regle S prime -> pas de noeud et toujours true (epsilon)
*/

static int		S_prime_function(t_tokens_list **tokens_list_struct, t_ptree **tree)
{
	int		save_index;

	// Retient l'index de la liste des tokens avant de commencer
	save_index = (*tokens_list_struct)->index;
	// Premiere regle de la grammaire
	if (test_current_token(tokens_list_struct, DOTCOMMA_TYPE, tree) && S_function(tokens_list_struct, tree) && S_prime_function(tokens_list_struct, tree))
	{
		return (TRUE);
	}
	// La regle a rate -> retourne sur l'index d'avant
	(*tokens_list_struct)->index = save_index;
	return (TRUE);
}

/*
**	Regle S -> Premiere regle
*/

static int		S_function(t_tokens_list **tokens_list_struct, t_ptree **tree)
{
	int		id;
	int		save_index;
	t_ptree		**tmp;

	// Ajout a l'arbre d'un noeud correspond a cette regle et recupere son id
	id = ft_ptree_add_child(tree, NULL, S_RULE);
	// Recupere ce noeud
	tmp = ft_ptree_get_node_with_id(tree, id);
	// Retient l'index de la liste des tokens avant de commencer
	save_index = (*tokens_list_struct)->index;
	// Premiere regle de la grammaire
	if (T_function(tokens_list_struct, tmp) && S_prime_function(tokens_list_struct, tmp))
	{
		return (TRUE);
	}
	// La regle a rate -> retourne sur l'index d'avant
	(*tokens_list_struct)->index = save_index;
	// Supprime l'arbre faux qui a ete cree
	ft_ptree_remove_node_with_id(tree, id);
	return (FALSE);
}

////////////////////////////////////////////////////////////////////////////////
//////////////													////////////////
//////////////				FIN REGLES DE GRAMMAIRE				////////////////
//////////////													////////////////
////////////////////////////////////////////////////////////////////////////////

/*
**	Creer la struct qui contient la liste de tokens et son index
*/

static t_tokens_list		*create_tokens_list_struct(t_list *lst)
{
	t_tokens_list	*result;

	result = ft_memalloc(sizeof(t_tokens_list));
	result->index = 0;
	result->size = ft_lstlen(lst);
	result->tokens_list = lst;
	return (result);
}

/*
**	Delete proprement l'arbre de syntaxe
*/

void 	delete_parsing_tree(t_ptree **tree)
{
	free_ptree_node(tree);
}

void syntax_tree(t_list **tokens_list, t_ptree **tree)
{
	t_tokens_list *tokens_list_struct;

	// Creer la struct qui contient la liste de tokens et son index
	tokens_list_struct = create_tokens_list_struct(*tokens_list);
	// Creer le premier noeud START
	ft_ptree_create_node(tree, NULL, START_TYPE);
	// Appelle la premiere regle
	S_function(&tokens_list_struct, tree);
	// Free la struct qui contient la liste de token et son index
	ft_memdel((void **)&tokens_list_struct);
}
