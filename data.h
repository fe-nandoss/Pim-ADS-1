//
// Created by Furflesx on 26/09/17.
//

#ifndef PROJETO_ADS_DATA_H
#define PROJETO_ADS_DATA_H

#include <time.h>
#include <stdio.h>
#include "utils.h"
#include "Cliente.h"

char * defineData(Cliente * cli,char * tipo){

    time_t resultado = 0;
    char * entradaData = malloc(20);
    char * entradaHora = malloc(20);
    int year = 0, month = 0, day = 0, hour = 0, min = 0;

    scanf("%s",entradaData);
    printf("%s",entradaData);
    sscanf(entradaData, "%2d/%2d/%4d", &day, &month, &year);

    limpa_console();

    printf("Digite o horário (HH:MM): ");
    scanf("%s",entradaHora);
    sscanf(entradaHora, "%2d:%2d", &hour, &min);

    struct tm breakdown = {0};
    breakdown.tm_year = year - 1900; /* years since 1900 */
    breakdown.tm_mon = month - 1;
    breakdown.tm_mday = day;
    breakdown.tm_hour = hour - 1;
    breakdown.tm_min = min;

    resultado = mktime(&breakdown);
    //tipo time_t será usado para fazer o difftime()

    if(tipo == "dataLocacao"){
        cli->dataLocacao = resultado;
    }

    if(tipo == "dataDevolucao"){
        cli->dataDevolucao = resultado;
    }

    return entradaData;
}

#endif //PROJETO_ADS_DATA_H
