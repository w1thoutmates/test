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
    }

    while(studentsList != NULL){
        int surnameSize = strlen(studentsList->surname);
        int nameSize = strlen(studentsList->name);
        int genderSize = strlen(studentsList->gender);
        int groupSize = strlen(studentsList->group);

        fwrite(&surnameSize, sizeof(int), 1, file);
        fwrite(studentsList->surname, sizeof(char), surnameSize, file);

        fwrite(&nameSize, sizeof(int), 1, file);
        fwrite(studentsList->name, sizeof(char), nameSize, file);

        fwrite(&genderSize, sizeof(int), 1, file);
        fwrite(studentsList->gender, sizeof(char), genderSize, file);

        fwrite(&studentsList->age, sizeof(int), 1, file);

        fwrite(&groupSize, sizeof(int), 1, file);
        fwrite(studentsList->group, sizeof(char), groupSize, file);

        fwrite(&studentsList->mark1, sizeof(int), 1, file);
        fwrite(&studentsList->mark2, sizeof(int), 1, file);
        fwrite(&studentsList->mark3, sizeof(int), 1, file);

        studentsList = studentsList->next;
    }

    fclose(file);
}

Student* load_students(Student* studentsList, const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }

    while(!feof(file)) {
        int surnameSize;
        int nameSize;
        int genderSize;
        int groupSize;
        fread(&surnameSize, sizeof(int), 1, file);
        studentsList->surname = calloc(sizeof(char),surnameSize + 1);
        studentsList->surname[surnameSize] = '\0';

        fread(&nameSize, sizeof(int), 1, file);
        studentsList->name = calloc(sizeof(char),nameSize + 1);
        studentsList->name[nameSize] = '\0';

        fread(&genderSize, sizeof(int), 1, file);
        studentsList->gender = calloc(sizeof(char),genderSize + 1);
        studentsList->gender[genderSize] = '\0';

        fread(&studentsList->age, sizeof(int), 1, file);

        fread(&groupSize, sizeof(int), 1, file);
        studentsList->group = calloc(sizeof(char),groupSize + 1);
        studentsList->group[groupSize] = '\0';

        fread(&studentsList->mark1, sizeof(int), 1, file);
        fread(&studentsList->mark2, sizeof(int), 1, file);
        fread(&studentsList->mark3, sizeof(int), 1, file);


    }

    free(studentsList);
    fclose(file);
    return studentsList;
    }
