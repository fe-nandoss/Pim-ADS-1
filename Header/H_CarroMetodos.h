//
//  carMetodos.h
//  Pim
//
//  Created by Furflesx on 25/11/2017.
//  Copyright © 2017 Furflesx. All rights reserved.
//

#ifndef carMetodos_h
#define carMetodos_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Carro.h"
#include "../Utils/_globals.h"

t_Carro * listaVeiculos(void);

t_Carro * veiculosDisponiveis(void);

int selecionaVeiculo(void);

void gravaVeiculos(t_Carro * listaDeCarros);

void alteraVeiculo(t_Carro * listaDeCarros, int codigo_veiculo, char * status);

t_Carro * retornaVeiculo(int cod);


#endif /* carMetodos_h */
