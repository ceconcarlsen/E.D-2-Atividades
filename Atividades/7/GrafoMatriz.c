/*
Gabriel Cecon Carlsen 03/02/2021
CodeBlocks
*/

#include <stdio.h>
#include <stdlib.h>

FILE *f;

int main(void){

    int permissao = 1;

    f = fopen("arquivo.txt", "r"); //abertura do arquivo em modo "read"

    if (f == NULL){
        printf("[ERRO]: Arquivo nao foi aberto corretamente. \n"); //ERRO, ponteiro apontando para null
        permissao=0;
    }

    if(permissao){ //permissão para manipulação do arquivo

      char tipo;

        tipo = fgetc(f); // pegando o 1º char do arquivo
        if ((tipo != '0') && (tipo != '1')){
         printf("[ERRO]: Tipo incorreto, verificar arquivo fonte .txt \n\n"); //ERRO, tipo deve ser 0 ou 1
         permissao = 0;
        }

    if(permissao){ //é digrafo ou grafo, logo está permitido a continuação
         char ajuda[5];
         int vertices, a1, a2;

    printf("Gabriel Cecon Carlsen, FTC-UNESP Presidente Prudente\n\n"); //Identificação

        fgetc(f);
        vertices = (int)fgetc(f) - 48; //fgetc retorna char, casting para int - 48(0) (ASCII), logo número de vértices
        fgetc(f);

        int matriz[vertices][vertices]; //matriz de adjacência

        for (a1 = 0; a1 < vertices; a1++) {
            for (a2 = 0; a2 < vertices; a2++)
                matriz[a1][a2] = 0; //zerando todas as posições da matriz
        }


        while ( fgets(ajuda, 5, f) != NULL ) {
            a1 = ((int) ajuda[0]) - 97;
            a2 = ((int) ajuda[2]) - 97;
            matriz[a1][a2] = 1;
            if (tipo == '1')
                matriz[a2][a1] = 1;
        }

        int a, b = 0, c = 0, d = 0; //variáveis auxiliares
        char aux;

        if (tipo == '1')
            printf("Grafo (Nao orientado)\n\n");
        else{
           printf("Digrafo (Orientado)\n\n");
        }

        //vértices
        printf("Vertices: ");

        for(a=0; a<vertices; a++){
            aux = (char) a+97;
            if (a==0)
                printf("%c\n", aux);
            else{
                printf("\t  %c\n", aux);
            }
        }
        a = 0;

        //ARESTAS ou ARCOS
        if (tipo == '1')
            printf("\nArestas: ");
        else {
            printf("\nArcos: ");
        }

        while (a < vertices) {
            while (b < vertices) {
                if (matriz[a][b] == 1) {
                    if (c == 0) {
                            if (tipo == '1') {
                                    printf("(%c,%c)\n", (char)(a + 97), (char)(b + 97));
                                    c++;
                            }
                            else {
                                 printf(" (%c---->%c)\n", (char)(a + 97), (char)(b + 97));
                                 c++;
                            }
                    }
                    else {
                            if (tipo == '1')
                                printf("\t (%c,%c)\n", (char)(a + 97), (char)(b + 97));
                            else {
                                printf("\t(%c---->%c)\n", (char) (a + 97), (char)(b + 97));
                            }
                    }
                    d++;
                }
                b++;
            }
            b = 0;
            a++;
        }
        a = 0, b = 0, c = 0; //resetando auxiliares

        if (tipo == '1')
                d = (int) d/2;
        printf("\n\nGraus: \n\n"); //graus

        if (tipo != '1')
            printf("\n");

            for(a; a<vertices; a++){
                aux = (char) (a + 97);
                for(b; b<vertices; b++)
                 if (matriz[a][b] == 1)
                    c++;

            b = 0;

            if (tipo == '1') {
                if (a == 0)
                    printf(" %c - %i\n", aux, c);
                else {
                    printf(" %c - %i\n", aux, c);
                }
            }
            else {
                printf("\n %c [Grau de saida]: %i", aux, c);
                c = 0;

                for(b; b<vertices; b++){
                    if (matriz[b][a] == 1)
                        c++;
                }
                b = 0;
                printf("\n %c [Grau de entrada]: %i\n", aux, c);
            }
            c = 0, a++;
        }
        printf("\n\nOrdem: %i\nTamanho: %i\n\n", vertices, d);

         fclose(f); //fechamento do arquivo
      }
     }

    printf("\t\t\t\t\t\t\tFIM DO PROGRAMA");

    printf("\n\n");
    system("pause");
    return(0);
}
