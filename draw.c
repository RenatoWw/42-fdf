/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 18:42:11 by ranhaia-          #+#    #+#             */
/*   Updated: 2025/09/03 17:38:49 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dest;

	if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
	{
		dest = data->addr + (y * data->line_length + x
				* (data->bits_per_pixel / 8));
		*(unsigned int *)dest = color;
	}
}

void	draw_line(t_data *data, t_point p1, t_point p2, int color)
{
	int		i;
	int		step;
	float	x;
	float	y;

	if (abs(p2.x - p1.x) >= abs(p2.y - p1.y))
		step = abs(p2.x - p1.x);
	else
		step = abs(p2.y - p1.y);
	x = p1.x;
	y = p1.y;
	i = 0;
	while (i <= step)
	{
		ft_pixel_put(data, round(x), round(y), color);
		x += (p2.x - p1.x) / (float)step;
		y += (p2.y - p1.y) / (float)step;
		i++;
	}
}

// fórmula isométrica
// screen_x = (x - y) * cos(ângulo)
// screen_y = (x + y) * sin(ângulo) - z
// offset and zoom
// normalizar o mapa

void	isometric_projection(int *x, int *y, int z)
{
	int	tmp;
	int	offset_z;

	tmp = *x;
	offset_z = z * 20;
	*x = (tmp - *y) * cos(0.523599);
	*y = (tmp + *y) * sin(0.523599) - offset_z;
}

// arrumar com numeros negativos
// basic test nao ta funcionando

void	draw_map(t_data *data, t_map *map, int offset_x, int offset_y)
{
	int		i;
	int		j;
	int		zoom_x;
	int		zoom_y;
	int		zoom;
	int		color;
	t_point	first_point;
	t_point	second_point;
	t_point	third_point;

	color = 0x000000FF;
	zoom_x = WINDOW_WIDTH / map->width;
	zoom_y = WINDOW_HEIGHT / map->height;
	zoom = zoom_x;
	if (zoom_x > zoom_y)
		zoom = zoom_y;
	offset_x = (WINDOW_WIDTH - (map->width * (zoom * 0.3))) / 2;
	offset_y = (WINDOW_HEIGHT - (map->height * (zoom * 0.5))) / 2;
	i = 0;
	printf("zoom_x: %d\nzoom_y: %d\n", zoom_x, zoom_y);
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			first_point.x = j * (zoom * 0.5);
			first_point.y = i * (zoom * 0.5);
			isometric_projection(&first_point.x, &first_point.y, map->map[i][j]);
			first_point.x += offset_x;
			first_point.y += offset_y;
			if ((j + 1) != map->width)
			{
				second_point.x = (j + 1) * (zoom * 0.5);
				second_point.y = i * (zoom * 0.5);
				isometric_projection(&second_point.x, &second_point.y, map->map[i][j + 1]);
				second_point.x += offset_x;
				second_point.y += offset_y;
				draw_line(data, first_point, second_point, color);
			}
			if ((i + 1) != map->height)
			{
				third_point.x = j * (zoom * 0.5);
				third_point.y = (i + 1) * (zoom * 0.5);
				isometric_projection(&third_point.x, &third_point.y, map->map[i + 1][j]);
				third_point.x += offset_x;
				third_point.y += offset_y;
				draw_line(data, first_point, third_point, color);
			}
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(data->mlx, data->window, data->img, 0, 0);
}
