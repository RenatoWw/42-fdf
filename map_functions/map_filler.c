/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_filler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 19:14:00 by ranhaia-          #+#    #+#             */
/*   Updated: 2025/09/12 14:51:11 by ranhaia-         ###   ########.fr       */
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
}

static void	fill_line(int *map, char **line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		map[i] = ft_atoi(line[i]);
		i++;
	}
	free_split(line);
}

void	*map_filler(t_map *map, int fd)
{
	char	*line;
	char	*newline;
	int		i;

	i = 0;
	while (map->map[i])
	{
		line = get_next_line(fd);
		if (!line)
			return (free_map(map, i));
		newline = ft_strtrim(line, " \n");
		fill_line(map->map[i], ft_split(newline, ' '));
		free(line);
		free(newline);
		i++;
	}
	free_gnl(fd, line);
	return (0);
}
