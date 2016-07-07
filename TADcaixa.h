#include "TADfila.h"
#include "TADbanco.h"
#ifndef CAIXA_H
#define CAIXA_H

//A função recebe a fila do caixa manual e desenfileira o primeiro da fila, até preencher todos os caixas do banco. O número de caixas do banco é passado como argumento.
//Depois, a função faz todo o fluxo de pessoas, ou seja, retira um e coloca outro no caixa. Esse fluxo segue a ordem da fila. 
//Além disso, a função verifica também o tempo de fila, o tempo de espera e a hora de saída de cada cliente.
void caixa_manual(int quant_caixa, TFila* fila_caixa, int tam_fila, dados* caixa, dados* imprime, int *k);

#endif
