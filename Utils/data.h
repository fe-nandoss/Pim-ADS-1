//
// Created by Furflesx on 26/09/17.
//

#ifndef PROJETO_ADS_DATA_H
#define PROJETO_ADS_DATA_H

#include <time.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "../Header/Cliente.h"

void defineData(t_Cliente * cli,char * tipo){

    if(strcmp(tipo,"dataLocacao") == 0){
        cabecalhoNovoCliente();
        printf("Data de locacao, Ex (DD/MM/AAAA): ");
    }
    if(strcmp(tipo,"dataDevolucao") == 0){
        printf("Data de Devolução, Ex (DD/MM/AAAA): ");
    }


    char * entradaData = malloc(100);
    char * entradaHora = malloc(100);
    int year = 0, month = 0, day = 0, hour = 0, min = 0;

    scanf("%s",entradaData);
    sscanf(entradaData, "%2d/%2d/%4d", &day, &month, &year);

    printf("Digite o horario (HH:MM): ");
    scanf("%s",entradaHora);
    sscanf(entradaHora, "%2d:%2d", &hour, &min);

    struct tm * breakdown = malloc(1000);
    breakdown->tm_year = year - 1900; /* years since 1900 */
    breakdown->tm_mon = month - 1;
    breakdown->tm_mday = day;
    breakdown->tm_hour = hour;
    breakdown->tm_min = min;

    //tipo time_t será usado para fazer o difftime()
    //printf("%s", ctime(&resultado));
    if(strcmp(tipo,"dataLocacao") == 0){
        cli->dataLocacao = breakdown;
    }
    if(strcmp(tipo,"dataDevolucao") == 0){
        cli->dataDevolucao = breakdown;
    }
}

double diffDatas(struct tm * s_data_Inicial, struct tm * s_data_Final){

    time_t t_data_Inicial;
    time_t t_data_Final;
    t_data_Inicial = mktime(s_data_Inicial);
    t_data_Final = mktime(s_data_Final);

    return difftime(t_data_Final,t_data_Inicial);
}

char * formataData(struct tm * data,char * formato){

    char dataFormatada[256];
    char * newData = (char *) malloc(sizeof(char *));
    strftime(dataFormatada, sizeof dataFormatada,formato,data);

    strcpy(newData,dataFormatada);

    return newData;
}

#endif //PROJETO_ADS_DATA_H
