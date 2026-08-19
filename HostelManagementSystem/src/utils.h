#ifndef UTILS_H
#define UTILS_H

#include <time.h>

/* ---------- UI Helpers ---------- */
void clearScreen(void);
void pauseScreen(void);
void printLine(char ch, int n);
void header(const char *title);

/* ---------- Input Helpers ---------- */
void readString(char *buf, int size);
void readInt(int *out);
void readFloat(float *out);

/* ---------- Date / Time ---------- */
void currentDate(char *out);   /* dd/mm/yyyy */
void currentTime(char *out);   /* hh:mm */

#endif
