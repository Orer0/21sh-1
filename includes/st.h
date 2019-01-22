/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 20:48:21 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/22 03:23:53 by ndubouil         ###   ########.fr       */
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
void 		delete_parsing_tree(t_ptree **tree);

#endif
