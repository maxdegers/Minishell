/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:18:47 by mbrousse          #+#    #+#             */
/*   Updated: 2024/05/18 21:03:15 by mbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/incs/libft.h"
# include "colors.h"

# include <signal.h>
# include <stdio.h>
# include <stdbool.h>
# include <dirent.h>
# include <limits.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>

///
# define ENV_VALID "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_"
///

///
# define WORD 0
# define PIPE 1
# define REDIR_IN 2
# define REDIR_OUT 3
# define REDIR_APPEND 4
# define REDIR_HEREDOC 5
# define OPERAT 6
///

///
# define S_QUOTE '\''
# define D_QUOTE '\"'
# define NONE '\0'
# define ESPACE ' '
# define TAB '\t'
///

/// PIPE
# define RD 0
# define WR 1
///

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
# define EM_ENV "\033[0;31mError:\n\t\033[0menv not found\n"

extern int	g_error;

typedef enum e_ERROR
{
	ERROR_MALLOC = 1,
	ERROR_PIPE = 1,
	ERROR_DUP = 1,
	ERROR_FORK = 1,
	ERROR_GERROR = 1,
	ERROR_SYNTAX = 2,
	ERROR_EXEC = 126,
	ERROR_COM = 127,
	ERROR_COTE = 128
}				t_ERROR;

typedef enum e_SIGNAL_MODE
{
	SIG_MAIN,
	SIG_CHILD
}	t_SIG_MODE;

typedef struct s_trash
{
	void			*data;
	struct s_trash	*next;
}	t_trash;

typedef struct s_redir
{
	int				fd;
	int				type;
	char			*file;
	int				is_in_cote;
	struct s_redir	*next;
}	t_redir;

typedef struct s_block
{
	char			*cmd;
	char			**args;
	t_redir			*redir;
	struct s_block	*next;
}	t_block;

typedef struct s_token
{
	char			*data;
	int				type;
	char			*new;
	int				is_expend;
	int				is_in_cote;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_env
{
	bool			show;
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_data
{
	int				exit;
	char			*line;
	char			*prompt;
	t_token			*token;
	t_block			*block;
	char			*error_cmd;
	t_env			*env;
}	t_data;

// main.c
void		ft_putheader(void);

// exec.c
int			ft_exec_line(t_data *data);
int			ft_is_builtin(t_block *block);
void		ft_exec_under_fork(t_block *block, t_data *data);

//pipes
int			ft_get_fd(int **fds, size_t i, int *res, size_t pipe_amount);
size_t		get_pipe_amount(t_block *block);
int			**ft_open_pipes(t_data *data, size_t pipe_amount);

//forks
int			*ft_fork(t_data *data, t_block *block, size_t childs, int **fds);
int			ft_wait_childs(int *pid, size_t child_amount);


//built-ins
void		ft_cd(t_block *block, t_data *data);
void		ft_echo(t_block *block);
void		ft_exit(t_data *data, t_block *block);

int			ft_export(t_data *data, t_block *block);
int			determine_export_type(const char *arg);
char		**ft_export_split(char *str, char *split);
void		ft_export_fork(t_data *data, t_block *block);
void		ft_put_env_exp(t_data *data);

void		ft_env(t_data *data);
void		ft_pwd(void);
int			ft_unset(t_block *block, t_data *data);

//closers
void		close2(int fd1, int fd2);
void		close3(int fd1, int fd2, int fd3);
void		close4(int fd1, int fd2, int fd3, int fd4);
void		ft_close_useless_fds(int **fds, int *used, size_t pipe_amount);
void		ft_close_heredoc_pipe(t_data *data);

//execve
void		ft_execve(t_data *data, t_block *block);

//redirections
char		*ft_redir(t_block *block, int *fd);

// error.c
void		ft_put_error(t_ERROR error, char *MSG);
void		ft_megafree(t_data *data);
void		destroy(t_data *data);
void		exit_error(t_ERROR error, char *MSG, t_data *data);
void		ft_free_int_tab(int **tab);

// parsing_env.c
int			ft_parsing_env(char **env, t_data *data);
int			ft_set_tab(t_data *data);
int			ft_init_tab(t_data *data, char **env);
char		**get_path(t_data *data);

// utils.c
int			ft_isblank(char c);
int			ft_iscontrol_operator(char c);

// t_env.c
size_t		ft_envsize(t_env *env);
t_env		*ft_envnew(char *name, char *value);
void		ft_envadd_back(t_env **env, t_env *new);
void		ft_envclear(t_env **env);
t_env		*ft_envfind(t_env *env, char *name);
char		*ft_envfind_data(t_env *env, char *name);
void		ft_envprint(t_env *env);
void		lt_remove(t_data *data, t_token *to_remouve);

// t_env_utils.c
int			ft_change_env(t_env *env, char *name, char *value);
char		**ft_env_to_tab(t_env *env);

// t_token_utils.c
char		**ft_tokento_tab(t_token *token);
void		ft_token_remouve(t_data *data, t_token *to_remouve);

// t_token.c
t_token		*ft_tokennew(char *line, size_t start, size_t end, int type);
void		ft_token_new_add(t_data *data, size_t start, size_t end, int type);
void		ft_tokenadd_back(t_token **token, t_token *new);
void		ft_token_clear(t_token **token);

// main_loop.c
int			ft_main_loop(t_data *data);

// signal.c
void		ft_handle_sig(int sig);
void		ft_set_signal(t_SIG_MODE mode);

// parsing_line.c
int			ft_parsing_line(t_data *data, char *line);

// parsing_line_utils.c
void		ft_add_to_str(char *str, size_t *i, char *add);
void		expansion2(t_token *token, size_t *i, size_t *j, t_data *data);
void		ft_param_expansion2(t_token *token, size_t size, t_data *data,
				char *new);

void		ft_block_print(t_block *block);
void		ft_set_block(t_data *data);
t_block		*ft_block_new(t_data *data);
void		ft_block_clear(t_block **block);
void		ft_parsing_quote(t_data *data);
char		**ft_word_split(char const *s);
void		word_split(t_data *data);

void		expansion1(t_token *tmp, size_t *size, t_data *data, size_t *i);
void		ft_param_expansion(t_data *data);
//parsing redir.c
int			ft_redir_expansion(t_data *data);
int			ft_iscaracter_env(char c, int type);
void		ft_redir_print(t_redir *redir);
void		ft_tokenadd_next(t_token *token, t_token *new);
void		ft_add_redir(t_block *block, t_token *token, t_data *data);
void		ft_redir_free(t_redir *redir);
int			ft_expand_here_doc(t_data *data);
void		ft_block_print(t_block *block);
void		ft_tokenprint(t_token *token);
void		ft_token_rm_redir(t_data *data, t_token *to_remouve);
void		ft_token_rmfurst(t_data *data, t_token *to_remouve);
void		do_expan(t_data *data, t_token *token, size_t size, int quote);
size_t		ft_count(t_data *data, char *s, int type);
void		exit_child(t_data *data, int **fds, int *fd);

void		ft_handle_sig_child(int sig);
char		*ft_do_count(t_data *data, char *s, int type, char *tmp2);
void		heredoc_calc_expan_size(char *line, t_data *data,
	size_t *size, size_t *i);
void	ft_heredoc_pipe(t_data *data, t_redir *redir, char *line);
char	*join_lines(char *s1, char *s2, t_data *data);
int	ft_islineblank(char *line);
int	word_check(t_data *data);
int	ft_check_is_incote(char *line, size_t *i);
void	ft_cal_expand_utils(size_t *i, size_t *size, char *line, t_data *data);
void	ft_expand_utils(size_t *i, size_t *j, t_token *token, t_data *data);
void	ft_expand_heredoc_utils(size_t *i, size_t *j, char *line, t_data *data);
int	check_pipe_token(t_data *data);
int	set_type(t_data *data);
#endif