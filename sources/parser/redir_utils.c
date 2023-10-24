/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 09:43:17 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/10/17 09:43:19 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_redir *redir_new(char *str)
{
    t_redir *new;

    new = malloc(sizeof(t_redir));
    if (!new)
        return (NULL);
    new->file = ft_strdup(str);
    new->next = NULL;
    new->prev = NULL;
    return (new);
}

void    redir_addback(t_redir **head, t_redir *new)
{
    t_redir *aux;

    aux = *head;
    if (*head == NULL)
        *head = new;
    else
    {
        while (aux->next)
            aux = aux->next;
        aux->next = new;
        new->prev = aux;
    }
}

void    redir_show(t_redir *list, char *str)
{
    while (list)
    {
        printf("%s: %s\n", str, list->file);
        list = list->next;
    }
}