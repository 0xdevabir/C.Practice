#ifndef ROOM_H
#define ROOM_H

#include "structs.h"

void roomMenu(void);
void viewRooms(void);
void viewAvailableBeds(void);
void allocateRoom(void);
void reassignRoom(void);
void addRoom(void);
Room* findRoom(int roomNo);

#endif