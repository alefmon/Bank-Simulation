#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "TADfila.h"

void FFVazia(TFila *Fila) {
	Fila->Frente = malloc(sizeof(TCelula)); 
	Fila->Tras = Fila->Frente; 
	Fila->Frente->Prox = NULL;
	Fila->tamanho=0;
}
int Vazia(TFila Fila) {
	return (Fila.Frente == Fila.Tras);
}
void Enfileira(dados cliente_novo, TFila *Fila){ 

	Fila->Tras->Prox = malloc(sizeof(TCelula)); 
	Fila->Tras->Prox->usuario = cliente_novo;
	Fila->Tras = Fila->Tras->Prox; 
	Fila->Tras->Prox = NULL;
	Fila->tamanho++;
}


dados Desenfileira(TFila *Fila){ 
	Apontador p = Fila->Frente; 
	Fila->Frente= Fila->Frente->Prox; 
	dados cliente_fora;
	cliente_fora = p->Prox->usuario; 
	free(p);
	Fila->tamanho--;
	return(cliente_fora);
}

void libera(TFila *Fila){
	while(Fila->Frente!=Fila->Tras){
		Desenfileira(Fila);
	}
	free(Fila->Frente);
}


