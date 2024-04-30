/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 17:47:27 by mpitot            #+#    #+#             */
/*   Updated: 2024/04/30 14:12:15 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_run_cmd(t_data *data, t_block *block, int *fd)
{
	/*if (ft_strcmp(block->cmd, "echo") == 0)
		ft_echo(block, );*/
	if (ft_strcmp(block->cmd, "pwd") == 0)
		return (ft_pwd(fd[1]));
	else if (ft_strcmp(block->cmd, "cd") == 0)
		return (ft_cd(block, data));
	else if (ft_strcmp(block->cmd, "export") == 0)
		return (ft_export(data, block));
	/*else if (ft_strcmp(block->cmd, "unset") == 0)
		return (ft_unset(block, data));*/
	else if (ft_strcmp(block->cmd, "env") == 0)
		return (ft_env(data, fd[1]));
	else if (ft_strcmp(block->cmd, "exit") == 0)
		return (ft_exit(data, block));
	/*else
		return (ft_execve(block, data));*/
	return (0);
}

int	ft_exec_line(t_data *data)
{
	t_block	*block;
	int		fd[2];

	block = data->block;
	while (block)
	{
		if (pipe(fd) == -1)
			return (1);
		ft_run_cmd(data, block, fd);
//		ft_redir(block, data);
		block = block->next;
	}
	return (0);
}