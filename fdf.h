/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 15:26:28 by ranhaia-          #+#    #+#             */
/*   Updated: 2025/08/27 20:22:29 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include "mlx/mlx.h"
# include "libft/libft.h"
# include "gnl/get_next_line.h"

typedef struct s_data
{
	void	*mlx;
	void	*window;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}		t_data;

typedef struct s_map
{
	int	width;
	int	height;
	int	**map;

}		t_map;

typedef struct s_point
{
	int	x;
	int	y;
	int	color;
}		t_point;

# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 800

t_map	*map_parser(char *map_name);
void	draw_map(t_data *data, t_map *map, int x, int y);
void	draw_line(t_data *data, int x1, int y1, int x2, int y2);
void	ft_pixel_put(t_data *data, int x, int y, int color);
void	free_map(t_map *map);
void	init_mlx(t_data *data);

#endif