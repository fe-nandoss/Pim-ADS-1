//
// Created by Furflesx on 26/09/17.
//

#ifndef PROJETO_ADS_DATA_H
#define PROJETO_ADS_DATA_H

#include <time.h>
#include <stdio.h>
#include "utils.h"
#include "ClienteMetodos.h"
#include "Cliente.h"

typedef struct mesesDoAno{
    char mes[30];
    int max_dia;
}mesesDoAno;

void meses(struct mesesDoAno meses[12]){

    char *mes[12] = {"Janeiro","Fevereiro","Março","Abril","Maio","Junho","Julho","Agosto","Setembro","Outubro","Novembro","Dezembro"};
    int dias[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

    for(int i=0;i<12;i++){
        strcpy(meses[i].mes,mes[i]);
        meses[i].max_dia = dias[i];
    }
}

void iniciaData(struct tm * data){

    data->tm_year = 2017;
    data->tm_mon = 0;
    data->tm_mday = 1;
    data->tm_hour = 0;
    data->tm_min = 0;
    data->tm_sec = 0;
}

void printData(struct tm * data,struct Cliente * cli){
    limpa_console();
    printf("Cliente: %s\n",cli->nome);
    printf("tipo: %d\n",cli->tipo);
    printf("ano: %d\n",data->tm_year);
    printf("mes: %d\n",data->tm_mon);
    printf("dia: %d\n",data->tm_mday);
    printf("hora: %d\n",data->tm_hour);
    printf("minuto: %d\n",data->tm_min);
}

void defineMinuto(struct tm * data){
    limpa_console();
    do{
        limpa_console();
        printf("Digite o minuto: ");
        scanf("%d",&data->tm_min);
    }
    while (data->tm_min < 0 || data->tm_min > 59);
}

void defineHora(struct tm * data){
    do{
        limpa_console();
        printf("Digite a hora: ");
        scanf("%d",&data->tm_hour);
    }while (data->tm_hour < 0 || data->tm_hour > 23);

}

void defineDia(struct tm * data){
    do{
        limpa_console();
        printf("Digite o dia: ");
        scanf("%d",&data->tm_mday);
    }
    while ( data->tm_mday < 1 || data->tm_mday > 31);
    printf("dia escolhido: %d",data->tm_mday);
    system("pause");
}

void defineMes(struct tm * data){

    struct mesesDoAno mes[12];
    int mesEscolhido,mesesDisponiveis;
    meses(mes);
    do{
        mesesDisponiveis=0;
        limpa_console();
        printf("Escolha o mes:\n");
        for(int i = 0;i<12;i++){
            if(data->tm_mday <= mes[i].max_dia){
                printf("%d - %s\n",i,mes[i].mes);
                mesesDisponiveis++;
            }
        }
        printf("opção: ");
        scanf("%d",&mesEscolhido);
    }
    while (mesEscolhido < 0 || 11 < mesEscolhido);

    printf("mes escolhido: %d",mesEscolhido);
    printf("mes escolhido: %d",mesEscolhido);

    data->tm_mon = mesEscolhido;

}

void defineAno(struct tm * data){
    do{
        limpa_console();
        printf("Defina o ano: ");
        scanf("%d",&data->tm_year);
    }while(data->tm_year < 2017 || data->tm_year > 2018);
}
#endif //PROJETO_ADS_DATA_H
