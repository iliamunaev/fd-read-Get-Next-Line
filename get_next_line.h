// get_next_line.h

#ifndef GET_NEXT_LINE
#define GET_NEXT_LINE

#include <unistd.h> // for read()
#include <stdlib.h> // for malloc(), free()

// default buffer size
#define BUFFER_SIZE 4096

// utils
char	*get_next_line(int fd);

#endif /* GET_NEXT_LINE */
