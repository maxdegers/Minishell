/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_bis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 10:09:34 by mpitot            #+#    #+#             */
/*   Updated: 2024/05/02 16:35:43 by mbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	ft_count_words(const char *str, char quote)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == D_QUOTE || str[i] == S_QUOTE)
		{
			quote = str[i];
			i++;
			while (str[i] && str[i] != quote)
				i++;
		}
		else if (i == 0 || str[i - 1] == SPACE || str[i - 1] == TAB)
		{
			if (str[i] != SPACE && str[i] != TAB && str[i] != '\0')
				count++;
		}
		i++;
	}
	return (count);
}

static size_t	ft_wordlen(const char *str)
{
	size_t	i;
	char	quote;

	i = 0;
	while (str[i])
	{
		if (str[i] == D_QUOTE || str[i] == S_QUOTE)
		{
			quote = str[i];
			i++;
			while (str[i] && str[i] != quote)
				i++;
		}
		if (str[i] == SPACE || str[i] == TAB)
			break ;
		i++;
	}
	return (i);
}

static char	**ft_fill_tab(char const *s, char **tab)
{
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != SPACE && s[i] != TAB)
		{
			len = ft_wordlen(&s[i]);
			tab[j] = ft_calloc(sizeof(char), (len + 1));
			if (!tab[j])
			{
				ft_free_tab(tab);
				return (NULL);
			}
			ft_strlcpy(tab[j], &s[i], len + 1);
			i += len;
			j++;
		}
		else
			i++;
	}
	return (tab);
}

char	**ft_word_split(char const *s)
{
	size_t	size;
	char	**tab;

	size = ft_count_words(s, 0);
	tab = ft_calloc(sizeof(char *), (size + 1));
	if (!tab)
		return (NULL);
	tab = ft_fill_tab(s, tab);
	if (!tab)
		return (NULL);
	tab[size] = NULL;
	return (tab);
}
