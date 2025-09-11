/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:42:31 by ranhaia-          #+#    #+#             */
/*   Updated: 2025/09/11 02:46:16 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// int	create_trgb(int t, int r, int g, int b)
// {
// 	return (t << 24 | r << 16 | g << 8 | b);
// }

int	ft_atoi_hex(char *str)
{
	
}

void	allocate_colors(t_map *map)
{
	int		i;
	int		j;

	map->colors = malloc((map->height + 1) * sizeof(int *));
	i = 0;
	while (i < map->height)
		map->colors[i++] = malloc(map->width * sizeof(int));
	map->colors[i] = NULL;
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			map->colors[i][j] = 0xFFFF00;
			j++;
		}
		i++;
	}
}

void	fill_color_line(int *color_array, char **newline)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (newline[i])
	{
		j = 0;
		while (newline[i][j])
		{
			j++;
			if (newline[i][j - 1] == ',' && newline[i][j])
			{
				str = ft_substr(newline[i], j, ft_strlen(newline[i]));
				printf("%s\n", str);
				free(str);
			}
		}
		i++;
	}
	free_split(newline);
}

void	*color_filler(t_map *map, char *map_name)
{
	int		i;
	int		fd;
	char	*line;
	char	*newline;

	i = 0;
	fd = open(map_name, O_RDONLY);
	allocate_colors(map);
	while (i < map->height)
	{
		line = get_next_line(fd);
		if (!line)
			return (free_map(map, i));
		newline = ft_strtrim(line, " \n");
		fill_color_line(map->colors[i], ft_split(newline, ' '));
		free(line);
		free(newline);
		i++;
	}
	// free_gnl
	line = get_next_line(fd);
	free(line);
	return (0);
}
