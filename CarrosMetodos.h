#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Carro.h"
#include <paths.h>
#define txt "/Users/furflesx/projetos/ADS-UNIP/projeto_ads/carrosDisponiveis.txt"

t_Carro * carrosDisponiveis(){

    t_Carro * ini_carro;
    t_Carro * proximo_carro;
    FILE * arq = fopen(txt, "r");

    ini_carro = (t_Carro *) malloc(sizeof(t_Carro));
    //oloco a quantidade de memoria para ini_ponto, esse tamanho irá variar por esse motivo usso malloc

    if(ini_carro == NULL)
        exit(1);

    proximo_carro = ini_carro;

    while((fscanf(arq,"%d %s %s %s %f %s\n",&proximo_carro->codigo,&proximo_carro->modelo[50],&proximo_carro->marca[50],&proximo_carro->placa[50],&proximo_carro->preco,&proximo_carro->status_alugado))!=EOF){
        proximo_carro->proximo = (t_Carro *) malloc(sizeof(t_Carro));
        proximo_carro = proximo_carro->proximo;
    }

    proximo_carro->proximo = NULL;
    proximo_carro = ini_carro;

    return proximo_carro;
}