//
//  ClienteMetodos.c
//  Pim
//
//  Created by Furflesx on 25/11/2017.
//  Copyright © 2017 Furflesx. All rights reserved.
//

#include "Header/H_ClienteMetodos.h"
#include "CarroMetodos.c"

void criaCliente(){

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

        fclose(regCliente);

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

        fprintf(regCliente, "%i %s %.2f %s %s %i\n", listaClientes->codigo, listaClientes->nome,
                listaClientes->desconto, data_locacao, data_devolucao, listaClientes->codigo_veiculo);
        listaClientes = listaClientes->proximo;
    }

    fclose(regCliente);
}

void resetaStructCliente(t_Cliente * cliente){

    strcpy(cliente->nome,"");
    cliente->dataLocacao = resetaStructData();
    cliente->dataDevolucao = resetaStructData();
    cliente->codigo = 0;
    cliente->codigo_veiculo = 0;
    cliente->desconto = 0.00;

}

t_Cliente * alteraCliente(temp_Cliente * listacliente,int codCliente){

    t_Cliente * cliente = (t_Cliente *) malloc(sizeof(t_Cliente));
    limpa_console();
    while (listacliente != NULL && listacliente->proximo != NULL){

        if(listacliente->codigo == codCliente){
            copyStructCliente(listacliente,cliente,"cliente");
            defineData(cliente,"dataDevolucao");
            copyStructCliente(listacliente,cliente,"temp");
        }

        listacliente = listacliente->proximo;
    }


    return cliente;

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

void resumoLocacaoCliente(double diff,t_Cliente * cliente,t_Carro * carro){

    double valorTotal = round(diff/60/60/24) * (carro->preco * cliente->desconto);
    int opcao = 0;


    while (opcao < 1 || opcao > 2){

        limpa_console();
        cabecalhoResumoCliente();
        printf("Nome: %s\n",cliente->nome);
        printf("Ticket: %d\n",cliente->codigo);
        printf("Locado em: %s\n",formataData(cliente->dataLocacao,"%d/%m/%Y as %H:%M"));
        printf("Devolvido em: %s\n",formataData(cliente->dataDevolucao,"%d/%m/%Y as %H:%M"));
        printf("Carro: %s %s\n",carro->marca,carro->modelo);
        printf("Placa: %s\n",carro->placa);
        printf("Total a pagar: R$ %.2f\n",valorTotal);

        printf("\n\nIr para menu inicial?\n<1> Sim || <2> Não, sair do programa.\nopcao: ");
        scanf("%d",&opcao);
    }

    if(opcao == 1)
        menuPrincipal();

    if(opcao == 2)
        exit(0);
}

void devolucaoCliente(){

    int opcao,op;
    int numeroClientesMax;
    int auxContador = 0;
    int codClienteEscolhido = 1;
    int codCarroCliente = 0;
    int semClientes = 0;
    int min =0,max=0;
    int primeiroCliente = 0;

    char data_devolucao[256];

    temp_Cliente * auxClientes = listaClientes();
    temp_Cliente * clientes;
    t_Cliente * clienteSelecionado = (t_Cliente *) malloc(sizeof(t_Cliente));

    t_Carro * carro;

    while (opcao < min || opcao > max){
        numeroClientesMax = 0;
        clientes = auxClientes;
        limpa_console();
        cabecalhoDevolucaoCliente();

        while (clientes != NULL && clientes->proximo != NULL) {

            carro = retornaVeiculo(clientes->codigo);
            if(strcmp(formataData(&clientes->dataDevolucao,"%d/%m/%Y"),"01/01/0000") == 0){
                if(primeiroCliente == 0){
                    min = clientes->codigo;
                }
                printf("Ticket: %d | Cliente: %s | Locado em: %s | Carro: %s %s | Placa: %s\n",
                       clientes->codigo, clientes->nome, formataData(&clientes->dataLocacao,"%d/%m/%Y as %H:%M"),carro->marca, carro->modelo, carro->placa);
                numeroClientesMax++;

                max = clientes->codigo;
                primeiroCliente = 1;
            }

            clientes = clientes->proximo;
        }
        if(numeroClientesMax >= 1){
            printf("\nDigite o numero do ticket: ");
            scanf("%d",&opcao);
        }else{
            limpa_console();
            semClientes = 1;
            break;
        }

    }


    if(semClientes == 0){

        clientes = auxClientes;

        while (clientes != NULL && clientes->proximo != NULL){
            if(clientes->codigo == opcao){
                codClienteEscolhido = clientes->codigo;
                codCarroCliente = clientes->codigo_veiculo;
                copyStructCliente(clientes,clienteSelecionado,"cliente");
            }
            auxContador++;
            clientes = clientes->proximo;
        }

        clientes = auxClientes;

        clienteSelecionado = alteraCliente(clientes,codClienteEscolhido);
        sobreEscreveClientes(clientes);

        double diffTime = diffDatas(clienteSelecionado->dataLocacao,clienteSelecionado->dataDevolucao);

        t_Carro * listaCarros = listaVeiculos();
        alteraVeiculo(listaCarros,codCarroCliente,"devolver");
        gravaVeiculos(listaCarros);
        resumoLocacaoCliente(diffTime,clienteSelecionado,retornaVeiculo(clienteSelecionado->codigo_veiculo));
    }else{
        while (op < 1 || op > 2){
            limpa_console();
            printf("***************************************************\n");
            printf("**** SEM CLIENTES PARA REALIZAR A DEVOLUCAO    ****\n");
            printf("***************************************************\n");

            printf("\n\nIr para menu inicial?\n<1> Sim || <2> Não, sair do programa.\nopcao: ");
            scanf("%d",&op);
        }

        if(op == 1)
            menuPrincipal();

        if(op == 2)
            exit(0);

    }

}

void relatorioClientes(){

    temp_Cliente * clientesComDevolucao = listaClientes();
    temp_Cliente * clientesDevolucaoAndamento = clientesComDevolucao;
    int op,tipoRelatorio;

    while (tipoRelatorio < 1 || tipoRelatorio > 2){
        limpa_console();
        printf("***************************************************\n");
        printf("****             TIPO DE RELATORIO             ****\n");
        printf("***************************************************\n");

        printf("\n\nQual Tipo de Relatorio?\n<1> Com Devolucao || <2> Locacao em Andamento.\nopcao: ");
        scanf("%d",&tipoRelatorio);
    }

    if(totalClientes(clientesComDevolucao) -1 > 0){

        if(tipoRelatorio == 1){

            while (clientesComDevolucao != NULL && clientesComDevolucao->proximo != NULL){
                limpa_console();
                cabecalhoRelatorioDevolucaoCliente();
                t_Carro * carro =  retornaVeiculo(clientesComDevolucao->codigo_veiculo);
                double diffTime = diffDatas(&clientesComDevolucao->dataLocacao,&clientesComDevolucao->dataDevolucao);
                double valorTotal = round(diffTime/60/60/24) * (carro->preco * clientesComDevolucao->desconto);

                if(strcmp(formataData(&clientesComDevolucao->dataDevolucao,"%d/%m/%Y"),"01/01/0000") == 0) {
                    printf("\n**********************************************************\n"
                                   "Ticket: %d\n"
                                   "Cliente: %s\n"
                                   "Carro: %s\n"
                                   "Placa: %s\n"
                                   "Data Locacao: %s\n"
                                   "Data Devolucao: %s\n"
                                   "Preco Diaria: R$ %.2f"
                                   "\tTotal Pago: R$ %.2f"
                                   "\n**********************************************************\n\n",
                           clientesComDevolucao->codigo,
                           clientesComDevolucao->nome,
                           carro->modelo,
                           carro->placa,
                           formataData(&clientesComDevolucao->dataLocacao, "%d/%m/%Y"),
                           formataData(&clientesComDevolucao->dataDevolucao, "%d/%m/%Y"),
                           carro->preco * clientesComDevolucao->desconto,
                           valorTotal
                    );
                }

                clientesComDevolucao = clientesComDevolucao->proximo;
            }

            while (op < 1 || op > 2){
                printf("\n\nIr para o menu?\n"
                               "<1> Sim | <2> Nao, Sair do programa.\n");
                scanf("%d",&op);
            }

            if(op == 1)
                menuPrincipal();

            if(op == 2)
                exit(0);

        }else{
            limpa_console();
            cabecalhoRelatorioSemDevolucaoCliente();
            while (clientesDevolucaoAndamento != NULL && clientesDevolucaoAndamento->proximo != NULL){
                t_Carro * carro =  retornaVeiculo(clientesDevolucaoAndamento->codigo_veiculo);
                double diffTime = diffDatas(&clientesDevolucaoAndamento->dataLocacao,&clientesDevolucaoAndamento->dataDevolucao);
                double valorTotal = round(diffTime/60/60/24) * (carro->preco * clientesDevolucaoAndamento->desconto);

                if(strcmp(formataData(&clientesDevolucaoAndamento->dataDevolucao,"%d/%m/%Y"),"01/01/0000") == 0) {
                    printf("\n**********************************************************\n"
                                   "Ticket: %d\n"
                                   "Cliente: %s\n"
                                   "Carro: %s\n"
                                   "Placa: %s\n"
                                   "Data Locacao: %s\n"
                                   "\n**********************************************************\n\n",
                           clientesDevolucaoAndamento->codigo,
                           clientesDevolucaoAndamento->nome,
                           carro->modelo,
                           carro->placa,
                           formataData(&clientesDevolucaoAndamento->dataLocacao, "%d/%m/%Y")
                    );
                }

                clientesDevolucaoAndamento = clientesDevolucaoAndamento->proximo;
            }

            while (op < 1 || op > 2){
                printf("\n\nIr para o menu?\n"
                               "<1> Sim | <2> Nao, Sair do programa.\n");
                scanf("%d",&op);
            }

            if(op == 1)
                menuPrincipal();

            if(op == 2)
                exit(0);

        }

    }
    else{

        while (op < 1 || op > 2){
            limpa_console();
            printf("***************************************************\n");
            printf("****    SEM CLIENTES PARA GERAR RELATORIO    ****\n");
            printf("***************************************************\n");

            printf("\n\nIr para menu inicial?\n<1> Sim || <2> Não, sair do programa.\nopcao: ");
            scanf("%d",&op);
        }

        if(op == 1)
            menuPrincipal();

        if(op == 2)
            exit(0);
    }


}