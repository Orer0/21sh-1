/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 16:39:01 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/19 23:03:12 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/*
**	Retourne le type du token
*/

static int			get_type_of_token(int last_state)
{
	if (last_state == NUMBER_STATE)
		return (NUMBER_TYPE);
	else if (last_state == CHAR_STATE)
		return (WORD_TYPE);
	else if (last_state == PIPE_V_STATE)
		return (PIPE_V_STATE);
	else if (last_state == DOTCOMMA_V_STATE)
		return (DOTCOMMA_TYPE);
	else if (last_state == LEFT_REDIRECTION_STATE
		|| last_state == RIGHT_REDIRECTION_STATE
		|| last_state == DOUBLE_LEFT_REDIRECTION_STATE
		|| last_state == DOUBLE_RIGHT_REDIRECTION_STATE)
		return (REDIRECTION_TYPE);
	else if (last_state == LEFT_AGGREGATION_V_STATE
			|| last_state ==  RIGHT_AGGREGATION_V_STATE)
		return (AGGREGATION_TYPE);
	else if (last_state == TILDE_STATE)
		return (TILDE_TYPE);
	return (NONE_TYPE);
}

/*
**	Initialise une structure representant le token
*/

static void 	create_token_struct(char *token, int last_state, t_token **tok)
{
	*tok = ft_memalloc(sizeof(t_token));
	(*tok)->token = ft_strdup(token);
	(*tok)->type = get_type_of_token(last_state);
}

/*
**	Retourne l'index de la colonne du tableau automate correspondant au caractere
*/

static int get_index_from_char(char *s, int i)
{
	if (s[i] == '-')
		return (DASH_INDEX);
	else if (s[i] == '~')
		return (TILDE_INDEX);
	else if (s[i] == ';')
		return (DOTCOMMA_INDEX);
	else if (s[i] == '|' && s[i + 1])
		return (PIPE_INDEX);
	else if (s[i] == '"')
		return (D_QUOTE_INDEX);
	else if (s[i] == '\'')
		return (S_QUOTE_INDEX);
	else if (s[i] == '\\' && s[i + 1])
		return (BACKSLASH_INDEX);
	else if (s[i] == '<' && s[i + 1])
		return (LEFT_REDIRECTION_INDEX);
	else if (s[i] == '>' && s[i + 1])
		return (RIGHT_REDIRECTION_INDEX);
	else if (s[i] == '&')
		return (AMPERSAND_INDEX);
	else if (ft_isspace(s[i]))
		return (SPACES_INDEX);
	else if (ft_isdigit(s[i]))
		return (NUMBER_INDEX);
	else if (ft_isgraph(s[i]) && s[i] != '-' && s[i] != '~' && s[i] != ';'
		&& s[i] != '|' && s[i] != '"' && s[i] != '\'' && s[i] != '<'
		&& s[i] != '>' && s[i] != '&' && s[i] != '\\')
		return (CHAR_INDEX);
	return (NONE_INDEX);
}

/*
**	Push un caractere dans la stack
*/

static void put_char_in_stack(char (*stack)[512], char c)
{
	if (ft_strlen(*stack) >= 510)
	{
		ft_printf("Stack depassee!");
		exit(0);
	}
	(*stack)[ft_strlen(*stack)] = c;
}

/*
**	Detecte si l'etat est accepteur ou pas
*/

static int	is_acceptor(int state)
{
	if (state == DOTCOMMA_V_STATE || state == SPACE_V_STATE
		|| state == LEFT_REDIRECTION_V_STATE
		|| state == RIGHT_REDIRECTION_V_STATE  || state == STAR_STATE
		|| state == PIPE_V_STATE || state == LEFT_AGGREGATION_V_STATE
		|| state == RIGHT_AGGREGATION_V_STATE)
		return (TRUE);
	return (FALSE);
}

/*
**	Detecte si l'etat est ignoré
*/

