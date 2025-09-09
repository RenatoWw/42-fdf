/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 15:26:28 by ranhaia-          #+#    #+#             */
/*   Updated: 2025/09/09 20:29:41 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include "includes/mlx/mlx.h"
# include "includes/libft/libft.h"
# include "includes/gnl/get_next_line.h"

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
	int		width;
	int		height;
	int		**map;
	int		**colors;
	float	z_min;
	float	z_max;

}		t_map;

typedef struct s_point
{
	int	x;
	int	y;
	int	color;
}		t_point;

# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 800

t_map	*allocate_map(char *map_name);
void	allocate_colors(t_map *map);
void	fill_colors(t_map *map, char *map_name);
void	draw_map(t_data *data, t_map *map, int x, int y);
void	draw_line(t_data *data, t_point p1, t_point p2, int color);
void	ft_pixel_put(t_data *data, int x, int y, int color);
void	*free_map(t_map *map, int len);
void	init_mlx(t_data *data);
void	handle_error(int fd, char *line, t_map *map, int i);
void	*map_filler(t_map *map, int fd);
void	free_split(char **line);
int		num_counter(char *line);
int		line_counter(char *map_name);
int		create_trgb(int t, int r, int g, int b);
int		validate_map(char *map_name);

#endif