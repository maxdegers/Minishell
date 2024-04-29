/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 17:47:27 by mpitot            #+#    #+#             */
/*   Updated: 2024/04/29 15:10:46 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec_line(t_data *data)
{
	t_block	*block;
	int		fd[2];

	block = data->block;
	while (block)
	{
		if (pipe(fd) == -1)
			return (1);
		// if (ft_strcmp(block->cmd, "echo") == 0)
		// 	ft_echo(block->token);
		// else if (ft_strcmp(block->cmd, "pwd") == 0)
		// 	ft_pwd();
		// else if (ft_strcmp(block->cmd, "cd") == 0)
		// 	ft_relative_cd(block->token, data);
		// else if (ft_strcmp(block->cmd, "export") == 0)
		// 	ft_export(block->token, data);
		// else if (ft_strcmp(block->cmd, "unset") == 0)
		// 	ft_unset(block->token, data);
		// else if (ft_strcmp(block->cmd, "env") == 0)
		// 	ft_env(data->env);
		// else if (ft_strcmp(block->cmd, "exit") == 0)
		// 	ft_exit(block->token, data);
		// /*else
		// 	ft_execve(block, data);*/
		block = block->next;
	}
	return (0);
}