/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 18:42:11 by ranhaia-          #+#    #+#             */
/*   Updated: 2025/09/12 15:32:55 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	determine_z_values(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	map->z_min = map->map[0][0];
	map->z_max = map->map[0][0];
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->map[i][j] > map->z_max)
				map->z_max = map->map[i][j];
			if (map->map[i][j] < map->z_min)
				map->z_min = map->map[i][j];
			j++;
		}
		i++;
	}
}

void	isometric_projection(int *x, int *y, int z, t_map *map)
{
	int		tmp;
	float	final_z;

	final_z = ((float)z - map->z_min) / (map->z_max - map->z_min);
	if (map->z_max <= 0)
		final_z = z;
	else if (map->z_max <= 10 && map->z_max > 0)
		final_z *= 150;
	else
		final_z *= 100;
	tmp = *x;
	*x = (tmp - *y) * cos(0.523599);
	*y = (tmp + *y) * sin(0.523599) - final_z;
}

void	draw_map(t_data *data, t_map *map, int offset_x, int offset_y)
{
	int		i;
	int		j;
	int		zoom;
	t_point	p1;
	t_point	p2;

	determine_z_values(map);
	zoom = WINDOW_WIDTH / map->width;
	if ((WINDOW_WIDTH / map->width) > (WINDOW_HEIGHT / map->height))
		zoom = WINDOW_HEIGHT / map->height;
	offset_x = (WINDOW_WIDTH - (map->width * (zoom * 0.3))) / 2;
	offset_y = (WINDOW_HEIGHT - (map->height * (zoom * 0.5))) / 2;
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			p1.x = j * (zoom * 0.5);
			p1.y = i * (zoom * 0.5);
			isometric_projection(&p1.x, &p1.y, map->map[i][j], map);
			p1.x += offset_x;
			p1.y += offset_y;
			if ((j + 1) != map->width)
			{
				p2.x = (j + 1) * (zoom * 0.5);
				p2.y = i * (zoom * 0.5);
				isometric_projection(&p2.x, &p2.y, map->map[i][j + 1], map);
				p2.x += offset_x;
				p2.y += offset_y;
				draw_line(data, p1, p2, map->colors[i][j]);
			}
			if ((i + 1) != map->height)
			{
				p2.x = j * (zoom * 0.5);
				p2.y = (i + 1) * (zoom * 0.5);
				isometric_projection(&p2.x, &p2.y, map->map[i + 1][j], map);
				p2.x += offset_x;
				p2.y += offset_y;
				draw_line(data, p1, p2, map->colors[i][j]);
			}
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(data->mlx, data->window, data->img, 0, 0);
	free_map(map, map->height);
}
