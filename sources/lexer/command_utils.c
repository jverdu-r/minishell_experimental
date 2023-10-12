/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 12:48:17 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/10/12 12:48:22 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_command   *init_cmd(void)
{
    t_command   *cmd;

    cmd = malloc(sizeof(t_command));
    cmd->redir = 0;
    cmd->cmd = NULL;
    cmd->limiter = NULL;
    cmd->args = NULL;
    cmd->exp = 0;
    cmd->file = NULL;
    cmd->next = NULL;
    cmd->prev = NULL;
    return (cmd);
}

void    comm_addback(t_command **head, t_command *new)
{
    t_command *aux;

    aux = *head;
    if (*head == NULL)
        *head = NULL;
    else
    {
        while (aux->next)
            aux = aux->next;
        aux->next = new;
        new->prev = aux;
    }
}

void    cmd_free(t_command *cmd)
{
    while (cmd->next)
    {
        if (cmd->cmd)
            free(cmd->cmd);
        if (cmd->args)
            free_arr(cmd->args);
        if (cmd->limiter)
            free(cmd->limiter);
        if (cmd->file)
            free(cmd->file);
        cmd = cmd->next;
        free(cmd->prev);
        cmd->prev = NULL;
    }
    if (!cmd->next)
    {
        if (cmd->cmd)
            free(cmd->cmd);
        if (cmd->args)
            free_arr(cmd->args);
        if (cmd->limiter)
            free(cmd->limiter);
        if (cmd->file)
            free(cmd->file);
    }
    free (cmd);
}

void    cmd_show(t_command *cmd)
{
    int i;
    t_command *aux;

    i = 0;
    aux = cmd;
    while (aux)
    {
        printf("---command---\n\n");
        if (aux->cmd)
            printf("command: %s\n", aux->cmd);
        if (aux->args)
        {
            i = 0;
            while(aux->args[i])
            {
                printf("arg [%d]: %s\n", i, aux->args[i]);
                i++;
            }
        }
        if (aux->redir)
        {
            if (aux->redir == LESS_LESS)
            {
                printf("heredoc\n");
                printf("limiter: %s\n", aux->limiter);
            }
            else
                printf("redir: %d\n", aux->redir);
        }
        printf("\n---end command---\n\n");
        aux = aux->next; 
    }
}

//pipeline functions

void    pipe_addback(t_pipeline **head, t_pipeline *new)
{
    t_pipeline *aux;

    aux = *head;
    if (*head == NULL)
        *head = NULL;
    else
    {
        while (aux->next)
            aux = aux->next;
        aux->next = new;
        new->prev = aux;
    }
}

t_pipeline  *init_pipe(t_command *cmd)
{
    t_pipeline  *new;

    new = malloc(sizeof(t_pipeline));
    new->cmd = cmd;
    new->next = NULL;
    new->prev = NULL;
    return (new);
}

void    pipe_show(t_pipeline *pipe)
{
    t_pipeline  *aux;
    int         i;

    aux = pipe;
    i = 0;
    while (aux)
    {
        printf("---pipe node %d---\n\n", i);
        if (aux->cmd)
            cmd_show(aux->cmd);
        printf("---end of pipe node %d---\n\n", i);
        i++;
        aux = aux->next;
    }
}