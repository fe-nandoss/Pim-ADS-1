#include <stdio.h>
#include "CarrosMetodos.h"
#include "ClienteMetodos.h"

int main() {

    //Cliente cliente;
    //criaCliente(&cliente);

    t_Carro * carro = carrosDisponiveis();
    do{
        printf("valor %f\n",carro->preco);
        carro = carro->proximo;

    }
    while (carro != NULL && carro->codigo != NULL);

    printf("main");

    return 0;
}