/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daparici <daparici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 09:25:35 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/09/20 11:16:52 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_p_toolbox	init_p_tools(t_toolbox *tools)
{
	t_p_toolbox	p_tools;

	p_tools.lexer_list = tools->lexer_list;
	p_tools.redirections = NULL;
	p_tools.redirections = 0;
	p_tools.tools = tools;
	return (p_tools);
}

int	word_count(t_lexer *list)
{
	int	i;

	if (!list)
		return (0);
	i = 0;
	while (list && list->token == 0)
	{
		i++;
		list = list->next;
	}
	return (i);
}

char	**get_cmd(t_lexer *list)
{
	int		w_count;
	char	**cmd;
	int		i;

	if (list == NULL)
		return (NULL);
	w_count = word_count(list);
	cmd = ft_calloc(w_count + 1, sizeof(char *));
	if (!cmd)
		return (NULL);
	i = 0;
	while (list && list->token == 0)
	{
		cmd[i] = ft_strdup(list->str);
		i++;
		list = list->next;
	}
	cmd[i] = NULL;
	return (cmd);
}

t_sp_cmds	*cmds_extract(t_lexer *list)
{
	t_sp_cmds	*node;
	char		**cmd;
	t_lexer		*aux;
	int			tk;

	if (!list)
		return (NULL);
	aux = list;
	node = NULL;
	while (aux)
	{
		tk = 0;
		if (aux->token == 0)
		{
			cmd = get_cmd(aux);
			while (aux && aux->token == 0)
				aux = aux->next;
		}
		if (aux && aux->token > 0)
			sp_cmds_addback(&node, sp_cmds_new(cmd, aux->token));
		if (aux)
			aux = aux->next;
	}
	sp_cmds_addback(&node, sp_cmds_new(cmd, tk));
	return (node);
}

t_sp_cmds	*parser(t_toolbox *tools)
{
	t_sp_cmds	*node;
	t_p_toolbox	p_tools;

	// if (tools->lexer_list->token == PIPE)
	// 	return (error_token(tools->lexer_list->token));
	node = NULL;
	p_tools = init_p_tools(tools);
	node = cmds_extract(p_tools.lexer_list);
	check_exp(node, tools);
	cmd_trim(node);
	sp_cmds_show(node);
	sp_cmds_free(node);
	return (node);
}
