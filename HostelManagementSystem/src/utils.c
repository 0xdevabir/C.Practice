#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clearScreen(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pauseScreen(void) {
    printf("\nPress ENTER to continue...");
    getchar();
}

void printLine(char ch, int n) {
    for (int i = 0; i < n; i++) putchar(ch);
    printf("\n");
}

void header(const char *title) {
    printf("\n");
    printLine('=', 60);
    printf("  %s\n", title);
    printLine('=', 60);
}

void readString(char *buf, int size) {
    if (fgets(buf, size, stdin) == NULL) {
        buf[0] = '\0';
        return;
    }
    size_t n = strlen(buf);
    if (n > 0 && buf[n - 1] == '\n') buf[n - 1] = '\0';
}

void readInt(int *out) {
    char buf[64];
    readString(buf, sizeof(buf));
    if (sscanf(buf, "%d", out) != 1) *out = 0;
}

void readFloat(float *out) {
    char buf[64];
    readString(buf, sizeof(buf));
    if (sscanf(buf, "%f", out) != 1) *out = 0.0f;
}

void currentDate(char *out) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(out, 15, "%d/%m/%Y", t);
}

void currentTime(char *out) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(out, 10, "%H:%M", t);
}
