/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:39:44 by mpitot            #+#    #+#             */
/*   Updated: 2024/04/29 17:26:30 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_path(t_data *data, char *cmd)
{
	char	**path;
	char	*res;
	size_t	i;

	path = ft_split(ft_envfind(data->env, "PATH")->value, ':');
	if (!path)
	{
		perror("malloc");
		ft_megafree(data);
		exit(1);
	}
	i = -1;
	res = NULL;
	while (path[++i])
	{
		res = ft_strjoin(path[i], cmd);
		if (access(res, F_OK | X_OK) == 1)
			return (res);
		free(res);
	}
	return (NULL);
}

int	ft_execve(t_data *data, t_block *block, int fd)
{
	char	**envp;
	int		pid;
	char	*path;

	envp = ft_env_to_tab(data->env);
	if (!envp)
	{
		perror("malloc");
		ft_megafree(data);
		exit(1);
	}
	path = ft_get_path(data, block->cmd);
	if (!path)
		return (ft_putstr_fd("command not found", 1), 0);
	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{	//CHILD
		dup2(fd, 1);
		execve(path, block->args, envp);
	}
	else
	{	//PARENT
		wait(NULL);
		return (0);
	}
	return (0);
}