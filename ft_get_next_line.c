/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamunoz <joamunoz@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 09:16:03 by joamunoz          #+#    #+#             */
/*   Updated: 2026/10/03 20:06:16 by joamunoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*get_stash(int fd, char *stash)
{
	char	*buf;
	char	*p;
	int		bytes_read;

	bytes_read = 1;
	buf = malloc(BUFFER_SIZE + 1);
	if (buf == NULL)
		return (NULL);
	while (bytes_read > 0 && stash != NULL && ft_strchr(stash, '\n') == NULL)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buf);
			free(stash);
			return (NULL);
		}
		buf[bytes_read] = '\0';
		p = stash;
		stash = ft_strjoin(stash, buf);
		free(p);
	}
	free(buf);
	return (stash);
}

static char	*ft_get_line(char *stash, char **p)
{
	char	*line;
	size_t	len;

	*p = ft_strchr(stash, '\n');
	if (*p != NULL)
	{
		len = *p - stash + 1;
		line = ft_strdup(stash, len);
	}
	else
	{
		line = ft_strdup(stash, ft_strlen(stash));
	}
	return (line);
}

static char	*ft_next_line(char *stash, char **p)
{
	char	*next;

	if (*p != NULL)
	{
		*p = *p + 1;
		next = ft_strdup(*p, ft_strlen(*p));
	}
	else
	{
		next = NULL;
	}
	free(stash);
	stash = NULL;
	return (next);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	char		*p;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (stash == NULL)
	{
		stash = malloc(1);
		if (stash == NULL)
			return (NULL);
		*stash = '\0';
	}
	stash = get_stash(fd, stash);
	if (stash == NULL)
		return (NULL);
	if (*stash == '\0')
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	line = ft_get_line(stash, &p);
	stash = ft_next_line(stash, &p);
	return (line);
}
