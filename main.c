#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "TADbanco.h"
#include "TADfila.h"
#include "TADautomatico.h"
#include "TADcaixa.h"
#include "TADcambio.h"

int main(int argc, char *argv[]){

//Validaçao da entrada
	if(argc!=3){
		printf("ENTRADA INVÁLIDA! 2 Arquivos devem ser passados como argumento.\n");
		exit(0);
	}
		
//Vetores que representam os caixas.
	dados aut[15], bio[10], caixa[3], cambio[1];
	int tam1, tam2, tam3;
	int k=0, cont=0;

//Arquivos passados como argumento.
	FILE *ent, *saida;
	ent= fopen(argv[1], "r");
	saida= fopen(argv[2], "w");
//Filas que serão utilizadas pelo programa.
	TFila *fila_caixa, *fila_cambio, *fila_aut, *fila_bio;
	fila_aut= (TFila*) malloc(sizeof(TFila));
	fila_caixa= (TFila*) malloc(sizeof(TFila));
	fila_cambio= (TFila*) malloc(sizeof(TFila));
	fila_bio= (TFila*) malloc(sizeof(TFila));
	FFVazia(fila_caixa);
	FFVazia(fila_cambio);
	FFVazia(fila_aut);
	FFVazia(fila_bio);

//Verificar o número de linhas do arquivo de entrada.
	char entrada[1000];
	while(fgets(entrada,1000,ent)!= NULL){		
		cont++;
	}
	fclose(ent);
	ent= fopen(argv[1], "r");

//Vetores que conterão os dados de cada linha da entrada. 
	dados* cliente, *imprime;
	cliente= (dados*) malloc(cont*sizeof(dados));
	imprime= (dados*) malloc(cont*sizeof(dados)); 
	
//Direcionamento dos clientes para suas devidas filas, de acordo com a operação.
	coloca_fila_correta(cliente, ent, fila_aut, fila_cambio, fila_caixa, cont);

//Verificação de quantas pessoas irão fazer cada operação.
	tam1= fila_aut->tamanho;
	tam2= fila_cambio->tamanho;
	tam3= fila_caixa->tamanho;

//Faz as operções com os 25 caixas automáticos.
	caixa_automatico(15, 10, fila_aut, fila_bio, tam1, aut, bio, imprime, &k);
//Faz as operações com o caixa de Câmbio.
	caixa_cambio(1, fila_cambio, tam2, cambio, imprime, &k);
//Faz as operações com os 3 caixas manuais.
	caixa_manual(3, fila_caixa, tam3, caixa, imprime, &k);
//Impressão dos dados no arquivo de saída.
	imprime_saida(imprime, saida, tam1, tam2, tam3, &k);

//Desalocação de memória.
	libera(fila_caixa);
	libera(fila_aut);
	libera(fila_cambio);
	libera(fila_bio);
	free(fila_caixa);
	free(fila_aut);
	free(fila_cambio);
	free(fila_bio);
	free(imprime);
	free(cliente);
	fclose(ent);
	fclose(saida);
	return 0;
}	
