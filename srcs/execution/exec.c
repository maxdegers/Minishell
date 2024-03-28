/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 17:24:11 by mbrousse          #+#    #+#             */
/*   Updated: 2024/03/28 18:39:58 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_token *token)
{
	t_token	*tmp;
	int		n;

	tmp = token;
	n = 0;
	if (tmp && !ft_strcmp(tmp->value, "-n"))
	{
		n = 1;
		tmp = tmp->next;
	}
	while (tmp && tmp->exec == 0)
	{
		if (tmp->cmd_t == ARGS)
			ft_printf("%s", tmp->value);
		tmp = tmp->next;
		if (tmp)
			ft_printf(" ");
	}
	if (!n)
		ft_printf("\n");
}

void	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	ft_printf("%s\n", pwd);
	free(pwd);
}

void	ft_relative_cd(t_token *token, t_data *data)
{
	t_token	*tmp;
	char	*path;
	char	*pwd;

	tmp = token;
	if (!tmp)
	{
		path = ft_strdup(ft_envfind(data->env, "HOME")->value);
		chdir(path);
		free(path);
	}
	else
	{
		pwd = getcwd(NULL, 0);
		path = ft_strjoin(pwd, tmp->value);
		free(pwd);
		if (chdir(path) == -1)
		{
			ft_printf("minishell: cd: %s: No such file or directory\n", path);
			g_error = 1;
		}
		free(path);
	}
}

void	ft_cd(t_token *token, t_data *data)
{
	t_token	*tmp;
	char	*path;

	tmp = token;
	if (!tmp)
	{
		path = ft_strdup(ft_envfind(data->env, "HOME")->value);
		chdir(path);
		free(path);
	}
	else
	{
		path = ft_strdup(tmp->value);
		if (chdir(path) == -1)
		{
			ft_printf("minishell: cd: %s: No such file or directory\n", path);
			g_error = 1;
		}
		free(path);
	}
}

int	ft_export(t_token *token, t_data *data)
{
	t_token	*tmp;
	t_env	*new;

	tmp = token;
	while (tmp)
	{
		new = ft_envnew(tmp->value, tmp->next->value);
		if (!new)
			return (1);
		ft_envadd_back(&data->env, new);
		tmp = tmp->next;
	}
	return (0);
}

void	ft_unset(t_token *token, t_data *data)
{
	t_token	*tmp;
	t_env	*env;
	t_env	*prev;

	tmp = token;
	while (tmp)
	{
		env = data->env;
		prev = NULL;
		while (env)
		{
			if (!ft_strcmp(env->name, tmp->value))
			{
				if (prev)
					prev->next = env->next;
				else
					data->env = env->next;
				free(env->name);
				free(env->value);
				free(env);
				break ;
			}
			prev = env;
			env = env->next;
		}
		tmp = tmp->next;
	}
}

int	ft_exec(t_data *data)
{
	t_token	*tmp;

	tmp = data->token;
	if (tmp->cmd_t == CMD)
	{
		if (!ft_strcmp(tmp->value, "echo"))
			ft_echo(tmp->next);
		else if (!ft_strcmp(tmp->value, "cd"))
			ft_cd(tmp->next, data);
		else if (!ft_strcmp(tmp->value, "pwd"))
			ft_pwd();
		else if (!ft_strcmp(tmp->value, "export"))
			return (ft_export(tmp->next, data));
		else if (!ft_strcmp(tmp->value, "unset"))
			ft_unset(tmp->next, data);
		else if (!ft_strcmp(tmp->value, "env"))
			ft_envprint(data->env);
		else if (!ft_strcmp(tmp->value, "exit"))
			return (2);
		/*else
			ft_execve(tmp, data);*/
	}
	return (0);
}
