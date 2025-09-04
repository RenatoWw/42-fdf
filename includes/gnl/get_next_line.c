/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 15:34:56 by ranhaia-          #+#    #+#             */
/*   Updated: 2025/08/01 15:27:55 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

static char	*parse_line(char **line, char *buffer)
{
	char	*leftover;
	int		i;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	*line = ft_substr(buffer, 0, i + 1);
	if (!*line)
		return (free_mem(buffer, NULL));
	leftover = ft_substr(buffer, i + 1, ft_strlen(buffer));
	if (!leftover)
		return (free_mem(buffer, leftover));
	free(buffer);
	return (leftover);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (buffer == NULL)
		buffer = ft_strdup("");
	buffer = read_buffer(fd, buffer);
	if (buffer == NULL)
		return (NULL);
	if (ft_strlen(buffer) == 0)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	buffer = parse_line(&line, buffer);
	return (line);
}

// int     main(void)
// {
//         int             fd;
//         char    *line;

//         fd = open("arquivo.txt", O_RDONLY);
//         if (fd == -1)
//             return (1);
//         // Loop para ler todas as linhas do arquivo
//         while ((line = get_next_line(fd)))
//         {
//                 printf("%s", line);
//                 free(line);
//         }
//         // A última chamada a get_next_line retornará NULL
//         // e o buffer estático interno será liberado.
//         close(fd);
//         return (0);
// }
