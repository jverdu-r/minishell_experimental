/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 19:22:42 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/10/25 19:22:44 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*char    *fill_err(t_command *cmd, char *str)
{
    char *aux;
    char *str;

    str = ft_strjoin(cmd->cmd, ":");
    aux = ft_strjoin(str, ' ');
    str = ft_strjoin(aux, str);
    if (i == 0)
        return (aux = ft_strjoin(str, ": No such file or directory"));
    else
        return (aux = ft_strjoin(str, ": Permission denied"));

}*/
void    get_fds(t_command *raw_cmd)
{
    t_command   *cmd;
    t_redir     *aux;
    
    cmd = raw_cmd;
    while (cmd->next)
    {
        if (cmd->out_files->file)
        {
            aux = cmd->out_files;
            while (aux)
            {
                cmd->out_fd = open(aux->file, O_CREAT | O_WRONLY | O_TRUNC);
                close(cmd->in_fd);
                aux = aux->next;
                printf("hola capullin\n");
            }
        }
        if (cmd->in_files)
        {
            aux = cmd->in_files;
            while (aux)
            {
                if (access(aux->file, R_OK) == -1)
                {
                    if (errno == EACCES)
                        error_msg("Access denied");
                    else if (errno == ENOENT)
                        error_msg("File does not exist");
                    else
                        error_msg("Access error");
                }
                aux = aux->next;
            }
        }
        cmd = cmd->next;
    }
}