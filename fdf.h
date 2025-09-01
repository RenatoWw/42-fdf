/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 15:26:28 by ranhaia-          #+#    #+#             */
/*   Updated: 2025/09/01 18:08:21 by ranhaia-         ###   ########.fr       */
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

t_map	*map_parser(char *map_name, int fd);
void	draw_map(t_data *data, t_map *map, int x, int y);
void	draw_line(t_data *data, int x1, int y1, int x2, int y2);
void	ft_pixel_put(t_data *data, int x, int y, int color);
void	*free_map(t_map *map, int len);
void	init_mlx(t_data *data);
void	handle_error(int fd, char *line, t_map *map, int i);
int		num_counter(char *line);
int		line_counter(char *map_name);

#endif