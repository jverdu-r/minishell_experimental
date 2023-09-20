/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 08:11:35 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/09/20 11:49:17 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	file_checker(char *str)
{
	int	i;

	if (str)
	{
		i = 0;
		while (str[i])
		{
			if (str[i] == '.' && (str[i + 1] == '/' || str[i + 1] == '.' ||
						str[i + 1] == '\0'))
				return (0);
			else if (str[i] == '.')
				return (1);
			i++;
		}
	}
	return (0);
}

void	exp_search(char **cmd, t_toolbox *tools)
{
	int	i;
	char	*aux;

	i = 0;
	aux = NULL;
	while (cmd[i])
	{
		if (cmd[i][0] == '\'' && cmd[i][1] == '$')
			aux = expander(tools, cmd[i]);
		else if (cmd[i][0] == '\"' && cmd[i][1] == '$')
			aux = expander(tools, cmd[i]);
		else if (cmd[i][0] == '$')
			aux = expander(tools, cmd[i]);
		if (aux != NULL)
		{
			free(cmd[i]);
			cmd[i] = ft_strdup(aux);
			free (aux);
			aux = NULL;
		}
		i++;
	}
}

void	check_exp(t_sp_cmds *node, t_toolbox *tools)
{
	t_sp_cmds	*aux_node;

	aux_node = node;
	while (aux_node)
	{
		if (aux_node->cmd != NULL)
			exp_search(aux_node->cmd, tools);
		aux_node = aux_node->next;	
	}
}

void	cmd_trim(t_sp_cmds *node)
{
	int		i;
	char	*aux;

	if (node->cmd)
	{
		i = 0;
		while (node->cmd[i])
		{
			if (check_quotes(node->cmd[i]) == 1)
			{
				aux = ft_substr(node->cmd[i], 1, ft_strlen(node->cmd[i]) - 2);
				free(node->cmd[i]);
				node->cmd[i] = aux;
			}
			if (check_quotes(aux) == 2)
			{
				aux = ft_substr(node->cmd[i], 1, ft_strlen(node->cmd[i]) - 2);
				free(node->cmd[i]);
				node->cmd[i] = aux;
			}
			i++;
		}
	}
}
