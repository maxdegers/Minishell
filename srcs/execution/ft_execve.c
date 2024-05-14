/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:39:44 by mpitot            #+#    #+#             */
/*   Updated: 2024/05/14 19:21:15 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_join_path(char *path, char *cmd)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(path, "/");
	if (!tmp)
		return (NULL);
	res = ft_strjoin(tmp, cmd);
	return (free(tmp), res);
}

char	*ft_get_absolute_path(char *cmd)
{
	char	*res;

	res = ft_strdup(cmd);
	if (!res)
		return (NULL);
	if (access(res, F_OK) == 0)
	{
		if (access(res, X_OK) == 0)
			return (res);
		g_error = 1;
	}
	else
		g_error = 127;
	return (free(res), NULL);
}

char	*ft_get_relative_path(t_data *data, char *cmd)
{
	char	**path;
	char	*res;
	size_t	i;

	path = get_path(data);
	if (!path)
		return (NULL);
	i = -1;
	while (path[++i])
	{
		g_error = 0;
		res = ft_join_path(path[i], cmd);
		if (access(res, F_OK) == 0)
		{
			if (access(res, X_OK) == 0)
				return (ft_free_tab(path), res);
			g_error = 1;
			return (ft_free_tab(path), NULL);
		}
		else
			g_error = 127;
		free(res);
	}
	return (ft_free_tab(path), NULL);
}

char	*ft_get_cwd_exec_path(char *cmd)
{
	char	*pwd;
	char	*res;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (NULL);
	res = ft_join_path(pwd, cmd);
	free(pwd);
	if (!res)
		return (cmd);
	if (access(res, F_OK) == 0)
	{
		if (access(res, X_OK) == 0)
			return (res);
		g_error = 1;
	}
	else
		g_error = 127;
	return (free(res), NULL);
}

char	*ft_get_path(t_data *data, char *cmd)
{

	if (!cmd)
		return (NULL);
	if (cmd[0] == '/')
		return (ft_get_absolute_path(cmd));
	else if (cmd[0] == '.' && cmd[1] == '/')
		return (ft_get_cwd_exec_path(cmd));
	else
		return (ft_get_relative_path(data, cmd));
}

void	ft_execve(t_data *data, t_block *block)		//TODO refaire la fonction nette
{
	char	**envp;
	char	*path;

	envp = ft_env_to_tab(data->env);
	if (!envp)
		exit_error(ERROR_MALLOC, NULL, data);
	path = ft_get_path(data, block->cmd);
	if (!path && g_error == 0)
		return (ft_free_tab(envp), exit_error(ERROR_MALLOC, NULL,data));
	else if (!path)
	{
		if (g_error == 127)
			ft_printf_fd(2, "%s: command not found\n", block->cmd);
		if (g_error == 1)
			ft_printf_fd(2, "%s: Permission denied\n", block->cmd);
		ft_free_tab(envp);
		free(path);
	}
	else if (execve(path, block->args, envp) == -1)
	{
		ft_free_tab(envp);
		free(path);
		g_error = 127;
	}
}