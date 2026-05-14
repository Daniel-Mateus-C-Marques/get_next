/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danicamp <danicamp@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 12:43:10 by danicamp          #+#    #+#             */
/*   Updated: 2026/05/11 20:39:49 by danicamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	int	fd = open("./text.txt", O_RDONLY);
	char *line;
	
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	while (line)
	{
		line = get_next_line(fd);
		printf("%s", line);
		free(line);
	}
	close(fd);
	
}