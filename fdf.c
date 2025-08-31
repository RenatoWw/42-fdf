/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:22:25 by ranhaia-          #+#    #+#             */
/*   Updated: 2025/08/31 16:33:15 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx/mlx.h"

int	key_handler(int keycode, t_data *data)
{
	if (keycode == 65307)
	{
		mlx_destroy_image(data->mlx, data->img);
		mlx_destroy_window(data->mlx, data->window);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		exit(0);
	}
	else
		write(1, "Tecla pressionada\n", 18);
	return (0);
}

// fórmula isométrica
// screen_x = (x - y) * cos(ângulo)
// screen_y = (x + y) * sin(ângulo) - z

// function to parse if map is not an rectangle and if it's empty
// parse spaces in final of the function
// parse invalid characters
// parse if line is empty
// parse still reachable bytes
// offset and zoom
// normalizar o mapa

int	main(void)
{
	int		x;
	int		y;
	t_map	*map;
	t_data	data;

	init_mlx(&data);
	map = map_parser("test_maps/42.fdf");
	x = WINDOW_WIDTH / 4;
	y = WINDOW_HEIGHT / 4;
	draw_map(&data, map, x, y);
	free_map(map);
	mlx_key_hook(data.window, &key_handler, &data);
	mlx_loop(data.mlx);

	return (0);
}
