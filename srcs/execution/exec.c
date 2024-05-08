/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 17:47:27 by mpitot            #+#    #+#             */
/*   Updated: 2024/05/07 19:35:18 by mpitot           ###   ########.fr       */
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

size_t	get_pipe_amount(t_block *block)
{
	size_t	i;

	i = 0;
	while (block)
	{
		if (block->next)
			i++;
		block = block->next;
	}
	return (i);
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
		ft_echo(block);
	if (ft_strcmp(block->cmd, "export") == 0)
		ft_put_env_exp(data);
	if (ft_strcmp(block->cmd, "pwd") == 0)
		ft_pwd();
	if (ft_strcmp(block->cmd, "env") == 0)
		ft_env(data);
	else
		ft_execve(data, block);
}

int	**ft_open_pipes(t_data *data, size_t pipe_amount)
{
	int		**fd;
	size_t	i;

	(void) data;	//TODO free all using data in case of error
	fd = malloc(sizeof(fd[2]) * (pipe_amount));
	i = 0;
	while (i < pipe_amount)
	{
		if (pipe(fd[i]) == -1)
		{
			while (--i)
			{
				close(fd[i][0]);
				close(fd[i][1]);
			}
			exit_error(ERROR_EXEC, NULL, data);	//TODO check ek daxi
		}
		i++;
	}
	return (fd);
}

void	ft_child_process(t_data *data, t_block *block, int *fd)
{
	if (ft_is_builtin(block) == 2)
	{
		close(fd[0]);
		close(fd[1]);
		exit_error(ERROR_MALLOC, "", data);		//TODO check ici aussi
	}
	ft_redir(block, fd);
	dup2(fd[1], STDOUT_FILENO);
	dup2(fd[0], STDIN_FILENO);
	ft_exec_under_fork(block, data);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);

}

int	*ft_fork(t_data *data, t_block *block, size_t childs, int **fd)
{
	int		*pid;
	size_t	i;
	int		child_fd[2];

	pid = malloc(sizeof(int) * (childs));
	i = 0;
	while (i < childs)
	{
		pid[i] = fork();
		if (pid[i] == -1)
			return (1);		//TODO free all and kill all childs
		if (pid[i] == 0)
		{
			child_fd = ft_get_fd();		//TODO
			ft_child_process(data, block, child_fd);
			//TODO execute command here
			//TODO the command will kill itself childs die here
		}
		block = block->next;
		i++;
	}
	return (pid);
}

int	ft_exec_line(t_data *data)
{
	t_block	*block;
	size_t	pipe_amount;
	int		**fd;
	int		*pid;

	block = data->block;
	pipe_amount = get_pipe_amount(block);
	if (pipe_amount == 0 && ft_is_builtin(block) == 1)
		return (ft_exec_simple_builtin(block, data), 0);
	fd = ft_open_pipes(data, pipe_amount);

	pid = ft_fork(data, block, pipe_amount + 1);


	free(fd);
	return (0);
}
