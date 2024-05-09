/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:39:52 by mpitot            #+#    #+#             */
/*   Updated: 2024/05/09 13:35:45 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_setenv(t_data *data, char *var, char *val)
{
	t_env	*tmp;

	tmp = ft_envfind(data->env, var);
	if (tmp)
	{
		free(tmp->value);
		tmp->value = ft_strdup(val);
	}
	else
		ft_envadd_back(&data->env, ft_envnew(ft_strdup(var), ft_strdup(val)));
}

t_env	*ft_dup_env(t_env *env)
{
	t_env	*new;
	t_env	*tmp;

	new = NULL;
	while (env)
	{
		tmp = ft_envnew(env->name, env->value);
		if (!tmp)
			return (ft_envclear(&new), NULL);
		ft_envadd_back(&new, tmp);
		env = env->next;
	}
	return (new);
}

t_env	*ft_sort_env(t_env **env)
{
	t_env	*tmp;
	t_env	*head;
	char	*tmp_name;
	char	*tmp_value;

	head = *env;
	while (*env)
	{
		tmp = (*env)->next;
		while (tmp)
		{
			if (ft_strcmp((*env)->name, tmp->name) > 0)
			{
				tmp_name = (*env)->name;
				tmp_value = (*env)->value;
				(*env)->name = tmp->name;
				(*env)->value = tmp->value;
				tmp->name = tmp_name;
				tmp->value = tmp_value;
			}
			tmp = tmp->next;
		}
		*env = (*env)->next;
	}
	return (head);
}

void	ft_put_env_exp(t_data *data)
{
	t_env	*dup;
	t_env	*tmp;

	dup = ft_dup_env(data->env);
	if (!dup)
		exit_error(ERROR_MALLOC, NULL, data);
	dup = ft_sort_env(&dup);
	tmp = dup;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, "_") != 0)
		{
			if (tmp->show)
				ft_printf("declare -x %s=\"%s\"\n", tmp->name, tmp->value);
			else
				ft_printf("declare -x %s\n", tmp->name);
		}
		tmp = tmp->next;
	}
	ft_envclear(&dup);
}

int	check_chars(char *s1)
{
	static char *s2 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_";

	if (ft_strchr(s2, s1[0]))
		return (1);
	ft_printf_fd(2, "minishell: export: `%s' is not a valid identifier\n", s1);
	g_error = 1;
	return (0);
}

int	ft_export_show(t_data *data, char *str)
{
	t_env	*tmp;
	char	*var;
	size_t	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	var = ft_substr(str, 0, i);
	if (!var)
		return (1);
	tmp = ft_envfind(data->env, var);
	if (tmp)
	{
		free(tmp->value);
		tmp->value = ft_strdup(&str[i + 1]);
	}
	else
	{
		tmp = ft_envnew(var, &str[i + 1]);
		if (!tmp)
			return (free(var), 1);
		ft_envadd_back(&data->env, tmp);
	}
	return (free(var), 0);
}

int	ft_export_nshow(t_data *data, char *str)
{
	t_env	*tmp;

	if (ft_envfind(data->env, str))
		return (0);
	tmp = ft_envnew(str, NULL);
	if (!tmp)
		return (1);
	ft_envadd_back(&data->env, tmp);
	return (0);
}

int	ft_export(t_data *data, t_block *block)
{
	size_t	i;
	int		ret;

	i = 0;
	while (block->args[++i])
	{
		if (!check_chars(block->args[i]))
			return (0);
		if (ft_strchr(block->args[i], '='))
			ret = ft_export_show(data, block->args[i]);
		else
			ret = ft_export_nshow(data, block->args[i]);
		if (ret)
			return (1);
	}
	return (0);
}
