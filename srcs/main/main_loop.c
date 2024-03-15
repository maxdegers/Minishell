/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 20:08:38 by mbrousse          #+#    #+#             */
/*   Updated: 2024/03/15 01:43:15 by mbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_error = 0;

static char	*ft_get_prompt(t_data *data)
{
	static char	*user = NULL;
	t_env		*node;
	char		*tmp;

	if (!user)
	{
		user = ft_strjoin(user, B_GREEN);
		node = ft_envfind(data->env, "USER");
		if (node)
		{
			tmp = ft_strdup(node->value);
			user = ft_strjoin(user, tmp);
			free(tmp);
		}
		user = ft_strjoin(user, "@"RESET": "\
		HEADER"minishell$ "RESET);
	}
	else
	{
		write(1, "------------\n", 12);
		if (g_error == 0)
			ft_strlcpy(user, B_GREEN, 7);
		else
			ft_strlcpy(user, B_RED, 7);
	}
	return (user);
}

int	ft_main_loop(t_data *data)
{
	char	*line;

	data->exit = 0;
	data->prompt = ft_get_prompt(data);
	while (!data->exit)
	{
		ft_set_signal();
		line = readline(data->prompt);
		if (line == NULL)
			return (ft_putstr_fd("exit\n", 1), 0);
		if (*line == '\0')
			continue ;
		add_history(line);
		ft_printf("%i\n", g_error);
		free(line);
	}
	return (0);
}
