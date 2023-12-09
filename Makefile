all: build run

# если не указать правило, будет выполнено первое правило
build:
# lm - математическая библиотека
	gcc -Wall -std=c99 ./src/*.c -lSDL2 -lm -o renderer

.PHONY: run clean

run:
	./renderer

clean:
	rm ./renderer

release:
	gcc -O3 -Wall -std=c99 ./src/*.c -lSDL2 -lm -o renderer
