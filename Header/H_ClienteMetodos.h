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
    long dataLocacao;
    long dataDevolucao;
    int codigo_veiculo;
    struct tempCliente * proximo;
}temp_Cliente;

void gravaCliente(t_Cliente * cliente);

int listagemClientes(void);

#endif /* H_ClienteMetodos */
