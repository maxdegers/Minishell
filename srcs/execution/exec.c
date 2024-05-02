/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 17:47:27 by mpitot            #+#    #+#             */
/*   Updated: 2024/05/02 16:07:36 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_run_cmd(t_data *data, t_block *block, int *fd)
{
	if (ft_strcmp(block->cmd, "echo") == 0)
		ft_echo(block, fd[1]);
	else if (ft_strcmp(block->cmd, "pwd") == 0)
		ft_pwd(fd[1]);
	else if (ft_strcmp(block->cmd, "cd") == 0)
		ft_cd(block, data);
	else if (ft_strcmp(block->cmd, "export") == 0)		//TODO check amount of pipes
		ft_export(data, block, fd[1]);				//TODO before calling the function
	else if (ft_strcmp(block->cmd, "unset") == 0)
		ft_unset(block, data);
	else if (ft_strcmp(block->cmd, "env") == 0)
		ft_env(data, fd[1]);
	else if (ft_strcmp(block->cmd, "exit") == 0)		//TODO check amount of pipes
		ft_exit(data, block);							//TODO before calling the function
	else
		ft_execve(data, block, fd);
}

int	ft_exec_line(t_data *data)
{
	t_block	*block;
	int		fd[2];
	int		save;

	block = data->block;
	save = 1;
	fd[0] = 0;
	fd[1] = 1;
	while (block)
	{
		if (block->next)
		{
			if (pipe(fd) == -1)
				return (1);
		}
		ft_swap(&fd[1], &save);
		ft_redir(block, fd);
		ft_run_cmd(data, block, fd);
		block = block->next;
	}
	return (0);
}
