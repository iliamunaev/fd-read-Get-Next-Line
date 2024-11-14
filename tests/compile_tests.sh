#!/bin/bash

# Define source files and compilation flags
SOURCE_FILES="../get_next_line.c ../get_next_line_utils.c main.c"
CFLAGS="-Wall -Werror -Wextra"

# Array of buffer sizes to test (excluding default 42)
BUFFER_SIZES=(1 7 2048 0)

# Compile with the default buffer size 42
echo "Compiling with default BUFFER_SIZE=42..."
cc $CFLAGS $SOURCE_FILES -o main_test_buffer_42
if [[ $? -eq 0 ]]; then
    echo "Compilation successful: main_test_buffer_42"
else
    echo "Compilation failed for default BUFFER_SIZE=42"
fi

# Compile for each specified buffer size in BUFFER_SIZES
for BUFFER_SIZE in "${BUFFER_SIZES[@]}"; do
    # Define output file name
    OUTPUT_FILE="main_test_buffer_${BUFFER_SIZE}"

    # Compile with the specified buffer size
    echo "Compiling with BUFFER_SIZE=${BUFFER_SIZE}..."
    cc $CFLAGS -D BUFFER_SIZE=$BUFFER_SIZE $SOURCE_FILES -o $OUTPUT_FILE

    # Check if compilation was successful
    if [[ $? -eq 0 ]]; then
        echo "Compilation successful: $OUTPUT_FILE"
    else
        echo "Compilation failed for BUFFER_SIZE=${BUFFER_SIZE}"
    fi
done

echo "All compilations completed."
