CC = g++
CFLAGS = -g -Wall -lsfml-graphics -lsfml-window -lsfml-system

clean-build-run: clean all

clean:
	rm -rf build/

build-run: all run

all: makeBuildDir main.o GameState.o Tank.o util.o
	$(CC) $(CFLAGS) -o build/main build/main.o build/GameState.o build/Tank.o build/util.o

makeBuildDir:
	mkdir -p build/

main.o: src/main.cpp src/GameState.h src/util.h
	$(CC) $(CFLAGS) -o build/main.o -c src/main.cpp

GameState.o: src/GameState.cpp src/GameState.h src/util.h
	$(CC) $(CFLAGS) -o build/GameState.o -c src/GameState.cpp

Tank.o: src/Tank.cpp src/Tank.h src/util.h
	$(CC) $(CFLAGS) -o build/Tank.o -c src/Tank.cpp

util.o: src/util.cpp src/util.h
	$(CC) $(CFLAGS) -o build/util.o -c src/util.cpp

run:
	./build/main
