/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 20:08:38 by mbrousse          #+#    #+#             */
/*   Updated: 2024/05/09 13:17:02 by mbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_set_prompt(t_data *data)
{
	char	*prompt;

	prompt = NULL;
	prompt = ft_strjoin_free(prompt, B_YELLOW, 1);
	if (!prompt)
		exit_error(ERROR_MALLOC, NULL, data);
	prompt = ft_strjoin_free(prompt, "minishell", 1);
	if (!prompt)
		exit_error(ERROR_MALLOC, NULL, data);
	prompt = ft_strjoin_free(prompt, RESET, 1);
	if (!prompt)
		exit_error(ERROR_MALLOC, NULL, data);
	prompt = ft_strjoin_free(prompt, "\001\xF0\x9F\002\x90\x9A ", 1);
	if (!prompt)
		exit_error(ERROR_MALLOC, NULL, data);
	return (prompt);
}

int	ft_main_loop(t_data *data)
{
	char	*line;

	data->exit = 0;
	data->prompt = ft_set_prompt(data);
	while (!data->exit)
	{
		ft_set_signal();
		line = readline(data->prompt);
		if (line == NULL)
			return (ft_putstr_fd("exit\n", 1), 0);
		if (*line == '\0')
			continue ;
		add_history(line);
		if (ft_parsing_line(data, line) == 1)
		{
			destroy(data);
			g_error = ERROR_SYNTAX;
			continue ;
		}
		ft_exec_line(data);
		destroy(data);
	}
	return (0);
}
