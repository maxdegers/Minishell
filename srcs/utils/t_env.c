/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:09:18 by mpitot            #+#    #+#             */
/*   Updated: 2024/05/21 11:36:41 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_envsize(t_env *env)
{
	size_t	i;

	i = 0;
	while (env)
	{
		if (env->show)
			i++;
		env = env->next;
	}
	return (i);
}

t_env	*ft_envnew(char *name, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->name = ft_strdup(name);
	if (!new->name)
		return (free(new), NULL);
	if (!value)
	{
		new->show = false;
		new->value = NULL;
	}
	else
	{
		new->show = true;
		new->value = ft_strdup(value);
		if (!new->value)
			return (free(new->name), free(new), NULL);
	}
	new->next = NULL;
	return (new);
}

void	ft_envadd_back(t_env **env, t_env *new)
{
	t_env	*tmp;

	if (!(*env))
	{
		(*env) = new;
		return ;
	}
	tmp = (*env);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	ft_envclear(t_env **env)
{
	t_env	*tmp;

	if (!env || !*env)
		return ;
	while (*env)
	{
		tmp = (*env)->next;
		free((*env)->name);
		free((*env)->value);
		free(*env);
		(*env) = tmp;
	}
}

t_env	*ft_envfind(t_env *env, char *name)
{
	while (env)
	{
		if (!ft_strcmp(env->name, name) && env->show)
			return (env);
		env = env->next;
	}
	return (NULL);
}
