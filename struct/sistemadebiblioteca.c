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