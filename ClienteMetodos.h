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
#include <math.h>

typedef struct tempCliente{
    int codigo;
    char nome[50];
    float desconto;
    long dataLocacao;
    long dataDevolucao;
    int codigo_veiculo;
    struct temp * proximo;
}temp_Cliente;

void gravaCliente(t_Cliente * cliente);

t_Cliente * criaCliente(){

    t_Cliente * cli = (t_Cliente *) malloc(sizeof(t_Cliente));
    limpa_console();
    printf("Nome: ");
    scanf("%s",cli->nome);

    float desconto = 1.00;
    int opcao = 0;
    
    do{
        limpa_console();
        printf("Participante de uma ONG\n"
               "<1> Sim || <2> Não\n"
               "Opção: ");
        scanf("%d",&opcao);
    }
    while (opcao < 1 || opcao > 2);

    if(opcao == 1)
        desconto += -0.05;
    
    limpa_console();

    do{
        limpa_console();
        printf("Idoso\n"
               "<1> Sim || <2> Não\n"
               "Opção: ");
        scanf("%d",&opcao);
    }
    while (opcao < 1 || opcao > 2);
    
    if(opcao == 1)
        desconto += -0.10;
    
    desconto = floorf(desconto * 100) / 100;
    cli->desconto = desconto;
    
    limpa_console();
    
    printf("Digite a locação(DD/MM/AAAA): ");

    defineData(cli,"dataLocacao");
    
    cli->codigo_veiculo = 1;
    cli->dataDevolucao = 0;
    
    gravaCliente(cli);
    
    return cli;
}

int listagemClientes(){
    
    int numeroRegistros = 1;
    char * listaClientes = PATH_TXT_CLIENTES;
    FILE * arq = fopen(listaClientes, "r+");
    temp_Cliente * ini_cliente;
    temp_Cliente * proximo_cliente;
    
    ini_cliente = (temp_Cliente *) malloc(sizeof(temp_Cliente));
    //aloco a quantidade de memoria para ini_ponto, esse tamanho irá variar por esse motivo usso malloc
    
    if(ini_cliente == NULL)
        exit(1);
    
    proximo_cliente = ini_cliente;
    
    while((fscanf(arq,"%i %s %f %li %li %i\n",
                  &proximo_cliente->codigo,
                  &proximo_cliente->nome[50],
                  &proximo_cliente->desconto,
                  &proximo_cliente->dataLocacao,
                  &proximo_cliente->dataDevolucao,
                  &proximo_cliente->codigo_veiculo
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
    char * listaClientes = PATH_TXT_CLIENTES;
    FILE * regCliente = fopen(listaClientes, "a+");
    int numeroDeRegistros = listagemClientes();
//    teste se o arquivo existe
    if (regCliente != NULL) {
        
        fprintf(regCliente, "%i %s %f %li %li %i\n",numeroDeRegistros,cliente->nome,cliente->desconto,mktime(cliente->dataLocacao),mktime(cliente->dataDevolucao),cliente->codigo_veiculo);
        printf("arquivo criado com sucesso");
    }else{
        printf("Crie o Arquivo: clientesReg.txt\n");
        exit(0);
    }

   fclose(regCliente);
    
}



#endif //PROJETO_ADS_CLIENTEMETODOS_H
