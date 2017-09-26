#include <stdio.h>
#include "CarrosDisponiveis.h"

int main() {

    Carro carro[100];
    carrosDisponiveis(carro);

    for(int i=0;i<20;i++){
        printf("Modelos: %s - preco: %.2f\n",carro[i].modelo,carro[i].preco);
    }
    return 0;
}