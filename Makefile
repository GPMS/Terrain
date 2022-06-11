CC = gcc
FLAGS = -Wall
LIB = -lGL -lglut -lGLU -lm
SRC = src/*.c

make:
	$(CC) $(LIB) $(FLAGS) $(SRC)
