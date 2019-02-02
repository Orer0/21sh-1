/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 01:53:21 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/28 06:49:08 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "21sh.h"
# include "st.h"

void 		execute_post_order_procedure(t_ptree **tree);
t_btree		*get_ast(t_ptree **parsing_tree);
void 		delete_ast(t_btree **ast);

#endif
