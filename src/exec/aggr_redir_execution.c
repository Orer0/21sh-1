/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aggr_redir_execution.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 22:58:14 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/09 02:58:20 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void	aggr_redir_execution(t_btree *tree)
{
	int		status;
	pid_t	pid;
	t_shell_data	*data;

	data = shell_data_singleton();

	pid = fork();
	// PROCESSUS ENFANT
	if (pid == 0)
	{
		if (is_redirection(get_type_token(tree->data)))
			redir_recursion(tree);
		else if (is_aggregation(get_type_token(tree->data)))
			aggr_recursion(tree);
		// Si le noeud de gauche est une command ou une variable
		if (get_type_token(tree->left->data) == CMD_TYPE || get_type_token(tree->left->data) == VAR_TYPE)
		{
			char	**tab;
			t_list	*old_intern_env;
			t_list	*tmp_intern_env;

			// EXECUTER LE NOEUD DE GAUCHE
			// ft_printf("EXECUTION NOEUD GAUCHE = %s\n", get_token_token(tree->left->data));
			if (get_type_token(tree->left->data) == CMD_TYPE)
			{
				// DECLARATION DES VARIABLES POUR CETTE COMMANDE
				if (get_var_token_in_cmd_token(tree->left->data))
				{
					old_intern_env = data->intern_env_lst;
					tmp_intern_env = ft_lstcpy(data->intern_env_lst, &tmp_intern_env);
					data->intern_env_lst = tmp_intern_env;
					tab = get_var_tab(((t_var_token **)(tree->left->data)));
					set_builtin(tab);
					ft_strtab_del(&tab);
				}
				// CREATION DU TABLEAU DE LA COMMANDE POUR EXECVE
				tab = get_cmd_tab(((t_cmd_token **)(tree->left->data)));
				if (!manage_builtins(tab))
				{
					char *final_path;
					if (!tab[0][0] || !(final_path = get_path_of_bin(tab[0])))
						return ;
					if (!execve(final_path, tab, data->env_tab))
						ft_printf("EXECVE A FOIRE\n");
				}
					//exec_command(tab, data->env_tab);
				// FREE
				ft_strtab_del(&tab);
				if (get_var_token_in_cmd_token(tree->left->data))
				{
					ft_lstdel(&data->intern_env_lst, del_env_var);
					data->intern_env_lst = old_intern_env;
				}
				exit(0);
				//
			}
			// VARIABLES
			else if (get_type_token(tree->left->data) == VAR_TYPE)
			{
				tab = get_var_tab(((t_var_token **)(tree->left->data)));
				set_builtin(tab);
				exit(0);
			// exec_ast(tree->left, TRUE);
			}
		}
	}
	// ERREUR DE FORK
	else if (pid < 0)
		ft_printf("fail fork\n");
	// PROCESSUS PERE
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		data->last_status = status;
		// ft_printf(" DANS LE PERE APRES\n");
	}
}
