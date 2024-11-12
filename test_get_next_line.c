/*
---------- ERROR MANAGMENT ----------

Carry out AT LEAST the following tests to try to stress the error
management.

Pass an arbitrary file descriptor to the get_next_line function
on which it is not possible to read, for example 42. The function must return NULL.

Check the error returns for read and malloc.
If there is an error, the evaluation stops here.
You can keep going and discuss the implementation of the code, but the assignment will not be graded.


---------- TESTING ----------

As the evaluator, you are expected to provide a main which will always check:

The return value of the get_next_line is NULL in case of error.
Otherwise, the function returns the line read, always with a \n at the end except
if the end of file was reached and does not end with a \n character.

Test all the possible combinations of the following rules:

Large BUFFER_SIZE (>1024)
Small BUFFER_SIZE (< 8, and 1)
BUFFER_SIZE exactly the length of the line to read
1 byte variant (+/-) between the line and the BUFFER_SIZE

Read on stdin

Read from a file

(Multiple/Single) Long line (2k+ characters)

(Multiple/Single) Short line (< 4 characters, even 1)

(Multiple/Single) Empty line

These tests should enable you to verify the strength of the student's
get_next_line.
If there is an error, the evaluation stops here.


---------- BOUNUS PART ----------

Multiple fd reading

Perform the same tests as you did before, this time launch multiple
instances of get_next_line with a different file descriptor on each. Make
sure that each get_next_line is returning the correct line. Combine with
a non-existing fd to check for errors.


Single static variable

Check the code and verify if there is indeed only one static variable.
Give the points if that's the case.
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <fcntl.h>
#include "get_next_line.h"

// Helper function to create a temporary file with given content and return its file descriptor
int	create_temp_file(const char *content)
{
    FILE *file = tmpfile();
    if (!file)
	{
        perror("Failed to create temporary file");
        exit(EXIT_FAILURE);
    }

    // Write the content to the temporary file
    fputs(content, file);
    fflush(file);

    // Get the file descriptor and reset the file position to the start
    int fd = fileno(file);
    lseek(fd, 0, SEEK_SET);

    return (fd);
}

int main(void)
{
    // Test cases as files
    int fd1 = create_temp_file("Well, Prince, so Genoa and Lucca are now just family estates of the Buonapartes.\n");
    int fd2 = create_temp_file("Ok\n");
    int fd3 = create_temp_file("v\n");
    int fd4 = create_temp_file("");  // Empty line
    int fd5 = create_temp_file("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
    int fd6 = create_temp_file("Well, Prince, so Genoa and Lucca are now just family estates of the Buonapartes. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nam congue arcu blandit accumsan faucibus. Nullam sed elit id nisl volutpat sodales at eget libero.\n");
    int fd7 = create_temp_file("A. B. C.\n");
    int fd8 = create_temp_file("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA. BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB\n");

    // Test each file descriptor with get_next_line
    assert(strcmp(get_next_line(fd1), "Well, Prince, so Genoa and Lucca are now just family estates of the Buonapartes.\n") == 0);
    assert(strcmp(get_next_line(fd2), "Ok\n") == 0);
    assert(strcmp(get_next_line(fd3), "v\n") == 0);
    assert(strcmp(get_next_line(fd4), "") == 0);  // Expecting NULL or empty string depending on implementation
    assert(strcmp(get_next_line(fd5), "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n") == 0);
    assert(strcmp(get_next_line(fd6), "Well, Prince, so Genoa and Lucca are now just family estates of the Buonapartes. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nam congue arcu blandit accumsan faucibus. Nullam sed elit id nisl volutpat sodales at eget libero.\n") == 0);
    assert(strcmp(get_next_line(fd7), "A. B. C.\n") == 0);
    assert(strcmp(get_next_line(fd8), "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA. BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB\n") == 0);

    // Close file descriptors
    close(fd1);
    close(fd2);
    close(fd3);
    close(fd4);
    close(fd5);
    close(fd6);
    close(fd7);
    close(fd8);

    printf("All tests passed successfully.\n");

    return (0);
}
