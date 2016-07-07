#ifndef FUNC_H
#define FUNC_H

//Estrutura usada para alocar em cada cliente seus atributos. Ou seja, cada cliente tem todos os seus dados em uma só estrutura.
typedef struct{
	long int hora_chegada;
	char nome[50];
	char operacao[10];
	float valor_brl;
	float valor_usd;
	int tempo_op;
	int tempo_fila;
	long int hora_saida;
	int espera;
} dados;

typedef struct Celula *Apontador;

//Definição das células que formam a fila. 
typedef struct Celula { 
	dados usuario;
	Apontador Prox; 
} TCelula;

//Definição da fila.
typedef struct { 
	Apontador Frente; 
	Apontador Tras;
	int tamanho;
} TFila;

//A função cria uma fila vazia.
void FFVazia(TFila *Fila);

//A função verifica se a fila está vazia.
int Vazia(TFila Fila);

//A função coloca um cliente no fim da fila.
void Enfileira(dados cliente_novo, TFila *Fila);

//A função retira o primeiro cliente da fila. 
dados Desenfileira(TFila *Fila);

//A função retira todos da fila e libera a memória alocada pela fila.
void libera(TFila *Fila);

#endif
