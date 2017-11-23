#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Carro.h"
#include <paths.h>
#include "_globals.h"

t_Carro * listaVeiculos(){
    
    char * listaCarros = txtListaCarros;
    t_Carro * ini_carro;
    t_Carro * proximo_carro;
    FILE * arq = fopen(listaCarros, "r");
    
    ini_carro = (t_Carro *) malloc(sizeof(t_Carro));
    //aloco a quantidade de memoria para ini_ponto, esse tamanho irá variar por esse motivo usso malloc
    
    if(ini_carro == NULL)
        exit(1);
    
    proximo_carro = ini_carro;
    
    while((fscanf(arq,"%d %s %s %s %f %s\n",&proximo_carro->codigo,&proximo_carro->modelo[50],&proximo_carro->marca[50],&proximo_carro->placa[50],&proximo_carro->preco,&proximo_carro->status[50]))!=EOF){
        proximo_carro->proximo = (t_Carro *) malloc(sizeof(t_Carro));
        proximo_carro = proximo_carro->proximo;
    }
    
    proximo_carro->proximo = NULL;
    proximo_carro = ini_carro;
    
    return proximo_carro;
}

t_Carro * carrosDisponiveis(){
    
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

