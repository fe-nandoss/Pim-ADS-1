#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "Carro.h"
#define txt "/Volumes/Dr Manhattan/Projects/ADS-UNIP/projeto_ads/carrosDisponiveis.txt"
#define MAX 100

void carrosDisponiveis(Carro x[MAX]){

    int i=0;
    FILE *arq;

    arq = fopen(txt, "r");
    if(arq == NULL){
        printf("Erro, nao foi possivel abrir o arquivo\n");
    }
    else{
        while( (fscanf(arq,"%d %20s %20s %20s %f %20s\n", &x[i].codigo, x[i].modelo, x[i].marca, x[i].placa,&x[i].preco, x[i].status_alugado))!=EOF ){
            i++;
        }
    }

    fclose(arq);

}