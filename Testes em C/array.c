#include <stdio.h>
#include <stdlib.h>

void printString(char *str[]) {
    if (str == NULL || *str == NULL) {
        return;
    }

    printf("%s\n", *str);  // imprime a string atual
    printString(++str);  // avança para a próxima
}

int main() {
    char *s[10];

    for (int i = 0; i < 10; i++) {
        s[i] = (char *) malloc(50);
        if (s[i] == NULL) {
            printf("Erro ao alocar memória.\n");
            exit(1);
        }
    }

    for (int i = 0; i < 10; i++) {
        scanf(" %[^\n]", s[i]);  // lê até a quebra de linha
        getchar();
    }

    printString(s);

    for (int i = 0; i < 10; i++) {
        free(s[i]);  // libera memória
    }

    return 0;
}
