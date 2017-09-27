#include <stdio.h>
#include "CarrosMetodos.h"
#include "ClienteMetodos.h"
#include "Cliente.h"

int main() {

    Cliente cliente;
    criaCliente(&cliente);

    int max;
    max = numeroDeCarros(); //numero maximo de registros no Txt
    Carro carro[max];
    carrosDisponiveis(carro);



//    FILE *novoArquivo;
//
//    novoArquivo = fopen("/Volumes/Dr Manhattan/Projects/ADS-UNIP/projeto_ads/arquivo.txt","a+");
//    fputs("sou um arquivo legal",novoArquivo);
//    fflush(novoArquivo);
//    fclose(novoArquivo);
    return 0;
}