#include <stdlib.h>
#include <string.h>
#include "Stud.h"


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
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("error");
        return;
    }

    Student *stud = studentsList;
    while(stud != NULL){
        fprintf(file, "%s %s %s %d %s %d %d %d\n",
                stud->surname, stud->name,
                stud->gender, stud->age,
                stud->group, stud->mark1,
                stud->mark2, stud->mark3);
        stud = stud->next;
    }

    fclose(file);
}

Student* load_students(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("error");
        return NULL;
    }

    Student *studentsList = NULL;
    char surname[25], name[25], gender[5], group[10];
    int age, mark1, mark2, mark3;

    while (fscanf(file, "%s %s %s %d %s %d %d %d",
                  surname, name, gender, &age, group, &mark1, &mark2, &mark3) == 8) {
        Student *newStudent = createStudent(surname, name, gender, age, group, mark1, mark2, mark3);
        if (studentsList == NULL) {
            studentsList = newStudent;
        } else {
            Param param;
            param.studentsList = studentsList;
            param.newStudent = newStudent;
            appendStudent(&param);
        }
    }

    fclose(file);
    return studentsList;
}