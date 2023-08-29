CC = g++
CFLAGS = -g -Wall -lsfml-graphics -lsfml-window -lsfml-system

clean-build-run: clean all

clean:
	rm -rf build/

build-run: all run

all: makeBuildDir main.o GameState.o Tank.o IO.o util.o debug.o
	$(CC) $(CFLAGS) -o build/main build/main.o build/GameState.o build/Tank.o build/IO.o build/util.o build/debug.o

makeBuildDir:
	mkdir -p build/

main.o: src/main.cpp src/GameState.h src/util.h src/debug.h
	$(CC) $(CFLAGS) -o build/main.o -c src/main.cpp

GameState.o: src/GameState.cpp src/GameState.h src/util.h src/debug.h
	$(CC) $(CFLAGS) -o build/GameState.o -c src/GameState.cpp

Tank.o: src/Tank.cpp src/Tank.h src/util.h src/debug.h
	$(CC) $(CFLAGS) -o build/Tank.o -c src/Tank.cpp

IO.o: src/IO.cpp src/IO.h src/GameState.h
	$(CC) $(CFLAGS) -o build/IO.o -c src/IO.cpp

util.o: src/util.cpp src/util.h
	$(CC) $(CFLAGS) -o build/util.o -c src/util.cpp

debug.o: src/debug.cpp src/debug.h src/IO.h
	$(CC) $(CFLAGS) -o build/debug.o -c src/debug.cpp

run:
	./build/main
