# Compiler
CC = gcc

# Compiler flags: enable warnings and use C99 standard
CFLAGS = -Wall -Wextra -std=c99

# Linker flags:
#   -lmingw32     : Required for Windows applications using MinGW
#   -lSDL2main    : SDL2 main entry point for Windows GUI applications
#   -lSDL2        : SDL2 library
#   -lm           : Math library
LDFLAGS = -lmingw32 -lSDL2main -lSDL2 -lm

# Directories
INCLUDE_DIR = include
SRC_DIR = src
OBJ_DIR = obj

# Source and object files
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SOURCES))
DEPENDS = $(OBJECTS:.o=.d)

# Output binary name
TARGET = SWRenderer

# Create the object directory if it doesn't exist
$(shell mkdir -p $(OBJ_DIR))

# Default target: build and run
all: $(TARGET)
	./$(TARGET) # Run the application after successful build

# Link the final executable from object files
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(LDFLAGS) -o $@

# Rule to compile .c source files into .o object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -MMD -MP -c $< -o $@

# Include generated dependency files
-include $(DEPENDS)

# Clean all generated files
clean:
	rm -f $(OBJ_DIR)/*.o $(OBJ_DIR)/*.d $(TARGET)

# Run the compiled program explicitly
run:
	@./$(TARGET)

.PHONY: all clean run