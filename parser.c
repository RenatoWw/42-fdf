/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 14:04:31 by ranhaia-          #+#    #+#             */
/*   Updated: 2025/08/20 21:28:18 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
		if (line[i] != ' ' && trigger == 0)
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
	if (!fd || !map_name)
		return (0);
	len = 0;
	while ((line = get_next_line(fd)))
	{
		len++;
		free(line);
	}
	close(fd);
	return (len);
}

int	**map_parser(char *map_name)
{
	int		**map;
	int		fd;
	int		i;
	int		j;
	char	*line;
	char	**clean_line;

	// abrir o arquivo na main
	fd = open(map_name, O_RDONLY);
	if (!fd)
		return (NULL);
	map = malloc(line_counter(map_name) * sizeof(int *));
	i = 0;
	while (i < line_counter(map_name))
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		map[i] = malloc(num_counter(line) * sizeof(int));
		printf("num: %d str: %s", num_counter(line) ,line);
		clean_line = ft_split(line, ' ');
		j = 0;
		while (clean_line[j] != NULL)
		{
			map[i][j] = ft_atoi(clean_line[j]);
			j++;
		}
		i++;
		j = 0;
		while (clean_line[j] != NULL)
			free(clean_line[j++]);
		free(clean_line);
		free(line);
	}
	close(fd);
	return (map);
}
