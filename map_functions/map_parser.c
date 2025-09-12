/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 15:38:27 by ranhaia-          #+#    #+#             */
/*   Updated: 2025/09/12 15:00:23 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

static void	free_gnl(int fd, char *line)
{
	while (1)
	{
		line = get_next_line(fd);
		free(line);
		if (!line)
			break ;
	}
}

int	num_counter(char *line)
{
	int	num_count;
	int	i;
	int	trigger;

	num_count = 0;
	trigger = 0;
	i = 0;
	while (line[i])
	{
		if ((line[i] != ' ' && line[i] != '\n') && trigger == 0)
		{
			trigger = 1;
			num_count++;
		}
		if (line[i] == ' ')
			trigger = 0;
		i++;
	}
	return (num_count);
}

int	line_counter(char *map_name)
{
	int		len;
	int		fd;
	char	*line;

	fd = open(map_name, O_RDONLY);
	if (fd < 0)
		return (1);
	len = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (num_counter(line) == 0)
		{
			free(line);
			break ;
		}
		len++;
		free(line);
	}
	close(fd);
	if (len == 0)
		exit(1);
	return (len);
}

static int	has_digits(char **line, char *linegnl, int fd)
{
	int	i;
	int	j;

	i = 0;
	while (line[i])
	{
		j = 0;
		while (line[i][j + 1])
		{
			if (line[i][j] == ',')
				break ;
			if (!ft_isdigit(line[i][j]) && line[i][0] != '-')
			{
				write(1, "Invalid character in map\n", 25);
				free_split(line);
				free_gnl(fd, linegnl);
				free(linegnl);
				exit (1);
			}
			j++;
		}
		i++;
	}
	free_split(line);
	return (0);
}

int	validate_map(char *map_name)
{
	int		fd;
	int		len;
	int		height;
	char	*line;

	fd = open(map_name, O_RDONLY);
	len = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		has_digits(ft_split(line, ' '), line, fd);
		len += num_counter(line);
		free(line);
	}
	height = line_counter(map_name);
	if (height == 0)
		height = 1;
	if ((len % height) != 0)
	{
		write(1, "Map is not an rectangle\n", 24);
		exit(1);
	}
	return (0);
}
