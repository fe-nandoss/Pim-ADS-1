#ifndef PROJETO_ADS_CARRO_H
#define PROJETO_ADS_CARRO_H

typedef struct Carro{

    int codigo;
    char modelo[50];
    char marca[50];
    char placa[50];
    float preco;
    struct Carro * proximo;
}t_Carro;

#endif //PROJETO_ADS_CARRO_H
