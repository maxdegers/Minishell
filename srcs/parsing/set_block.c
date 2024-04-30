/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_block.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 13:03:37 by mbrousse          #+#    #+#             */
/*   Updated: 2024/04/30 14:09:38 by mbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_set_block(t_data *data)
{
	t_token	*tmp;
	t_token	*tmp2;
	t_block	*block;
	size_t	size;
	char	**args;
	size_t	i;

	tmp = data->token;
	while (tmp)
	{
		block = ft_block_new(data);
		size = 0;
		i = 0;
		block->cmd = ft_strdup(tmp->data);
		tmp2 = tmp;
		while (tmp && ft_strcmp(tmp->data, "|") != 0)
		{
			size++;
			tmp = tmp->next;
		}
		printf("size: %zu\n", size);
		args = ft_calloc(sizeof(char *), (size + 1));
		args[size] = NULL;
		
		while (tmp2 && ft_strcmp(tmp2->data, "|") != 0)
		{
			args[i++] = ft_strdup(tmp2->data);
			tmp2 = tmp2->next;
		}
		block->args = args;
		if (tmp)
			tmp = tmp->next;
	}
}
