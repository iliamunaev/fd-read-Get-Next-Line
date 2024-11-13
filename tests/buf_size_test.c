// buf_size_test.c
#include "tests.h"

static void	test_file(const char *filename)
{
	int	fd = open(filename, O_RDONLY);
	char	*line;
	int	line_number = 1;

	if (fd < 0)
	{
		perror("Error opening file");
		return;
	}
	printf("Testing file: %s\n", filename);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("Line %d: %s", line_number, line);
		free(line);
		line_number++;
	}
	close(fd);
	printf("\n");
}

int	buf_size_test(void)
{
	// Test with various buffer sizes
	printf("Testing with BUFFER_SIZE = %d\n", BUFFER_SIZE);

	// Create and test with various files
	test_file("empty_file.txt");	   // Empty file
	test_file("short_lines.txt");	  // File with multiple short lines
	test_file("long_line.txt");		// File with a single long line (>2k characters)
	test_file("mixed_content.txt");	// File with mixed content

	return (0);
}