static int	is_ignored(int current, int state)
{
	if ((current == START_STATE && state == D_QUOTE_STATE)
		|| (current == CHAR_STATE && state == D_QUOTE_STATE)
		|| (current == NUMBER_STATE && state == D_QUOTE_STATE)
		|| (current == TILDE_STATE && state == D_QUOTE_STATE)
		|| (current == END_D_QUOTE_STATE && state == D_QUOTE_STATE)
		|| (current == END_S_QUOTE_STATE && state == D_QUOTE_STATE)
		|| (current == START_STATE && state == S_QUOTE_STATE)
		|| (current == CHAR_STATE && state == S_QUOTE_STATE)
		|| (current == NUMBER_STATE && state == S_QUOTE_STATE)
		|| (current == TILDE_STATE && state == S_QUOTE_STATE)
		|| (current == END_D_QUOTE_STATE && state == S_QUOTE_STATE)
		|| (current == END_S_QUOTE_STATE && state == S_QUOTE_STATE)
		|| (current == START_STATE && state == START_STATE)
		|| state == END_D_QUOTE_STATE
		|| state == END_S_QUOTE_STATE
		|| (current == BACKSLASH_D_QUOTE_STATE && state == D_QUOTE_STATE)
		|| state == BACKSLASH_STATE)
		return (TRUE);
	return (FALSE);
}

/*
**	Detecte si on ne pas peut pas terminer sur cette etat
*/
//
// static int	is_not_terminal(int state)
// {
// 	if (state == D_QUOTE_STATE || state == S_QUOTE_STATE
// 		|| state == CHAR_D_QUOTE_STATE || state == CHAR_S_QUOTE_STATE
// 		|| state == LEFT_REDIRECTION_STATE || state == RIGHT_REDIRECTION_STATE
// 		|| state == IGNORE_SPACE_REDIRECTION_STATE
// 		|| state == DOUBLE_LEFT_REDIRECTION_STATE
// 		|| state == DOUBLE_RIGHT_REDIRECTION_STATE
// 		|| state == IGNORE_SPACE_PIPE_STATE
// 		|| state == BACKSLASH_STATE)
// 		return (TRUE);
// 	return (FALSE);
// }

/*
**	Detecte si on ne pas peut pas terminer sur cette etat
*/

static int	if_take_the_last(int state)
{
	if (state == NUMBER_STATE || state == CHAR_STATE
		|| state == END_D_QUOTE_STATE
		|| state == END_S_QUOTE_STATE)
		return (TRUE);
	return (FALSE);
}

/*
**	Detecte si l'etat est etoile ou pas
*/

static int is_star(int state)
{
	if (state == STAR_STATE)
		return (TRUE);
	return (FALSE);
}

/*
**	Free un token
*/

static void 	free_token(void *content, size_t size)
{
	(void)size;
	ft_strdel(&((*((t_token **)(content)))->token));
	ft_memdel((void **)((t_token **)(content)));
	ft_memdel(&content);
}

/*
**	Delete proprement la liste des tokens
*/

void 	delete_list_tokens(t_list **tokens_list)
{
	ft_lstdel(tokens_list, free_token);
}

int 	first_check_tokens_list(t_list *lst)
{
	t_list		*tmp;

	tmp = lst;
	if (lst == NULL)
		return (0);
	//premier element
	if (((t_token *)(tmp->content))->type == DOTCOMMA_TYPE || ((t_token *)(tmp->content))->type == PIPE_TYPE)
	{
		ft_printf("syntax error near unexpected token : %s\n", ((t_token *)(tmp->content))->token);
		return (FALSE);
	}
	while (tmp != NULL)
	{
		// dernier element
		if (tmp->next == NULL)
		{
			if (((t_token *)(tmp->content))->type == PIPE_TYPE || ((t_token *)(tmp->content))->type == NONE_TYPE)
			{
				ft_printf("syntax error, command not terminated in token : %s\n", ((t_token *)(tmp->content))->token);
				return (0);
			}
		}
		tmp = tmp->next;
	}
	return (1);
}

/*
**	The main function of the Lexer
*/

