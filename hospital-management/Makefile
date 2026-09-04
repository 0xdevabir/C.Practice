CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -O2
SRCS = main.c utils.c storage.c patients.c doctors.c rooms.c \
       appointments.c pharmacy.c lab.c billing.c reports.c
OBJS = $(SRCS:.c=.o)
TARGET = hospital

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

%.o: %.c hospital.h
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
