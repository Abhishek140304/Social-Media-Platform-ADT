# Compiler to use
CC = gcc

# Compiler flags: 
# -g: Adds debugging information
# -Wall: Enables all warnings
CFLAGS = -g -Wall

# Name of the code subdirectory
CODE_DIR = code

# The final executable file name (will be created in this folder)
TARGET = social_app

# Find all .c source files inside the CODE_DIR
SRCS = $(wildcard $(CODE_DIR)/*.c)

# Create a list of object files (e.g., code/main.o, code/platform.o)
OBJS = $(SRCS:.c=.o)

# The default rule (builds the executable)
all: $(TARGET)

# Rule to link all object files into the final executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile a .c file (in code/) into a .o file (in code/)
$(CODE_DIR)/%.o: $(CODE_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to clean up all compiled files
# This is the corrected rule
clean:
	rm -f $(TARGET) $(CODE_DIR)/*.o