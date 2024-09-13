# .cpp files are in this directory
SOURCE_PATH = ./src
# .h files are in this directory
INCLUDE_PATH = ./include
# .o files and executable file will be in this directory
BUILD_PATH = ./build

# Path to the hiredis library and include directory
HIREDIS_INCLUDE_PATH = /usr/local/include/hiredis
HIREDIS_LIB_PATH = /usr/local/lib

# The compiler command
CC = g++
# The flags to pass when compiling using the above compiler
CFLAGS := -Wall -Wextra -std=c++20 -g -I$(INCLUDE_PATH) -I$(HIREDIS_INCLUDE_PATH)
LDFLAGS := -L$(HIREDIS_LIB_PATH) -lhiredis

# Use the shell to find all .cpp files, including subdirectories
SOURCES := $(shell find $(SOURCE_PATH) -type f -name '*.cpp')
# Shorthand for $( patsubst %suffix,%replacement,$(SOURCES) )
OBJECTS := $(SOURCES:$(SOURCE_PATH)/%.cpp=$(BUILD_PATH)/%.o)
# The name of the executable file that will be generated
TARGET = bin

# Compile and run the executable
.PHONY: run
run: all
	@echo "Updating environment variables..."
	@LD_LIBRARY_PATH=/usr/local/lib
	@echo "Running executable..."
	@./$(BUILD_PATH)/$(TARGET)

# Compile the executable
.PHONY: all
all: $(BUILD_PATH)/$(TARGET)

# Recipe to actually compile the executable
$(BUILD_PATH)/$(TARGET): $(OBJECTS)
	@echo "Compiling executable at" $@ 
	@mkdir -p $(BUILD_PATH)
	$(CC) $(CFLAGS) $(OBJECTS) $(LDFLAGS) -o $@

# Recipe to compile each .cpp file into a .o file, depends on .cpp and build directory
$(BUILD_PATH)/%.o: $(SOURCE_PATH)/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Recipe to delete executable and all .o files
.PHONY: clean
clean:
	@echo "Removing build files and empty build directories..."
	rm -f $(BUILD_PATH)/$(TARGET) $(OBJECTS) 
	rm -df $(shell find $(BUILD_PATH) -type d -empty)

.PHONY: a
a:
	@echo $(shell find $(BUILD_PATH) -type d -empty)
