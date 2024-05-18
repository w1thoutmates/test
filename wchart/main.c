#include <stdio.h>
#include <string.h>
#include <ctype.h>

int isVowels(int c) {
    c = tolower(c);

    if (c == 'а' || c == 'о' || c == 'у' || c == 'ы' || c == 'е' || c == 'ё' || c == 'ю' || c == 'я' ||
        c == 'a' || c == 'o' || c == 'u' || c == 'i' || c == 'e' || c == 'y' || c == 'u' || c == 'a') {
        return 1;

    }
    return 0;
}

int main() {
    system("chcp 65001");

    char str[100];
    int count = 0;

    printf("Введите строку: ");
    fgets(str, sizeof(str), stdin);

    int VowCount = 0;
    int string_len = strlen(str);

    char *token = strtok(str, " \n");
    while (token != NULL) {
        VowCount = 0;
        for(int i = 0; i < strlen(token); i++) {
            if (isVowels(token[i])) {
                VowCount++;
            }
        }
        if (VowCount >= 3){
            count++;
        }
        token = strtok(NULL, " \n");
    }

    printf("Количество слов с 3 гласными: %d\n", count);

    return 0;
}