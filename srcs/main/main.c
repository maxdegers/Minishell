/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:20:57 by mbrousse          #+#    #+#             */
/*   Updated: 2024/03/13 15:12:25 by mbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putheader(void)
{
	printf("\n\n"HEADER);
	printf("___  ___ _         _       _            _  _ \n");
	printf("|  \\/  |(_)       (_)     | |          | || |\n");
	printf("| .  . | _  _ __   _  ___ | |__    ___ | || |\n");
	printf("| |\\/| || || '_ \\ | |/ __|| '_ \\  / _ \\| || |\n");
	printf("| |  | || || | | || |\\__ \\| | | ||  __/| || |\n");
	printf("\\_|  |_/|_||_| |_||_||___/|_| |_| \\___||_||_|\n\n\n"RESET);
}

int	main(int argc, char **argv, char **env)
{
	if (argc > 1)
		return (ft_put_error("minishell: too many arguments"), 1);
	ft_putheader();
	return (0);
}
