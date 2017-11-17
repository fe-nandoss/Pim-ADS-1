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

void listaCliente(void);
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

    char * msg;
    msg = defineData(cli,"dataLocacao");
    
    gravaCliente(cli);

    return 0;
}

void gravaCliente(t_Cliente * cliente){
    char * listaClientes = txtListaClientes;
    FILE * regCliente = fopen(listaClientes, "a+");
    
//    teste se o arquivo existe
    if (regCliente != NULL) {
        
        fprintf(regCliente, "%i %s %i %li %li\n",1,cliente->nome,cliente->tipo,mktime(cliente->dataLocacao),mktime(cliente->dataDevolucao));
    }else{
        printf("Crie o Arquivo: clientesReg.txt\n");
        exit(0);
    }

   fclose(regCliente);
    
    printf("deseja listar os clientes? <1> sim | <2> não : ");
    int opcao;
    scanf("%i",&opcao);
    
    if (opcao == 1) {
       listaCliente();
    }else{
        printf("obrg");
    }
    
}

void listaCliente(){
    
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
                  &proximo_cliente->nome,
                  &proximo_cliente->tipo,
                  &proximo_cliente->dataLocacao,
                  &proximo_cliente->dataDevolucao
                  ))!=EOF){
        proximo_cliente->proximo = (temp_Cliente *) malloc(sizeof(temp_Cliente));
        proximo_cliente = proximo_cliente->proximo;
    }

    proximo_cliente->proximo = NULL;
    proximo_cliente = ini_cliente;

    temp_Cliente * newCliente = proximo_cliente;
    do{
        printf("\nvalor %s\n",newCliente->nome);
        newCliente = newCliente->proximo;

    }
    while (newCliente != NULL && newCliente->proximo != NULL);

    printf("deseja criar novo cliente? <1> sim | <2> não : ");
    int opcao;
    scanf("%i",&opcao);
    
    if (opcao == 1) {
        criaCliente();
    }else{
        printf("obrg");
    }
}

#endif //PROJETO_ADS_CLIENTEMETODOS_H
