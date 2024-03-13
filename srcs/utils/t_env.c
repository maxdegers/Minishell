/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:09:18 by mpitot            #+#    #+#             */
/*   Updated: 2024/03/13 17:23:54 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_envsize(t_env *env)
{
	size_t	i;

	i = 0;
	while (env)
	{
		env = env->next;
		i++;
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
	new->value = ft_strdup(value);
	if (!new->value)
		return (free(new->name), free(new), NULL);
	new->next = NULL;
	return (new);
}

void	ft_envadd_back(t_env **env, t_env *new)
{
	t_env	*tmp;

	tmp = (*env);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}
