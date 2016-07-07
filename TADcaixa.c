#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "TADcaixa.h"
#include "TADfila.h"
#include "TADbanco.h"


void caixa_manual(int quant_caixa, TFila* fila_caixa, int tam_fila, dados* caixa, dados* imprime, int *k){

	int hora_caixa_livre;
	int i=0, j=0, cont=0;
// preenche os caixas com os q chegaram primeiro (n primeiros da fila).
	while(!Vazia(*fila_caixa) && i< quant_caixa){
			caixa[i]=Desenfileira(fila_caixa);
			caixa[i].tempo_fila=0;
			//Verifica a hora que o cliente deixará o caixa.
			caixa[i].hora_saida= (caixa[i].tempo_fila + caixa[i].tempo_op + caixa[i].hora_chegada);
			caixa[i].espera= (caixa[i].hora_saida - caixa[i].hora_chegada);
			//Aloca o cliente que foi para o caixa em um vetor, que será utilizado para imprimir os clientes no final.
			imprime[*k]=caixa[i];
			(*k)++;
			i++;
			cont++;
	}	
	j=quant_caixa;

//Executa o while somente se houver alguém na fila.
	while(j<tam_fila){
		//Percorre o vetor e verifica qual pessoa será a próxima a deixar um dos caixas.
		for(i=0; i< quant_caixa; i++){
			if(caixa[i].hora_saida==proximo_qsai(caixa, cont).hora_saida){
				hora_caixa_livre= caixa[i].hora_saida;
				//O proximo da fila de espera ocupa o caixa cambio que ficou disponivel.
				caixa[i]= Desenfileira(fila_caixa);
				//Verifica o tempo que o cliente ficou na fila.
				caixa[i].tempo_fila= hora_caixa_livre - caixa[i].hora_chegada;
				if(caixa[i].tempo_fila<0)
					caixa[i].tempo_fila= 0;
				//Verifica a hora que o cliente deixará o caixa.
				caixa[i].hora_saida= (caixa[i].tempo_fila + caixa[i].tempo_op + caixa[i].hora_chegada);
				caixa[i].espera= (caixa[i].hora_saida - caixa[i].hora_chegada);					
				//Aloca o cliente que foi para o caixa em um vetor, que será utilizado para imprimir os clientes no final.
				imprime[*k]=caixa[i];
				(*k)++;
				//sai do loop e verifica todos os 3 caixas de novo, para ver quem é o proximo a terminar a operaçao.
				i= quant_caixa;
			}
		}	
		j++;
	}
}
