#include <stdlib.h>
#include <string.h>
#include "stud.h"


Student* createStudent(char* surname, char* name, char* gender, int age, char* group, int mark1, int mark2, int mark3) {
    Student* newStudent = malloc(sizeof(Student));
    strcpy(newStudent->surname, surname);
    strcpy(newStudent->name, name);
    strcpy(newStudent->gender, gender);
    newStudent->age = age;
    strcpy(newStudent->group, group);
    newStudent->mark1 = mark1;
    newStudent->mark2 = mark2;
    newStudent->mark3 = mark3;
    newStudent->next = NULL;
    newStudent->printStudent = printStudent;
    newStudent->appendStudent = appendStudent;
    newStudent->NoTwoNoThree = NoTwoNoThree;
    newStudent->save_student = save_student;
    newStudent->load_students = load_students;
    return newStudent;
}

void appendStudent(void* param) {
    Param *appendParam = (Param*)param;
    Student* newStudent = appendParam->newStudent;
    Student* studentsList = appendParam->studentsList;
    Student* cur_elem = studentsList;

    while(cur_elem->next != NULL){
        cur_elem = cur_elem->next;
    }
    cur_elem->next = newStudent;
}

int NoTwoNoThree(void *student) {
    Student *stud = (Student*)student;
    return stud->mark1 > 3 && stud->mark2 > 3 && stud->mark3 > 3;
}

void printStudent(void *student) {
    Student *stud = (Student*)student;
    printf("Фамилия: %s\n", stud->surname);
    printf("Имя: %s\n", stud->name);
    printf("Пол: %s\n", stud->gender);
    printf("Возраст: %d\n", stud->age);
    printf("Группа: %s\n", stud->group);
    printf("Оценка по математике: %d\n", stud->mark1);
    printf("Оценка по физике: %d\n", stud->mark2);
    printf("Оценка по химии: %d\n\n", stud->mark3);
}
void save_student(Student *studentsList,const char *filename){
    FILE* file = fopen(filename, "wb");

    Student *stud = studentsList;
    while(stud != NULL){
        fwrite(stud, sizeof(Student), 1, file);
        stud = stud->next;
    }

    fclose(file);
}

Student* load_students(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }

    Student *studentsList = NULL;
    Student stud;

    while (fread(&stud, sizeof(Student), 1, file) == 1) {
        char *surname = malloc(strlen(stud.surname) + 1);
        char *name = malloc(strlen(stud.name) + 1);
        char *gender = malloc(strlen(stud.gender) + 1);
        char *group = malloc(strlen(stud.group) + 1);

        strcpy(surname, stud.surname);
        strcpy(name, stud.name);
        strcpy(gender, stud.gender);
        strcpy(group, stud.group);

        Student *newStudent = createStudent(surname, name, gender, stud.age, group, stud.mark1, stud.mark2, stud.mark3);
        if (studentsList == NULL) {
            studentsList = newStudent;
        }
        else {
            Param param;
            param.studentsList = studentsList;
            param.newStudent = newStudent;
            appendStudent(&param);
        }
    }

    fclose(file);
    return studentsList;
}