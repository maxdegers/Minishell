/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 20:08:38 by mbrousse          #+#    #+#             */
/*   Updated: 2024/03/14 23:18:39 by mbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_error = 0;

static char	*ft_get_prompt(t_data *data)
{
	static char	*user = NULL;
	char		*tmp;

	user = ft_strjoin(user, B_GREEN);
	tmp = ft_envfind(data->env, "USER");
	if (tmp)
		user = ft_strjoin(user, tmp);
	user = ft_strjoin(user, "@"RESET": "\
HEADER"minishell$ "RESET);
	return (user);
}

int	ft_main_loop(t_data *data)
{
	char	*line;

	data->exit = 0;
	while (!data->exit)
	{
		ft_set_signal();
		data->prompt = ft_get_prompt(data);
		line = readline(data->prompt);
		if (line == NULL)
			return (ft_putstr_fd("exit\n", 1), 0);
		if (*line == '\0')
			continue ;
		add_history(line);
	}
	return (0);
}
