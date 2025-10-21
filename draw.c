/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 18:42:11 by ranhaia-          #+#    #+#             */
/*   Updated: 2025/10/21 16:09:14 by ranhaia-         ###   ########.fr       */
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
	int		tmp_x;
	float	final_z;

	final_z = (z - map->z_min) / (map->z_max - map->z_min);
	if (map->z_max <= 0)
		final_z = z;
	else if (map->z_max <= 10 && map->z_max > 0)
		final_z *= 150;
	else
		final_z *= 100;
	tmp_x = *x;
	*x = (tmp_x - *y) * cos(0.523599);
	*y = (tmp_x + *y) * sin(0.523599) - final_z;
}

void	initialize_points(t_point *p1, t_map *map, int i, int j)
{
	int	zoom;
	int	offset_x;
	int	offset_y;

	zoom = WINDOW_WIDTH / map->width;
	if ((WINDOW_WIDTH / map->width) > (WINDOW_HEIGHT / map->height))
		zoom = WINDOW_HEIGHT / map->height;
	offset_x = (WINDOW_WIDTH - (map->width * (zoom * 0.3))) / 2;
	offset_y = (WINDOW_HEIGHT - (map->height * (zoom * 0.5))) / 2;
	p1->x = j * (zoom * 0.5);
	p1->y = i * (zoom * 0.5);
	isometric_projection(&p1->x, &p1->y, map->map[i][j], map);
	p1->x += offset_x;
	p1->y += offset_y;
}

void	draw_map(t_data *data, t_map *map, int i, int j)
{
	t_point	p1;
	t_point	p2;

	i = -1;
	while (++i < map->height)
	{
		j = -1;
		while (++j < map->width)
		{
			initialize_points(&p1, map, i, j);
			if ((j + 1) != map->width)
			{
				initialize_points(&p2, map, i, j + 1);
				draw_line(data, p1, p2, map->colors[i][j]);
			}
			if ((i + 1) != map->height)
			{
				initialize_points(&p2, map, i + 1, j);
				draw_line(data, p1, p2, map->colors[i][j]);
			}
		}
	}
	mlx_put_image_to_window(data->mlx, data->window, data->img, 0, 0);
	free_map(map, map->height);
}
