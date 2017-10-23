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

    printf("\nmain data: %s\n",ctime(&cli->dataLocacao));
}

#endif //PROJETO_ADS_CLIENTEMETODOS_H
