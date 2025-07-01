# Это комментарий, который говорит, что переменная CC указывает компилятор, используемый для сборки
CC=gcc
# B переменной CFLAGS лежат флаги, которые передаются компилятору
CFLAGS=-c -Wall -g -std=c11
# B переменной LFLAGS лежат флаги, которые передаются компоновщику
LFLAGS=-lm -lcrypto -lssl

all: debug

debug: main.o
	clear
	$(CC)  main.o -o main.out $(LFLAGS)
	clear
	./main.out

main.o: main.c
	clear
	$(CC) $(CFLAGS) main.c

clean:
	rm -rf *.o
	rm -rf *.*~
	rm -rf *~
	
	rm main.out
