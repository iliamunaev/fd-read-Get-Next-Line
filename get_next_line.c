/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imunaev- <imunaev-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 20:39:00 by imunaev-          #+#    #+#             */
/*   Updated: 2024/11/14 10:25:59 by imunaev-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** Reads a line from the file descriptor 'fd' and returns it.
** Returns NULL if there is nothing else to read or an error occurs.
*/

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*line;
	char		*buffer;
	ssize_t		bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(remainder, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			free(remainder);
			remainder = NULL;
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		remainder = ft_strjoin_and_free(remainder, buffer);
		if (!remainder)
		{
			free(buffer);
			return (NULL);
		}
	}
	free(buffer);
	line = extract_line(remainder);
	remainder = update_remainder(remainder);
	return (line);
}

/*
** Extracts the line from 'remainder' up to and including the newline character.
** Returns the extracted line.
*/
char	*extract_line(char *remainder)
{
	size_t	i;
	char	*line;

	if (!remainder || *remainder == '\0')
		return (NULL);
	i = 0;
	while (remainder[i] && remainder[i] != '\n')
		i++;
	if (remainder[i] == '\n')
		i++;
	line = (char *)malloc(i + 1);
	if (!line)
		return (NULL);
	ft_strncpy(line, remainder, i);
	return (line);
}

/*
** Updates 'remainder' by removing the extracted line.
** Returns the updated 'remainder'.
*/
char	*update_remainder(char *remainder)
{
	size_t	i;
	size_t	len;
	char	*new_remainder;

	i = 0;
	while (remainder[i] && remainder[i] != '\n')
		i++;
	if (remainder[i] == '\0')
	{
		free(remainder);
		return (NULL);
	}
	len = ft_strlen(remainder);
	new_remainder = (char *)malloc(len - i + 1);
	if (!new_remainder)
	{
		free(remainder);
		return (NULL);
	}
	ft_strcpy(new_remainder, remainder + i + 1);
	free(remainder);
	return (new_remainder);
}
