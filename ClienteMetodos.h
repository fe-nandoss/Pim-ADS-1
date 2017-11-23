//
// Created by Furflesx on 26/09/17.
//

#ifndef PROJETO_ADS_CLIENTEMETODOS_H
#define PROJETO_ADS_CLIENTEMETODOS_H

#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "utils.h"
#include "Cliente.h"

typedef struct tempCliente{
    int codigo;
    char nome[50];
    int tipo;
    long dataLocacao;
    long dataDevolucao;
    struct temp * proximo;
}temp_Cliente;

void gravaCliente(t_Cliente * cliente);

t_Cliente * criaCliente(){

    t_Cliente * cli = malloc(100 * sizeof(char *));
    limpa_console();
    printf("Nome: ");
    scanf("%s",cli->nome);

    do{
        limpa_console();
        printf("Escolha uma opção abaixo\n"
                       "1 - Participante de uma ONG\n"
                       "2 - Idoso\n"
                       "3 - Nenhuma das opções\n"
                       "Opção: ");
        scanf("%d",&cli->tipo);
    }
    while (cli->tipo < 1 || cli->tipo > 3);

    limpa_console();

    printf("Digite a locação(DD/MM/AAAA): ");

    defineData(cli,"dataLocacao");
    
    gravaCliente(cli);
    
    return 0;
}

int listagemClientes(){
    
    int numeroRegistros = 1;
    char * listaClientes = txtListaClientes;
    FILE * arq = fopen(listaClientes, "r+");
    temp_Cliente * ini_cliente;
    temp_Cliente * proximo_cliente;
    
    ini_cliente = (temp_Cliente *) malloc(sizeof(temp_Cliente));
    //aloco a quantidade de memoria para ini_ponto, esse tamanho irá variar por esse motivo usso malloc
    
    if(ini_cliente == NULL)
        exit(1);
    
    proximo_cliente = ini_cliente;
    
    while((fscanf(arq,"%i %s %i %li %li\n",
                  &proximo_cliente->codigo,
                  &proximo_cliente->nome[50],
                  &proximo_cliente->tipo,
                  &proximo_cliente->dataLocacao,
                  &proximo_cliente->dataDevolucao
                  ))!=EOF){
        proximo_cliente->proximo = (temp_Cliente *) malloc(sizeof(temp_Cliente));
        proximo_cliente = proximo_cliente->proximo;
        numeroRegistros = numeroRegistros + 1;
    }
    
    proximo_cliente->proximo = NULL;
    proximo_cliente = ini_cliente;
    
    fclose(arq);
    
    return numeroRegistros;
}

void gravaCliente(t_Cliente * cliente){
    char * listaClientes = txtListaClientes;
    FILE * regCliente = fopen(listaClientes, "a+");
    int numeroDeRegistros = listagemClientes();
//    teste se o arquivo existe
    if (regCliente != NULL) {
        
        fprintf(regCliente, "%i %s %i %li\n",numeroDeRegistros,cliente->nome,cliente->tipo,mktime(cliente->dataLocacao),mktime(cliente->dataDevolucao));
    }else{
        printf("Crie o Arquivo: clientesReg.txt\n");
        exit(0);
    }

   fclose(regCliente);
    
}



#endif //PROJETO_ADS_CLIENTEMETODOS_H
