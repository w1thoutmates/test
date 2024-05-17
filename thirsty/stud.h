#ifndef STUD_H
#define STUD_H

#include <stdio.h>

typedef struct Student {
    char surname[25];
    char name[20];
    char gender[5];
    int age;
    char group[10];
    int mark1;
    int mark2;
    int mark3;
    struct Student *next;
    void (*printStudent)(void*);
    void (*appendStudent)(void*);
    int (*NoTwoNoThree)(void*);
} Student;

typedef struct Param {
    Student *studentsList;
    Student *newStudent;
} Param;

Student* createStudent(char* surname, char* name, char* gender, int age, char* group, int mark1, int mark2, int mark3);
void appendStudent(void* param);
int NoTwoNoThree(void *student);
void printStudent(void *student);
void save_student(Student *studentsList,const char *filename);
Student* load_students(const char *filename);
#endif