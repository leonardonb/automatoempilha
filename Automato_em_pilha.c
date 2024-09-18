#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX 100

typedef struct {
    int topo;
    char itens[MAX];
} Pilha;

void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

void empilhar(Pilha *p, char item) {
    if (p->topo < MAX - 1) {
        p->itens[++(p->topo)] = item;
    }
}

char desempilhar(Pilha *p) {
    if (p->topo >= 0) {
        return p->itens[(p->topo)--];
    }
    return '\0';
}

int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

int automatoAceita(char *cadeia) {
    Pilha pilha;
    inicializarPilha(&pilha);

    int estado = 0;
    int i = 0;
    char simbolo;

    if (strlen(cadeia) == 0) {
        return 1;
    }

    while (cadeia[i] != '\0') {
        simbolo = cadeia[i];

        switch (estado) {
            case 0:
                if (simbolo == 'a') {
                    empilhar(&pilha, 'a');
                } else if (simbolo == 'b') {
                    if (pilhaVazia(&pilha)) {
                        return 0;
                    }
                    desempilhar(&pilha);
                    estado = 1;
                } else {
                    return 0;
                }
                break;

            case 1:
                if (simbolo == 'b') {
                    if (pilhaVazia(&pilha)) {
                        return 0;
                    }
                    desempilhar(&pilha);
                } else {
                    return 0;
                }
                break;
        }
        i++;
    }

    return estado == 1 && pilhaVazia(&pilha);
}

int exibirMenu() {
    int opcao;
    printf("\nMenu de opções:\n");
    printf("1. Rodar cadeias de exemplo\n");
    printf("2. Digitar a própria cadeia\n");
    printf("3. Sair\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);
    getchar();
    return opcao;
}

void rodarCadeiasExemplo() {
    char cadeias[7][MAX] = {"aabb", "aaabbb", "", "abab", "aaaabbbb", "abbabbaabb", "ababa"}; // Se modificar o número de palavras lembrar de modificar o número de cadeias nessa linha e na linha abaixo

    printf("\nRodando cadeias de exemplo:\n");
    for (int i = 0; i < 7; i++) {
        if (automatoAceita(cadeias[i])) {
            printf("A cadeia '%s' é aceita.\n", cadeias[i]);
        } else {
            printf("A cadeia '%s' é rejeitada.\n", cadeias[i]);
        }
    }
}

void digitarCadeia() {
    char cadeia[MAX];

    printf("\nDigite a cadeia que deseja testar: ");
    fgets(cadeia, MAX, stdin);

    cadeia[strcspn(cadeia, "\n")] = '\0';

    if (strlen(cadeia) == 0) {
        printf("Você digitou uma cadeia vazia.\n");
    }

    if (automatoAceita(cadeia)) {
        printf("A cadeia '%s' é aceita.\n", cadeia);
    } else {
        printf("A cadeia '%s' é rejeitada.\n", cadeia);
    }
}

int main() {

    setlocale(LC_ALL, "Portuguese");

    int opcao;

    do {
        opcao = exibirMenu();

        switch (opcao) {
            case 1:
                rodarCadeiasExemplo();
                break;
            case 2:
                digitarCadeia();
                break;
            case 3:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }

    } while (opcao != 3);

    return 0;
}
