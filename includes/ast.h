/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 01:53:21 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/22 02:08:14 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "21sh.h"
# include "st.h"

typedef struct		s_ast_token
{
	int				type;
	char			*data;
}					t_ast_token;

t_btree		*get_ast(t_ptree **parsing_tree);
void 		delete_ast(t_btree *ast);

#endif
