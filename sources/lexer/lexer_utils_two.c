/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 14:28:22 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/08/09 08:52:19 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	lexer_length(t_lexer *list)
{
	int			i;
	t_lexer	*aux;

	if (!list)
		return (0);
	aux = list;
	i = 0;
	while (aux)
	{
		aux = aux->next;
		i++;
	}
	return (i);
}

void	lexer_free(t_lexer *list)
{
	int	i;

	i = 0;
	if (list)
	{
		while (list->next)
		{
			if (list->token == 0)
				free(list->str);
			list = list->next;
			free(list->prev);
		}
		if (!list->next)
		{
			if (list->token == 0)
				free(list->str);

		}
		free(list);
	}
}

void	lexer_show(t_lexer *list) //only for testing
{
	t_lexer	*tmp;

	tmp = list;
	printf("\n");
	while (tmp)
	{
		if (tmp->str)
			printf("%s\n", tmp->str);
		if (tmp->token)
			printf("%d\n", tmp->token);
		tmp = tmp->next;
	}
	printf("\n");
}
