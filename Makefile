# File: Makefile

# Compiler and Flags
CPP = g++
CFLAGS = -O3 -w -fPIC -I./include -I/usr/include/nautylibrary -c

# Directories
BIN_DIR = bin
SRC_DIR = src
INCLUDE_DIR = include
NAUTY_LIB_DIR = nautylibrary

# Targets
OBJECTS = $(BIN_DIR)/nautyClassify.o $(BIN_DIR)/testnautyClassify.o $(BIN_DIR)/nauty.o $(BIN_DIR)/naugraph.o $(BIN_DIR)/nautil.o

# Default Target
all: $(OBJECTS)

# Compile nautyClassify.cpp
$(BIN_DIR)/nautyClassify.o: $(SRC_DIR)/nautyClassify.cpp $(INCLUDE_DIR)/nautyClassify.h
	$(CPP) $(CFLAGS) $< -o $@

# Compile testnautyClassify.cpp (if needed)
$(BIN_DIR)/testnautyClassify.o: $(SRC_DIR)/testnautyClassify.cpp $(INCLUDE_DIR)/nautyClassify.h
	$(CPP) $(CFLAGS) $< -o $@

# Compile Nauty C Files
$(BIN_DIR)/nauty.o: $(NAUTY_LIB_DIR)/nauty.c
	$(CPP) $(CFLAGS) $< -o $@

$(BIN_DIR)/naugraph.o: $(NAUTY_LIB_DIR)/naugraph.c
	$(CPP) $(CFLAGS) $< -o $@

$(BIN_DIR)/nautil.o: $(NAUTY_LIB_DIR)/nautil.c
	$(CPP) $(CFLAGS) $< -o $@

# Clean Build Artifacts
clean:
	@echo "Removing objects..."
	rm -f $(BIN_DIR)/*.o *.log src/*~ include/*~ *~ core

# Archive the Project
ar:
	make clean
	tar -czvf ../nautycaller_objects_$(shell date +"%Y%m%d%H%M%S").tar.gz *
