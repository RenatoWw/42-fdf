/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:22:25 by ranhaia-          #+#    #+#             */
/*   Updated: 2025/09/11 02:44:31 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "includes/mlx/mlx.h"

int	key_handler(int keycode, t_data *data)
{
	if (keycode == 65307)
	{
		mlx_destroy_image(data->mlx, data->img);
		mlx_destroy_window(data->mlx, data->window);
		mlx_destroy_display(data->mlx);
		if (data->mlx != NULL)
			free(data->mlx);
		exit(0);
	}
	if (keycode == 65361)
	{
		write(1, "left\n", 5);
	}
	if (keycode == 65363)
	{
		write(1, "right\n", 6);
	}
	if (keycode == 65362)
	{
		write(1, "up\n", 3);
	}
	if (keycode == 65364)
	{
		write(1, "down\n", 5);
	}
	return (0);
}

void	fd_validate(int argc, int fd)
{
	if (argc != 2)
	{
		write(1, "Wrong number of arguments\n", 26);
		exit(1);
	}
	if (fd < 0)
	{
		write(1, "Map not found\n", 14);
		exit(1);
	}
}

void	print_map(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			printf("%d ", map->colors[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_data	data;
	t_map	*map;
	int		fd;
	int		x;
	int		y;

	fd = open(argv[1], O_RDONLY);
	fd_validate(argc, fd);
	validate_map(argv[1]);
	x = WINDOW_WIDTH / 4;
	y = WINDOW_HEIGHT / 4;
	map = allocate_map(argv[1]);
	if (!map)
		return (1);
	map_filler(map, fd);
	if (!map)
		return (1);
	color_filler(map, argv[1]);
	// printf("%d", 0x00FF00FF);
	// printf("\n%d\n", map->colors[5][2]);
	print_map(map);
	init_mlx(&data);
	draw_map(&data, map, x, y);
	mlx_key_hook(data.window, &key_handler, &data);
	mlx_loop(data.mlx);
	close(fd);
	return (0);
}
