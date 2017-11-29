//
// Created by Kelvin Furfles on 29/11/2017.
//
#include "Header/H_Interface.h"

#include "Utils/utils.h"
#include "ClienteMetodos.c"

void menuPrincipal(){

    int opcao = 0;


    do{
        limpa_console();
        printf("->Bem Vindo<-");
        printf("\nMenu:\n"
                       "1: Cadastrar Novo Cliente\n"
                       "2: Devolução de Veiculo\n"
                       "3: Relatorio\n"
                       "4: Sair do Programa\n");
        printf("\nOpcao: ");
        scanf("%d",&opcao);
    }
    while (opcao < 1 || opcao > 2);

    switch (opcao){
        case 1:
            novoCliente();
            break;

        case 2:
            limpa_console();
            printf("devolucao veiculo");
            break;

        case 3:
            limpa_console();
            printf("relatorio");
            break;

        case 4:
            limpa_console();
            printf("sair do programa");
            break;

        default:
            limpa_console();
            printf("sair do programa");
            break;
    }

}

void novoCliente(){

    limpa_console();
    t_Cliente * cliente = criaCliente();

}