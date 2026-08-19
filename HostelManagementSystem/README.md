# Hostel Management System (C)

A menu-driven Hostel Management System written in C, using file handling for
persistent storage. Manages student records, room allocation, fee tracking,
complaints, and visitor logs.

## Features

- **Student Management** - add, view, search, update, delete
- **Room Management** - allocate, reassign, view available beds, add room
- **Fee Management** - collect fees, view dues, fee report
- **Complaints** - log, view, update status
- **Visitor Tracking** - log in/out, view log
- **Reports** - vacancy, fee, complaint, dashboard
- **Persistent storage** - binary files in `data/`

## Project Structure

```
HostelManagementSystem/
├── src/
│   ├── main.c
│   ├── structs.h
│   ├── utils.h / utils.c
│   ├── file_ops.h / file_ops.c
│   ├── student.h  / student.c
│   ├── room.h     / room.c
│   ├── fee.h      / fee.c
│   ├── complaint.h / complaint.c
│   ├── visitor.h  / visitor.c
│   └── report.h   / report.c
├── data/                  # auto-created at runtime
├── docs/
├── Makefile
└── README.md
```

## Build & Run

```bash
cd HostelManagementSystem
make           # builds bin/hostel
make run       # build + run
make clean     # remove build output
```

Or manually:

```bash
gcc -Wall -Wextra -std=c99 -Isrc src/*.c -o hostel
./hostel
```

## Default Admin Password

`admin123`

(This is the constant `PASSWORD` in `src/structs.h`. Change it before
deployment.)

## Notes

- All data is stored in binary under `data/`. Delete files there to reset.
- Rooms are auto-seeded (101-110) on first run.
- Student IDs are auto-generated starting at 1001.
