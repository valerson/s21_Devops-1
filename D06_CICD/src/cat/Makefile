CC=gcc
FLAG = -g -Werror -Wextra -Wall -std=c11

all: s21_cat

s21_cat: s21_cat.o cat.o
	$(CC) $(FLAG) s21_cat.o cat.o -o s21_cat

s21_cat.o: s21_cat.c cat.h
	$(CC) $(FLAG) -c s21_cat.c

cat.o: cat.c cat.h
	$(CC) $(FLAG) -c cat.c

clean:
	rm -rf *.o s21_cat

rebuild: clean all