#include <stdio.h>
#include <stdlib.h>
#include "stud.h"

#define ОЧИСТИТЬ(i) free(i)

int main() {
    system("chcp 65001");

    Student *studentsList = createStudent("Никифоров", "Денчик", "man", 17, "исп-206", 4, 5, 4);
    Student *student2 = createStudent("Семенов", "Ярослав", "man", 17, "исп-206", 5, 4, 2);
    Student *student3 = createStudent("Гераськина", "Настя", "woman", 17, "исп-206", 3, 3, 3);
    Student *student4 = createStudent("Давыденко", "Рома", "man", 17, "исп-206", 4, 4, 4);


    Param param1;
    param1.studentsList = studentsList;
    param1.newStudent = student2;
    appendStudent(&param1);

    Param param2;
    param2.studentsList = studentsList;
    param2.newStudent = student3;
    appendStudent(&param2);

    Param param3;
    param3.studentsList = studentsList;
    param3.newStudent = student4;
    appendStudent(&param3);


    printf("Студенты, у которых нет двоек и троек:\n\n");
    Student* cur_elem = studentsList;
    while (cur_elem != NULL) {
        if (NoTwoNoThree(cur_elem)) {
            printStudent(cur_elem);
        }
        cur_elem = cur_elem->next;
    }

    save_student(studentsList, "D:\\students.txt");

    ОЧИСТИТЬ(studentsList);
    ОЧИСТИТЬ(student2);
    ОЧИСТИТЬ(student3);
    ОЧИСТИТЬ(student4);

    studentsList = load_students("D:\\students.txt");
    return 0;
}
