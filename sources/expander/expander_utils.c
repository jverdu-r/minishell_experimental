/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 18:54:39 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/10/24 18:54:42 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_exp   *exp_new(char *raw, char exp)
{
    t_exp   *new;

    new = malloc(sizeof(t_exp));
    new->str = raw;
    new->exp = exp;
    new->next = NULL;
    new->prev = NULL;
    return (new);
}

void    exp_lst_addback(t_exp **head, t_exp *new)
{
    t_exp	*tmp;

	tmp = *head;
	if (*head == NULL)
		*head = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
}