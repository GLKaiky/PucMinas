#include <stdio.h>
#include <stdlib.h>

typedef struct No{
    int valor;
    struct No* esq;
    struct No* dir;
}No;

No* insert(int value) {
    No* ptr = (No*) malloc (sizeof(No) * 1);
    ptr->dir = NULL;   
    ptr->esq = NULL;

    ptr->valor = value;

    return ptr;
}

void inserirArvore(No* ptr, int valor) {

    if(ptr->valor > valor && ptr->esq != NULL) {
        inserirArvore(ptr->esq, valor);
    }else if(ptr->valor < valor && ptr->dir != NULL) {
        inserirArvore(ptr->dir, valor);
    } else {
        if(ptr->valor < valor) {
            ptr->dir = insert(valor);
            return;
        }else if(ptr->valor > valor){
            ptr->esq = insert(valor);
            return;
        }else {
            ptr = insert(valor);
        }
    }
}

int main() {
    No* ptr;

    int valor = 5;

    inserirArvore(ptr, valor);

    printf("%d", ptr->valor);
}