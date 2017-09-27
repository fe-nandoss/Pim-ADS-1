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

void criaCliente(struct Cliente * cli){

    struct tm data;
    iniciaData(&data);

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

    defineMinuto(&data);

    defineHora(&data);

    defineDia(&data);

    defineMes(&data);

    defineAno(&data);

    printData(&data,cli);

//
//
//    int mes;
//    do{
//
//    }while (mes < 1 || mes > 12);
//
//    data.tm_mon = mes - 1;
//
//    do{
//     limpa_console();
//        printf("Digite o ano: ");
//        scanf("%d",&data.tm_year);
//    }while (data.tm_year < 2017 || data.tm_year > 2018);
}

#endif //PROJETO_ADS_CLIENTEMETODOS_H
