//
// Created by Furflesx on 27/09/17.
//

#ifndef PROJETO_ADS_CLIENTE_H
#define PROJETO_ADS_CLIENTE_H

#include <time.h>

typedef struct Cliente{

    int codigo;
    char nome[50];
    float desconto;
    struct tm * dataLocacao;
    struct tm * dataDevolucao;
    int codigo_veiculo;

}t_Cliente;

#endif //PROJETO_ADS_CLIENTE_H
