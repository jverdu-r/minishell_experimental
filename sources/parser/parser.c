/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_in_progress_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 18:38:55 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/10/23 18:38:57 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_command   *cmd_list(t_lexer *list)
{
    t_command *cmd;
    t_lexer   *aux;

    cmd = NULL;
    aux = list;
    while (aux)
    {
        if (aux->prev == NULL || aux->prev->token == PIPE)
            comm_addback(&cmd, init_cmd());
        aux = aux->next;
    }
    printf("command created\n");
    while (cmd->prev != NULL)
        cmd = cmd->prev;
    printf("command rewind\n");
    return (cmd);
}

t_lexer *redir_add(t_command *cmd, t_lexer *list)
{
    if (list->token == LESS)
        redir_addback(&cmd->in_files, redir_new(ft_strdup(list->next->str)));
    if (list->token == GREAT)
        redir_addback(&cmd->out_files, redir_new(ft_strdup(list->next->str)));
    if (list->token == LESS_LESS)
    {
        cmd->limiter = ft_strdup(list->next->str);
        cmd->heredoc = 1;
    }
    if (list->token == GREAT_GREAT)
        cmd->append = ft_strdup(list->next->str);
    list = list->next;
    return (list);
}

char    **get_args(t_lexer *list)
{
    t_lexer *aux;
    int     i;
    char    **args;

    aux = list;
    i = 0;
    while(aux)
    {
        aux = aux->next;
        i++;
    }
    aux = list;
    args = malloc(sizeof(char *) * i);
    if (!args)
        return (NULL);
    while(list)
    {
        args[i++] = ft_strdup(list->str);
        list = list->next;
    }
    args[i] = 0;
    lexer_free(aux);
    return (args);
}

t_command *parser(t_toolbox *tools)
{
    t_lexer     *aux;
    t_command   *cmd;
    t_lexer     *args;

    aux = tools->lexer_list;
    cmd = cmd_list(aux);
    args = NULL;
    while (aux)
    {
        if (aux->token == PIPE)
            cmd = cmd->next;
        else if (aux->token > 1)
            aux = redir_add(cmd, aux);
        else if (!cmd->cmd && !aux->token)
            cmd->cmd = ft_strdup(aux->str);
        else
            lexer_addback(&args, lexer_new(ft_strdup(aux->str), 0));
        aux = aux->next;
    }
    cmd->args = get_args(args);
    return (cmd);
}