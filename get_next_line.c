/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imunaev- <imunaev-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 20:39:00 by imunaev-          #+#    #+#             */
/*   Updated: 2024/11/12 20:58:41 by imunaev-         ###   ########.fr       */
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

char *get_next_line(int fd)
{
    unsigned static char	main_buf[MAIN_BUF_SIZE]; // Static buffer for leftover data
    unsigned char	*temp_buf;                       // Temporary buffer for reading in chunks
    int	data;                                        // "Loop marker" for read status
    char	*line;
	int	head;
	int	tail;

	data = 1;
	line = NULL;
	head = 0;
	tail = 0;

	//


    // Allocate temporary buffer
    temp_buf = malloc(BUFFER_SIZE);
    if (!temp_buf)
        return (NULL);

    // Retrieve data until read() returns 0 (EOF)
    while (data)
    {
        // Process any complete lines already in MAIN_BUF
        while ((line = get_line(main_buf, head, tail)) != NULL)
        {
            free(temp_buf); // Free temp buffer if line is found
            return (line);  // Return the extracted line
        }

        // Read from fd into TEMP_BUF, returns number of bytes read or 0 for EOF
        data = read(fd, temp_buf, BUFFER_SIZE);

        if (data > 0)
            add_data(temp_buf, main_buf, head, tail); // Append TEMP_BUF contents to MAIN_BUF
        else
            return get_last_line(main_buf); // Return last line if no more data
    }

    // Free allocated memory and clean up
    free(temp_buf);
    clean_up(main_buf); // Reset or clear MAIN_BUF as needed

    return NULL; // Return NULL to indicate EOF or no more data
}
