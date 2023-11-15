/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_reader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:46:24 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/10/17 11:53:45 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_white_space(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' \
			|| c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

int	*token_add(char *args, t_lexer **list, int *st_nd)
{
	lexer_addback(list, lexer_new(NULL, check_token(args, st_nd[1])));
	if (check_token(args, st_nd[1]) == LESS_LESS \
			|| check_token(args, st_nd[1]) == GREAT_GREAT)
	{
		st_nd[0] = st_nd[1] + 2;
		st_nd[1] += 1;
	}
	else
	{
		
		st_nd[0] = st_nd[1] + 1;
		st_nd[1]++;
	}
	return (st_nd);
}

void	read_words(char *args, t_lexer **list, t_bool *qt, int *s_n)
{
	while (args[s_n[1]])
	{
		if (args[s_n[1]] == '\'' && !qt[1])
			qt[0] = switch_bool(qt[0]);
		else if (args[s_n[1]] == '\"' && !qt[0])
			qt[1] = switch_bool(qt[1]);
		else if (check_token(args, s_n[1]) && !qt[0] && !qt[1])
			s_n = token_add(args, list, s_n);
		else if (is_white_space(args[s_n[1]]) && !qt[0] && !qt[1])
		{	
			if (s_n[0] != s_n[1])
			{
				if (args[s_n[0]] == ' ')
					s_n[0]++;
				lexer_addback(list, \
						lexer_new(ft_substr(args, s_n[0], s_n[1] - s_n[0]), 0));
			}
			s_n[0] = s_n[1];
		}
		s_n[1]++;
	}
	if (args[s_n[0]] == ' ')
		s_n[0]++;
	if (s_n[0] != s_n[1])
		lexer_addback(list, \
				lexer_new(ft_substr(args, s_n[0], s_n[1] - s_n[0]), 0));
}

int	token_reader(t_toolbox *tools)
{
	t_bool	qt[2];
	int		st_nd[2];
	//t_command	*cmd;

	qt[0] = FALSE;
	qt[1] = FALSE;
	st_nd[0] = 0;
	st_nd[1] = 0;
	read_words(tools->args, &tools->lexer_list, qt, st_nd);
	//cmd = cmd_extract(tools->lexer_list);
	//cmd_show(cmd);
	//cmd_free(cmd);
	return (1);
}
