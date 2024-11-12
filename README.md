# Get Next Line

This project implements a function, `get_next_line`, that reads a single line from a file descriptor each time it is called, making it easy to handle line-by-line reading.

## Features

- Reads from any file descriptor (e.g., files, standard input).
- Efficiently manages leftover data between calls.
- Utilizes a static buffer for minimal memory allocation and optimized performance.
