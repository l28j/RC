# Compiler
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -pthread
#CXXFLAGS = -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused

# Directories
USER_DIR = src/user
SERVER_DIR = src/server
COMMON_DIR = src/common

# Find all cpp files in the user and server directories
USER_SOURCES = $(shell find $(USER_DIR) -name '*.cpp')
SERVER_SOURCES = $(shell find $(SERVER_DIR) -name '*.cpp')
COMMON_SOURCES = $(shell find $(COMMON_DIR) -name '*.cpp')

# Executable names
USER_EXEC = ./user
SERVER_EXEC = ./server

# Default target is to build the user and server executables but before clean
all: clean $(USER_EXEC) $(SERVER_EXEC)

user: clean-user $(USER_EXEC)

server: clean-server $(SERVER_EXEC)

# Rules for building user and server executables
$(USER_EXEC):
	$(CXX) $(CXXFLAGS) $(USER_SOURCES) $(COMMON_SOURCES) -o $(USER_EXEC)

$(SERVER_EXEC):
	$(CXX) $(CXXFLAGS) $(SERVER_SOURCES) $(COMMON_SOURCES) -o $(SERVER_EXEC)

# Debugging
debug:
	@echo "User Sources: $(USER_SOURCES)"
	@echo "Server Sources: $(SERVER_SOURCES)"
	@echo "Common Sources: $(COMMON_SOURCES)"

# Clean up
clean:
	rm -f $(USER_EXEC) $(SERVER_EXEC)

clean-user:
	rm -f $(USER_EXEC)

clean-server:

.PHONY: all clean debug
