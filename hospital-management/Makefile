# simple makefile for the hospital project (single-file build)
CC=gcc
CFLAGS=-Wall -std=c11

hospital: hospital.c
	$(CC) $(CFLAGS) -o hospital hospital.c

clean:
	rm -f hospital

run: hospital
	./hospital
