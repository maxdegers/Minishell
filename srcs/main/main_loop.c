/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 20:08:38 by mbrousse          #+#    #+#             */
/*   Updated: 2024/03/30 14:32:36 by mbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_error = 0;

static char	*ft_set_prompt(t_data *data)
{
	static char	*user = NULL;
	t_env		*node;
	char		*tmp;
	char		*user_tmp;

	user = ft_strjoin(user, B_GREEN);
	node = ft_envfind(data->env, "USER");
	if (node)
	{
		tmp = ft_strdup(node->value);
		user_tmp = ft_strjoin(user, tmp);
		free(user);
		user = user_tmp;
		free(tmp);
	}
	user_tmp = ft_strjoin(user, "@"RESET": "\
	HEADER"minishell$ "RESET);
	free(user);
	user = user_tmp;
	return (user);
}

static void	ft_get_prompt(t_data *data)
{
	char	*color;
	size_t	i;
	size_t	size;

	i = 0;
	size = 7;
	if (g_error == 0)
	{
		color = B_GREEN;
		while (color[i] != '\0' && i < size - 1)
		{
			data->prompt[i] = color[i];
			i++;
		}
	}
	else
	{
		color = B_RED;
		while (color[i] != '\0' && i < size - 1)
		{
			data->prompt[i] = color[i];
			i++;
		}
	}
}

int	ft_main_loop(t_data *data)
{
	char	*line;

	data->exit = 0;
	data->prompt = ft_set_prompt(data);
	while (!data->exit)
	{
		ft_set_signal();
		ft_get_prompt(data);
		line = readline(data->prompt);
		if (line == NULL)
			return (ft_putstr_fd("exit\n", 1), 0);
		if (*line == '\0')
			continue ;
		add_history(line);
		if (ft_parsing_line(data, line) == 1)
		{
			destroy(data);
			continue ;
		}
		ft_exec(data);
		destroy(data);
	}
	return (0);
}
