/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 09:49:51 by mbrousse          #+#    #+#             */
/*   Updated: 2024/04/15 15:37:32 by mbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parsing_line(t_data *data, size_t *i, size_t *start, size_t *end)
{
	char	quote;

	if (data->line[*i] == '\'' || data->line[*i] == '\"')
	{
		quote = data->line[*i];
		*i += 1;
		while (data->line[*i] && data->line[*i] != quote)
			*i += 1;
	}
	if (data->line[*i] == '<' || data->line[*i] == '>')
	{
		if (*i != 0 && data->line[*i - 1] != ' ' )
		{
			*end = *i;
			ft_token_new_add(data, *start, *end, WORD);
			*start = *i;
		}
		if (data->line[*i + 1] != '\0' && data->line[*i + 1] == data->line[*i])
			*i += 1;
		*i += 1;
		return (1);
	}
	*i += 1;
	return (0);
}

void	ft_token_set(char *line, t_data *data)
{
	size_t	i;
	size_t	end;
	size_t	start;

	i = 0;
	while (line[i])
	{
		if (line[i] != ESPACE)
		{
			start = i;
			while (line[i] && line[i] != ESPACE)
			{
				if (parsing_line(data, &i, &start, &end) == 1)
					break ;
			}
			end = i;
			ft_token_new_add(data, start, end, WORD);
		}
		else
			i++;
	}
}

static int	checkerreur(char *line)
{
	size_t	i;
	bool	s_quote;
	bool	d_quote;

	i = 0;
	s_quote = false;
	d_quote = false;
	while (line[i])
	{
		if (line[i] == '\'' && d_quote == false)
			s_quote = !s_quote;
		if (line[i] == '\"' && s_quote == false)
			d_quote = !d_quote;
		i++;
	}
	if (s_quote == true || d_quote == true)
		return (1);
	return (0);
}

void	ft_add_to_str(char *str, size_t *i, char *add, t_data *data)
{
	size_t	j;

	if (!add)
		exit_error(ERROR_MALLOC, "malloc error", data);
	j = 0;
	while (add[j])
	{
		str[*i] = add[j];
		*i += 1;
		j++;
	}
	free(add);
}

void	ft_param_expansion2(t_token *token, size_t size, t_data *data)
{
	char	*new;
	size_t	i;
	size_t	j;
	size_t	start;
	char	c;
	char	*tmp;

	new = malloc(sizeof(char) * (size + 1));
	if (!new)
		exit_error(ERROR_MALLOC, "malloc error", data);
	i = 0;
	j = 0;
	while (token->data[i])
	{
		if (token->data[i] == '$' && token->data[i + 1] != '\0')
		{
			if (token->data[i + 1] == '?')
			{
				tmp = ft_itoa(g_error);
				ft_add_to_str(new, &j, tmp, data);
				i += 1;
			}
			else
			{
				start = i + 1;
				while (token->data[i] && token->data[i] != ' ' && token->data[i] != '$')
					i++;
				c = token->data[i];
				token->data[i] = '\0';
				tmp = ft_strdup(ft_envfind_data(data->env, &token->data[start]));
				token->data[i] = c;
				ft_add_to_str(new, &j, tmp, data);
			}
		}
		else
			new[j] = token->data[i];
		i++;
		j++;
	}
	new[j] = '\0';
	free(token->data);
	token->data = new;
}

void	ft_param_expansion(t_data *data)
{
	t_token	*tmp;
	size_t	i;
	size_t	size;
	size_t	start;
	char	c;

	tmp = data->token;
	while (tmp)
	{
		i = 0;
		size = 0;
		while (tmp->data[i])
		{
			if (tmp->data[i] == '$' && tmp->data[i + 1] != '\0')
			{
				if (tmp->data[i + 1] == '?')
				{
					size += strlen(ft_itoa(g_error));
					i += 1;
				}
				else
				{
					start = i + 1;
					i++;
					while (tmp->data[i] && tmp->data[i] != ' ' && tmp->data[i] != '$')
						i++;
					c = tmp->data[i];
					tmp->data[i] = '\0';
					size += ft_strlen(ft_envfind_data(data->env, &tmp->data[start]));
					tmp->data[i] = c;
				}
			}
			else
				size++;
			i++;
		}
		ft_param_expansion2(tmp, size, data);
		tmp = tmp->next;
	}
}

int	ft_parsing_line(t_data *data, char *line)
{
	data->line = line;
	if (checkerreur(line) == 1)
		return (ft_put_error(255, "minishell: invalid pattern\n"), 1);
	ft_token_set(line, data);
	ft_param_expansion(data);
	g_error = 0;
	return (0);
}
