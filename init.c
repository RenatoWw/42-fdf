/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 18:57:22 by ranhaia-          #+#    #+#             */
/*   Updated: 2025/09/01 20:57:58 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	data->window = mlx_new_window
		(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "FDF");
	data->img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	data->addr = mlx_get_data_addr
		(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
}
