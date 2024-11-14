#include "test_gnl.h"

// Assuming extract_line and ft_strncpy are defined elsewhere

void test_extract_line(void)
{
    char *result;

    // Test 1: Normal case with newline
    char test1[] = "Hello\nWorld";
    result = extract_line(test1);
    printf("Test 1 - Expected: \"Hello\\n\", Got: \"%s\"\n", result);
    free(result);

    // Test 2: String without newline
    char test2[] = "Hello";
    result = extract_line(test2);
    printf("Test 2 - Expected: \"Hello\", Got: \"%s\"\n", result);
    free(result);

    // Test 3: Empty string
    char test3[] = "";
    result = extract_line(test3);
    printf("Test 3 - Expected: (null), Got: \"%s\"\n", result ? result : "(null)");
    free(result);

    // Test 4: String with only newline
    char test4[] = "\n";
    result = extract_line(test4);
    printf("Test 4 - Expected: \"\\n\", Got: \"%s\"\n", result);
    free(result);

    // Test 5: NULL input
    result = extract_line(NULL);
    printf("Test 5 - Expected: (null), Got: \"%s\"\n", result ? result : "(null)");

    // Test 6: Multiple lines
    char test6[] = "First line\nSecond line\n";
    result = extract_line(test6);
    printf("Test 6 - Expected: \"First line\\n\", Got: \"%s\"\n", result);
    free(result);
}

int main(void)
{
    test_extract_line();
    return 0;
}
