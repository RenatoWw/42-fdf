/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 14:04:31 by ranhaia-          #+#    #+#             */
/*   Updated: 2025/09/01 20:58:03 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	cfree(int fd, char *line)
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

int	num_counter(char *line)
{
	int	num_count;
	int	i;
	int	trigger;

	num_count = 0;
	trigger = 0;
	i = 0;
	while (line[i])
	{
		if ((line[i] != ' ' && line[i] != '\n') && trigger == 0)
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

int	line_counter(char *map_name)
{
	int		len;
	int		fd;
	char	*line;

	fd = open(map_name, O_RDONLY);
	if (!fd || !map_name)
		return (1);
	len = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (num_counter(line) == 0)
		{
			free(line);
			break ;
		}
		len++;
		free(line);
	}
	cfree(fd, line);
	return (len);
}

static int	copy_map(t_map *map, char **clean_line, int *i)
{
	int			j;
	static int	old_j = 0;

	j = 0;
	while (clean_line[j] != NULL)
	{
		map->map[*i][j] = ft_atoi(clean_line[j]);
		j++;
	}
	if (*i > 0 && j != old_j)
	{
		j = 0;
		while (clean_line[j] != NULL)
			free(clean_line[j++]);
		free(clean_line);
		return (1);
	}
	old_j = j;
	j = 0;
	while (clean_line[j] != NULL)
		free(clean_line[j++]);
	free(clean_line);
	return (0);
}

t_map	*map_parser(char *map_name, int fd)
{
	int		i;
	char	*line;
	t_map	*map;

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
		map->map[i] = malloc(num_counter(line) * sizeof(int));
		if (copy_map(map, ft_split(line, ' '), &i) == 1)
		{
			cfree(fd, line);
			handle_error(fd, line, map, i + 1);
		}
		free(line);
		i++;
	}
	cfree(fd, line);
	return (map);
}
