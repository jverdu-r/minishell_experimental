/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 10:53:31 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/09/20 10:18:22 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*fully_prompt(char *input, char c)
{
	char	*aux;
	char	*pipe;

	if (c == '|')
		while (input[ft_strlen(input) - 1] == '|')
		{
			aux = readline(">");
			pipe = input;
			input = ft_strjoin(pipe, aux);
			free(pipe);
			free(aux);
		}
	return (input);
}

t_bool	switch_bool(t_bool bool)
{
	if (bool == FALSE)
		bool = TRUE;
	else
		bool = FALSE;
	return (bool);
}
