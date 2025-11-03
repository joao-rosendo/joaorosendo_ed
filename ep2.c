// Implementando fila utilizando lista ligada

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


//////// OPCIONAL para utilizar pegacara //////////
#include <termios.h>
#include <unistd.h>
///////////////////////////////////////////////////


typedef struct no {
    int numero;
    struct no *proximo;
} NoListaLigada;


typedef struct {
    NoListaLigada *frente;  // início
    NoListaLigada *tras;    // final
} Fila;

// Inicializa a fila
void inicializarFila(Fila *f) {
    f->frente = NULL;
    f->tras = NULL;
}

// Enfileirando
void enfileirar(Fila *f, int valor) {
    NoListaLigada *novoNo = malloc(sizeof(NoListaLigada));
    if (!novoNo) {
        printf("\nERRO de alocação de memória\n");
        exit(-1);
    }
    novoNo->numero = valor;
    novoNo->proximo = NULL;

    if (f->tras == NULL) {
        f->frente = novoNo;
        f->tras = novoNo;
    } else {
        f->tras->proximo = novoNo;
        f->tras = novoNo;
    }
}

// Desinfileirando
int desinfileirar(Fila *f, int *valor) {
    if (f->frente == NULL) return 0; // Fila vazia

    NoListaLigada *temp = f->frente;
    *valor = temp->numero;
    f->frente = f->frente->proximo;

    if (f->frente == NULL) // Se ficou vazia
        f->tras = NULL;

    free(temp);
    return 1;
}

// Frente (peek)
int frente(Fila *f, int *valor) {
    if (f->frente == NULL) return 0;
    *valor = f->frente->numero;
    return 1;
}

// Fila vazia
int filavazia(Fila *f) {
    return f->frente == NULL;
}

/////////////////////////////////
// Função para ler apenas 1 caracter do teclado - sem ENTER
int pegacara() {
    struct termios old_tio, new_tio;
    char ch;
    tcgetattr(STDIN_FILENO, &old_tio);
    new_tio = old_tio;
    new_tio.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);
    return toupper(ch);
}

void clear_stdin_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
////////////////

// main
int main() {
    Fila f;
    inicializarFila(&f);
    int valor;
    char op = 0;

    while (op != 'X') {
        printf("\nOperações: Enfileirar(E), Desinfileirar(D), Frente(F), Vazia(V), Sair(X): ");
        op = pegacara();
        printf(" -> %c\n", op);

        switch (op)
	{
        case 'E':
	/* code Enf */
            printf("Entre com valor: ");
            scanf("%d", &valor);
            clear_stdin_buffer();
            enfileirar(&f, valor);
            break;
        case 'D':
	/* code Desinf */
            if (desinfileirar(&f, &valor))
                printf("Valor removido: %d\n", valor);
            else
                printf("Fila vazia\n");
            break;
        case 'F':
	/* code FRENTE */
            if (frente(&f, &valor))
                printf("Valor na frente da fila: %d\n", valor);
            else
                printf("Fila vazia\n");
            break;
        case 'V':
	/* code VAZIA */
            if (filavazia(&f))
                printf("Fila vazia\n");
            else
                printf("Fila contém elementos\n");
            break;
        case 'X':
            printf("Encerrando...\n");
            break;
        default:
            printf("Opção inválida: %c\n", op);
            break;
        }
    }
    return 0;
}
