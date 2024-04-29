/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 20:08:38 by mbrousse          #+#    #+#             */
/*   Updated: 2024/04/29 12:01:05 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_set_prompt(void)
{
	char	*prompt;

	prompt = NULL;
	prompt = ft_strjoin_free(prompt, B_YELLOW, 1);
	prompt = ft_strjoin_free(prompt, "minishell", 1);
//	prompt = ft_strjoin_free(prompt, B_ORANGE, 1);
//	prompt = ft_strjoin_free(prompt, " $ ", 1);
	prompt = ft_strjoin_free(prompt, RESET, 1);
	prompt = ft_strjoin_free(prompt, "🐚 ", 1);
	if (!prompt)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	return (prompt);
}

int	ft_main_loop(t_data *data)
{
	char	*line;

	data->exit = 0;
	data->prompt = ft_set_prompt();
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
			continue ;
		}
		ft_tokenprint(data->token);
		// ft_exec(data);
		destroy(data);
	}
	return (0);
}
