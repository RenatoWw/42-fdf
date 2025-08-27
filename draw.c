/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 18:42:11 by ranhaia-          #+#    #+#             */
/*   Updated: 2025/08/27 20:26:42 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dest;

	if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
	{
		dest = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int *)dest = color;
	}
}

void	draw_line(t_data *data, int x1, int y1, int x2, int y2)
{
	int	i;
	int	step;
	float	x;
	float	y;

	if (abs(x2 - x1) >= abs(y2 - y1))
		step = abs(x2 - x1);
	else
		step = abs(y2 - y1);
	x = x1;
	y = y1;
	i = 0;
	while (i <= step)
	{
		ft_pixel_put(data, round(x), round(y), 0x0000FFFF);
		x += (x2 - x1) / (float)step;
		y += (y2 - y1) / (float)step;
		i++;
	}
}
// substituir o x e o y pelo struct s_point?
void	draw_map(t_data *data, t_map *map, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	printf("%d %d", map->height, map->width);
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			ft_pixel_put(data, x, y, 0x00FFFFFF);
			draw_line(data, x, y, x + 50, y);
			draw_line(data, x, y, x, y + 50);
			if ((j + 1) == map->width)
				draw_line(data, x + 50, y, x + 50, y + 50);
			if ((i + 1) == map->height)
				draw_line(data, x, y + 50, x + 50, y + 50);
			x += 50;
			j++;
		}
		y = y + 50;
		x = WINDOW_WIDTH / 4;
		i++;
	}
	mlx_put_image_to_window(data->mlx, data->window, data->img, 0, 0);
}
