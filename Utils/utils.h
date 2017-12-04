//
// Created by Furflesx on 26/09/17.
//
#include <stdio.h>

#ifndef PROJETO_ADS_UTILS_H
#define PROJETO_ADS_UTILS_H

void limpa_console(void)
{
#ifdef linux //|| LINUX || Linux || UNIX
    //código especifico para linux
    //system ("clear");//poderia ser este mas escolhi este outro pois é mais a cara do C
    printf("\33[H\33[2J");
#elif defined WIN32
    //código específico para windows
    system ("cls");
#else
    printf("\33[H\33[2J");
#endif

}

void bemVindo(void){
    printf("**************************\n"
           "*        BEM VINDO       *\n"
           "**************************");
}

void cabecalhoNovoCliente(void){
    printf("**************************\n"
           "*      NOVO CLIENTE      *\n"
           "**************************\n");
}

void cabecalhoDevolucaoCliente(void){
    printf("*******************************\n"
           "*      Devolucao CLIENTE      *\n"
           "*******************************\n");
}

void cabecalhoResumoCliente(void){
    printf("*******************************\n"
           "*            RESUMO           *\n"
           "*******************************\n");
}
void cabecalhoRelatorioDevolucaoCliente(void){
    printf("**********************************************************\n"
           "*       Relatorio - Locacao com Devolucao               *\n"
           "*--------------------------------------------------------*\n"
           "**********************************************************\n"
           "\n");
}

void cabecalhoRelatorioSemDevolucaoCliente(void){
    printf("*****************************************************************\n"
           "*       Relatorio - Locacao em Andamento                        *\n"
           "-----------------------------------------------------------------\n"
           "*****************************************************************\n");
}

#endif //PROJETO_ADS_UTILS_H
