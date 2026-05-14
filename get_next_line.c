/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danicamp <danicamp@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 12:34:44 by danicamp          #+#    #+#             */
/*   Updated: 2026/05/11 21:48:49 by danicamp         ###   ########.fr       */
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
		if (bytes < 0)
			return (free(temp), NULL);
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

	i = 0;
	if (!stash)
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	line = malloc(i + 2);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	line[i] = stash[i];
	line[++i] = '\0';
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
	static char	*stash;
	char		*ret;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	stash = read_file(fd, stash);
	if (!stash)
		return (stash = NULL, NULL);
	ret = line(stash);
	stash = rest(stash);
	return (ret);
}
