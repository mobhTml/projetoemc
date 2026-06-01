#include <stdio.h>
#include <string.h>

struct territorio{
    char nome[30];
    char cor[10];
    int tropas;
};

int main(){
    //criando um vetor de struct para guardar 5 territorio de uma vez
    struct territorio lista_territorio[5];
    int i;

    /* logica do laço de entrada:
    utiliza um laço 'for' para rodar 5 vezes, permintindo que o usuario cadastre todos os 5 territorios em sequencia sem sobreescrever os dados.*/
    for(i = 0; i < 5; i++){
        printf("=== CADASTRO DE TERRITORIOS ===\n\n");

        printf("Digite o nome do %d territorio:\n", i + 1);
        scanf(" %[^\n]s", lista_territorio[i].nome);

        printf("Digite a Cor do exercito:\n");
        scanf(" %[^\n]s", lista_territorio[i].cor);

        printf("Digite a Quantidade de Tropas:\n");
        scanf("%d", &lista_territorio[i].tropas);

        printf("\n");

    }
    /* logica do laço de saida:
    percorre novamente o vetor de estruturas de dados preenchindo para exibir as informação de todos os registros com formatação clara.*/

    printf("=== EXIBICAO DOS DADOS CADASTRADOS ===\n");

    for(i = 0; i < 5; i++){
        printf("------------------------------\n");
        printf("Territorio %d:\n", i+1);
        printf("Nome: %s\n", lista_territorio[i].nome);
        printf("Cor do Exercito: %s\n", lista_territorio[i].cor);
        printf("Quantidade de Tropas: %d\n", lista_territorio[i].tropas);
    }
      printf("------------------------------\n");

      return 0;
}