/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 17:47:27 by mpitot            #+#    #+#             */
/*   Updated: 2024/05/11 15:54:05 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_builtin(t_block *block)
{
	if (ft_strcmp(block->cmd, "echo") == 0
	|| ft_strcmp(block->cmd, "pwd") == 0
	|| (ft_strcmp(block->cmd, "export") == 0 && !block->args[1])
	|| ft_strcmp(block->cmd, "env") == 0)
		return (1);
	if (ft_strcmp(block->cmd, "cd") == 0
	|| (ft_strcmp(block->cmd, "export") == 0 && block->args[1])
	|| ft_strcmp(block->cmd, "unset") == 0
	|| ft_strcmp(block->cmd, "exit") == 0)
		return (2);
	return (0);
}

void	ft_exec_simple_builtin(t_block *block, t_data *data)
{
	if (ft_strcmp(block->cmd, "cd") == 0)
		ft_cd(block, data);
	if (ft_strcmp(block->cmd, "export") == 0)
		ft_export(data, block);
	if (ft_strcmp(block->cmd, "unset") == 0)
		ft_unset(block, data);
	if (ft_strcmp(block->cmd, "exit") == 0)
		ft_exit(data, block);
}

void	ft_exec_under_fork(t_block *block, t_data *data)
{
	if (ft_strcmp(block->cmd, "echo") == 0)
		return (ft_echo(block));
	if (ft_strcmp(block->cmd, "export") == 0)
		return (ft_put_env_exp(data));
	if (ft_strcmp(block->cmd, "pwd") == 0)
		return (ft_pwd());
	if (ft_strcmp(block->cmd, "env") == 0)
		return (ft_env(data));
	else
		ft_execve(data, block);
}

int	ft_exec_line(t_data *data)
{
	t_block	*block;
	size_t	pipe_amount;
	int		**fd;
	int		*pid;

	block = data->block;
	pipe_amount = get_pipe_amount(block);
	if (pipe_amount == 0 && ft_is_builtin(block) == 2)
		return (ft_exec_simple_builtin(block, data), 0);
	fd = ft_open_pipes(data, pipe_amount);
	ft_set_signal(SIG_CHILD);
	pid = ft_fork(data, block, pipe_amount + 1, fd);
	ft_close_useless_fds(fd, NULL, pipe_amount);
	ft_wait_childs(pid, pipe_amount + 1);
	free(pid);
	ft_free_int_tab(fd);
	return (0);
}
