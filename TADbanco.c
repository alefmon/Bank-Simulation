#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "TADfila.h"
#include "TADbanco.h"

dados proximo_qsai(dados* vetor_clientes, int n){
	int i;
	dados proximo_qsai= vetor_clientes[0];
	for(i=1;i<n; i++){
		if(vetor_clientes[i].hora_saida < proximo_qsai.hora_saida)
			proximo_qsai= vetor_clientes[i];
	}
	return proximo_qsai;
}

void coloca_fila_correta(dados* cliente, FILE* ent, TFila* fila_aut, TFila* fila_cambio, TFila* fila_caixa, int linhas){
	
	int i=0, j=0, k=0, m=0;
	char matriz [6][100];
	char *sq= "SAQUE", *dep= "DEPOSITO", *cx= "CAIXA", *cbio= "CÂMBIO";
	char x, entrada[1000];	
	while(fgets(entrada,1000,ent)!= NULL){
		//Apagar o conteúdo da matriz que irá conter os atributos do cliente.
			for(j=0;j<6;j++){
				for(k=0;k<100;k++)
					matriz[j][k]=0;
			}	
			j=0, k=0, m=0;
		//Cada linha da matriz recebe um atributo do cliente.
			x=entrada[j];
			while(x!='\0' ){
				if(x==','){
					k++;
					m=0;
				}
				else{
					matriz[k][m]=entrada[j];
					m++;
				}	
				j++;
				x=entrada[j];
			}
		//Verificar se a entrada contém o número correto de campos por linha.
			if(k!=5){
				printf("ENTRADA INVÁLIDA! Cada linha deve conter 6 atributos.\n");
				exit(0);
			}
		//Alocação dos atributos de cada cliente.
			cliente[i].hora_chegada= atol(matriz[0]);
			for(k=0;k<50;k++)
				cliente[i].nome[k]=(matriz[1][k]);
			for(k=0;k<10;k++)
				cliente[i].operacao[k]=(matriz[2][k]);
			cliente[i].valor_brl= atof(matriz[3]);
			cliente[i].valor_usd= atof(matriz[4]);
			cliente[i].tempo_op= atoi(matriz[5]);s
		
		//Enfileirar o cliente de acordo a operação que ele executará.
			if(strcmp(cliente[i].operacao,sq)==0){
				Enfileira(cliente[i], fila_aut);
				//Verificar que a operação SAQUE só pode retirar dinheiro do banco.
				if(cliente[i].valor_brl>0){
					printf("ENTRADA INVÁLIDA! SAQUE deve conter valor negativo.\n");
					exit(0);
				}
			}
			else if(strcmp(cliente[i].operacao,dep)==0){
				Enfileira(cliente[i], fila_aut);
				//Verificar que a operação DEPOSITO só pode colocar dinheiro no banco.
				if(cliente[i].valor_brl<0){
					printf("ENTRADA INVÁLIDA! DEPOSITO deve conter valor positivo.\n");
					exit(0);
				}
			}
			else if(strcmp(cliente[i].operacao,cbio)==0){
				Enfileira(cliente[i], fila_cambio);
			}
			else if(strcmp(cliente[i].operacao,cx)==0){
				Enfileira(cliente[i], fila_caixa);
			}
		//Verificar se o campo "operação bancária" da entrada é válido.
			else{
				printf("OPERAÇÃO BANCÁRIA INVÁLIDA! Operações válidas: SAQUE, DEPOSITO, CÂMBIO, CAIXA.\n");
				exit(0);
			}
			i++;
	}
}	

void imprime_saida (dados* imprime, FILE* saida, int tam1, int tam2, int tam3, int* k){

	dados imp;
	int espera_minimo, espera_maximo;
	int i=0, j=0;
	float banco_usd=0, banco_brl=0, minimo_brl=0, maximo_brl=0, minimo_usd=0, maximo_usd=0;
//A cada ciclo ocorre a impressão de uma linha no arquivo de saída.
	while(j<(tam1+tam2+tam3)){ 
			//Verificação da ordem de saída dos clientes do banco.
			for(i=0;i<(*k);i++){
				if(imprime[i].hora_saida==proximo_qsai(imprime, *k).hora_saida){
					imp= imprime[i];
					// mudar isso aquiiiiii...////////////////////////*****************************MUDAAAAAA*****
					imprime[i].hora_saida+= 10000000;
					i=(*k); /*para sair do for se tiver entrado no if*/
				}	
			}
			//Atualização dos valores do banco.
			banco_brl+= imp.valor_brl;
			banco_usd+= imp.valor_usd;

			//Inicialização do valor do tempo de espera mínimo e máximo. 
			if(j==0){
					espera_minimo= imp.tempo_op;
					espera_maximo= imp.tempo_op;
				}
			//Verificação da variaçao do dinheiro no banco.
			if(banco_brl<minimo_brl)
				minimo_brl=banco_brl;	
			else if(banco_brl>maximo_brl)
				maximo_brl=banco_brl;
			if(banco_usd<minimo_usd)
				minimo_usd=banco_usd;
			else if(banco_usd>maximo_usd)
				maximo_usd=banco_usd;
			//verificação da variacao do tempo de espera.
			if(imp.espera < espera_minimo)
				espera_minimo= imp.espera;
			else if(imp.espera > espera_maximo)
				espera_maximo= imp.espera;
		
			//Impressão dos dados no arquivo de saída.
			fprintf(saida, "%ld,%s,%s,%.2f,%.2f,%d\n", imp.hora_saida, imp.nome, imp.operacao, banco_brl, banco_usd, imp.espera);
			j++;
	}

//Impressão do Resumo Geral.
	fprintf(saida, "VARIACAO DE BRL: %.2f a %.2f\n", minimo_brl, maximo_brl);
	fprintf(saida, "VARIACAO DE USD: %.2f a %.2f\n", minimo_usd, maximo_usd);
	fprintf(saida, "VARIACAO DE TEMPO: %d a %d\n", espera_minimo, espera_maximo);

}

