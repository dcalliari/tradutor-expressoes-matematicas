#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_EXPRESSION_LENGTH 256
#define MAX_STACK_SIZE 256

typedef struct {
    char items[MAX_STACK_SIZE];
    int top;
} Stack;

void initStack(Stack* s) {
    s->top = -1;
}

int isStackEmpty(Stack* s) {
    return s->top == -1;
}

int isStackFull(Stack* s) {
    return s->top == MAX_STACK_SIZE - 1;
}

void push(Stack* s, char item) {
    if (isStackFull(s)) {
        fprintf(stderr, "Erro: Pilha cheia!\n");
        return; 
    }
    s->items[++(s->top)] = item;
}

char pop(Stack* s) {
    if (isStackEmpty(s)) {
        fprintf(stderr, "Erro: Pilha vazia ao tentar desempilhar!\n");
        return '\0';
    }
    return s->items[(s->top)--];
}

char peek(Stack* s) {
    if (isStackEmpty(s)) {
        return '\0';
    }
    return s->items[s->top];
}

int obterPrecedencia(char op) {
    if (op == '^')
        return 3;
    if (op == '*' || op == '/')
        return 2;
    if (op == '+' || op == '-')
        return 1;
    return 0;
}

int infixaParaPosfixa(const char* infixa, char* posfixa) {
    Stack pilha;
    initStack(&pilha);
    int k = 0;

    for (int i = 0; infixa[i] != '\0'; i++) {
        char token = infixa[i];

        if (isspace(token)) {
            continue;
        }

        if (isalnum(token)) {
            posfixa[k++] = token;
        } else if (token == '(') {
            push(&pilha, token);
        } else if (token == ')') {
            while (!isStackEmpty(&pilha) && peek(&pilha) != '(') {
                posfixa[k++] = pop(&pilha);
            }
            if (!isStackEmpty(&pilha) && peek(&pilha) == '(') {
                pop(&pilha);
            } else {
                fprintf(stderr, "Erro: Parênteses desbalanceados na expressão '%s'.\n", infixa);
                posfixa[0] = '\0';
                return 0;
            }
        } else {
            while (!isStackEmpty(&pilha) && obterPrecedencia(peek(&pilha)) >= obterPrecedencia(token)) {
                posfixa[k++] = pop(&pilha);
            }
            push(&pilha, token);
        }
    }

    while (!isStackEmpty(&pilha)) {
        if (peek(&pilha) == '(') {
            fprintf(stderr, "Erro: Parênteses desbalanceados na expressão '%s'.\n", infixa);
            posfixa[0] = '\0';
            return 0;
        }
        posfixa[k++] = pop(&pilha);
    }

    posfixa[k] = '\0';
    return 1;
}

int main(int argc, char* argv[]) {
    char arquivoEntradaNome[FILENAME_MAX];
    char arquivoSaidaNome[FILENAME_MAX];

    if (argc == 3) {
        strncpy(arquivoEntradaNome, argv[1], FILENAME_MAX - 1);
        arquivoEntradaNome[FILENAME_MAX - 1] = '\0';
        strncpy(arquivoSaidaNome, argv[2], FILENAME_MAX - 1);
        arquivoSaidaNome[FILENAME_MAX - 1] = '\0';
    } else if (argc == 1) {
        printf("Digite o nome do arquivo de entrada: ");
        if (scanf("%s", arquivoEntradaNome) != 1) {
            fprintf(stderr, "Erro ao ler nome do arquivo de entrada.\n");
            return 1;
        }
        printf("Digite o nome do arquivo de saida: ");
        if (scanf("%s", arquivoSaidaNome) != 1) {
            fprintf(stderr, "Erro ao ler nome do arquivo de saida.\n");
            return 1;
        }
    } else {
        fprintf(stderr, "Uso: tradutor_c <arquivo_entrada> <arquivo_saida>\n");
        fprintf(stderr, "Ou execute sem argumentos para modo interativo.\n");
        return 1;
    }

    FILE* arquivoEntrada = fopen(arquivoEntradaNome, "r");
    FILE* arquivoSaida = fopen(arquivoSaidaNome, "w");

    if (arquivoEntrada == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo de entrada: %s\n", arquivoEntradaNome);
        return 1;
    }

    if (arquivoSaida == NULL) {
        fprintf(stderr, "Erro ao criar o arquivo de saida: %s\n", arquivoSaidaNome);
        fclose(arquivoEntrada);
        return 1;
    }

    char linhaInfixa[MAX_EXPRESSION_LENGTH];
    char linhaPosfixa[MAX_EXPRESSION_LENGTH * 2];

    while (fgets(linhaInfixa, sizeof(linhaInfixa), arquivoEntrada) != NULL) {
        linhaInfixa[strcspn(linhaInfixa, "\n")] = 0;
        linhaInfixa[strcspn(linhaInfixa, "\r")] = 0;

        if (strlen(linhaInfixa) == 0) continue;

        if (infixaParaPosfixa(linhaInfixa, linhaPosfixa)) {
            fprintf(arquivoSaida, "%s\n", linhaPosfixa);
        } else {
            fprintf(arquivoSaida, "Erro ao processar: %s\n", linhaInfixa);
        }
    }

    printf("Tradução concluida. Resultados em: %s\n", arquivoSaidaNome);

    fclose(arquivoEntrada);
    fclose(arquivoSaida);

    return 0;
}
