//
// Created by Furflesx on 25/09/17.
//

#ifndef PROJETO_ADS_CARRO_H
#define PROJETO_ADS_CARRO_H

typedef struct Carro{

    int codigo;
    char modelo[50];
    char marca[50];
    char placa[50];
    float preco;
    char status_alugado[50];
}Carro;

#endif //PROJETO_ADS_CARRO_H
