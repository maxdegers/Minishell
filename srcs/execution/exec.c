/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 17:47:27 by mpitot            #+#    #+#             */
/*   Updated: 2024/05/09 12:05:05 by mpitot           ###   ########.fr       */
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

int	**malloc_fd_tab(size_t size)
{
	int		**fd;
	size_t	i;

	fd = malloc(sizeof(int *) * size);
	if (!fd)
		return (NULL);
	i = -1;
	while (++i < size)
	{
		fd[i] = malloc(sizeof(int) * 2);
		if (!fd[i])
		{
			while (--i)
				free(fd[i]);
			free(fd);
			return (NULL);
		}
	}
	return (fd);
}

int	**ft_open_pipes(t_data *data, size_t pipe_amount)
{
	int		**fd;
	size_t	i;

	fd = malloc_fd_tab(pipe_amount);
	if (!fd)
		exit_error(ERROR_MALLOC, NULL, data);
	i = 0;
	while (i < pipe_amount)
	{
		if (pipe(fd[i]) == -1)
		{
			while (--i)
				close2(fd[i][0], fd[i][1]);
			exit_error(ERROR_EXEC, NULL, data);	//TODO check ek daxi
		}
		i++;
	}
//	ft_printf("%d, %d\n", fd[0][0], fd[0][1]);
	return (fd);
}

void	ft_child_process(t_data *data, t_block *block, int *fd)
{
	if (ft_is_builtin(block) == 2)
	{
		close(fd[0]);
		close(fd[1]);
		exit_error(ERROR_MALLOC, "", data);		//TODO check ici aussi / faire un exit de child qui free tout
	}
	ft_redir(block, fd);
//	ft_printf("%d, %d\n", fd[0], fd[1]);
	if (fd[0] != 0)
	{
		close(fd[0]);
		dup2(fd[0], STDIN_FILENO);
	}
	if (fd[1] != 1)
	{
		close(fd[1]);
		dup2(fd[1], STDOUT_FILENO);
	}
	ft_exec_under_fork(block, data);
	exit(0);		//TODO free everything

}

void	ft_close_useless_fds(int **fds, int *used, size_t pipe_amount)
{
	size_t	i;

	i = -1;
	if (!used)
	{
		while (++i < pipe_amount)
			close2(fds[i][0], fds[i][1]);
		return ;
	}
	while (++i < pipe_amount)
	{
		if (fds[i][0] != used[0] || fds[i][0] != used[1])
			close(fds[i][0]);
		if (fds[i][1] != used[0] || fds[i][1] != used[1])
			close(fds[i][1]);
	}
}

int	ft_get_fd(int **fds, size_t i, int *res, size_t pipe_amount)
{
	if (pipe_amount == 0)
		return (res[0] = 0, res[1] = 1, 0);
	if (i == 0)
		res[0] = 0;
	else
		res[0] = fds[i - 1][0];
	if (i == pipe_amount)
		res[1] = 1;
	else
		res[1] = fds[i][1];
	ft_close_useless_fds(fds, res, pipe_amount);
	return (0);
}

int	*ft_fork(t_data *data, t_block *block, size_t childs, int **fds)
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
			return (NULL);		//TODO free all and kill all childs
		if (pid[i] == 0)
		{
			ft_get_fd(fds, i, child_fd, childs - 1);
			ft_child_process(data, block, child_fd);
		}
		block = block->next;
		i++;
	}
	return (pid);
}

int	ft_wait_childs(int *pid, size_t child_amount)
{
	size_t	i;
	int		ret_status;

	i = -1;
	while (++i < child_amount)
	{
		ret_status = waitpid(pid[i], NULL, 0);
	}
	return (ret_status);
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
	pid = ft_fork(data, block, pipe_amount + 1, fd);
	ft_close_useless_fds(fd, NULL, pipe_amount);
	ft_wait_childs(pid, pipe_amount + 1);
	free(fd);
	return (0);
}
