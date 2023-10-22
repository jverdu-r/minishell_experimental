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
#include "structs.h"

t_token	check_token(char *tk, int i);

t_command   *init_cmd(void);
void    comm_addback(t_command **head, t_command *new);
void    cmd_show(t_command *cmd);
void    cmd_free(t_command *cmd);

t_pipeline  *init_pipe(void);
void    pipe_addback(t_pipeline **head, t_pipeline *new);
void    pipe_show(t_pipeline *pipe);

//for parse.h
t_pipeline  *behavior(t_token tk, t_pipeline *pipe, t_lexer *list);

#endif