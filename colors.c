/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:42:31 by ranhaia-          #+#    #+#             */
/*   Updated: 2025/09/09 20:29:47 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	allocate_colors(t_map *map)
{
	int		i;

	map->colors = malloc((map->height + 1) * sizeof(int *));
	i = 0;
	while (i < map->height)
		map->colors[i++] = malloc(map->width * sizeof(int));
	map->colors[i] = NULL;
}

// usar iterador i[3];

void	fill_colors(t_map *map, char *map_name)
{
	int		i;
	int		j;
	int		k;
	int		fd;
	char	*line;
	char	**newline;

	i = 0;
	fd = open(map_name, O_RDONLY);
	while (i < map->height)
	{
		line = get_next_line(fd);
		newline = ft_split(line, ' ');
		j = 0;
		while (newline[j])
		{
			k = 0;
			while (newline[j][k])
			{
				if (newline[j][k - 1] == ',')
				{
					printf("j: %d ", j);
					while (newline[j][k])
					{
						printf("%c", newline[j][k]);
						k++;
					}
					printf("\n");
					k++;
				}
				k++;
			}
			j++;
		}
		free_split(newline);
		if (!line)
			break ;
		free(line);
		i++;
	}
	line = get_next_line(fd);
	free(line);
}
