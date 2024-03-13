/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:32:43 by mbrousse          #+#    #+#             */
/*   Updated: 2024/03/13 15:44:41 by mbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_parsing_env(char **env, t_data *data)
{
	int	i;

	i = 0;
	data->id = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}
