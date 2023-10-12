/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 09:45:51 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/10/10 09:45:55 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
#define TOKENS_H

#include "minishell.h"

typedef enum	s_token
{
	PIPE = 1,
	LESS,
	LESS_LESS,
	GREAT,
	GREAT_GREAT
}	t_token;

typedef struct s_command
{
    char                *cmd;
    t_token             redir;
    char                *limiter;
    char                **args;
    int                 exp;
    char                *file;
    struct s_command    *next;
    struct s_command    *prev;
}   t_command;

typedef struct s_pipeline
{
    t_command           *cmd;
    struct s_pipeline   *next;
    struct s_pipeline   *prev;
}   t_pipeline;

t_command   *init_cmd(void);
void    comm_addback(t_command **head, t_command *new);
void    cmd_show(t_command *cmd);
void    cmd_free(t_command *cmd);

t_pipeline  *init_pipe(t_command *cmd);
void    pipe_addback(t_pipeline **head, t_pipeline *new);
void    pipe_show(t_pipeline *pipe);
#endif