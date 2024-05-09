/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:32:43 by mbrousse          #+#    #+#             */
/*   Updated: 2024/05/08 15:37:28 by mbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	inc_shlvl(t_env	*tmp)
{
	int		nb;

	if (!ft_strcmp(tmp->name, "SHLVL"))
	{
		nb = ft_atoi(tmp->value);
		nb++;
		free(tmp->value);
		tmp->value = ft_itoa(nb);
	}
}

int	ft_parsing_env(char **env, t_data *data)
{
	int			i;
	int			j;
	t_env		*tmp;

	data->env = NULL;
	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		if (env[i][j] == '=')
		{
			env[i][j] = '\0';
			tmp = ft_envnew(env[i], &env[i][j + 1]);
			if (!tmp)
				return (ft_put_error(1, EM_MALLOC), 1);
			ft_envadd_back(&data->env, tmp);
			env[i][j] = '=';
			inc_shlvl(tmp);
		}
		i++;
	}
	return (0);
}

char	**get_path(t_data *data)
{
	t_env	*tmp;
	char	**path;

	tmp = ft_envfind(data->env, "PATH");
	if (!tmp)
	{
		path = malloc(sizeof(char *));
		if (!path)
			return (NULL);
		path[0] = NULL;
		return (path);
	}
	path = ft_split(tmp->value, ':');
	if (!path)
		return (NULL);
	return (path);
}

int	ft_set_tab(t_data *data)
{
	data->exit = 1;
	data->prompt = NULL;
	data->line = NULL;
	data->block = NULL;
	data->token = NULL;
	data->error_cmd = NULL;
	return (0);
}

int	ft_init_tab(t_data *data, char **env)
{
	if (env == NULL || env[0] == NULL)
		return (ft_put_error(1, EM_ENV), 1);
	if (ft_parsing_env(env, data))
		return (1);
	if (ft_set_tab(data))
		return (1);
	return (0);
}
