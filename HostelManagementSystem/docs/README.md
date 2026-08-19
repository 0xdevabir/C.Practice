# Hostel Management System - User Guide

## How to Build

```bash
cd HostelManagementSystem
make
```

## How to Run

```bash
./bin/hostel         # macOS/Linux
bin\hostel.exe       # Windows (after build)
```

## Default Login

Password: `admin123`

You can change it in `src/structs.h` (`#define PASSWORD "admin123"`).

## Main Menu

```
1. Student management
2. Room management
3. Fee management
4. Complaint management
5. Visitor tracking
6. Reports
7. Save all data
0. Exit
```

## Typical Workflow

1. **Add students** (Student management → Add student).
2. **Allocate rooms** (Room management → Allocate room).
3. **Collect fees** (Fee management → Collect fee payment).
4. **Log complaints** (Complaint management → Log new complaint).
5. **Track visitors** (Visitor tracking → Log visitor IN).
6. **Generate reports** (Reports → Dashboard summary).

## Data Files

All data is saved in binary format under `data/`:

- `student.dat`    - student records
- `rooms.dat`      - room records
- `complaints.dat` - complaint log
- `visitors.dat`   - visitor log
- `counters.dat`   - next ID counters

To reset, delete the contents of `data/` and run again.

## Notes

- Rooms 101-110 are auto-seeded on first run.
- Student IDs are auto-incremented from 1001.
- All data is saved automatically when you choose option 7, or on exit.
- Each module has a "Back" option (0) to return to the main menu.
