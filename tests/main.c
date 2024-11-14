// main.c

#include <stdio.h>
#include <fcntl.h>
#include "../get_next_line.h"

// multiple_empty_lines.txt
// multiple_long_lines.txt
// multiple_short_lines.txt
// single_empty_line.txt
// single_long_line.txt
// single_short_line.txt

int main(void)
{
	int fd;
	char *line;

	// ------- REPLACE TEXT FILE HERE -------
	fd = open("single_short_line.txt", O_RDONLY);
	if (fd == -1)
	{
	perror("Error opening file");
		return (1);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
