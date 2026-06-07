#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// definindo o tipo territorio usando typedef para facilitar o uso de ponteiros
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
}territorio;


// PROTOTIPOS DAS FUNCOES (MODULARIZÇÃO)
void cadastrarterritorios(territorio* mapa, int quantidade);
void exibirterritorios(territorio* mapa, int quantidade);
void atacar(territorio* atacante, territorio*defensor); 
void liberarmemoria(territorio* mapa);

int main(){
    // garante a aleatoridade que sera usada na função de ataqui mais tarde
    srand(time(NULL));

    int quantidade;
    printf("Digite o numero total de trritorio a cadastrar: ");
    scanf("%d",&quantidade);

    // alocação dinâmica do vetor structs usando calloc (limpa amemoria com zeros)
    territorio* lista_territorio = (territorio*)calloc(quantidade, sizeof (territorio));
    
    // validacao simple para garantir que a memoria foi alocada 
    if (lista_territorio == NULL){
        printf("erro ao alocar memoria.\n");
        return 1;
    }

    // chamada das funções passando o ponteiro da lista
    cadastrarterritorios(lista_territorio,quantidade);
    exibirterritorios(lista_territorio, quantidade);

    int idxatacante, idxdefensor;
    printf("\n=== HORA DO ATAQUE ===\n");
    printf("escolha o numero do territorio atacante (1 a %d): ", quantidade);
    scanf("%d", &idxatacante);
    printf("escolha o numero do territorio defensor (1 a %d): ", quantidade);
    scanf("%d",&idxdefensor);

    // ajustando o numero que o usuario digitou para o idice do vetor (que começa em 0)
    idxatacante--;
    idxdefensor--;
    // strcmp retorna 0 se as strings forem perfeitamente iguais
    if(strcmp(lista_territorio[idxatacante].cor, lista_territorio[idxdefensor].cor) == 0) {
        printf("\n[ERRO] voce nao pode atacar um territorio da sua propria cor (%s)!\n", lista_territorio[idxatacante].cor);
    } else {
        // se as cores forem difierentes, manda os endereços (&) para a função de ataque 
        atacar(&lista_territorio[idxatacante], &lista_territorio[idxdefensor]);
    }
    
    // exibe o mapa atualizado para ver o resultado da guerra
    exibirterritorios(lista_territorio, quantidade);


    // liberação de memoria obrigatoria antes de fechar o programa 
    liberarmemoria(lista_territorio);

    return 0;
}

// função para cadastrar os dados usando ponteiros 
void cadastrarterritorios(territorio* mapa, int quantidade ){
    int i;
    for (i = 0; i < quantidade; i++){
        printf("\n=== CADASTRO DE TERRITORIO %d ===\n", i + 1);

        printf("digite o nome do territorio: ");
        scanf(" %[^\n]s", mapa[i].nome);

        printf("digite a cor do exercito: ");
        scanf(" %[^\n]s", mapa[i].cor);

        printf("digite a quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

// funcao para exibir os dados utilizando ponteiros
void exibirterritorios(territorio* mapa, int quantidade){
    int i;
    printf("\n=== EXIBICAO DOS DADOS CADASTRADOS ===\n");
    for(i = 0; i < quantidade; i++) {
        printf("----------------------------------------------\n");
        printf("territorio %d:\n", i + 1);
        printf("nome: %s\n", mapa[i].nome);
        printf("cor do exercito: %s\n", mapa[i].cor);
        printf("quantidade de tropas: %d\n", mapa[i].tropas);
    }
    printf("----------------------------------------------\n");
}

// nova função: logica de combate usado seta (->)

void atacar(territorio* atacante, territorio* defensor) {
    // sorteia um numero de 1 a 6 para cada um
    int dadoatacante = (rand() % 6) + 1;
    int dadodefensor = (rand() % 6) + 1;

    printf("\n--- CONFRONTO: %s vs %s ---\n", atacante->nome, defensor->nome);
    printf("dado do atacante [%s]: %d\n", atacante->nome, dadoatacante );
    printf("dado de defensor [%s]: %d\n",defensor->nome, dadodefensor);

    // critério: atacante só ganha se o dado for maior. empate ou menor é defesa
    if (dadoatacante > dadodefensor) {
        printf("\nVITORIA DO ATACANTE! %s conquistou %s!\n", atacante->nome, defensor->nome);

        // o territorio defensor muda para a cor do atacante 
        strcpy(defensor->cor, atacante->cor);

        // o defensor recebe metade das tropas do atacante
        defensor->tropas = atacante->tropas / 2;

        // o atacante perde as tropas que enviou para ocupar o novo territorio
        atacante->tropas = atacante->tropas - defensor->tropas;
    } else {
        printf("\nVITORIA DA DEFESA! %s resistiu ao ataque.\n", defensor->nome);
        // atacante perde uma tropa por ter falhado
        atacante->tropas--;
    }
}

// funcao para liberar a memoria alocada dinamicamente
void liberarmemoria(territorio* mapa){
    free(mapa);
    printf("\n[memoria liberada com sucesso!]\n");
}