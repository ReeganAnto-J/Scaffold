CC = gcc
BUILD_FLAGS = -O0 -Wall
RELEASE_FLAGS = -Os
SOURCE_PATH = ./src/*.c
DEBUG_PATH = ./bin/debug/scaffold
RELEASE_PATH = ./bin/release/scaffold

EXECUTION_FLAGS =

build:
	@$(CC) $(BUILD_FLAGS) $(SOURCE_PATH) -o $(DEBUG_PATH)
	@$(CC) $(RELEASE_FLAGS) $(SOURCE_PATH) -o $(RELEASE_PATH)

# To run the debug version of the software
run: build
	@$(DEBUG_PATH) $(EXECUTION_FLAGS)

# To run the release version of the software
deploy: build
	@$(RELEASE_PATH) $(EXECUTION_FLAGS)

clean:
	rm $(DEBUG_PATH)
	rm $(RELEASE_PATH)

