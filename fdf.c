/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:22:25 by ranhaia-          #+#    #+#             */
/*   Updated: 2025/08/20 21:36:07 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx/mlx.h"

int	key_handler(int keycode, t_data *data)
{
	if (keycode == 65307)
	{
		mlx_destroy_window(data->mlx, data->window);
		exit(0);
	}
	else if (keycode == 97)
		write(1, "Tecla pressionada: a\n", 21);
	return (0);
}

void	ft_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dest;

	dest = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dest = color;
}

void	ft_draw_line(t_data *data, int x1, int y1, int x2, int y2)
{
	int	dx;
	int	dy;
	int	i;
	int	step;
	float	xin;
	float	yin;
	float	x;
	float	y;

	dx = x2 - x1;
	dy = y2 - y1;
	if (abs(dx) >= abs(dy))
		step = abs(dx);
	else
		step = abs(dy);
	xin = dx / (float)step;
	yin = dy / (float)step;
	x = x1;
	y = y1;
	i = 0;
	while (i <= step)
	{
		ft_pixel_put(data, round(x), round(y), 0x00FFFF00);
		x += xin;
		y += yin;
		i++;
	}
}

int	main(void)
{
	int		x;
	int		y;
	int		color;
	int		**map;
	int		i;
	int		j;
	// t_data	data;

	// data.mlx = mlx_init();
	// data.window = mlx_new_window(data.mlx, 1280, 800, "42 sp");
	// data.img = mlx_new_image(data.mlx, 1280, 800);
	// data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
	x = 200;
	y = 0;
	color = 0x0000FFFF;
	map = map_parser("test_maps/42.fdf");
	// while (map[i] != NULL)
	// {
		// 	// printf("%d ", map[i]);
		// 	i++;
		// }
		// while (i > 0)
		// {
			// 	free(map[i--]);
			// }
	i = 0;
	j = 0;
	while (i < 11)
	{
		j = 0;
		while (j < 19)
		{
			printf("%d", map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	// while (i < 15)
	// {
	// 	free(map[i]);
	// 	i++;
	// }
	// free(map);
	// printf("%d\n", data.line_length);
	// ft_draw_line(&data, 800, 300, 200, 300);
	// ft_draw_line(&data, 500, 700, 500, 100);
	// ft_draw_line(&data, 100, 100, 500, 700);
	// ft_draw_line(&data, 800, 500, 100, 200);
	// ft_draw_line(&data, 500, 800, 200, 100);
	// ft_draw_line(&data, 300, 700, 400, 600);
	// printf("white color: %x\n", 0x00000000);
	// printf("red color: %x\n", 0x00FF0000);
	// printf("green color: %x\n", 0x0000FF00);
	// printf("blue color: %x\n", 0x000000FF);
	// mlx_put_image_to_window(data.mlx, data.window, data.img, 0, 0);
	// mlx_key_hook(data.window, &key_handler, &data);
	// mlx_loop(data.mlx);
	// mlx_clear_window(&data.mlx, &data.window);
	// mlx_destroy_window(&data.mlx, &data.window);
	return (0);
}
