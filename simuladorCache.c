/*
 * 	Os tamanhos das memórias cache l1,l2,L3 e principal serão definidos da seguinte forma: 
 * 	- L1 definida por usuário.
 * 	- L2 será 2 * o tamanho de L1
 * 	- L3 será 4 * o tamanho de L1
 * 	- A principal será 8 * o tamanho de L1
 * 
 * 	Os dados diponíveis para montagem da sequencia de teste serão definidos a partir do tamanho da memória principal,
 * 	de modo que, eles serão números inteiros de 0 até o tamanho da memória principal.
 * 
 * 	A sequencia de teste poderá ser dada pelo usuário ou gerada randomicamente. Sendo que quando gerada randomicamente
 * 	ela terá o tamanho igual ao da memória principal mais 10.
 * 	
 *	Utilizarei o conceito de fila para implementar a cache com algoritmo FIFO.
 *
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct lista Lista;
typedef struct fila Fila;
typedef struct memoria Memoria;

struct memoria{
	int tamanho,
		cont;
	Fila* dados_memoria;
};

struct lista{
	int dado;
	struct lista* prox;
};

struct fila{
	Lista* ini;
	Lista* fim;
};

void preencheMemoriaPrincipal(Memoria* mem_prin);
void recebeSequenciaTeste(void);
void usaFifo(void);
void usaLru(void);
Memoria* criaMemoria(int tamMemoria);
void insereDadoMemoria(Memoria* mem,int dado);
void mostraMemoria(Memoria* mem);
int trocaNivelDadoNaMemoria(Memoria* mem1, Memoria* mem2,int dado);
int verificaDadoNaMemoria(Memoria* mem, int dado);
Fila* criaFila(void);
void insereFila(Fila* f,int dado);
void liberaFila(Fila* f);
int filaVazia(Fila* f);
int retiraFila(Fila* f);

int main(int argc, char **argv)
{
	
	return 0;
}

Memoria* criaMemoria(int tamMemoria){
	Memoria* mem = (Memoria*)malloc(sizeof(Memoria));
	
	mem->dados_memoria = criaFila();
	mem->tamanho = tamMemoria;
	
	return mem;
}
	
/*
 *	Na função de troca de nivel o dado na memoria, sempre vai verificar se o dado está na mem1 caso esteja vai passa-lo para mem2,
 * 	caso contrário retornará que o dado procurado não está em mem1.
*/
int trocaNivelDadoNaMemoria(Memoria* mem1,Memoria* mem2, int dado){
	return 0;
}

Fila* criaFila(void){
	
	Fila* f = (Fila*)malloc(sizeof(Fila));
	f->ini = f->fim = NULL;
		
	return f;
}
void insereFila(Fila* f, int info){
	Lista* lista = (Lista*)malloc(sizeof(Lista));
	
	lista->dado = info;
	lista->prox = NULL;
	
	if( f->fim != NULL)
		f->fim->prox = lista;
	else
		f->ini = f->fim = lista;
			
}
int filaVazia(Fila* f){
	if( f->ini == NULL)
		return 1;
	return 0;
}
int retiraFila(Fila* f){
	Lista* lista;
	int temp;
	
	if( filaVazia(f))
		printf("erro");
	
	lista = f->ini;
	temp = lista->dado;
	f->ini = lista->prox;
	
	if( f->ini == NULL)
		f->fim = NULL;
	
	free(lista);
	
	return temp;
}
void liberaFila(Fila* f){
	Lista* temp = f->ini;
	
	while(temp != NULL){
		Lista* temp2 = temp->prox;
		free(temp);
		temp = temp2;
	}
	
	free(f);
}













