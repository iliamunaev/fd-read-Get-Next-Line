/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imunaev- <imunaev-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 20:39:00 by imunaev-          #+#    #+#             */
/*   Updated: 2024/11/13 13:27:50 by imunaev-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ssize_t read(int fildes, void *buf, size_t nbyte);
// If the value of nbyte is greater than {SSIZE_MAX}, the result is implementation-defined.

/*
** get_next_line() reads the text file pointed to by the f one line at a time.
**
** fd: ile descriptor.
** Return: One line that was read, one line at a time,
** NULL if there is nothing else to read, or an error occurred.
*/

#include "get_next_line.h"

char	*get_next_line(int fd)
{
    static char	*main_buf;  // Static buffer for leftover data
    char	    *temp_buf;  // Temporary buffer for reading in chunks
    char	    *line;
    ssize_t     bytes_read;

    main_buf = NULL;
    if (fd < 0 || BUFFER_SIZE <= 0) // Validate file descriptor and BUFFER_SIZE
        return (NULL);
    if (line = check_main_buf(main_buf))
        return (line);
    temp_buf = malloc(BUFFER_SIZE + 1); // Allocate memory for the temporary buffer
    if (!temp_buf)
        return (NULL);
    while (get_data(fd, temp_buf, BUFFER_SIZE)) > 0) // Read data from the file descriptor
    {

        temp_buf[bytes_read] = '\0'; // Null-terminate the buffer
        main_buf = ft_strjoin_and_free(main_buf, temp_buf); // Append temp_buf to main_buf
        if (!main_buf)
        {
            free(temp_buf);
            return (NULL);
        }
        if ((line = get_line(main_buf))) // Check if a complete line can be extracted
        {
            main_buf = update_main_buf(main_buf); // Update main_buf to hold any leftover data
            free(temp_buf);
            return (line);
        }
    }
    free(temp_buf);
    if (get_data == -1) // Handle read error
    {
        free(main_buf);
        main_buf = NULL;
        return (NULL);
    }
    if (main_buf && *main_buf != '\0') // If there's leftover data without a newline
    {
        line = ft_strdup(main_buf);
        free(main_buf);
        main_buf = NULL;
        return (line);
    }
    free(main_buf); // No more data to read; clean up and return NULL
    main_buf = NULL;
    return (NULL);
}