void lexer(char *line, t_list **tokens_list)
{
	char stack[512];
	static int A[14][15] = {
		{CHAR_STATE, NUMBER_STATE, START_STATE, CHAR_STATE, BACKSLASH_STATE, TILDE_STATE, DOTCOMMA_V_STATE, PIPE_V_STATE, D_QUOTE_STATE, S_QUOTE_STATE, LEFT_REDIRECTION_STATE, RIGHT_REDIRECTION_STATE, CHAR_STATE, NONE_STATE},
		{CHAR_STATE, CHAR_STATE, STAR_STATE, CHAR_STATE, BACKSLASH_STATE, CHAR_STATE, STAR_STATE, STAR_STATE, D_QUOTE_STATE, S_QUOTE_STATE, STAR_STATE, STAR_STATE, CHAR_STATE, NONE_STATE},
		{CHAR_STATE, NUMBER_STATE, STAR_STATE, CHAR_STATE, BACKSLASH_STATE, CHAR_STATE, STAR_STATE, STAR_STATE, D_QUOTE_STATE, S_QUOTE_STATE, LEFT_REDIRECTION_STATE, RIGHT_REDIRECTION_STATE, CHAR_STATE, NONE_STATE},
		{CHAR_STATE, CHAR_STATE, CHAR_STATE, CHAR_STATE, CHAR_STATE, CHAR_STATE, CHAR_STATE, CHAR_STATE, CHAR_STATE, CHAR_STATE, CHAR_STATE, CHAR_STATE, CHAR_STATE, NONE_STATE},
		{CHAR_STATE, CHAR_STATE, STAR_STATE, CHAR_STATE, BACKSLASH_STATE, CHAR_STATE, STAR_STATE, STAR_STATE, D_QUOTE_STATE, S_QUOTE_STATE, STAR_STATE, STAR_STATE, CHAR_STATE, NONE_STATE},
		{D_QUOTE_STATE, D_QUOTE_STATE, D_QUOTE_STATE, D_QUOTE_STATE, BACKSLASH_D_QUOTE_STATE, D_QUOTE_STATE, D_QUOTE_STATE, D_QUOTE_STATE, END_D_QUOTE_STATE, D_QUOTE_STATE, D_QUOTE_STATE, D_QUOTE_STATE, D_QUOTE_STATE, NONE_STATE},
		{S_QUOTE_STATE, S_QUOTE_STATE, S_QUOTE_STATE, S_QUOTE_STATE, S_QUOTE_STATE, S_QUOTE_STATE, S_QUOTE_STATE, S_QUOTE_STATE, S_QUOTE_STATE, END_S_QUOTE_STATE, S_QUOTE_STATE, S_QUOTE_STATE, S_QUOTE_STATE, NONE_STATE},
		{CHAR_STATE, NUMBER_STATE, STAR_STATE, CHAR_STATE, BACKSLASH_STATE, CHAR_STATE, STAR_STATE, STAR_STATE, D_QUOTE_STATE, S_QUOTE_STATE, STAR_STATE, STAR_STATE, CHAR_STATE, NONE_STATE},
		{CHAR_STATE, NUMBER_STATE, STAR_STATE, CHAR_STATE, BACKSLASH_STATE, CHAR_STATE, STAR_STATE, STAR_STATE, D_QUOTE_STATE, S_QUOTE_STATE, STAR_STATE, STAR_STATE, CHAR_STATE, NONE_STATE},
		{D_QUOTE_STATE, D_QUOTE_STATE, D_QUOTE_STATE, D_QUOTE_STATE, D_QUOTE_STATE, D_QUOTE_STATE, D_QUOTE_STATE, D_QUOTE_STATE, D_QUOTE_STATE, D_QUOTE_STATE, D_QUOTE_STATE, D_QUOTE_STATE, D_QUOTE_STATE, NONE_STATE},
		{STAR_STATE, STAR_STATE, STAR_STATE, STAR_STATE, STAR_STATE, STAR_STATE, NONE_STATE, NONE_STATE, STAR_STATE, STAR_STATE, DOUBLE_LEFT_REDIRECTION_STATE, NONE_STATE, LEFT_AGGREGATION_V_STATE, NONE_STATE},
		{STAR_STATE, STAR_STATE, STAR_STATE, STAR_STATE, STAR_STATE, STAR_STATE, NONE_STATE, NONE_STATE, STAR_STATE, STAR_STATE, NONE_STATE, DOUBLE_RIGHT_REDIRECTION_STATE, RIGHT_AGGREGATION_V_STATE, NONE_STATE},
		{STAR_STATE, STAR_STATE, STAR_STATE, STAR_STATE, STAR_STATE, STAR_STATE, NONE_STATE, NONE_STATE, STAR_STATE, STAR_STATE, NONE_STATE, NONE_STATE, NONE_STATE, NONE_STATE},
		{STAR_STATE, STAR_STATE, STAR_STATE, STAR_STATE, STAR_STATE, STAR_STATE, NONE_STATE, NONE_STATE, STAR_STATE, STAR_STATE, NONE_STATE, NONE_STATE, NONE_STATE, NONE_STATE}
	};
	int current_state;
	int next_state;
	t_list	*token;
	t_token	*token_struct;
	int i;

	// On selectionne l'etat de depart
	current_state = START_STATE;
	// Clean la stack
	ft_bzero((void *)&stack, 512);
	// Boucle sur chaque charactere de la string
	i = -1;
	while (line[++i])
	{
		// Determine le prochain etat grace a l'automate
		next_state = A[current_state][get_index_from_char(line, i)];
		// Push dans la stack
		if (!is_ignored(current_state, next_state))
			put_char_in_stack(&stack, line[i]);
		// Si c'est un etat d'erreur -> Syntax error
		if (next_state == NONE_STATE)
		{
			ft_printf("Syntax error near character %c at position %d\n", line[i], i + 1);
			// Quitter proprement
			exit(0);
		}
		// Si c'est un etat accepteur
		else if (is_acceptor(next_state))
		{
			// Si c'est un etat etoile
			if (is_star(next_state))
			{
				// Retire le dernier caractere de la stack
				stack[ft_strlen(stack) - 1] = 0;
				// Recule d'un caractere dans la string
				i--;
			}
			// Creer un token avec la stack
			create_token_struct(stack, current_state, &token_struct);
			// Creer un maillon de liste avec ce token
			token = ft_lstnew(&token_struct, sizeof(t_token));
			// Ajoute a la liste des tokens
			if ((*tokens_list) == NULL)
				(*tokens_list) = token;
			else
				ft_lstaddend(tokens_list, token);
			// Nettoie la stack
			ft_strclr(stack);
			// On retourne sur l'etat de depart
			current_state = START_STATE;
			// Reprends la boucle au debut
			continue ;
		} // Fin de l'etat accepteur on a eu un token et on continue
		// L'etat courant devient le suivant
		current_state = next_state;
	} // Fin de la boucle
	// if (is_not_terminal(current_state))
	// {
	// 	ft_printf("Syntax error on token \"%s\" : not terminated\n", stack);
	// 	exit(0);
	// }
	// Si le dernier etat etait un nombre ou un caractere on doit prendre le dernier token
	if (if_take_the_last(current_state))
	{
		// Creer un token avec la stack
		create_token_struct(stack, current_state, &token_struct);
		// Creer un maillon de liste avec ce token
		token = ft_lstnew(&token_struct, sizeof(t_token));
		// Ajoute a la liste des tokens
		if ((*tokens_list) == NULL)
			(*tokens_list) = token;
		else
			ft_lstaddend(tokens_list, token);
	}
	if (!first_check_tokens_list(*tokens_list))
		exit(0);
	// create_token_struct(NULL, current_state, &token_struct);
	// token = ft_lstnew(&token_struct, sizeof(t_token));
	// ft_lstaddend(tokens_list, token);
}
