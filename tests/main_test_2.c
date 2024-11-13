#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "../get_next_line.h"

void test_get_next_line(int fd) {
    char *line;
    while ((line = get_next_line(fd)) != NULL) {
        printf("Line: %s", line);
        free(line);
    }
}

int main() {
    // Buffer size scenarios
    #define BUFFER_SIZE 4096 // large buffer size
    #define SMALL_BUFFER_SIZE 1 // small buffer size
    #define EXACT_BUFFER_SIZE 5 // exact length of line

    // Open a test file with various content
    int fd = open("testfile.txt", O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
        return 1;
    }

    // 1. Large BUFFER_SIZE (>1024)
    test_get_next_line(fd);

    // 2. Small BUFFER_SIZE (< 8, and 1)
    #define BUFFER_SIZE SMALL_BUFFER_SIZE
    test_get_next_line(fd);

    // 3. BUFFER_SIZE exactly the length of the line to read
    #define BUFFER_SIZE EXACT_BUFFER_SIZE
    test_get_next_line(fd);

    // 4. BUFFER_SIZE with 1 byte variation (+/-)
    #define BUFFER_SIZE (EXACT_BUFFER_SIZE + 1)
    test_get_next_line(fd);

    #define BUFFER_SIZE (EXACT_BUFFER_SIZE - 1)
    test_get_next_line(fd);

    // Other tests:
    // - Read from stdin: Uncomment below to test with stdin.
    /*
    int stdin_fd = 0;
    printf("Enter lines:\n");
    test_get_next_line(stdin_fd);
    */

    // - Read from a file with long and short lines
    // Example with a long line (2k+ characters) and a short line (< 4 chars)
    int long_line_fd = open("longline.txt", O_RDONLY);
    if (long_line_fd >= 0) {
        test_get_next_line(long_line_fd);
        close(long_line_fd);
    } else {
        printf("Error opening longline.txt\n");
    }

    // - Single and multiple empty lines
    int empty_line_fd = open("emptylines.txt", O_RDONLY);
    if (empty_line_fd >= 0) {
        test_get_next_line(empty_line_fd);
        close(empty_line_fd);
    } else {
        printf("Error opening emptylines.txt\n");
    }

    close(fd);
    return 0;
}
