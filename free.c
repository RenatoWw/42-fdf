/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 17:23:46 by ranhaia-          #+#    #+#             */
/*   Updated: 2025/09/01 18:09:14 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	*free_map(t_map *map, int len)
{
	int	i;

	i = 0;
	while (i < len)
		free(map->map[i++]);
	free(map->map);
	free(map);
	return (NULL);
}

void	handle_error(int fd, char *line, t_map *map, int i)
{
	write(1, "Invalid map\n", 12);
	free_map(map, i);
	free(line);
	while (line != NULL)
	{
		line = get_next_line(fd);
		free(line);
	}
	exit(0);
}
