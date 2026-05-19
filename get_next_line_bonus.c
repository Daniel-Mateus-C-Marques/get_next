/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danicamp <danicamp@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 17:06:20 by danicamp          #+#    #+#             */
/*   Updated: 2026/05/14 17:12:21 by danicamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_file(int fd, char *stash)
{
	char	*temp;
	int		bytes;

	if (stash && ft_strchr(stash, '\n'))
		return (stash);
	bytes = 1;
	temp = malloc(BUFFER_SIZE + 1);
	if (!temp)
		return (NULL);
	while ((!stash || !ft_strchr(stash, '\n')) && bytes > 0)
	{
		bytes = read(fd, temp, BUFFER_SIZE);
		if (bytes == -1 || (!stash && bytes == 0))
			return (free(temp), free(stash), NULL);
		temp[bytes] = '\0';
		stash = ft_strjoin(stash, temp);
	}
	free(temp);
	return (stash);
}

static char	*line(char *stash)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!stash)
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	line = malloc(i + 1);
	while (j < i)
	{
		line[j] = stash[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

static char	*rest(char *stash)
{
	char	*temp;
	int		i;
	int		j;

	temp = NULL;
	i = 0;
	j = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
		return (free(stash), NULL);
	temp = malloc(ft_strlen(stash) - i + 1);
	i++;
	while (stash[i])
		temp[j++] = stash[i++];
	temp[j] = '\0';
	free(stash);
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	*stash[1024];
	char		*ret;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	stash[fd] = read_file(fd, stash[fd]);
	if (!stash[fd])
		return (stash[fd] = NULL, NULL);
	if (!stash[fd][0])
		return (free(stash[fd]), stash[fd] = NULL, NULL);
	ret = line(stash[fd]);
	stash[fd] = rest(stash[fd]);
	return (ret);
}
