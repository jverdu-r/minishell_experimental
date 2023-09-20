/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 19:40:51 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/07/25 09:03:39 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

int	token_handler(t_toolbox *tools, int i)
{
	t_token tk;

	tk = check_token(tools->args, i);
	if (tk == LESS_LESS || tk == GREAT_GREAT)
	{
		lexer_addback(&tools->lexer_list, lexer_new(NULL, tk));
		return (2);
	}
	if (tk == PIPE || tk == LESS || tk == GREAT)
	{
		lexer_addback(&tools->lexer_list, lexer_new("", tk));
		return (1);
	}
	return (0);
}


