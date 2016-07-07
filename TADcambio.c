#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "TADfila.h"
#include "TADcambio.h"
#include "TADbanco.h"


void caixa_cambio(int quant_cambio, TFila* fila_cambio, int tam_fila, dados* cambio, dados* imprime, int *k){

	int hora_caixa_livre;
	int i=0, j=0, cont=0;
// preenche os caixas com os que chegaram primeiro (n primeiros da fila).
	while(!Vazia(*fila_cambio) && i< quant_cambio){
			cambio[i]=Desenfileira(fila_cambio);
			cambio[i].tempo_fila=0;
			//Verifica a hora que o cliente deixará o cambio.
			cambio[i].hora_saida= (cambio[i].tempo_fila + cambio[i].tempo_op + cambio[i].hora_chegada);
			cambio[i].espera= (cambio[i].hora_saida - cambio[i].hora_chegada);
			//Aloca o cliente que foi para o cambio em um vetor, que será utilizado para imprimir os clientes no final.
			imprime[*k]=cambio[i];
			(*k)++;
			i++;
			cont++;
	}	
	j=quant_cambio;

//Executa o while somente se houver alguém na fila.
	while(j<tam_fila){
		//Percorre o vetor e verifica qual pessoa será a próxima a deixar um dos caixas.
		for(i=0; i< quant_cambio; i++){
			if(cambio[i].hora_saida==proximo_qsai(cambio, cont).hora_saida){
				hora_caixa_livre= cambio[i].hora_saida;
				//O proximo da fila de espera ocupa o caixa cambio que ficou disponivel.
				cambio[i]= Desenfileira(fila_cambio);
				//Verifica o tempo que o cliente ficou na fila.
				cambio[i].tempo_fila= hora_caixa_livre - cambio[i].hora_chegada;
				if(cambio[i].tempo_fila<0)
					cambio[i].tempo_fila= 0;
				//Verifica a hora que o cliente deixará o caixa.
				cambio[i].hora_saida= (cambio[i].tempo_fila + cambio[i].tempo_op + cambio[i].hora_chegada);
				cambio[i].espera= (cambio[i].hora_saida - cambio[i].hora_chegada);					
				//Aloca o cliente que foi para o caixa em um vetor, que será utilizado para imprimir os clientes no final.
				imprime[*k]=cambio[i];
				(*k)++;
				//sai do loop e verifica todos os 3 caixas de novo, para ver quem é o proximo a terminar a operaçao.
				i= quant_cambio;
			}
		}	
		j++;
	}
}
