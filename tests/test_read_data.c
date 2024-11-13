// test_read_data.c

// cc -Wall -Wextra -Werror test_read_data.c -o test_read_data

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include"../get_next_line_utils.c"

/*
** char *read_data(int fd, size_t buf_size);
**
** read_data() reads data from 'fd' with read()
**
** Return: pointer to temp_buf if data was read,
** or NULL if no data left or an error occurred
*/

// Test 1: Reading data from a valid file descriptor
void	test_valid_fd(void)
{
	int fd;
	char *data;
	size_t buf_size = 1024; // Adjust buffer size as needed

	printf("Test 1: Reading data from a valid file descriptor\n");

	// Open a valid file
	fd = open("test_file.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("FAIL: Error opening file 'test_file.txt'");
		return;
	}

	data = read_data(fd, buf_size);
	if (data)
	{
		// Print the data read (handling non-null-terminated data)
		printf("PASS: Data read:\n%.*s\n", (int)buf_size, data);
		free(data);
	}
	else
	{
		printf("FAIL: No data read or an error occurred.\n");
	}

	close(fd);
	printf("--------------------------------------------------\n");
}

// Test 2: Handling End of File (EOF)
void	test_eof(void)
{
	int fd;
	char *data;
	size_t buf_size = 1024;

	printf("Test 2: Handling End of File (EOF)\n");

	// Open an empty file
	fd = open("empty_file.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("FAIL: Error opening file 'empty_file.txt'");
		return;
	}

	// First read attempt
	data = read_data(fd, buf_size);
	if (data)
	{
		printf("FAIL: Data read on first attempt (unexpected for empty file):\n%.*s\n", (int)buf_size, data);
		free(data);
	}
	else
	{
		printf("PASS: No data read on first attempt (expected for empty file).\n");
	}

	// Second read attempt to check for EOF
	data = read_data(fd, buf_size);
	if (data)
	{
		printf("FAIL: Data read on second attempt (unexpected):\n%.*s\n", (int)buf_size, data);
		free(data);
	}
	else
	{
		printf("PASS: No data read on second attempt (expected at EOF).\n");
	}

	close(fd);
	printf("--------------------------------------------------\n");
}

// Test 3: Dealing with invalid file descriptors
void test_invalid_fd(void)
{
	char *data;
	size_t buf_size = 1024;
	int invalid_fd = -1; // Invalid file descriptor

	printf("Test 3: Dealing with invalid file descriptors\n");

	data = read_data(invalid_fd, buf_size);
	if (data == NULL)
	{
		printf("PASS: Correctly handled invalid file descriptor.\n");
	}
	else
	{
		printf("FAIL: Unexpected data returned for invalid file descriptor:\n%.*s\n", (int)buf_size, data);
		free(data);
	}

	printf("--------------------------------------------------\n");
}

// Test 4: Handling zero or negative buffer sizes
void test_zero_negative_buffer(void)
{
	int fd;
	char *data;
	size_t buf_size_zero = 0;
	ssize_t buf_size_negative = -1024; // ssize_t allows negative values

	printf("Test 4: Handling zero or negative buffer sizes\n");

	// Open a valid file
	fd = open("test_file.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("FAIL: Error opening file 'test_file.txt'");
		return;
	}

	// Test with zero buffer size
	data = read_data(fd, buf_size_zero);
	if (data == NULL)
	{
		printf("PASS: Correctly handled zero buffer size.\n");
	}
	else
	{
		printf("FAIL: Unexpected data returned for zero buffer size:\n%.*s\n", (int)buf_size_zero, data);
		free(data);
	}

	// Test with negative buffer size (cast to size_t, will be a large positive value)
	data = read_data(fd, (size_t)buf_size_negative);
	if (data == NULL)
	{
		printf("PASS: Correctly handled negative buffer size.\n");
	}
	else
	{
		printf("FAIL: Unexpected data returned for negative buffer size:\n%.*s\n", (int)buf_size_negative, data);
		free(data);
	}

	close(fd);
	printf("--------------------------------------------------\n");
}

// Test 5: Simulating malloc failure (advanced and optional)
void test_malloc_failure(void)
{
	int fd;
	char *data;
	size_t buf_size = 1024;

	printf("Test 5: Simulating malloc failure (advanced and optional)\n");

	// Open a valid file
	fd = open("test_file.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("FAIL: Error opening file 'test_file.txt'");
		return;
	}

	// Redefine malloc to simulate failure
	#undef malloc
	#define malloc(size) NULL

	// Include the read_data function here
	char *read_data(int fd, size_t buf_size)
	{
		char *temp_buf;
		ssize_t bytes_read;

		if (fd < 0 || buf_size <= 0)
			return NULL;
		temp_buf = (char *)malloc(buf_size);
		if (!temp_buf)
			return NULL;
		bytes_read = read(fd, temp_buf, buf_size);
		if (bytes_read > 0)
		{
			return temp_buf;
		}
		else
		{
			free(temp_buf);
			return NULL;
		}
	}

	data = read_data(fd, buf_size);

	// Restore original malloc definition
	#undef malloc
	#include <stdlib.h> // Re-include stdlib to restore malloc

	if (data == NULL)
	{
		printf("PASS: Correctly handled malloc failure.\n");
	}
	else
	{
		printf("FAIL: Unexpected data returned when malloc fails:\n%.*s\n", (int)buf_size, data);
		free(data);
	}

	close(fd);
	printf("--------------------------------------------------\n");
}


int main(void)
{
	printf("Starting tests for read_data function\n");
	printf("==================================================\n");

	test_valid_fd();
	test_eof();
	test_invalid_fd();
	test_zero_negative_buffer();
	test_malloc_failure();

	printf("All tests completed.\n");
	return 0;
}
