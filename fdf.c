/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:22:25 by ranhaia-          #+#    #+#             */
/*   Updated: 2025/08/21 19:08:47 by ranhaia-         ###   ########.fr       */
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

	if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
	{
		dest = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int *)dest = color;
	}
}

void	draw_line(t_data *data, int x1, int y1, int x2, int y2)
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
		ft_pixel_put(data, round(x), round(y), 0x0000FFFF);
		x += xin;
		y += yin;
		i++;
	}
}
// fórmula isométrica
// screen_x = (x - y) * cos(ângulo)
// screen_y = (x + y) * sin(ângulo) - z

int	main(void)
{
	int		x;
	int		y;
	int		color;
	t_map		*map;
	int		i;
	int		j;
	int		screen_x1;
	int		screen_y1;
	int		screen_x2;
	int		screen_y2;
	int		z1;
	int		z2;
	
	t_data	data;

	data.mlx = mlx_init();
	data.window = mlx_new_window(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "42 sp");
	data.img = mlx_new_image(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
	color = 0x0000FFFF;
	map = map_parser("test_maps/basictest.fdf");
	// z = map->map[i][j];
	// ft_pixel_put();
	// printf("%d", z);
	x = WINDOW_WIDTH / 4;
	y = WINDOW_HEIGHT / 4;
	i = 0;
	j = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			z1 = map->map[i][j];
			z2 = map->map[i][j + 1];
			screen_x1 = (j - i) * cos(30) - (WINDOW_WIDTH / 4);
			screen_y1 = (j + i) * sin (30) - z1 - (WINDOW_HEIGHT / 4);
			screen_x2 = ((j + 1) - i) * cos(30) - (WINDOW_WIDTH / 4);
			screen_y2 = ((j + 1) + i) * sin (30) - z2 - (WINDOW_HEIGHT / 4);
			// printf("%d\n%d\n%d\n%d", screen_x1, screen_y1, screen_x2, screen_y2);
			ft_pixel_put(&data, x, y, 0x00FFFFFF);
			// draw_line(&data, screen_x1, screen_y1, screen_x2, screen_y2);
			draw_line(&data, abs(screen_x1), abs(screen_y1), abs(screen_x2), abs(screen_y2));
			x += 50;
			j++;
		}
		y = y + 50;
		x = WINDOW_WIDTH / 4;
		i++;
	}
	printf("width: %d\nheight: %d", map->width, map->height);
	i = 0;
	while (i < map->height)
	{
		free(map->map[i]);
		i++;
	}
	free(map->map);
	free(map);
	// printf("%d\n", data.line_length);
	// draw_line(&data, 800, 300, 200, 300);
	// draw_line(&data, 500, 700, 500, 100);
	// draw_line(&data, 100, 100, 500, 700);
	// draw_line(&data, 800, 500, 100, 200);
	// draw_line(&data, 500, 800, 200, 100);
	// draw_line(&data, 300, 700, 400, 600);
	// printf("white color: %x\n", 0x00000000);
	// printf("red color: %x\n", 0x00FF0000);
	// printf("green color: %x\n", 0x0000FF00);
	// printf("blue color: %x\n", 0x000000FF);
	mlx_put_image_to_window(data.mlx, data.window, data.img, 0, 0);
	mlx_key_hook(data.window, &key_handler, &data);
	mlx_loop(data.mlx);
	mlx_clear_window(&data.mlx, &data.window);
	mlx_destroy_window(&data.mlx, &data.window);
	return (0);
}
