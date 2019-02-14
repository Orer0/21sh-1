/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aggr_redir_execution.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 22:58:14 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/13 17:54:19 by aroblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static void	aggr_get_var(t_btree *tree, char **arr, t_list **old_intern_env)
{
	t_shell_data	*data;
	t_list			*tmp_intern_env;

	data = shell_data_singleton();
	*old_intern_env = data->intern_env_lst;
	tmp_intern_env = ft_lstcpy(data->intern_env_lst, &tmp_intern_env);
	data->intern_env_lst = tmp_intern_env;
	arr = get_var_tab(((t_var_token **)(tree->left->data)));
	set_builtin(arr, &data);
	ft_strtab_del(&arr);
}

static void	aggr_exec_child(t_btree *tree, char **arr)
{
	char			*final_path;
	t_shell_data	*data;
	t_list			*old_intern_env;

	old_intern_env = NULL;
	data = shell_data_singleton();
	if (get_var_token_in_cmd_token(tree->left->data))
		aggr_get_var(tree, arr, &old_intern_env);
	arr = get_cmd_tab(((t_cmd_token **)(tree->left->data)));
	if (!manage_builtins(arr))
	{
		if (!arr[0][0] || !(final_path = get_path_of_bin(arr[0])))
			exit(EXIT_FAILURE);
		if (!execve(final_path, arr, data->env_tab))
			exit(EXIT_FAILURE);
	}
	ft_strtab_del(&arr);
	if (get_var_token_in_cmd_token(tree->left->data))
	{
		ft_lstdel(&data->intern_env_lst, del_env_var);
		data->intern_env_lst = old_intern_env;
	}
	exit(EXIT_SUCCESS);
}

static void	aggr_manag_type(t_btree *tree)
{
	char			**arr;
	t_shell_data	*data;

	data = shell_data_singleton();
	arr = NULL;
	if (get_type_token(tree->left->data) == CMD_TYPE)
		aggr_exec_child(tree, arr);
	else if (get_type_token(tree->left->data) == VAR_TYPE)
	{
		arr = get_var_tab(((t_var_token **)(tree->left->data)));
		set_builtin(arr, &data);
		exit(EXIT_SUCCESS);
	}
}

void		aggr_redir_execution(t_btree *tree)
{
	int				status;
	pid_t			pid;
	t_shell_data	*data;

	data = shell_data_singleton();
	pid = fork();
	if (pid == 0)
	{
		if (is_redirection(get_type_token(tree->data)))
			redir_recursion(tree);
		else if (is_aggregation(get_type_token(tree->data)))
			aggr_recursion(tree);
		if (get_type_token(tree->left->data) == CMD_TYPE
				|| get_type_token(tree->left->data) == VAR_TYPE)
			aggr_manag_type(tree);
	}
	else if (pid < 0)
		quit_shell(EXIT_FAILURE, FORK_ERR);
	else if (pid > 0)
	{
		signal(SIGINT, catch_signal_kill);
		waitpid(pid, &status, 0);
		data->last_status = status;
	}
}
