/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_line_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 10:22:35 by mbrousse          #+#    #+#             */
/*   Updated: 2024/04/30 11:45:43 by mbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expansion2(t_token *token, size_t *i, size_t *j, t_data *data)
{
	char	c;
	size_t	start;
	char	*tmp;

	if (token->data[*i + 1] == '?')
	{
		tmp = ft_itoa(g_error);
		if (!tmp)
			exit_error(ERROR_MALLOC, "malloc error", data);
		ft_add_to_str(token->new, j, tmp);
		*i += 1;
	}
	else
	{
		// calcule la taille du mot "$USER"
		// start end
		// envfind_data(env, data->line, start, end) => mbrousse
		start = *i + 1;
		while (token->data[*i] && token->data[*i] != ' '
			&& token->data[*i] != '$' && token->data[*i] != '"')
			*i += 1;
		*i -= 1;
		c = token->data[*i];
		token->data[*i] = '\0';
		tmp = ft_strdup(ft_envfind_data(data->env, &token->data[start]));
		token->data[*i] = c;
		ft_add_to_str(token->new, j, tmp);
		*i -= 1;
	}
}

void	ft_param_expansion2(t_token *token, size_t size,
		t_data *data, char *new)
{
	size_t	i;
	size_t	j;
	int		quote;

	i = 0;
	j = 0;
	quote = -1;
	while (token->data[i] != '\0' && j < size)
	{
		if (token->data[i] == '\'')
			quote *= -1;
		if (token->data[i] == '$' && token->data[i + 1] != '\0' && quote != 1)
			expansion2(token, &i, &j, data);
		else
		{
			new[j] = token->data[i];
			j++;
		}
		i++;
	}
	new[j] = '\0';
	printf("new = %s\n", new);
	free(token->data);
	token->data = new;
}

void	ft_set_param_expansion2(t_token *token, size_t size, t_data *data)
{
	char	*new;

	new = ft_calloc(sizeof(char), (size + 1));
	if (!new)
		exit_error(ERROR_MALLOC, "malloc error\n", data);
	token->new = new;
	ft_param_expansion2(token, size, data, new);
}

void	expansion1(t_token *tmp, size_t *size, t_data *data, size_t *i)
{
	char	c;
	size_t	start;

	start = 0;
	if (tmp->data[*i + 1] == '?')
	{
		*size += strlen(ft_itoa(g_error));
		*i += 1;
	}
	else
	{
		start = *i + 1;
		*i += 1;
		while (tmp->data[*i] && !ft_isblank(tmp->data[*i])
			&& !ft_iscontrol_operator(tmp->data[*i])
			&& tmp->data[*i] != '$' && tmp->data[*i] != '"')
			*i += 1;
		c = tmp->data[*i];
		tmp->data[*i] = '\0';
		*size += ft_strlen(ft_envfind_data(data->env, &tmp->data[start]));
		tmp->data[*i] = c;
		*i -= 1;
	}
}

void	ft_param_expansion(t_data *data)
{
	t_token	*tmp;
	size_t	i;
	size_t	size;
	int		quote;

	tmp = data->token;
	while (tmp)
	{
		i = 0;
		size = 0;
		quote = -1;
		while (tmp->data[i] != '\0')
		{
			if (tmp->data[i] == '\'')
				quote *= -1;
			if (tmp->data[i] == '$' && tmp->data[i + 1] != '\0' && quote != 1)
				expansion1(tmp, &size, data, &i);
			else
				size++;
			i++;
		}
		printf("size = %zu\n", size);
		ft_set_param_expansion2(tmp, size, data);
		tmp = tmp->next;
	}
}
