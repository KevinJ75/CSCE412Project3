# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall

# Target executable
TARGET = load_balancer

# Source files
SRCS = LoadBalancer.cpp WebServer.cpp Request.cpp main.cpp

# Header files
HEADERS = LoadBalancer.h WebServer.h Request.h

# Object files
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Rule to build the target executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile .cpp files to .o object files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $<

# Clean rule to remove generated files
clean:
	rm -f $(TARGET) $(OBJS)

# Phony target to prevent conflicts with files named 'clean'
.PHONY: clean all
