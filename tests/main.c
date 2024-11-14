// main.c

// multiple_empty_lines.txt
// multiple_long_lines.txt
// multiple_short_lines.txt
// single_empty_line.txt
// single_long_line.txt
// single_short_line.txt

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "../get_next_line.h"

int main(int argc, char **argv)
{
    int fd;
    char *line;

    // Check if a filename is provided as an argument
    if (argc == 2)
    {
        // Open the specified file
        fd = open(argv[1], O_RDONLY);
        if (fd == -1)
        {
            printf("Error opening file");
            return (1);
        }
        printf("Reading from file: %s\n", argv[1]);
    }
    else
    {
        // No file specified, read from standard input (terminal)
        fd = 0; // Standard input
        printf("Reading from terminal. Enter text, press Ctrl+D to end:\n");
    }

    // Read and print each line
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }

    // Close the file if reading from a file
    if (fd != 0)
    {
        close(fd);
    }

    printf("\nEnd of input.\n");
    return (0);
}
