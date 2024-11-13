// test_add_data_to_main_buf.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../get_next_line.c"

// Function prototypes
//char	*adjust_space_main_buf(char *main_buf, size_t buf_size, c
char	*ft_strjoin(char const *s1, char const *s2);

// Test 1: Normal case where main_buf and temp_buf are non-empty
void test_add_data_to_main_buf_normal_case(void)
{
    char *main_buf = strdup("Hello, ");
    char *temp_buf = strdup("World!");
    size_t buf_size = strlen(temp_buf);

    printf("Test 1: Normal case where main_buf and temp_buf are non-empty\n");

    char *result = add_data_to_main_buf(main_buf, temp_buf, buf_size);
    if (result)
    {
        printf("Result: %s\n", result);
        free(result);
    }
    else
    {
        printf("add_data_to_main_buf returned NULL\n");
    }

    printf("--------------------------------------------------\n");
}

// Test 2: main_buf is NULL, temp_buf is non-empty
void test_add_data_to_main_buf_null_main_buf(void)
{
    char *main_buf = NULL;
    char *temp_buf = strdup("New data");
    size_t buf_size = strlen(temp_buf);

    printf("Test 2: main_buf is NULL, temp_buf is non-empty\n");

    char *result = add_data_to_main_buf(main_buf, temp_buf, buf_size);
    if (result)
    {
        printf("Result: %s\n", result);
        free(result);
    }
    else
    {
        printf("add_data_to_main_buf returned NULL\n");
    }

    printf("--------------------------------------------------\n");
}

// Test 3: temp_buf is empty
void test_add_data_to_main_buf_empty_temp_buf(void)
{
    char *main_buf = strdup("Existing data");
    char *temp_buf = strdup("");
    size_t buf_size = strlen(temp_buf);

    printf("Test 3: temp_buf is empty\n");

    char *result = add_data_to_main_buf(main_buf, temp_buf, buf_size);
    if (result)
    {
        printf("Result: %s\n", result);
        free(result);
    }
    else
    {
        printf("add_data_to_main_buf returned NULL\n");
    }

    printf("--------------------------------------------------\n");
}

// Test 4: Simulate failure in adjust_space_main_buf (e.g., realloc fails)
void test_add_data_to_main_buf_adjust_space_failure(void)
{
    char *main_buf = strdup("Data");
    char *temp_buf = strdup("More data");
    size_t buf_size = strlen(temp_buf);

    printf("Test 4: Simulate failure in adjust_space_main_buf\n");

    // Redefine realloc to simulate failure
    #undef realloc
    #define realloc(ptr, size) NULL

    char *result = add_data_to_main_buf(main_buf, temp_buf, buf_size);

    // Restore original realloc definition
    #undef realloc
    #include <stdlib.h> // Re-include stdlib to restore realloc

    if (result == NULL)
    {
        printf("Correctly handled adjust_space_main_buf failure.\n");
    }
    else
    {
        printf("add_data_to_main_buf did not handle adjust_space_main_buf failure.\n");
        free(result);
    }

    printf("--------------------------------------------------\n");
}

// Test 5: Simulate failure in ft_strjoin (e.g., malloc fails)
void test_add_data_to_main_buf_ft_strjoin_failure(void)
{
    char *main_buf = strdup("Data");
    char *temp_buf = strdup("More data");
    size_t buf_size = strlen(temp_buf);

    printf("Test 5: Simulate failure in ft_strjoin\n");

    // Redefine malloc to simulate failure
    #undef malloc
    #define malloc(size) NULL

    char *result = add_data_to_main_buf(main_buf, temp_buf, buf_size);

    // Restore original malloc definition
    #undef malloc
    #include <stdlib.h> // Re-include stdlib to restore malloc

    if (result == NULL)
    {
        printf("Correctly handled ft_strjoin failure.\n");
    }
    else
    {
        printf("add_data_to_main_buf did not handle ft_strjoin failure.\n");
        free(result);
    }

    printf("--------------------------------------------------\n");
}

int main(void)
{
    printf("Starting tests for add_data_to_main_buf function\n");
    printf("==================================================\n");

    test_add_data_to_main_buf_normal_case();
    test_add_data_to_main_buf_null_main_buf();
    test_add_data_to_main_buf_empty_temp_buf();
    test_add_data_to_main_buf_adjust_space_failure();
    test_add_data_to_main_buf_ft_strjoin_failure();

    printf("All tests completed.\n");
    return 0;
}
