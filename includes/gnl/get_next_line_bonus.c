/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 15:34:56 by ranhaia-          #+#    #+#             */
/*   Updated: 2025/08/01 13:28:36 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static void	*free_mem(void *p1, void *p2)
{
	free(p1);
	free(p2);
	return (NULL);
}

static char	*read_buffer(int fd, char *buffer)
{
	char	*temp_buffer;
	int		iread;

	temp_buffer = malloc(BUFFER_SIZE + 1 * sizeof(char));
	if (!temp_buffer || !buffer)
		return (NULL);
	iread = 1;
	while (ft_strchr(buffer, '\n') == NULL && iread > 0)
	{
		iread = read(fd, temp_buffer, BUFFER_SIZE);
		if (iread == -1)
			return (free_mem(temp_buffer, buffer));
		temp_buffer[iread] = '\0';
		buffer = ft_strjoin(buffer, temp_buffer);
		if (!buffer)
			return (free_mem(temp_buffer, buffer));
	}
	free(temp_buffer);
	return (buffer);
}

static char	*parse_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = ft_substr(buffer, 0, i + 1);
	if (!line)
		return (NULL);
	return (line);
}

static char	*clean_buffer(char *buffer)
{
	char	*leftover;
	int		i;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	leftover = ft_substr(buffer, i + 1, ft_strlen(buffer) + 1);
	if (!leftover)
	{
		free(leftover);
		free(buffer);
		return (NULL);
	}
	free(buffer);
	return (leftover);
}

char	*get_next_line(int fd)
{
	static char	*buffer[MAX_FD];
	char		*line;

	line = NULL;
	if (fd < 0 || fd > MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	if (buffer[fd] == NULL)
		buffer[fd] = ft_strdup("");
	buffer[fd] = read_buffer(fd, buffer[fd]);
	if (buffer[fd] == NULL)
		return (NULL);
	if (ft_strlen(buffer[fd]) == 0)
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
		return (NULL);
	}
	line = parse_line(buffer[fd]);
	buffer[fd] = clean_buffer(buffer[fd]);
	return (line);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*line;
// 	int		i;

// 	fd = open("arquivo.txt", O_RDONLY);
// 	i = 0;
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	free(line);
// 	// line = get_next_line(fd);
// 	// printf("%s", line);
// 	// free(line);
// 	// line = get_next_line(fd);
// 	// printf("%s", line);
// 	// free(line);
// 	// line = get_next_line(fd);
// 	// printf("%s", line);
// 	// free(line);
// 	return (0);
// }
