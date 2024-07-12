# To build the debug version of the software
build:
	@gcc -O0 -Wall ./src/main.c -o ./bin/debug/snippet.out

# To build the release version of the software
buildr:
	@gcc -Os ./src/main.c -o ./bin/release/snippet

# To run the debug version of the software
run: build
	@./bin/debug/snippet.out

# To run the release version of the software
runr: buildr
	@./bin/release/snippet

# To clean the debug builds
cleanb:
	@rm ./bin/debug/snippet

# To clean the release builds
cleanr:
	@rm ./bin/release/snippet

# To clean both builds
clean: cleanb cleanr

