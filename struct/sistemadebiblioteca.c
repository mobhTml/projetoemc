#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Constantes globais ---
#define max_livros 50
#define max_emprestimos 100 // definimos uma capacidade para emprestimos.
#define tam_string 100

// --- definição das estruturas ---
// struct livro agora tem um campo 'disponivel' para controlar o status.
struct livro{
    char nome[tam_string];
    char autor[tam_string];
    char editora[tam_string];
    int edicao;
    int disponivel; // 1 para sim, 0 para não.
};

// nova struct para armazenar informações do empréstimo.
struct emprestimo {
    int indicelivro; // para saber qual livro do array 'biblioteca' foI emprestado.
    char nomeUsuario[tam_string];
};

// --- função para limpar o buffer de entrada ---
void limparbufferentrada(){
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
}

// ---FUNÇÃO PRINCIPAL (MAIN) ---
int main(){
    // 1. alocação dinamica de memoria
    // agora, em vez de arrays estaticos, usamos ponteiros.
    struct livro *biblioteca;
    struct emprestimo *emprestimo;


    // usammos calloc para o array de livros. calloc(num_elemento, tamanho_de_cada_elemento)
    // vantagem: inicializa toda a memoria com zeros, isso significa que 'disponivel' ja começa com 
    biblioteca =(struct livro *)calloc(max_livros, sizeof(struct livro));

    // usamos malloc para o array de emprestimos. malloc(tamanho_total_em_bytes)
    emprestimo = (struct emprestimo *)malloc(max_emprestimos * sizeof(struct emprestimo));

    //verrificação: é crucial verificar se a alocação de memoria deu certo.
    if (biblioteca == NULL || emprestimo == NULL){
        printf("erro falha ao alocar memoria.\n");
        return 1;
    }

    int totallivros = 0;
    int totalemprestimos = 0;
    int opcao;

    do{
       printf("=====================================\n");
       printf("    BIBLIOTECA - PARTE 2\n");
       printf("=====================================\n");
       printf("1 - Cadastrar novo livro\n");
       printf("2 - Listar todos os livros\n");
       printf("3 - Realizar emprestimo\n");
       printf("4 - listar emprestimos\n");
       printf("0 - Sair\n");
       printf("------------------------------------\n");
       printf("Escolha uma opcao: ");
       scanf("%d", &opcao);
       limparbufferentrada();

       switch (opcao)
       {
       case 1: // cadstro de livro 
        printf("--- cadastro de novo livro ---\n\n");
        if (totallivros < max_livros) {
            // o acesso aos campos é igual ao do array estatico
            printf("Digite o nome do livro: ");
            fgets(biblioteca[totallivros].nome, tam_string, stdin);

            printf("Digite o autor: ");
            fgets(biblioteca[totallivros].autor, tam_string,stdin);

            printf("Digite a editora: ");
            fgets(biblioteca[totallivros].editora, tam_string, stdin);

            biblioteca[totallivros].nome[strcspn(biblioteca[totallivros].nome, "\n")]= '\0';
            biblioteca[totallivros].autor[strcspn(biblioteca[totallivros].autor, "\n")]= '\0';
            biblioteca[totallivros].editora[strcspn(biblioteca[totallivros].editora, "\n")] = '\0';


            printf("digite a edicao: ");
            scanf("%d",&biblioteca[totallivros].edicao);
            limparbufferentrada();

            biblioteca[totallivros].disponivel = 1;

            totallivros++;

            printf("\nlivro cadastrado com sucesso!\n");
        }   else{
            printf("biblioteca cheia nao é possivel cadastra mais livros.\n");

        }
           printf("\npressione enter para continuar....");
           getchar();
        break;
       case 2:
            printf("-----lista de livros cadastrados ----\n\n");
            
            if(totallivros == 0){
            printf("nehum livro cadastrado ainda\n");
            } else {
            for(int i = 0; i < totallivros; i++){
             printf("-------------------------------------\n");
             printf("livro %d\n", i + 1);
             printf("nome: %s\n", biblioteca[i].nome);
             printf("autor: %s\n",biblioteca[i].autor);
              printf("editora: %s\n",biblioteca[i].editora);
            }
            printf("---------------------------------------\n");
             }
            printf("\npressione enter para continuar....");
            getchar();
            break;

            case 3:
            printf("--- realizar emprestimo ---\n\n");

            if (totalemprestimos >= max_emprestimos){
               printf("limite de emprestimos atingido!\n");
            } else {
                printf("livros disponiveis:\n");
                int disponiveis = 0;
                for (int i = 0; i < totallivros; i++) {
                    if (biblioteca[i].disponivel){
                        printf("%d - %s\n", i + 1, biblioteca[i].nome);
                        disponiveis++;
                    }

                }
                if (disponiveis == 0) {
                    printf("nenhum livro disponivel para emprestimo.\n");
                } else {
                    printf("\nDigite o numero de livro que deseja emprestar: ");
                    int numlivro;
                    scanf("%d", &numlivro);
                    limparbufferentrada();

                    int indice = numlivro - 1; // coverte para o indice do array (0 a n-1).

                    // validação da escolha do usuario.
                    if (indice >= 0 && indice < totallivros && biblioteca[indice].disponivel) {
                        printf("digite o nome do usuario que esta pegando o livro: ");
                        fgets(emprestimo[totalemprestimos].nomeUsuario, tam_string,stdin);
                        emprestimo[totalemprestimos].nomeUsuario[strcspn(emprestimo[totalemprestimos].nomeUsuario, "\n")] ='\0';

                        // registra o emprestimo
                        emprestimo[totalemprestimos].indicelivro = indice;

                        // atualiza o status do livro para indisponivel.
                        biblioteca[indice].disponivel = 0;

                        totalemprestimos++;
                        printf("\nemprestimo realizado com sucesso!\n");
                    } else {
                        printf("\nnumero de livro invalido ou livro indisponivel.\n");

                    }
                }
            }
            printf("\npressione enter para continuar...");
            getchar();
            break;

            case 4: //listar emprestimos
                printf("--- lista de emprestimos ---\n\n");
                if (totalemprestimos == 0) {
                    printf("nenhum emprestimo realizado.\n");
                } else {
                    for (int i = 0; i < totalemprestimos; i++) {
                        // usa o indice armazenado no emprestimo ara buscar o nome do livro.
                        int indicelivro = emprestimo[i].indicelivro;
                        printf("--------------------------------------------\n");
                        printf("emprestimo %d\n", i + 1);
                        printf("livro: %s\n", biblioteca[indicelivro].nome);
                        printf("usuario: %s\n", emprestimo[i].nomeUsuario);

                        
                    }
                    printf("--------------------------------------------\n");
                }
                printf("\npressione enter para continuar...");
                getchar();
                break;

            case 0:
            printf("\n saindo do sistema....\n");
            break;

            default: 
            printf("\nopcao invalida! tente novamente.\n");
            printf("\npressione enter para continuar...\n");
            getchar();
            break;
       
    
       }
    } while (opcao != 0);

    // 2. liberação da memoria
    // antes de terminar, é essecial liberar a memoria que foi alocada dinamicamente.
    // isso evita "memory leaks" (vazamentos de memória).
    free(biblioteca);
    free(emprestimo);

    printf("memoria liberada com sucesso.\n");

    return 0;
}
