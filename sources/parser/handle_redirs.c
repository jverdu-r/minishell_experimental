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
void    get_fds(t_command *cmd)
{
    t_redir     *in_files;
    t_redir     *out_files;

    while (cmd)
    {
        if (cmd->in_files)
        {
            in_files = cmd->in_files;
            while (in_files)
            {
                if (access(in_files->file, R_OK) == -1)
                {
                    if (errno == EACCES)
                        error_msg("Access denied\n");
                    else if (errno == ENOENT)
                        error_msg("File does not exist\n");
                    else
                        error_msg("Access error\n");
                }
                in_files = in_files->next;
            }
        }
        if (cmd->out_files)
        {
            out_files = cmd->out_files;
            while (out_files)
            {
                cmd->out_fd = open(out_files->file, O_CREAT | O_WRONLY | O_TRUNC);
                close(cmd->out_fd);
                out_files = out_files->next;
            }

        }
        if (cmd->next)
            cmd = cmd->next;
        else
            break;
    }
}