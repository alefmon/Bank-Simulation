#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "TADfila.h"
#ifndef BANCO_H
#define BANCO_H

//A função recebe um vetor e verifica qual é o cliente com a menor hora de saída.
dados proximo_qsai(dados* vetor_clientes, int n);

//A função recebe o arquivo de entrada e aloca cada cliente da entrada em uma fila, de acordo com a operação que será realizada por ele.
void coloca_fila_correta(dados* cliente, FILE* ent, TFila* fila_aut, TFila* fila_cambio, TFila* fila_caixa, int linhas);

//A função imprime todos os clientes no arquivo de saída. Além disso, a função verifica a variação do dinheiro em caixa e a variação do tempo de espera. Depois, ela imprime o resumo geral no arquivo de saída.
void imprime_saida (dados* imprime, FILE* saida, int tam1, int tam2, int tam3, int* k);

#endif
