# File: Makefile

# Compilers and Flags
CPP = g++
CC = gcc
CFLAGS = -O3 -w -fPIC -I./include -I/usr/include/nautylibrary -DMAXN=WORDSIZE
LDFLAGS = -L$(NAUTY_LIB_DIR)

# Directories
BIN_DIR = bin
SRC_DIR = src
INCLUDE_DIR = include
NAUTY_LIB_DIR = nautylibrary

# Executable name
EXEC = $(BIN_DIR)/test_nauty

# Objects
OBJECTS = $(BIN_DIR)/nautyClassify.o $(BIN_DIR)/testnautyClassify.o $(BIN_DIR)/nauty.o $(BIN_DIR)/naugraph.o $(BIN_DIR)/nautil.o

# Default Target
all: $(EXEC)

# Link the executable
$(EXEC): $(OBJECTS)
	$(CPP) $(OBJECTS) -o $(EXEC) $(LDFLAGS)

# Compile nautyClassify.cpp
$(BIN_DIR)/nautyClassify.o: $(SRC_DIR)/nautyClassify.cpp $(INCLUDE_DIR)/nautyClassify.h
	$(CPP) $(CFLAGS) -c $< -o $@

# Compile testnautyClassify.cpp
$(BIN_DIR)/testnautyClassify.o: $(SRC_DIR)/testnautyClassify.cpp $(INCLUDE_DIR)/nautyClassify.h
	$(CPP) $(CFLAGS) -c $< -o $@

# Compile Nauty C Files
$(BIN_DIR)/nauty.o: $(NAUTY_LIB_DIR)/nauty.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/naugraph.o: $(NAUTY_LIB_DIR)/naugraph.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/nautil.o: $(NAUTY_LIB_DIR)/nautil.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean Build Artifacts
clean:
	@echo "Removing objects and executable..."
	rm -f $(BIN_DIR)/*.o $(EXEC) *.log src/*~ include/*~ *~ core

# Archive the Project
ar:
	make clean
	tar -czvf ../nautycaller_objects_$(shell date +"%Y%m%d%H%M%S").tar.gz *

.PHONY: all clean ar