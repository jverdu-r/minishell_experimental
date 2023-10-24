/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:59:56 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/10/24 17:59:58 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
#define EXPANDER_H

#include "libft/libft.h"
#include "structs.h"
#include "minishell.h"

void    *expander(t_command *cmd, t_toolbox *tools);
t_exp   *exp_new(char *raw, char exp);
void    exp_lst_addback(t_exp **head, t_exp *new);
#endif