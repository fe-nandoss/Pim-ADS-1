//
// Created by Furflesx on 27/09/17.
//

#ifndef PROJETO_ADS_CLIENTE_H
#define PROJETO_ADS_CLIENTE_H

#include <time.h>

typedef struct Cliente{

    char nome[50];
    int tipo;
    time_t dataLocacao;
    time_t dataDevolucao;

}Cliente;

#endif //PROJETO_ADS_CLIENTE_H