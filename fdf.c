/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:22:25 by ranhaia-          #+#    #+#             */
/*   Updated: 2025/09/04 20:10:12 by ranhaia-         ###   ########.fr       */
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
			printf("%d ", map->map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

// validate height and width
// if ok, alloc the map
// fill the map after allocating

int	main(int argc, char *argv[])
{
	int		fd;
	t_map	*map;
	int		x;
	int		y;
	int		color;
	t_data	data;

	fd = open(argv[1], O_RDONLY);
	fd_validate(argc, fd);
	validate_map(argv[1]);
	map = allocate_map(argv[1]);
	if (!map)
		return (1);
	map_filler(map, fd);
	if (!map)
		return (1);
	// print_map(map);
	init_mlx(&data);
	x = WINDOW_WIDTH / 4;
	y = WINDOW_HEIGHT / 4;
	color = create_trgb(1, 255, 50, 20);
	printf("\ncolor: %d\n", color);
	draw_map(&data, map, x, y);
	free_map(map, map->height);
	mlx_key_hook(data.window, &key_handler, &data);
	mlx_loop(data.mlx);
	close(fd);
	return (0);
}
