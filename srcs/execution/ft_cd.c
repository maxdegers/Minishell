/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:39:30 by mpitot            #+#    #+#             */
/*   Updated: 2024/05/17 13:19:17 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_pwd(t_data *data, char *pwd)
{
	t_env	*tmp;
	t_env	*tmp2;

	tmp = ft_envfind(data->env, "PWD");
	if (!tmp)
	{
		tmp2 = ft_envnew("PWD", pwd);
		if (!tmp2)
			return (1);
		ft_envadd_back(&data->env, tmp2);
		return (0);
	}
	free(tmp->value);
	tmp->value = ft_strdup(pwd);
	if (!tmp->value)
		return (1);
	return (0);
}

static int	update_oldpwd(t_data *data, char *oldpwd)
{
	t_env	*tmp;
	t_env	*tmp2;

	tmp = ft_envfind(data->env, "OLDPWD");
	if (!tmp)
	{
		tmp2 = ft_envnew("OLDPWD", oldpwd);
		if (!tmp2)
			return (1);
		ft_envadd_back(&data->env, tmp2);
		return (0);
	}
	free(tmp->value);
	tmp->value = ft_strdup(oldpwd);
	if (!tmp->value)
		return (1);
	return (0);
}

static int	update_env(t_data *data, char *oldpwd)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (1);
	if (update_pwd(data, pwd))
		return (1);
	if (update_oldpwd(data, oldpwd))
		return (1);
	free(pwd);
	free(oldpwd);
	return (0);
}

static int	ft_check_arg_num(t_block *block)
{
	size_t	i;

	i = -1;
	while (block->args[++i])
		continue ;
	if (i > 2)
	{
		ft_printf_fd(2, "minishell: cd: too many arguments\n");
		g_error = 1;
	}
	return (i);
}

void	ft_cd(t_block *block, t_data *data)
{
	t_env	*env;
	char	*path;
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		exit_error(ERROR_MALLOC, NULL, data);
	if (ft_check_arg_num(block) > 2)
		return (free(oldpwd));
	env = ft_envfind(data->env, "HOME");
	if (!env && !block->args)
		return (ft_put_error(1, "minishell: cd: HOME not set\n"),
			free(oldpwd));
	if (!block->args[1])
		path = env->value;
	else
		path = block->args[1];
	if (chdir(path) == -1)
	{
		ft_printf_fd(2, "minishell: cd: %s: No such file or directory\n", path);
		g_error = 1;
	}
	if (update_env(data, oldpwd))
		exit_error(ERROR_MALLOC, NULL, data);
}
