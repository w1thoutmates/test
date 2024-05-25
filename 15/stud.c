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
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }
    Student *stud = studentsList;
    while(stud != NULL){
        fwrite(stud.surname, sizeof(stud.surname), 1, file);
        fwrite(stud.name, sizeof(stud.name), 1, file);
        fwrite(stud.gender, sizeof(stud.gender), 1, file);
        fwrite(stud.age, sizeof(stud.age), 1, file);
        fwrite(stud.group, sizeof(stud.group), 1, file);
        fwrite(stud.mark1, sizeof(stud.mark1), 1, file);
        fwrite(stud.mark2, sizeof(stud.mark2), 1, file);
        fwrite(stud.mark3, sizeof(stud.mark3), 1, file);
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
    char surname[30];
    char name[30];
    char gender[10];
    char group[10];
    
    Student *studentsList = NULL;
    while(!feof(file)){
        Student *student = malloc(sizeof(Student));
        surname = malloc((strlen(student.surname) + '\0');
        name = malloc((strlen(student.name) + '\0');
        gender = malloc((strlen(student.gender) + '\0');
        group = malloc((strlen(student.group) + '\0');

        strcpy(surname, student.surname);
        strcpy(name, student.name);
        strcpy(gender, student.gender);
        strcpy(group, student.group);

        fread(surname, sizeof(surname), 1, file);
        fread(name, sizeof(name), 1, file);
        fread(gender, sizeof(gender), 1, file);
        fread(student.age, sizeof(student.age), 1, file);
        fread(group, sizeof(group), 1, file);
        fread(student.mark1, sizeof(student.mark1), 1, file);
        fread(student.mark2, sizeof(student.mark2), 1, file);
        fread(student.mark3, sizeof(student.mark3), 1, file);

    free(student);
    fclose(file);
    return studentsList;
}
