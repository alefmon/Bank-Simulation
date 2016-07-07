#include "TADfila.h"
#include "TADbanco.h"
#ifndef AUT_H
#define AUT_H

//A função recebe a fila do caixa automático e desenfileira o primeiro da fila, até preencher todos os caixas automáticos do banco. O número de caixas do banco é passado como argumento.
//Depois, a função faz todo o fluxo de pessoas do caixa automático, ou seja, retira um e coloca outro no caixa. Esse fluxo segue a ordem da fila e os critérios propostos pelo Trabalho. 
//Além disso, a função verifica também o tempo de fila, o tempo de espera e a hora de saída de cada cliente.
void caixa_automatico(int quant_aut, int quant_bio, TFila* fila_aut, TFila* fila_bio, int tam_fila, dados* aut, dados* bio, dados* imprime, int *k);



#endif
