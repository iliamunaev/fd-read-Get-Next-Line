// read_error_test.c
#include "tests.h"

// Function to simulate a failing read (For demonstration purposes only)
static ssize_t	read(int fd, void *buf, size_t count)
{
	(void)fd;
	(void)buf;
	(void)count;
	return (-1); // Simulate read error
}

int	read_error_test(void)
{
	int	fd = open("test_file.txt", O_RDONLY);
	char	*line;

	if (fd < 0)
	{
		perror("Error opening file");
		return (1);
	}

	line = get_next_line(fd);
	if (line == NULL)
		printf("Test Passed: get_next_line returned NULL on read error.\n");
	else
	{
		printf("Test Failed: get_next_line did not return NULL on read error.\n");
		free(line);
	}

	close(fd);
	return (0);
}
