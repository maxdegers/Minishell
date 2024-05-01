/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 16:15:42 by mbrousse          #+#    #+#             */
/*   Updated: 2024/05/01 12:30:19 by mbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//echo $USER"$USER"'$USER'$"USER"$'USER'
void	ft_add_to_str(char *str, size_t *i, char *add)
{
	size_t	j;

	j = 0;
	while (add && add[j])
	{
		str[*i] = add[j];
		*i += 1;
		j++;
	}
	free(add);
}

void	do_expan(t_data *data, t_token *token, size_t size, int quote)
{
	size_t	i;
	size_t	j;
	char	*new;

	i = 0;
	j = 0;
	ft_printf("size = %u\n", size);
	(void)quote;
	(void)data;
	(void)token;
	(void)i;
	(void)j;
	(void)new;
	// new = ft_calloc(size + 1, sizeof(char));
	// if (new == NULL)
	// 	exit_error(ERROR_MALLOC, NULL, data);
	// while (token->data[i] != '\0' && j < size)
	// {
	// 	if (token->data[i] == S_QUOTE)
	// 		quote *= -1;
	// 	if (token->data[i] == '$' && quote != 1)
	// 	{
	// 		if (token->data[i + 1] == '?')
	// 			ft_add_to_str(new, &j, ft_itoa(g_error));
	// 		else if (token->data[i + 1] == D_QUOTE
	// 			|| token->data[i + 1] == S_QUOTE)
	// 			i++;
	// 		else if (token->data[i + 1] != '$' && token->data[i + 1] != '\0')
	// 		{
	// 			while (token->data[i] && token->data[i] != ESPACE
	// 				&& token->data[i] != '$' && token->data[i] != D_QUOTE)
	// 				i++;
	// 			i--;
	// 			ft_add_to_str(new, &j, ft_envfind_data(data->env,
	// 					&token->data[i + 1]));
	// 		}
	// 	}
	// 	else
	// 	{
	// 		new[j] = token->data[i];
	// 		j++;
	// 	}
	// 	i++;
	// }
}

size_t	ft_count(t_data *data, char *s)
{
	size_t	i;

	if (s == NULL)
		exit_error(ERROR_MALLOC, NULL, data);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	calc_expan_size(t_token	*token, t_data *data, size_t *size, size_t *i)
{
	size_t	start;
	size_t	end;
	char	*tmp;
	
	if (token->data[*i + 1] == '?')
	{
		*size += ft_count(data, ft_itoa(g_error));
		*i += 1;
	}
	else
	{
		start = *i + 1;
		while (token->data[*i] && ft_iscaracter_env(token->data[*i]) != 0)
			*i += 1;
		end = *i;
		tmp = ft_strdup_size(&token->data[start], end - start);
		*size += ft_count(data, ft_envfind_data(data->env, tmp));
		free(tmp);
		// *i -= 1;
	}
}

size_t	calc_expan(t_token	*token, t_data *data, int quote)
{
	size_t size;
	size_t	i;


	i = 0;
	size = 0;
	while (token->data[i] != '\0')
	{
		printf("token->data[i] = %c\n", token->data[i]);
		if (token->data[i] == S_QUOTE)
			quote *= -1;
		if (token->data[i] == '$' && quote != 1)
		{
			calc_expan_size(token, data, &size, &i);
		}
		else
			size++;
		printf("size = %lu\n", size);
		
		i++;
	}
	return (size);
}

void	ft_param_expansion(t_data *data)
{
	t_token	*tmp;
	int		quote;

	quote = -1;
	tmp = data->token;
	while (tmp)
	{
		if (tmp->type == PIPE || tmp->type == REDIR_HEREDOC)
		{
			tmp = tmp->next;
			continue ;
		}
		else
		{
		   do_expan(data, tmp, calc_expan(tmp, data, quote), quote);
		}
		tmp = tmp->next;   
	}
}
