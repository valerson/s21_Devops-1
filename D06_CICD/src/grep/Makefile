CC=gcc
FLAG = -g -Werror -Wextra -Wall -std=c11

all: s21_grep

s21_grep: s21_grep.o grep.o
	$(CC) $(FLAG) s21_grep.o grep.o -o s21_grep

s21_grep.o: s21_grep.c grep.h
	$(CC) $(FLAG) -c s21_grep.c

grep.o: grep.c grep.h
	$(CC) $(FLAG) -c grep.c

clean:
	rm -rf *.o s21_grep

rebuild: clean all