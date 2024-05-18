#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <wchar.h>

int isVowels(int c) {
    c = towlower(c);

    if (c == L'а' || c == L'о' || c == L'у' || c == L'ы' || c == L'е' || c == L'ё' || c == L'ю' || c == L'я' ||
        c == L'a' || c == L'o' || c == L'u' || c == L'i' || c == L'e' || c == L'y' || c == L'u' || c == L'a') {
        return 1;
    }
    return 0;
}

int main() {
    system("chcp 65001");

    wchar_t str[100];
    int count = 0;

    printf("Введите строку: ");
    fgetws(str, sizeof(str) / sizeof(wchar_t), stdin);

    int VowCount = 0;
    int string_len = wcslen(str);

    wchar_t *word = wcstok(str, L" \n");
    while (word != NULL) {
        VowCount = 0;
        for(int i = 0; i < wcslen(word); i++) {
            if (isVowels(word[i])) {
                VowCount++;
            }
        }
        if (VowCount >= 3){
            count++;
        }
        a = wcstok(NULL, L" \n");
    }

    printf("Количество слов с 3 гласными: %d\n", count);

    return 0;
}
