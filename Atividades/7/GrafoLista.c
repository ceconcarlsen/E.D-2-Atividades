/*
Gabriel Cecon Carlsen 03/02/2021
CodeBlocks 13.12
*/

#include <stdio.h>
#include <stdlib.h>

//STRUCTS
struct grafo {
    char c;
    struct grafo *baixo;
    struct grafo *direita;
};

struct inicio {   //aponta para o inicio da lista
    struct grafo *ini;
};


//FUNÇÕES
void Inicializa(struct inicio *G) {
    G->ini = NULL;
}

void Insercao(struct inicio *G, char c, char a, int op) { // Inserção do vértice: erro com ini == null perdir ajuda !
    struct grafo *aux1;
    struct grafo *aux2;
    aux1 = G->ini;
    while(1) {
        if (op == 0) {
            if (G->ini == NULL) {
                struct grafo *Novo = (struct grafo*)malloc(sizeof(struct grafo));
                Novo->c = c, Novo->baixo = NULL, Novo->direita = NULL;
                G->ini = Novo;
                break;
            }
            else if (aux1->baixo == NULL) {
                struct grafo *Novo = (struct grafo*)malloc(sizeof(struct grafo));
                Novo->c = c, Novo->baixo = NULL, Novo->direita = NULL;
                aux1->baixo = Novo;
                break;
            }
            else {
                    aux1 = aux1->baixo;
            }
        }
        else {
            while (aux1->c != a) {
                    aux1 = aux1->baixo;
            }
            aux2 = aux1->direita;
            while(1) {
                if (aux2 == NULL) {
                    struct grafo *Novo = (struct grafo*)malloc(sizeof(struct grafo));
                    Novo->c = c, Novo->baixo = NULL, Novo->direita = NULL;
                    aux1->direita = Novo;
                    break;
                }
                else {
                    aux1 = aux1->direita; aux2 = aux1->direita;
                }
            }
            break;
        }
    }
}

void vertices(int quant, char op) {
    int a = 0;
    char aux;

    if (op == '1')  printf("Grafo (Nao Orientado) \n\n");
    else {
            printf("Digrafo (Orientado) \n\n");
    }

    printf("Vertices: ");
    while (a < quant) {
        aux = (char) (a + 97);
        if (a == 0)  printf("%c\n", aux);
        else {
            printf("\t  %c\n", aux);
        }
        a++;
    }
}

void arestas_arcos(struct inicio *G, char op) {
    int a = 0;
    struct grafo *aux1;
    struct grafo *aux2;
    aux1 = G->ini;

    if (op == '1')  printf("\nArestas: ");
    else {
            printf("\nArcos: ");
    }

    while (aux1 != NULL) {
        aux2 = aux1->direita;
        while (aux2 != NULL) {
            if (a == 0) {
                    if (op == '1') { printf("(%c, %c)\n", aux1->c, aux2->c); a++; }
                    else { printf("  (%c ----> %c)\n", aux1->c, aux2->c); a++; }
            }
            else {
                    if (op == '1') { printf("\t (%c, %c)\n", aux1->c, aux2->c); }
                    else { printf("\t (%c ----> %c)\n", aux1->c, aux2->c); }
            }
            aux2 = aux2->direita;
        }
        aux1 = aux1->baixo;
    }
}

void graus(struct inicio *G, char op, int amount) {
    int a[amount], b = 0, c = 0, aux;
    struct grafo *aux1;
    struct grafo *aux2;

    while (b < amount) {
        a[b] = 0;
        b++;
    }
    b = 0;
    aux1 = G->ini;
    printf("\n\nGraus: \n\n");

    while (aux1 != NULL) {
        aux = ((int) aux1->c) - 97;
        aux2 = aux1->direita;
        while (aux2 != NULL) {
            a[aux]++;
            aux2 = aux2->direita;
        }
        if (op == '0') { printf("\n %c [Grau de saida]: %i", aux1->c, a[aux]); }
        aux1 = aux1->baixo;
    }
    if (op == '0') {
        printf("\n");
        while (b < amount) {
            a[b] = 0;
            b++;
        }
        b = 0;
    }
    aux1 = G->ini;
    while (aux1 != NULL) {
        aux2 = aux1->direita;
        while (aux2 != NULL) {
            aux = ((int) aux2->c) - 97;
            a[aux]++;
            aux2 = aux2->direita;
        }
        aux1 = aux1->baixo;
    }
    while (c < amount) {
        if (op == '1') {
            if (c == 0) printf("%c - %i\n", ((char)(c + 97)), a[c]);
            else {
                    printf("%c - %i\n", ((char)(c + 97)), a[c]);
            }
        }
        else {
            printf("\n %c [Grau de Entrada]: %i", ((char) (c + 97)), a[c]);
    }
        c++;
    }
}

void ordem_tamanho(int ordem, int tamanho) {
    printf("\n\nOrdem: %i \nTamanho: %i\n\n", ordem, tamanho);
}




FILE *f;
char tipo, ajuda[5];

int main(void) {

    struct inicio I;
    int vertice, aux = 0;
    char aux1, aux2;
    int permissao = 1;

    Inicializa(&I);
    f = fopen("arquivo.txt", "r"); // abrindo o arquivo no modo "read"
    if (f == NULL) {
            printf("[ERRO]: Arquivo nao foi aberto corretamente.\n\n");
            permissao = 0;
    }

    if(permissao) {
         tipo = fgetc(f); // verificando se é um Dígrafo ou Grafo


         if ((tipo != '0') && (tipo != '1')) {
                printf("[ERRO]: Tipo incorreto, verificar arquivo fonte .txt\n\n");
                permissao = 0;
         }

         if(permissao){
         fgetc(f);
         vertice = (int)fgetc(f) - 48; // verificando o número de vértices
         fgetc(f);

         while (aux < vertice) {

            aux1 = (char) (aux + 97);
            Insercao(&I, aux1, '0', 0);
            aux++;
         }
         aux = 0;
         while (fgets(ajuda, 5, f) != NULL ) {

            aux1 = (char) ajuda[0];
            aux2 = (char) ajuda[2];
            Insercao(&I, aux2, aux1, 1);
            aux++;

         }

        printf("Gabriel Cecon Carlsen, FTC-UNESP Presidente Prudente\n\n"); //Identificação

         vertices(vertice, tipo); //vértices
         arestas_arcos(&I, tipo); //arestas e arcos
         graus(&I, tipo, vertice); //graus
         ordem_tamanho(vertice, aux); //ordem e tamanho
    }

    fclose(f); //fechamento do arquivo

    }

    printf("\t\t\t\t\t\t\tFIM DO PROGRAMA");

    printf("\n\n\n");
    system("pause");
    return(0);
}
