#include "TADfila.h"
#include "TADbanco.h"
#ifndef CAMBIO_H
#define CAMBIO_H

//A função recebe a fila do câmbio e desenfileira o primeiro da fila, até preencher todos os caixas de câmbio do banco. O número de caixas do banco é passado como argumento.
//Depois, a função faz todo o fluxo de pessoas, ou seja, retira um e coloca outro no caixa. Esse fluxo segue a ordem da fila. 
//Além disso, a função verifica também o tempo de fila, o tempo de espera e a hora de saída de cada cliente.
void caixa_cambio(int quant_cambio, TFila* fila_cambio, int tam_fila, dados* cambio, dados* imprime, int *k);

#endif
