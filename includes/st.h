/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 20:48:21 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/28 06:08:16 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ST_H
# define ST_H

# include "libft.h"
# include "tokens.h"

# define	S_RULE						800
# define	S_PRIME_RULE				801
# define 	T_RULE						802
# define	T_PRIME_RULE				903
# define	U_RULE						904
# define	U_PRIME_RULE				904
# define	V_RULE						905
# define	V_PRIME_RULE				905
# define	F_RULE						905
# define	A_RULE						906
# define	A_PRIME_RULE				907

typedef struct			s_ptree
{
	int				id;
	char			*data;
	int				type;
	t_list			*childs_lst;
	int				nb_childs;
	t_btree			*ast;
}						t_ptree;

typedef struct	s_tokens_list
{
				t_list	*tokens_list;
				int		index;
				int		size;
}				t_tokens_list;

void 		syntax_tree(t_list **tokens_list, t_ptree **tree);

/*
**	ft_ptree functions
*/

int		ft_ptree_remove_node_with_id(t_ptree **tree, int id);
t_ptree		**ft_ptree_get_node_with_id(t_ptree **tree, int id);
int		ft_ptree_add_child(t_ptree **tree, void *data, int type);
void 	ft_ptree_create_node(t_ptree **tree, void *data, int type);

/*
** Rules
*/

int		test_current_token(t_tokens_list **tokens_s, int type, t_ptree **tree);
int		s_rule(t_tokens_list **tokens_list_struct, t_ptree **tree);
int		s_prime_rule(t_tokens_list **tokens_list_struct, t_ptree **tree);
int		a_rule(t_tokens_list **tokens_list_struct, t_ptree **tree);
int		a_prime_rule(t_tokens_list **tokens_list_struct, t_ptree **tree);
int		t_rule(t_tokens_list **tokens_list_struct, t_ptree **tree);
int		t_prime_rule(t_tokens_list **tokens_list_struct, t_ptree **tree);
int		u_prime_rule(t_tokens_list **tokens_list_struct, t_ptree **tree);
int		u_rule(t_tokens_list **tokens_list_struct, t_ptree **tree);
int		v_rule(t_tokens_list **tokens_list_struct, t_ptree **tree);
int		v_prime_rule(t_tokens_list **tokens_list_struct, t_ptree **tree);
int		f_rule(t_tokens_list **tokens_list_struct, t_ptree **tree);


/*
**	Delete
*/

void 		free_ptree_node(t_ptree **tree);
void 		del_ptree_node(void *content, size_t size);
void 		delete_parsing_tree(t_ptree **tree);

#endif
