#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#include <unistd.h> // for read()
#include <stdlib.h> // for malloc(), free()

// Set default BUFFER_SIZE
#ifndef BUFFER_SIZE
    #define BUFFER_SIZE 4096
#elif BUFFER_SIZE != 4096
    #undef BUFFER_SIZE
    #define BUFFER_SIZE 4096
#endif

#define MAIN_BUF_SIZE 8192

// Function prototype
char	*get_next_line(int fd);

#endif /* GET_NEXT_LINE_H */
