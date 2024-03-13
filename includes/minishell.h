/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:18:47 by mbrousse          #+#    #+#             */
/*   Updated: 2024/03/13 17:59:06 by mbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/incs/libft.h"
# include "colors.h"

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

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

extern size_t	g_error;

typedef enum e_signal
{
	ERROR_M
}				t_signal;

typedef struct s_env
{
	char				*name;
	char				*value;
	struct s_env		*next;
}	t_env;

typedef struct s_data
{
	char		*user;
	t_env		*env;
}	t_data;

// main.c
void		ft_putheader(void);
// error.c
int			ft_put_error(char *str, int error);
void		ft_free_data(t_data *data);
void		ft_megafree(t_data *data);
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

#endif