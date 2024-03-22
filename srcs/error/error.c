/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:12:57 by mbrousse          #+#    #+#             */
/*   Updated: 2024/03/22 15:08:57 by mbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_put_error(t_ERROR error, char *MSG)
{
	char	*str;

	g_error = error;
	if (MSG == NULL)
	{
		if (g_error == ERROR_COTE)
			str = "minishell: invalid pattern\n";
	}
	else
		str = MSG;
	ft_printf_fd(2, str);
}

void	ft_megafree(t_data *data)
{
	if (data->env)
		ft_envclear(&data->env);
	if (data->prompt)
		free(data->prompt);
	if (data->path)
		ft_free_tab(data->path);
}

void	destroy(t_data *data)
{
	if (data->line)
		free(data->line);
	if (data->token)
		lt_clear(&data->token);
}
