/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_allocator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 16:35:50 by ranhaia-          #+#    #+#             */
/*   Updated: 2025/09/04 18:01:33 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

static void	free_gnl(int fd, char *line)
{
	while (1)
	{
		line = get_next_line(fd);
		free(line);
		if (!line)
			break ;
	}
	close(fd);
}

t_map	*allocate_map(char *map_name)
{
	t_map	*map;
	char	*line;
	int		fd;
	int		i;

	fd = open(map_name, O_RDONLY);
	if (fd < 0)
		return (NULL);
	map = malloc(sizeof(t_map));
	map->height = line_counter(map_name);
	map->map = malloc(map->height * sizeof(int *));
	i = 0;
	while (i < map->height)
	{
		line = get_next_line(fd);
		if (!line)
			return (free_map(map, i));
		map->width = num_counter(line);
		map->map[i] = malloc(map->width * sizeof(int));
		i++;
		free(line);
	}
	free_gnl(fd, line);
	return (map);
}
