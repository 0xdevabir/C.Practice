#ifndef STUDENT_H
#define STUDENT_H

#include "structs.h"

void studentMenu(void);
void addStudent(void);
void viewAllStudents(void);
void searchStudent(void);
void updateStudent(void);
void deleteStudent(void);
Student* findStudentById(int id);

#endif