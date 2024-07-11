build:
	@gcc -O0 -Wall ./src/main.c -o ./bin/debug/snippet

buildr:
	@gcc -Os ./src/main.c -o ./bin/release/snippet

run: build
	@./bin/debug/snippet

runr: buildr
	@./bin/release/snippet

cleanb:
	@rm ./bin/debug/snippet

cleanr:
	@rm ./bin/release/snippet

clean: cleanb cleanr

