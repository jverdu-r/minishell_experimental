/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 10:00:46 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/10/10 10:00:52 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char    **arg_count(t_lexer *list)
{
    t_lexer *aux;
    int     i;
    char    **args;

    aux = list;
    i = 0;
    while (aux && aux->token < 1)
    {
        i++;
        aux = aux->next;
    }
    args = malloc(sizeof(char *) * i);
    args[i] = 0;
    return (args);
}

void    cmd_add(t_command *cmd, t_lexer **list, int rd)
{
    int i;
    t_lexer *aux;
    char    *str_aux;

    i = 0;
    aux = *list;
    if (rd == 2)
    {
        cmd->cmd = ft_strdup(aux->str);
        aux = aux->next;
        if (aux && aux->str)
        {
            cmd->args = arg_count(aux);
            while (aux && aux->token == 0 && aux->str)
            {
                cmd->args[i] = ft_strdup(aux->str);
                i++;
                aux = aux->next;
            }
        }
    }
    if (rd == 1)
    {
        str_aux = aux->str;
        aux = aux->next;
        cmd->cmd = ft_strdup(aux->str);
        aux = aux->next;
        if (aux && aux->str)
        {
            aux = aux->next;
            cmd->args = arg_count(aux);
            while (aux && aux->token == 0 && aux->str)
            {
                cmd->args[i] = str_aux;
                i++;
                aux = aux->next;
            }
        }
        else
        {
            cmd->args = malloc(sizeof(char *) * 2);
            cmd->args[0] = ft_strdup(str_aux);
            cmd->args[1] = 0;
        }
    }
    else if (rd == 0)
    {
        cmd->cmd = ft_strdup(aux->str);
        aux = aux->next;
        cmd->args = arg_count(aux);
        while (aux && aux->token == 0 && aux->str)
        {
            cmd->args[i] = ft_strdup(aux->str);
            i++;
            aux = aux->next;
        }
    }
}

t_command   *cmd_extract(t_lexer *list)
{
    t_command   *cmd;
    //t_pipeline  *pipe;
    int         i;

    i = 0;
    //pipe = init_pipe(init_cmd());
    //cmd = pipe->cmd;
    cmd = init_cmd();
    while (list)
    {
        if (list->token == PIPE)
        {
            break;
            /*pipe_addback(&pipe, init_pipe(init_cmd()));
            pipe = pipe->next;
            cmd = pipe->cmd;*/
        }
        else if (list->token > 1 && list->token != LESS_LESS && !cmd->prev)
        {
            cmd->redir = list->token;
            list = list->next;
            comm_addback(&cmd, init_cmd());
            cmd = cmd->next;
            cmd_add(cmd, &list, 1);
        }
        else if (list->token > 1 && list->token != LESS_LESS && cmd->prev)
        {
            cmd->redir = list->token;
            list = list->next;
            comm_addback(&cmd, init_cmd());
            cmd = cmd->next;
            cmd_add(cmd, &list, 2);
            
        }
        else if (list->token == LESS_LESS)
        {
            cmd->redir = list->token;
            list = list->next;
            cmd->limiter = ft_strdup(list->str);
            comm_addback(&cmd, init_cmd());
            cmd = cmd->next;  
        }
        else
        {  
            cmd_add(cmd, &list, 0);
            comm_addback(&cmd, init_cmd());
            cmd = cmd->next;
        }
        while (list && list->token < 1)
            list = list->next;
    }
    while (cmd->prev)
        cmd = cmd->prev;
    if (cmd->prev)
        cmd = cmd->prev;
    cmd_show(cmd->prev);
    //pipe_show(pipe);
    return (cmd);
}

