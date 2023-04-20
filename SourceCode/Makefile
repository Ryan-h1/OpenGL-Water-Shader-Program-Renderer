CC = g++
CXXFLAGS = -Wall -Wextra -Wpedantic -O3 -std=c++20
LDFLAGS = -lglfw -lGLEW -lOpenGL
TARGET = assign6

# Source files
SRCS = main.cpp

# Header files
HDRS = CamControls.hpp Constants.hpp Headers.hpp LoadBMP.hpp PlaneMesh.hpp Shader.hpp

# Set the obj directory path
OBJ_DIR = ObjectFiles

# Generate a list of object files from the source files
OBJS = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(TARGET)

# Compile each source file into an object file
$(OBJ_DIR)/%.o: %.cpp $(HDRS)
	mkdir -p $(OBJ_DIR)
	$(CC) -c $(CXXFLAGS) $< -o $@

.PHONY: clean
clean:
	rm -rf $(TARGET) $(OBJ_DIR)
