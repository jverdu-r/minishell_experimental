/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redistribution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 18:59:55 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/12/12 18:59:56 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int arr_len(char **arr)
{
    int i;

    i = 0;
    if (!arr)
        return(i);
    while (arr[i])
        i++;
    return (i);
}

void    exchange(t_command *cmd, char **arr, int len)
{
    char    **aux;
    char    *n_cmd;
    int     i;
    int     j;

    aux = ft_calloc(sizeof(char *), len);
    n_cmd = ft_strdup(arr[0]);
    i = 0;
    j = 0;
    while(arr[i + 1])
    {
        aux[i] = ft_strdup(arr[i + 1]);
        i++;
    }
    if (cmd->args)
    {
        while (cmd->args[j])
        {
            aux[i] = cmd->args[j];
            i++;
            j++;
        }
        free_arr(cmd->args);
    }
    free_arr(arr);
    free(cmd->cmd);
    cmd->cmd = n_cmd;
    cmd->args = aux;
}
int space_search(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (is_white_space(str[i]))
            return (1);
        i++;
    }
    return (0);
}
void    redis(t_command *r_cmd)
{
    
    t_command *cmd;
    char    **aux;
    int     t_len;

    cmd = r_cmd;
    while (cmd)
    {
        if (space_search(cmd->cmd))
        {
            aux = ft_split(cmd->cmd, ' ');
            t_len = arr_len(aux) + arr_len(cmd->args) + 1;
            exchange(cmd, aux, t_len);
        }
        cmd = cmd->next;
    }
}