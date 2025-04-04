# Compiler
CC = gcc
# Compiler flags: -g for debugging, -Wall/-Wextra for warnings
CFLAGS = -g -Wall -Wextra
# Linker flags: -lpthread needed if/when you add threading
LDFLAGS = # Add -lpthread later if needed

# Source files directory
SRC_DIR = src
# Object files directory (optional, keeps things clean)
OBJ_DIR = obj
# Binary output directory (optional)
BIN_DIR = bin

# Find all .c files in SRC_DIR
SRCS = $(wildcard $(SRC_DIR)/*.c)
# Create object file names based on source files, put them in OBJ_DIR
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# Name of the final executable
TARGET = $(BIN_DIR)/server

# Default target: Build the executable
all: $(TARGET)

# Rule to link the executable
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR) # Create bin directory if it doesn't exist
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
	@echo "Linked '$@' successfully."

# Rule to compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR) # Create obj directory if it doesn't exist
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled '$<'."

# Target to clean up compiled files
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
	@echo "Cleaned build files."

# Target to run the server (example, customize port/args later)
run: all
	./$(TARGET) 8080 ./www # Example: run server on port 8080 serving from ./www

.PHONY: all clean run