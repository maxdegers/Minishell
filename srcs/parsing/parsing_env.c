/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:32:43 by mbrousse          #+#    #+#             */
/*   Updated: 2024/03/13 17:31:16 by mbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
				return (ft_put_error(EM_MALLOC, 1));
			ft_envadd_back(&data->env, tmp);
			env[i][j] = '=';
		}
		i++;
	}
	return (0);
}

int	ft_set_tab(t_data data)
{
	
}

int	init_tab(t_data *data)
{
	if (ft_parsing_env(data->env, data))
		return (1);
	if (ft_set_tab(data))
		return (1);
	return (0);
}