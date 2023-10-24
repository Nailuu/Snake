all:
	gcc -Isrc/Include -Lsrc/lib -o main src/main.c src/render.c src/texture.c -lmingw32 -lSDL2main -lSDL2