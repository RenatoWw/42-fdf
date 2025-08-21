/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 15:26:28 by ranhaia-          #+#    #+#             */
/*   Updated: 2025/08/21 17:51:24 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

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

typedef struct	s_map
{
	int	width;
	int	height;
	int	**map;
	
}		t_map;

# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 800

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include "mlx/mlx.h"
# include "libft/libft.h"
# include "gnl/get_next_line.h"

t_map	*map_parser(char *map_name);

#endif