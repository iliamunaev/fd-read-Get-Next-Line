
#include "get_next_line.h"

// ssize_t read(int fildes, void *buf, size_t nbyte);
// If the value of nbyte is greater than {SSIZE_MAX}, the result is implementation-defined.

/*
** get_next_line() reads the text file pointed to by the f one line at a time.
**
** fd: ile descriptor.
** Return: One line that was read, one line at a time,
** NULL if there is nothing else to read, or an error occurred.
*/
char	*get_next_line(int fd)
{

	// static buffer for store data and work with it
	unsigned static char	*buffer;

	int	next_l_index;

	// serves as marker for loop
	int	line;

	// allocate memory for the buffer (size_t for SSIZE_MAX)
	buffer = allocate_memory(BUFFER_SIZE);
	if (!buffer)
		return (NULL);

	next_l_index = 0;

	// retrive data untill read() return '0' (EOF)
	// if line found return line, else return '0'
	while (line)
	{
		// iterate through the buffer and find a line
		line = get_line(buffer, next_l_index);

		// adjust the index from which next itaration
		next_l_index += len_line(line); // 

		return (line);
	}

	// free memory allocated for the buffer
	clean_up(buffer);

	// nothing to read
	return (NULL);
}
