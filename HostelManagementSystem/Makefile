# ===== Hostel Management System - Makefile =====
CC      = gcc
CFLAGS  = -Wall -Wextra -std=c99 -g -Isrc
SRC_DIR = src
BIN_DIR = bin
BIN     = $(BIN_DIR)/hostel

SRCS = $(SRC_DIR)/main.c \
       $(SRC_DIR)/utils.c \
       $(SRC_DIR)/file_ops.c \
       $(SRC_DIR)/student.c \
       $(SRC_DIR)/room.c \
       $(SRC_DIR)/fee.c \
       $(SRC_DIR)/complaint.c \
       $(SRC_DIR)/visitor.c \
       $(SRC_DIR)/report.c

# Provide a stub for mkdir on Windows if needed
ifeq ($(OS),Windows_NT)
    MKDIR = if not exist $(BIN_DIR) mkdir $(BIN_DIR)
    RM    = rmdir /S /Q $(BIN_DIR)
else
    MKDIR = mkdir -p $(BIN_DIR)
    RM    = rm -rf $(BIN_DIR)
endif

all: $(BIN)

$(BIN): $(SRCS)
	$(MKDIR)
	$(CC) $(CFLAGS) $(SRCS) -o $(BIN)

run: $(BIN)
	./$(BIN)

clean:
	$(RM)

rebuild: clean all

# Compile to object files separately (optional)
OBJS = $(SRCS:.c=.o)
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all run clean rebuild