/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:39:52 by mpitot            #+#    #+#             */
/*   Updated: 2024/04/30 22:32:22 by mpitot           ###   ########.fr       */
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

void	ft_put_env_exp(t_data *data, int fd)
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
			ft_printf_fd(fd, "declare -x %s=\"%s\"\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
	ft_envclear(&dup);
}

int	ft_export(t_data *data, t_block *block, int fd)		//TODO voir les export sans contenu (ex: export a)
{
	size_t	i;
	size_t	j;
	char	*var;
	char	*val;

	i = -1;
	if (!block->args[1])
		ft_put_env_exp(data, fd);
	while (block->args[++i])
	{
		j = 0;
		while (block->args[i][j] && block->args[i][j] != '=')
			j++;
		if (block->args[i][j] == '=')
		{
			var = ft_substr(block->args[i], 0, j);
			val = ft_substr(block->args[i], j + 1, ft_strlen(block->args[i]) - j - 1);
			ft_setenv(data, var, val);
			free(var);
			free(val);
		}
		else
		{
			var = ft_strdup(block->args[i]);
			ft_setenv(data, var, NULL);
			free(var);
		}
	}
	return (0);
}
