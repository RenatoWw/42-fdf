/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 18:42:11 by ranhaia-          #+#    #+#             */
/*   Updated: 2025/09/01 21:11:58 by ranhaia-         ###   ########.fr       */
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

	tmp = *x;
	*x = (tmp - *y) * cos(0.523599);
	*y = (tmp + *y) * sin(0.523599) - z;
}

void	draw_map(t_data *data, t_map *map, int x, int y)
{
	int		i;
	int		j;
	int		color;
	t_point	first_line;
	t_point	second_line;

	color = 0x000000FF;
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			first_line.x = x;
			first_line.y = y;
			second_line.x = x + 50;
			second_line.y = y;
			isometric_projection(&first_line.x, &first_line.y, map->map[i][j]);
			isometric_projection(&second_line.x, &second_line.y, map->map[i][j]);
			draw_line(data, first_line, second_line, color);
			// second_line.x = x;
			second_line.y = y + 50;
			isometric_projection(&first_line.x, &first_line.y, map->map[i][j]);
			isometric_projection(&second_line.x, &second_line.y, map->map[i][j]);
			draw_line(data, first_line, second_line, color);
			// if ((i + 1) == map->height)
			// {
			// 	first_line.x = x;
			// 	first_line.y = y + 50;
			// 	second_line.x = x + 50;
			// 	second_line.y = y + 50;
			// 	draw_line(data, first_line, second_line, color);
			// }
			// if ((j + 1) == map->width)
			// {
			// 	first_line.x = x + 50;
			// 	first_line.y = y;
			// 	second_line.x = x + 50;
			// 	second_line.y = y + 50;
			// 	draw_line(data, first_line, second_line, color);
			// }
			x += 50;
			j++;
		}
		y = y + 50;
		x = WINDOW_WIDTH / 8;
		i++;
	}
	mlx_put_image_to_window(data->mlx, data->window, data->img, 0, 0);
}
