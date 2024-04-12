/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 11:39:17 by mpitot            #+#    #+#             */
/*   Updated: 2023/12/05 14:55:39 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

static char	*ft_join_n_free(char *s1, const char *s2)
{
	char	*new;

	new = ft_strjoin(s1, s2);
	return (free(s1), new);
}

static char	*ft_read(int fd, char *res)
{
	ssize_t	sz;
	char	buffer[BUFFER_SIZE + 1];
	char	*new;

	new = ft_strdup(res);
	if (!new)
		return (NULL);
	sz = 1;
	while (sz > 0)
	{
		sz = read(fd, buffer, BUFFER_SIZE);
		if (sz == -1)
			return (ft_bzero(res, BUFFER_SIZE + 1), free(new), NULL);
		buffer[sz] = '\0';
		new = ft_join_n_free(new, buffer);
		if (!new)
			return (NULL);
		if (ft_strchr(new, '\n'))
			break ;
	}
	return (new);
}

static char	*ft_next(char *line, char *buffer)
{
	size_t	i;
	size_t	j;
	size_t	size;
	char	*new;

	if (!line[0] && !buffer[0])
		return (free(line), NULL);
	i = 0;
	j = 0;
	while (line[i] != '\n' && line[i])
		i++;
	if (line[i])
		i++;
	size = i;
	while (line[i])
		buffer[j++] = line[i++];
	while (buffer[j])
		buffer[j++] = '\0';
	new = malloc(sizeof(char) * (size + 1));
	if (!new)
		return (free(line), NULL);
	i = -1;
	while (++i < size)
		new[i] = line[i];
	return (new[i] = '\0', free(line), new);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1] = "\0";
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, buffer, 0) < 0)
		return (ft_bzero(buffer, BUFFER_SIZE + 1), NULL);
	if (ft_strchr(buffer, '\n'))
	{
		line = ft_strdup(buffer);
		if (!line)
			return (NULL);
	}
	else
	{
		line = ft_read(fd, buffer);
		if (!line)
			return (NULL);
	}
	line = ft_next(line, buffer);
	return (line);
}
