/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:22:25 by ranhaia-          #+#    #+#             */
/*   Updated: 2025/08/19 17:33:02 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx/mlx.h"
#include "fdf.h"

typedef struct	s_data
{
	void	*mlx;
	void	*window;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}		t_data;

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

// void	ft_draw_vertical_line(t_data *data, int x0, int y0, int x1, int y1, int color)
// {
// 	int	dy;
// 	int	x;
// 	int	dx;
// 	int	i;
// 	int	p;
// 	int	dir;
// 	int	temp;

// 	if (y0 > y1)
// 	{
// 		temp = x0;
// 		x0 = x1;
// 		x1 = temp;
// 		temp = y0;
// 		y0 = y1;
// 		y1 = temp;
// 	}
// 	dy = y1 - y0;
// 	dx = x1 - x0;
// 	if (dx < 0)
// 		dir = -1;
// 	else
// 		dir = 1;
// 	dx *= dir;
// 	if (dy != 0)
// 	{
// 		x = x0;
// 		i = 0;
// 		p = 2 * dx - dy;
// 		while (i < dy + 1)
// 		{
// 			ft_pixel_put(data, x, y0 + i, color);
// 			if (p >= 0)
// 			{
// 				x += dir;
// 				p = p - 2 * dy;
// 			}
// 			p = p + 2 * dx;
// 			i++;
// 		}
// 	}
// }

// void	ft_draw_horizontal_line(t_data *data, int x0, int y0, int x1, int y1, int color)
// {
// 	int	dy;
// 	int	y;
// 	int	dx;
// 	int	i;
// 	int	p;
// 	int	dir;
// 	int	temp;

// 	if (x0 > x1)
// 	{
// 		temp = x0;
// 		x0 = x1;
// 		x1 = temp;
// 		temp = y0;
// 		y0 = y1;
// 		y1 = temp;
// 	}
// 	dy = y1 - y0;
// 	dx = x1 - x0;
// 	if (dy < 0)
// 		dir = -1;
// 	else
// 		dir = 1;
// 	dy *= dir;
// 	if (dx != 0)
// 	{
// 		y = y0;
// 		i = 0;
// 		p = 2 * dy - dx;
// 		while (i < dx + 1)
// 		{
// 			ft_pixel_put(data, x0 + i, y, color);
// 			if (p >= 0)
// 			{
// 				y += dir;
// 				p = p - 2 * dx;
// 			}
// 			p = p + 2 * dy;
// 			i++;
// 		}
// 	}
// }

// void	ft_draw_line(t_data *data, int x0, int x1, int y0, int y1, int color)
// {
// 	if (abs(x1 - x0) > abs(y1 - y0))
// 		ft_draw_horizontal_line(data, x0, y0, x1, y1, color);
// 	else
// 		ft_draw_vertical_line(data, x0, y0, x1, y1, color);
// }

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
	t_data	data;

	data.mlx = mlx_init();
	data.window = mlx_new_window(data.mlx, 1280, 800, "42 sp");
	data.img = mlx_new_image(data.mlx, 1280, 800);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
	x = 200;
	y = 0;
	color = 0x0000FFFF;
	// printf("%d\n", data.line_length);
	ft_draw_line(&data, 800, 300, 200, 300);
	ft_draw_line(&data, 500, 700, 500, 100);
	ft_draw_line(&data, 100, 100, 500, 700);
	ft_draw_line(&data, 800, 500, 100, 200);
	ft_draw_line(&data, 500, 800, 200, 100);
	ft_draw_line(&data, 300, 700, 400, 600);
	// printf("white color: %x\n", 0x00000000);
	// printf("red color: %x\n", 0x00FF0000);
	// printf("green color: %x\n", 0x0000FF00);
	// printf("blue color: %x\n", 0x000000FF);
	mlx_put_image_to_window(data.mlx, data.window, data.img, 0, 0);
	mlx_key_hook(data.window, &key_handler, &data);
	mlx_loop(data.mlx);
	return (0);
}
