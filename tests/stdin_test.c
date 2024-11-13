// stdin_test.c
#include "tests.h"

static void	test_stdin(void)
{
	char	*line;
	int	line_number = 1;

	printf("Testing stdin (Type some lines and press Ctrl+D to end):\n");
	while ((line = get_next_line(STDIN_FILENO)) != NULL)
	{
		printf("Line %d: %s", line_number, line);
		free(line);
		line_number++;
	}
	printf("\n");
}

int	stdin_test(void)
{

	// Test reading from standard input
	test_stdin();

	return 0;
}
