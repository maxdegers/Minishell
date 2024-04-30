/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:40:02 by mpitot            #+#    #+#             */
/*   Updated: 2024/04/30 12:03:52 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_data *data, int fd)
{
	t_env *env;

	env = data->env;
	while (env)
	{
		ft_printf_fd(fd, "%s=%s\n", env->name, env->value);
		env = env->next;
	}
	return (0);
}
