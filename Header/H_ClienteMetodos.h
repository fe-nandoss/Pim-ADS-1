//
//  H_ClienteMetodos
//  Pim
//
//  Created by Furflesx on 25/11/2017.
//  Copyright © 2017 Furflesx. All rights reserved.
//

#ifndef H_ClienteMetodos
#define H_ClienteMetodos

#include <stdio.h>
#include <stdlib.h>
#include "../Utils/data.h"
#include "../Utils/utils.h"
#include "../Utils/_globals.h"
#include "Cliente.h"
#include <math.h>

typedef struct tempCliente{
    int codigo;
    char nome[50];
    float desconto;
    struct tm dataLocacao;
    struct tm dataDevolucao;
    int codigo_veiculo;
    struct tempCliente * proximo;
}temp_Cliente;

void criaCliente(void);

void gravaCliente(t_Cliente * cliente);

temp_Cliente * listaClientes(void);

int totalClientes(temp_Cliente * clientes);

void resetaStructCliente(t_Cliente * cliente);

struct tm * resetaStructData();

void copyStructCliente(temp_Cliente * temp_cliente, t_Cliente * t_cliente, char * destino);

t_Cliente * alteraCliente(temp_Cliente * listacliente,int codCliente);

void sobreEscreveClientes(temp_Cliente * listaClientes);

void devolucaoCliente(void);

#endif /* H_ClienteMetodos */
