#include "get_next_line.h"

/*
** init_buffer() allocates memory for the buffer.
**
** buffer_zize: default buffer size, or size provided with -D BUFFER_SIZE=n
** Return: ptr to the memory allocated
*/

int	len_line(char *line)
{
	int len_line;

	len_line = 0;
	while(line++)
		len_line ++;
	return (len_line);
}
void	*allocate_memory(size_t num_bytes)
{
	void	*space;

	space = (void *)malloc(size_of (num_bytes));
	if (!space)
		return (NULL);
	return (space);
}

char	get_line(char *buffer, int index)
{
	unsigned char	*line;
	size_t	len_line;
	int	last_line;

	len_line = 0;

	// marker for the new line
	last_line = 0;

	// calculate the line lenth for memory allocation
	while (buffer[index] != '/0' || index <= BUFFER_SIZE - 1)
	{
		len_line++;
		index++;

		// check do we reach the EOF
		if (index == BUFFER_SIZE - 1 && index != '\0')

			// change marker TRUE
			last_line = 1;

	// allocate memory for the line
	line = allocate_memory(len_line + 1); // +1 for '\n' or '\0'

	// copy line from the buffer to the str 'line'
	while (len_line > 0)
		line[--len_line] = buffer[index--];

	// if we found the last line, append EOF
	if (last_line)
		line[len_line] = '\0';
	
	// if NOT the last line, just append '\n'
	else
		line[len_line] = '\n';

	return (line);
}
