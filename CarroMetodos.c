//
//  CarroMetodos.c
//  Pim
//
//  Created by Furflesx on 25/11/2017.
//  Copyright © 2017 Furflesx. All rights reserved.
//

#include "Header/H_CarroMetodos.h"

t_Carro * listaVeiculos(){
    
    char * listaCarros = PATH_TXT_CARROS;
    t_Carro * ini_carro;
    t_Carro * proximo_carro;
    FILE * arq = fopen(listaCarros, "r");
    
    ini_carro = (t_Carro *) malloc(sizeof(t_Carro));
    //aloco a quantidade de memoria para ini_ponto, esse tamanho irá variar por esse motivo usso malloc
    
    if(ini_carro == NULL)
        exit(1);
    
    proximo_carro = ini_carro;
    
    while((fscanf(arq,"%d %s %s %s %f %s\n",&proximo_carro->codigo,proximo_carro->modelo,proximo_carro->marca,proximo_carro->placa,&proximo_carro->preco,proximo_carro->status))!=EOF){
        proximo_carro->proximo = (t_Carro *) malloc(sizeof(t_Carro));
        proximo_carro = proximo_carro->proximo;
    }
    
    proximo_carro->proximo = NULL;
    proximo_carro = ini_carro;
    
    return proximo_carro;
}

t_Carro * veiculosDisponiveis(){
    
    t_Carro * carrosDisponiveis = listaVeiculos();
    
    if (carrosDisponiveis != NULL){
        t_Carro *no = carrosDisponiveis, *aux = no->proximo, *anterior = NULL;
        while (aux != NULL)
        {
            if (no == carrosDisponiveis)
            {
                if (strcmp(no->status,"alugado") == 0)
                {
                    carrosDisponiveis = aux;
                    free(no);
                    no = carrosDisponiveis;
                    aux = aux->proximo;
                }
                else
                {
                    anterior = no;
                    no = no->proximo;
                    aux = aux->proximo;
                }
            }
            else
            {
                if (strcmp(no->status,"alugado") == 0)
                {
                    anterior->proximo = aux;
                    free(no);
                    no = aux;
                    aux = aux->proximo;
                }
                else
                {
                    anterior = no;
                    no = no->proximo;
                    aux = aux->proximo;
                }
            }
        }
        //condição para o último nó
        if (strcmp(no->status,"alugado") == 0)
        {
            free(no);
            carrosDisponiveis = NULL;
            
        }
    }
    
    return carrosDisponiveis;
    
}

void gravaVeiculos(t_Carro * listaDeCarros){
    
    char * TXTPATHCARROS = PATH_TXT_CARROS;
    FILE * arq = fopen(TXTPATHCARROS, "w+");
    while (listaDeCarros != NULL && listaDeCarros->proximo != NULL) {
        fprintf(arq,"%d %s %s %s %.0f %s\n",listaDeCarros->codigo,listaDeCarros->modelo,listaDeCarros->marca,listaDeCarros->placa,listaDeCarros->preco,listaDeCarros->status);
        listaDeCarros = listaDeCarros->proximo;
    }
    
    fclose(arq);
}

void alteraVeiculo(t_Carro * listaDeCarros, int codigo_veiculo){
    
    while (listaDeCarros != NULL && listaDeCarros->proximo != NULL) {
        if(listaDeCarros->codigo == codigo_veiculo){
            printf("\nCarro escolhido - cod %i - carro: %s\n",listaDeCarros->codigo,listaDeCarros->modelo);
            strcpy(listaDeCarros->status,"alugado") ;
        }
        listaDeCarros = listaDeCarros->proximo;
    }
}
