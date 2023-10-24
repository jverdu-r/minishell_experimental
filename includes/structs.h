/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 10:25:27 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/10/17 10:25:30 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct	s_exp
{
	char	*str;
	int		exp;
	struct s_exp *next;
	struct s_exp *prev;
}	t_exp;
typedef enum	s_token
{
	PIPE = 1,
	LESS,
	LESS_LESS,
	GREAT,
	GREAT_GREAT
}	t_token;

typedef struct  s_redir
{
    char    *file;
    struct s_redir   *next;
    struct s_redir   *prev;
}   t_redir;

typedef struct s_command
{
    char                *cmd;
	char				*append;
	int					heredoc;
    char                *limiter;
    char                **args;
	int					out_fd;
	int					in_fd;
    t_redir             *in_files;
	t_redir				*out_files;

    struct s_command    *next;
    struct s_command    *prev;
}   t_command;

typedef struct s_pipeline
{
    t_command           *cmd;
    struct s_pipeline   *next;
    struct s_pipeline   *prev;
}   t_pipeline;

typedef enum	s_bool
{
	FALSE = 0,
	TRUE = 1
}	t_bool;

typedef struct	s_lexer
{
	char			*str;
	t_token			token;
	int				index;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;

typedef struct	s_sp_cmds
{
	char				**cmd;
	int					token;
	char				*file;
	struct s_sp_cmds	*next;
	struct s_sp_cmds	*prev;
}	t_sp_cmds;

typedef struct	s_toolbox
{
	char		*args;
	char		**env;
	char		**sort_env;
	char		*env_rute;
	char		*pwd;
	char		*old_pwd;
	t_sp_cmds	*sp_cmds;
	t_lexer		*lexer_list;
}	t_toolbox;

typedef struct	s_p_toolbox
{
	t_lexer		*lexer_list;
	t_lexer		*redirections;
	int			num_redirections;
	t_toolbox	*tools;
}	t_p_toolbox;

#endif