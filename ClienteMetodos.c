//
//  ClienteMetodos.c
//  Pim
//
//  Created by Furflesx on 25/11/2017.
//  Copyright © 2017 Furflesx. All rights reserved.
//

#include "Header/H_ClienteMetodos.h"
#include "CarroMetodos.c"

t_Cliente * criaCliente(){

    t_Cliente * cli = (t_Cliente *) malloc(sizeof(t_Cliente));
    resetaStructCliente(cli);

    limpa_console();
    cabecalhoNovoCliente();
    printf("Nome: ");

    scanf("%s",cli->nome);

    float desconto = 1.00;
    int opcao = 0;

    do{
        limpa_console();
        cabecalhoNovoCliente();
        printf("Participante de uma ONG\n"
               "<1> Sim || <2> Nao\n"
               "Opcao: ");
        scanf("%d",&opcao);
    }
    while (opcao < 1 || opcao > 2);

    if(opcao == 1)
        desconto += -0.05;

    limpa_console();

    do{
        limpa_console();
        cabecalhoNovoCliente();
        printf("Idoso\n"
               "<1> Sim || <2> Nao\n"
               "Opcao: ");
        scanf("%d",&opcao);
    }
    while (opcao < 1 || opcao > 2);

    if(opcao == 1)
        desconto += -0.10;

    desconto = floorf(desconto * 100) / 100;
    cli->desconto = desconto;

    limpa_console();



    defineData(cli,"dataLocacao");

    cli->codigo_veiculo = selecionaVeiculo();

    gravaCliente(cli);

    return cli;
}

temp_Cliente * listaClientes(){
    
    char * listaClientes = PATH_TXT_CLIENTES;
    FILE * arq = fopen(listaClientes, "r+");
    temp_Cliente * ini_cliente;
    temp_Cliente * proximo_cliente;
    
    ini_cliente = (temp_Cliente *) malloc(sizeof(temp_Cliente));
    //aloco a quantidade de memoria para ini_ponto, esse tamanho irá variar por esse motivo usso malloc
    
    if(ini_cliente == NULL)
        exit(1);
    
    proximo_cliente = ini_cliente;

    while((fscanf(arq,"%i %s %f %i/%i/%i %i:%i %i/%i/%i %i:%i %i\n",
    //while((fscanf(arq,"%i %s %f %i/%i/%i %i:%i:%i %i/%i/%i %i:%i:%i %i\n",
                  &proximo_cliente->codigo
                  ,proximo_cliente->nome
                  ,&proximo_cliente->desconto
                  ,&proximo_cliente->dataLocacao.tm_mday
                  ,&proximo_cliente->dataLocacao.tm_mon
                  ,&proximo_cliente->dataLocacao.tm_year
                  ,&proximo_cliente->dataLocacao.tm_hour
                  ,&proximo_cliente->dataLocacao.tm_min
                  ,&proximo_cliente->dataDevolucao.tm_mday
                  ,&proximo_cliente->dataDevolucao.tm_mon
                  ,&proximo_cliente->dataDevolucao.tm_year
                  ,&proximo_cliente->dataDevolucao.tm_hour
                  ,&proximo_cliente->dataDevolucao.tm_min
                  ,&proximo_cliente->codigo_veiculo
                  ))!=EOF){

        proximo_cliente->dataLocacao.tm_year += -1900;
        proximo_cliente->dataLocacao.tm_mon += - 1;
        proximo_cliente->dataDevolucao.tm_year += -1900;
        proximo_cliente->dataDevolucao.tm_mon += - 1;

        proximo_cliente->proximo = (temp_Cliente *) malloc(sizeof(temp_Cliente));
        proximo_cliente = proximo_cliente->proximo;
    }
    
    proximo_cliente->proximo = NULL;
    proximo_cliente = ini_cliente;
    
    fclose(arq);

    return proximo_cliente;
}

int totalClientes(temp_Cliente * clientes){

    int totalClientes = 1;

    while (clientes != NULL && clientes->proximo != NULL){
        totalClientes += 1;
        clientes = clientes->proximo;
    }

    return totalClientes;
}

