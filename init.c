/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 18:57:22 by ranhaia-          #+#    #+#             */
/*   Updated: 2025/08/31 04:12:47 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// retornar um int, caso algo de erro retornar 1, caso não, retornar zero
// ai eu faço um if na main com essa verificação
void	init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	data->window = mlx_new_window
		(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "FDF");
	data->img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	data->addr = mlx_get_data_addr
		(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
}

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->height)
		free(map->map[i++]);
	free(map->map);
	free(map);
}
