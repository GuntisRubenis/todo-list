CC=gcc
C_F=-Wall -Wextra -Wshadow -Wformat=2 -Wconversion -std=c99 -O0 -g -fsanitize=address,undefined -fno-omit-frame-pointer 

main: main.o utils.o list.o
	$(CC) $(C_F) -o main main.o utils.o list.o

main.o: main.c utils.h list.h
	$(CC) $(C_F) -c main.c

utils.o: utils.c
	$(CC) $(C_F) -c utils.c

list.o: list.c utils.h
	$(CC) $(C_F) -c list.c

run: main
	./main

