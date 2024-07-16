CC = gcc

BUILD_FLAGS = -O0 -Wall
RELEASE_FLAGS = -Os

SOURCE_FILES = ./src/*.c
LIB_FILES = ./src/lib/*.c

DEBUG_PATH = ./bin/debug/scaffold
RELEASE_PATH = ./bin/release/scaffold

EXECUTION_FLAGS = --help

build:
	@$(CC) $(BUILD_FLAGS) $(SOURCE_FILES) $(LIB_FILES) -o $(DEBUG_PATH)
	@$(CC) $(RELEASE_FLAGS) $(SOURCE_FILES) $(LIB_FILES) -o $(RELEASE_PATH)

# To run the debug version of the software
run: build
	$(DEBUG_PATH) $(EXECUTION_FLAGS)

# To run the release version of the software
deploy: build
	@$(RELEASE_PATH) $(EXECUTION_FLAGS)

clean:
	rm $(DEBUG_PATH)
	rm $(RELEASE_PATH)