/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 12:48:17 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/10/17 12:10:59 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_command	*init_cmd(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	cmd->cmd = NULL;
	cmd->heredoc = 0;
	cmd->append = NULL;
	cmd->limiter = NULL;
	cmd->args = NULL;
	cmd->in_fd = 0;
	cmd->in_files = NULL;
	cmd->out_fd = 0;
	cmd->out_files = NULL;
	cmd->next = NULL;
	cmd->prev = NULL;
	return (cmd);
}

void	comm_addback(t_command **head, t_command *new)
{
	t_command	*aux;

	aux = *head;
	if (*head == NULL)
		*head = new;
	else
	{
		while (aux->next)
			aux = aux->next;
		aux->next = new;
		new->prev = aux;
	}
}

void	cmd_free(t_command *cmd) //need a rework
{
	while (cmd->next)
	{
		if (cmd->cmd)
			free(cmd->cmd);
		if (cmd->args)
			free_arr(cmd->args);
		if (cmd->limiter)
			free(cmd->limiter);
		/*if (cmd->file)
		 	free(cmd->file);*/
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
		/*if (cmd->file)
			free(cmd->file);*/
	}
	free (cmd);
}

