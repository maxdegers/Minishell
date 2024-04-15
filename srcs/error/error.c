/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:12:57 by mbrousse          #+#    #+#             */
/*   Updated: 2024/04/15 10:47:08 by mbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_put_error(t_ERROR error, char *MSG)
{
	char	*str;

	g_error = error;
	str = MSG;
	if (str == NULL)
	{
		perror("minishell:");
		return ;
	}
	ft_printf_fd(2, str);
}

void	exit_error(t_ERROR error, char *MSG, t_data *data)
{
	destroy(data);
	ft_megafree(data);
	ft_put_error(error, MSG);
	exit(g_error);
}

void	ft_megafree(t_data *data)
{
	if (data->env)
		ft_envclear(&data->env);
	if (data->prompt)
		free(data->prompt);
}

void	destroy(t_data *data)
{
	if (data->line)
		free(data->line);
	if (data->token)
		ft_token_clear(&data->token);
}