void gravaCliente(t_Cliente * cliente){
    char * TXT_CLIENTES = PATH_TXT_CLIENTES;
    FILE * regCliente = fopen(TXT_CLIENTES, "a+");
    int numeroDeRegistros = totalClientes(listaClientes());
    int opcao;
    //    teste se o arquivo existe
    if (regCliente != NULL) {
        char data_locacao[256]; strftime(data_locacao, sizeof data_locacao, "%d/%m/%Y %H:%M", cliente->dataLocacao);
        char data_devolucao[256]; strftime(data_devolucao, sizeof data_devolucao,"%d/%m/%Y %H:%M", cliente->dataDevolucao);
        fprintf(regCliente, "%i %s %.2f %s %s %i\n",numeroDeRegistros,cliente->nome,cliente->desconto,data_locacao,data_devolucao,cliente->codigo_veiculo);

        strftime(data_locacao, sizeof data_locacao, "%d/%m/%Y as %H:%M", cliente->dataLocacao);
        t_Carro * carroLocado = retornaVeiculo(cliente->codigo_veiculo);

        while (opcao < 1 || opcao > 2){
            limpa_console();
            cabecalhoNovoCliente();
            printf("Cliente: %s\n",cliente->nome);
            printf("Ticket: %d\n",numeroDeRegistros);
            printf("Data locacao: %s\n",data_locacao);
            printf("Carro: %s - %s\n",carroLocado->marca,carroLocado->modelo);
            printf("Preco Diaria: R$ %.2f\n",carroLocado->preco * cliente->desconto);

            printf("\n\nIr para o menu?\n"
                   "<1> Sim | <2> Nao, Sair do programa.\n");
            scanf("%d",&opcao);
        }

        if(opcao == 1)
            menuPrincipal();

        if(opcao == 2)
            exit(0);

    }else{
        printf("Crie o Arquivo: clientesReg.txt\n");
        exit(0);
    }
    
    fclose(regCliente);

}

void sobreEscreveClientes(temp_Cliente * listaClientes){

            char * TXT_CLIENTES = PATH_TXT_CLIENTES;
            FILE * regCliente = fopen(TXT_CLIENTES, "w+");

            while (listaClientes != NULL && listaClientes->proximo != NULL) {

                char data_locacao[256];
                char data_devolucao[256];

                strftime(data_locacao, sizeof data_locacao, "%d/%m/%Y %H:%M", &listaClientes->dataLocacao);
                strftime(data_devolucao, sizeof data_devolucao, "%d/%m/%Y %H:%M", &listaClientes->dataDevolucao);

                printf("\nnome: %s data final %s\n", listaClientes->nome, data_devolucao);
                fprintf(regCliente, "%i %s %.2f %s %s %i\n", listaClientes->codigo, listaClientes->nome,
                        listaClientes->desconto, data_locacao, data_devolucao, listaClientes->codigo_veiculo);
                listaClientes = listaClientes->proximo;
            }
}

void resetaStructCliente(t_Cliente * cliente){

    strcpy(cliente->nome,"");
    cliente->dataLocacao = resetaStructData();
    cliente->dataDevolucao = resetaStructData();
    cliente->codigo = 0;
    cliente->codigo_veiculo = 0;
    cliente->desconto = 0.00;

}

void alteraCliente(temp_Cliente * listacliente,int codCliente){

    t_Cliente * cliente = (t_Cliente *) malloc(sizeof(t_Cliente));
    limpa_console();
    while (listacliente != NULL && listacliente->proximo != NULL){

        if(listacliente->codigo == codCliente){
            copyStructCliente(listacliente,cliente,"cliente");
            defineData(cliente,"dataDevolucao");
            copyStructCliente(listacliente,cliente,"temp");
            printf("nome %s",listacliente->nome);
        }

        listacliente = listacliente->proximo;
    }

}

void copyStructCliente(temp_Cliente * temp_cliente, t_Cliente * t_cliente, char * destino){

    if(strcmp(destino,"temp") == 0){
        temp_cliente->codigo = t_cliente->codigo;
        temp_cliente->dataDevolucao = *t_cliente->dataDevolucao;
        temp_cliente->dataLocacao = *t_cliente->dataLocacao;
        temp_cliente->codigo_veiculo = t_cliente->codigo_veiculo;
        temp_cliente->desconto = t_cliente->desconto;
        strcpy(temp_cliente->nome,t_cliente->nome);
    }

    if(strcmp(destino,"cliente") == 0){
        t_cliente->codigo = temp_cliente->codigo;
        t_cliente->dataDevolucao = &temp_cliente->dataDevolucao;
        t_cliente->dataLocacao = &temp_cliente->dataLocacao;
        t_cliente->codigo_veiculo = temp_cliente->codigo_veiculo;
        t_cliente->desconto = temp_cliente->desconto;
        strcpy(t_cliente->nome,temp_cliente->nome);
    }
}

struct tm * resetaStructData(){

    time_t rawtime;
    struct tm * timeinfo;
    char buffer [80];

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );

    strftime (buffer,80,"Now it's %y/%m/%d.",timeinfo);
    timeinfo->tm_year = 0 - 1900;
    timeinfo->tm_mday = 1;
    timeinfo->tm_mon = 0;
    return  timeinfo;
}
