#include <stdio.h>

void saudacao() {
    printf("OLA, MUNDO!\n");

}

int main() {
    // Declarando um ponteiro 'ptr' para uma função 
    // que não retorna nada (void) e não tem parâmetro ().

    void (*ptr)() = saudacao;
    
    // Chamando a função através do ponteiro 

    ptr();

    return 0;

}
