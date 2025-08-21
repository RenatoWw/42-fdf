/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 14:04:31 by ranhaia-          #+#    #+#             */
/*   Updated: 2025/08/21 16:07:44 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	num_counter(char *line)
{
	int	num_count;
	int	i;
	int	trigger;

	num_count = 0;
	trigger = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && trigger == 0)
		{
			trigger = 1;
			num_count++;
		}
		if (line[i] == ' ')
			trigger = 0;
		i++;
	}
	return (num_count);
}

static int	line_counter(char *map_name)
{
	int		len;
	int		fd;
	char	*line;

	fd = open(map_name, O_RDONLY);
	if (!fd || !map_name)
		return (0);
	len = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		len++;
		free(line);
	}
	close(fd);
	return (len);
}

static void	copy_map(t_map *map, char **clean_line, int *i)
{
	int	j;

	j = 0;
	while (clean_line[j] != NULL)
	{
		map->map[*i][j] = ft_atoi(clean_line[j]);
		j++;
	}
	j = 0;
	while (clean_line[j] != NULL)
		free(clean_line[j++]);
	free(clean_line);
}

static void	cfree(int fd, char *line)
{
	line = get_next_line(fd);
	free(line);
	close(fd);
}

t_map	*map_parser(char *map_name)
{
	int		fd;
	int		i;
	char	*line;
	t_map	*map;

	fd = open(map_name, O_RDONLY);
	if (!fd)
		return (NULL);
	map = malloc(sizeof(t_map));
	map->height = line_counter(map_name);
	map->map = malloc(map->height * sizeof(int *));
	i = 0;
	while (i < map->height)
	{
		line = get_next_line(fd);
		if (!line)
			return (NULL);
		map->width = num_counter(line);
		map->map[i] = malloc(num_counter(line) * sizeof(int));
		copy_map(map, ft_split(line, ' '), &i);
		free(line);
		i++;
	}
	cfree(fd, line);
	return (map);
}
