/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_reader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:46:24 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/10/07 17:40:35 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_white_space(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' ||
			c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

t_token	check_token(char *tk, int i)
{
	if (tk[i] == '|')
		return (PIPE);
	if (tk[i] == '<')
	{
		if (tk[i + 1] == '<')
			return (LESS_LESS);
		else
			return (LESS);
	}
	if (tk[i] == '>')
	{
		if (tk[i + 1] == '>')
			return (GREAT_GREAT);
		else
			return (GREAT);
	}
	return (0);
}

t_bool switch_bool(t_bool bool)
{
	if (bool == FALSE)
		bool = TRUE;
	else
		bool = FALSE;
	return (bool);
}

int	*token_add(char *args, t_lexer **list, int *st_nd)
{
	if (st_nd[0] != st_nd[1])
	{
		lexer_addback(list, lexer_new(ft_substr(args, st_nd[0], st_nd[1] - st_nd[0]), 0));
				st_nd[0] = st_nd[1];
	}
	lexer_addback(list, lexer_new(NULL, check_token(args, st_nd[1])));
	if (check_token(args, st_nd[1]) == LESS_LESS || check_token(args, st_nd[1]) == GREAT_GREAT)
		st_nd[0] = st_nd[1] + 2, st_nd[1] += 2;
	else
	st_nd[0] = st_nd[1] + 1, st_nd[1]++;
	return (st_nd);
}

void	read_words(char *args, t_lexer **list, t_bool *qt, int *st_nd)
{
	while(args[st_nd[1]])
	{
		if (args[st_nd[1]] == '\'' && !qt[1])
			qt[0] = switch_bool(qt[0]);
		else if (args[st_nd[1]] == '\"' && !qt[0])
			qt[1] = switch_bool(qt[1]);
		else if (check_token(args, st_nd[1]) && !qt[0] && !qt[1])
			st_nd = token_add(args, list, st_nd);
 		else if (is_white_space(args[st_nd[1]]) && !qt[0] && !qt[1])
		{
			if (st_nd[0] != st_nd[1])
				lexer_addback(list, lexer_new(ft_substr(args, st_nd[0], st_nd[1] - st_nd[0]), 0));
			st_nd[0] = st_nd[1] + 1;
		}
		if (qt[1] && args[st_nd[1]] == '\\' && args[st_nd[1] + 1])
			st_nd[1]++;
		st_nd[1]++;
	}
	if (st_nd[0] != st_nd[1])
		lexer_addback(list, lexer_new(ft_substr(args, st_nd[0], st_nd[1] - st_nd[0]), 0));
}
int	token_reader(t_toolbox *tools)
{
	t_bool	qt[2];
	int	st_nd[2];

	qt[0] = FALSE;
	qt[1] = FALSE;
	st_nd[0] = 0;
	st_nd[1] = 0;
	read_words(tools->args, &tools->lexer_list, qt, st_nd);
	return (1);
}
