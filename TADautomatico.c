#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "TADautomatico.h"
#include "TADfila.h"
#include "TADbanco.h"

void caixa_automatico(int quant_aut, int quant_bio, TFila* fila_aut, TFila* fila_bio, int tam_fila, dados* aut, dados* bio, dados* imprime, int* k){

	dados proximo;
	int hora_caixa_livre;
	int i=0, j=0, m=0, z=0, cont=0, cont2=0;

// Preenchimento dos caixas automáticos com os que chegaram primeiro.
	while(!Vazia(*fila_aut) && (cont+cont2)<(quant_aut + quant_bio)){
			proximo=Desenfileira(fila_aut);
		//Caso o cliente deseje sacar mais de 300 reais, ele deve ir para o caixa biométrico.
			if(proximo.valor_brl< -300 && m< quant_bio){
				bio[m]=proximo;
				bio[m].tempo_fila=0;
				//Verifica a hora que o cliente deixará o caixa.
				bio[m].hora_saida= (bio[m].tempo_fila + bio[m].tempo_op + bio[m].hora_chegada);
				bio[m].espera= (bio[m].hora_saida - bio[m].hora_chegada);
				//Aloca o cliente que foi para o caixa em um vetor, que será utilizado para imprimir os clientes no final.			
				imprime[*k]=bio[m];
				(*k)++;
				m++;
				cont2++;
			}	
		//Caso o cliente não necessite utilizar o biométrico, ele dá preferência ao caixa automático normal.
			else if(proximo.valor_brl>= -300 && i< quant_aut){
				aut[i]=proximo;
				aut[i].tempo_fila=0;
				//Verifica a hora que o cliente deixará o caixa.
				aut[i].hora_saida= (aut[i].tempo_fila + aut[i].tempo_op + aut[i].hora_chegada);
				aut[i].espera= (aut[i].hora_saida - aut[i].hora_chegada);
				//Aloca o cliente que foi para o caixa em um vetor, que será utilizado para imprimir os clientes no final.			
				imprime[*k]=aut[i];
				(*k)++;
				i++;
				cont++;
			}	
		//Caso os caixas normais estiverem cheios, o cliente utiliza o biométrico.
			else if(m< quant_bio){
				bio[m]=proximo;
				bio[m].tempo_fila=0;
				//Verifica a hora que o cliente deixará o caixa.
				bio[m].hora_saida= (bio[m].tempo_fila + bio[m].tempo_op + bio[m].hora_chegada);
				bio[m].espera= (bio[m].hora_saida - bio[m].hora_chegada);
				//Aloca o cliente que foi para o caixa em um vetor, que será utilizado para imprimir os clientes no final.			
				imprime[*k]=bio[m];
				(*k)++;
				m++;
				cont2++;
			}	
		//Caso os caixas biométricos estejam cheios, o cliente entra em uma fila só pra caixas biométricos.
			else{
				Enfileira(proximo, fila_bio);
			}
	}		
	j=cont+cont2; 
//Executa o while somente se houver alguém na fila.
	while(j<tam_fila){
			//Verificar qual caixa aut será liberado antes, o biometrico ou o normal.
			if(proximo_qsai(bio, cont2).hora_saida < proximo_qsai(aut, cont).hora_saida || Vazia(*fila_aut)){
				//Percorre o vetor e verifica qual pessoa será a próxima a deixar um dos caixas.
				for(m=0; m< quant_bio; m++){
					if(bio[m].hora_saida==proximo_qsai(bio, cont2).hora_saida){
						hora_caixa_livre= bio[m].hora_saida;
						//Caso o haja alguém esperando há mais tempo, por necessitar usar o caixa biométrico, ele ocupa o caixa disponível.
						if(!Vazia(*fila_bio))
							bio[m]= Desenfileira(fila_bio);
						//Caso contrário, o próximo da fila ocupa o caixa biométrico.
						else
							bio[m]= Desenfileira(fila_aut);
						bio[m].tempo_fila= hora_caixa_livre - bio[m].hora_chegada;
						if(bio[m].tempo_fila<0)
							bio[m].tempo_fila= 0;
						//Verifica a hora que o cliente deixará o caixa.
						bio[m].hora_saida= (bio[m].tempo_fila + bio[m].tempo_op + bio[m].hora_chegada);
						bio[m].espera= (bio[m].hora_saida - bio[m].hora_chegada);
						//Aloca o cliente que foi para o caixa em um vetor, que será utilizado para imprimir os clientes no final.			
						imprime[*k]=bio[m];
						(*k)++;
						j++;
						//Sai do loop. Reinicia o procedimento e verifica todos os caixas de novo, para ver quem é o proximo a terminar a operaçao.
						m= quant_bio;
					}
				}			
			}
		//Caso o próximo caixa a ser liberado seja um caixa normal.
			else{
				//Verifica se o próximo da fila pode usar um caixa normal.
				proximo= Desenfileira(fila_aut);
				//Caso o próximo não possa utilizar o caixa normal, executa o while.
				while(proximo.valor_brl< -300 && z!=1){
					Enfileira(proximo, fila_bio);
					//se ainda houver gente na fila, chama o proximo.
					if(!Vazia(*fila_aut)){
						proximo= Desenfileira(fila_aut);
					}	
					else
						z=1; /*Para sair do while e não entrar no for */
				}	
				//Percorre o vetor e verifica qual pessoa será a próxima a deixar um dos caixas.
				for(i=0; i< quant_aut && z!=1; i++){
					if(aut[i].hora_saida==proximo_qsai(aut, cont).hora_saida){
						hora_caixa_livre= aut[i].hora_saida;
						aut[i]=proximo;
						//Verifica o tempo que o cliente ficou na fila.
						aut[i].tempo_fila= hora_caixa_livre - aut[i].hora_chegada;
						if(aut[i].tempo_fila<0)
								aut[i].tempo_fila= 0;	
						//Verifica a hora que o cliente deixará o caixa.
						aut[i].hora_saida= (aut[i].tempo_fila + aut[i].tempo_op + aut[i].hora_chegada);
						aut[i].espera= (aut[i].hora_saida - aut[i].hora_chegada);		
						//Aloca o cliente que foi para o caixa em um vetor, que será utilizado para imprimir os clientes no final.			
						imprime[*k]=aut[i];
						j++;
						(*k)++;	
						//Sai do loop. Reinicia o procedimento e verifica todos os caixas de novo, para ver quem é o proximo a terminar a operaçao.
						i=quant_aut; 
					}
				}
			}
			z=0;	
	}
}	