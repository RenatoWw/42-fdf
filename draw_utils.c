/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 15:18:27 by ranhaia-          #+#    #+#             */
/*   Updated: 2025/09/12 15:18:39 by ranhaia-         ###   ########.fr       */
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
