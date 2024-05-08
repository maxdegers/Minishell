/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:40:02 by mpitot            #+#    #+#             */
/*   Updated: 2024/05/02 15:03:39 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_data *data)
{
	t_env *env;

	env = data->env;
	while (env)
	{
		if (env->show)
			ft_printf("%s=%s\n", env->name, env->value);
		env = env->next;
	}
	return ;
}
