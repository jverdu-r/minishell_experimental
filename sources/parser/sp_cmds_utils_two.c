/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sp_cmds_utils_two.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 13:52:34 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/09/20 10:56:56 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	sp_cmds_length(t_sp_cmds *list)
{
	int			i;
	t_sp_cmds	*aux;

	if (!list)
		return (0);
	aux = list;
	i = 0;
	while (aux)
	{
		aux = aux->next;
		i++;
	}
	return (i);
}

void	sp_cmds_free(t_sp_cmds *list)
{
	int	i;

	i = 0;
	if (list)
	{
		while (list->next)
		{
			if (list->cmd)
				free_arr(list->cmd);
			if (list->file)
				free(list->file);
			list = list->next;
			free(list->prev);
		}
		if (!list->next)
		{
			if (list->file)
				free(list->file);
			if (list->cmd)
				free_arr(list->cmd);
		}
		free(list);
	}
}

void	sp_cmds_show(t_sp_cmds *list)
{
	int	i;
	int	a;

	a = 0;
	while (list)
	{
		printf("\n----node %d--\n", a);
		if (list->file)
			printf("----file----\n%s\n", list->file);
		if (list->cmd)
		{
			i = 0;
			printf("----cmd-----\n");
			while (list->cmd[i])
			{
				printf("%s\n", list->cmd[i]);
				i++;
			}
		}
		if (list->token > 0)
			printf("----token---\n%d\n", list->token);
		a++;
		list = list->next;
	}
}


