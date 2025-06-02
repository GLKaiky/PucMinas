#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printNames(char **names) {
    
    printf("%s\n", *names);
    
    if (*(++names) == NULL) {
        return;
    }
    printNames(++names);
}

int main() {
    char *Lista[5];

    for (int i = 0; i < 5; i++) {
        Lista[i] = (char*) malloc(50 * sizeof(char));
        if (Lista[i] == NULL) {
            printf("Erro de alocação\n");
            return 1;
        }

        scanf("%s", Lista[i]);
        getchar();  // captura '\n', embora nesse caso possa ser desnecessário com %s
    }

    printNames(Lista);

    // Liberar memória alocada
    for (int i = 0; i < 5; i++) {
        free(Lista[i]);
    }

    return 0;
}
