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

#include "ft_get_next_line.h"

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

static char	*extract_line(char **stash)
{
	char	*line;
	char	*next;
	char	*p;
	size_t	len;

	if (**stash == '\0')
	{
		free(*stash);
		*stash = NULL;
		return (NULL);
	}
	p = ft_strchr(*stash, '\n');
	len = ft_strlen(*stash);
	if (p != NULL)
	{
		len = p - *stash + 1;
		next = ft_strdup(p + 1, ft_strlen(p + 1));
	}
	else
		next = NULL;
	line = ft_strdup(*stash, len);
	free(*stash);
	*stash = next;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stash;

	if (fd < 0)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	if (BUFFER_SIZE <= 0)
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
	return (extract_line(&stash));
}

void	get_next_line_clear(void)
{
	get_next_line(-1);
}
