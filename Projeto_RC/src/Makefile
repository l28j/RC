# Compiler and flags
CXX = g++
CXXFLAGS = -g -Wall -Wextra -std=c++17 -Icommon -Iclient -Iclient/network -Iclient/commands

# Target executable
TARGET = player

# Directories
SRC_DIR = client
COMMON_DIR = common
NETWORK_DIR = client/network
COMMANDS_DIR = client/commands
UDP_DIR = client/commands/UDP
TCP_DIR = client/commands/TCP

# Source files (using wildcards to gather all .cpp files)
SRC_MAIN = $(wildcard $(SRC_DIR)/*.cpp)
COMMON_SRC = $(wildcard $(COMMON_DIR)/*.cpp)
NETWORK_SRC = $(wildcard $(NETWORK_DIR)/*.cpp)
COMMANDS_SRC = $(wildcard $(COMMANDS_DIR)/*.cpp)
UDP_SRC = $(wildcard $(UDP_DIR)/*.cpp)
TCP_SRC = $(wildcard $(TCP_DIR)/*.cpp)

# All source files combined
SRCS = $(SRC_MAIN) $(COMMON_SRC) $(NETWORK_SRC) $(COMMANDS_SRC) $(UDP_SRC) $(TCP_SRC)

# Object files list
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Linking target executable from object files
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compiling each .cpp file to its corresponding .o file
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean target
clean:
	rm -f $(OBJS) $(TARGET)
