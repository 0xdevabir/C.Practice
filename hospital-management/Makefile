# simple makefile for the hospital project
CC=gcc
CFLAGS=-Wall -std=c11
OBJS=main.o utils.o storage.o patients.o doctors.o rooms.o appointments.o pharmacy.o lab.o billing.o reports.o

hospital: $(OBJS)
	$(CC) $(CFLAGS) -o hospital $(OBJS)

%.o: %.c hospital.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o hospital

run: hospital
	./hospital
