/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:18:47 by mbrousse          #+#    #+#             */
/*   Updated: 2024/03/23 13:17:13 by mbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/incs/libft.h"
# include "colors.h"
# include <signal.h>

# include <stdio.h>
# include <dirent.h>
# include <limits.h>
# include <errno.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>

# define EM_MALLOC "\033[0;31mError:\n\t\033[0mmalloc failed\n"
# define EM_FORK "\033[0;31mError:\n\t\033[0mfork failed\n"
# define EM_PIPE "\033[0;31mError:\n\t\033[0mpipe failed\n"
# define EM_EXECVE "\033[0;31mError:\n\t\033[0mexecve failed\n"
# define EM_OPEN "\033[0;31mError:\n\t\033[0mopen failed\n"
# define EM_CLOSE "\033[0;31mError:\n\t\033[0mclose failed\n"
# define EM_DUP2 "\033[0;31mError:\n\t\033[0mdup2 failed\n"
# define EM_WAIT "\033[0;31mError:\n\t\033[0mwait failed\n"
# define EM_SIGNAL "\033[0;31mError:\n\t\033[0msignal failed\n"
# define EM_ARGS "\033[0;31mError:\n\t\033[0mtoo much arguments\n"

extern int	g_error;	

typedef enum e_ERROR
{
	ERROR_MALLOC = 0,
	ERROR_GERROR = 1,
	ERROR_EXEC = 126,
	ERROR_COM = 127,
	ERROR_COTE = 128
}				t_ERROR;

typedef enum e_type
{
	CMD,
	STRING,
	REDIR_R,
	REDIR_L,
	REDIR_RR,
	POINT_VIRGULE,
	PIPE,
	FILE_NAME,
	SIMPLE_COTE,
	DOUBLE_COTE
}	t_type;

typedef struct s_token
{
	char				*value;
	t_type				type;
	int					pos;
	int					exec;
	struct s_token		*next;
}	t_token;

typedef struct s_env
{
	char				*name;
	char				*value;
	struct s_env		*next;
}	t_env;

typedef struct s_data
{
	int			exit;
	char		*line;
	char		*prompt;
	char		**path;
	t_token		*token;
	char		*error_cmd;
	t_env		*env;
}	t_data;

// main.c
void		ft_putheader(void);
// error.c
void		ft_put_error(t_ERROR error, char *MSG);
void		ft_megafree(t_data *data);
void		destroy(t_data *data);
void		exit_error(t_ERROR error, char *MSG, t_data *data);
// parsing_env.c
int			ft_parsing_env(char **env, t_data *data);
int			ft_set_tab(t_data *data);
int			ft_init_tab(t_data *data, char **env);
// t_env.c
size_t		ft_envsize(t_env *env);
t_env		*ft_envnew(char *name, char *value);
void		ft_envadd_back(t_env **env, t_env *new);
void		ft_envclear(t_env **env);
t_env		*ft_envfind(t_env *env, char *name);
void		ft_envprint(t_env *env);
// t_token.c
size_t		lt_size(t_token *token);
size_t		lt_size_type(t_token *token, t_type type);
t_token		*lt_new(char *value, t_type type);
void		lt_addback(t_token **token, t_token *new);
void		lt_clear(t_token **token);
void		lt_print(t_token *token);
// main_loop.c
int			ft_main_loop(t_data *data);
// signal.c
void		ft_handle_sig(int sig);
void		ft_set_signal(void);
// parsing_line.c
int			ft_parsing_line(t_data *data, char *line);
// parsing_line_utils.c
int			puttype(char *line, size_t *i, t_data *data);
int			putword(char *line, size_t *i, t_data *data);

#endif