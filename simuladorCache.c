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
		nivel,
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

static Memoria* cacheL1;
static Memoria* cacheL2;
static Memoria* cacheL3;
static Memoria* principal;

void preencheMemoriaPrincipal(int);
/* FALTA */void recebeSequenciaTeste(void);
/* FALTA */void usaFifo(void);
/* FALTA */void usaLru(void);
Memoria* criaMemoria(int,int);
void insereDadoMemoria(Memoria* mem,int dado);
/* FALTA */void mostraMemoria(Memoria* mem);
int trocaNivelDadoNaMemoria(Memoria* mem1, Memoria* mem2,int dado);
int verificaDadoNaMemoria(Memoria* mem, int dado);
Fila* criaFila(void);
void insereFila(Fila*,int);
void liberaFila(Fila*);
int filaVazia(Fila*);
int retiraFila(Fila*);

int main(int argc, char **argv)
{
	cacheL1 = criaMemoria(2,1);
	cacheL2 = criaMemoria(4,2);
	cacheL3 = criaMemoria(8,3);
	principal = criaMemoria(16,4);
	return 0;
}
void preencheMemoriaPrincipal(int n){
	int i;
	for(i =0; i < n*8; i++)
		insereDadoMemoria(principal,i);
}
Memoria* criaMemoria(int tamMemoria,int nivel){
	Memoria* mem = (Memoria*)malloc(sizeof(Memoria));
	
	mem->dados_memoria = criaFila();
	mem->tamanho = tamMemoria;
	mem->nivel=nivel;
	
	return mem;
}

int verificaDadoNaMemoria(Memoria* mem,int dado){
	Fila* f = (Fila*)malloc(sizeof(Fila));
	int i;
	f = mem->dados_memoria;
	
	for(i = 0; i < mem->cont; i++){
		if(f->ini->dado == dado)
			return 1;
		else
		{
			Lista* temp = f->ini->prox;
			free(f);
			f->ini = temp;
		}
	}	
	
	return -1;
}
	
void insereDadoMemoria(Memoria* mem, int dado){
	if(mem->cont+1 <= mem->tamanho){
		insereFila(mem->dados_memoria,dado);
		mem->cont++;
	}
	else{
		int valido;
		if(mem->nivel == 1){
			inicio:
			valido = trocaNivelDadoNaMemoria(cacheL2,cacheL1,dado);
			
			if(valido != 1){
				valido = trocaNivelDadoNaMemoria(cacheL3,cacheL2,dado);
				if(valido != 1){
					valido = trocaNivelDadoNaMemoria(principal,cacheL3,dado);
					if(valido != 1){
						int temp1,temp2,temp3,temp4;
						temp1 = verificaDadoNaMemoria(cacheL1,dado);
						temp2 = verificaDadoNaMemoria(cacheL2,dado);
						temp3 = verificaDadoNaMemoria(cacheL3,dado);
						temp4 = verificaDadoNaMemoria(principal,dado);
						if(temp1 != 1 && temp2 != 1 && temp3 != 1 && temp4 != 1){
							printf("Dado da sequencia de teste não foi previamente alocado na memória principal");	
						}
						else
							goto inicio;
					}
				}
				else
					goto inicio;
			}
		}
		if(mem->nivel == 2){
			inicio1:
			valido = trocaNivelDadoNaMemoria(cacheL3,cacheL2,dado);
				if(valido != 1){
					valido = trocaNivelDadoNaMemoria(principal,cacheL3,dado);
					if(valido != 1){
						int temp1,temp2,temp3,temp4;
						temp1 = verificaDadoNaMemoria(cacheL1,dado);
						temp2 = verificaDadoNaMemoria(cacheL2,dado);
						temp3 = verificaDadoNaMemoria(cacheL3,dado);
						temp4 = verificaDadoNaMemoria(principal,dado);
						if(temp1 != 1 && temp2 != 1 && temp3 != 1 && temp4 != 1){
							printf("Dado da sequencia de teste não foi previamente alocado na memória principal");	
						}
						else
							goto inicio1;
					}
					else
						goto inicio1;
				}
		}
		if(mem->nivel == 3){
			valido = trocaNivelDadoNaMemoria(principal,cacheL3,dado);
			if(valido != 1){
				int temp1,temp2,temp3,temp4;
				temp1 = verificaDadoNaMemoria(cacheL1,dado);
				temp2 = verificaDadoNaMemoria(cacheL2,dado);
				temp3 = verificaDadoNaMemoria(cacheL3,dado);
				temp4 = verificaDadoNaMemoria(principal,dado);
				if(temp1 != 1 && temp2 != 1 && temp3 != 1 && temp4 != 1){
					printf("Dado da sequencia de teste não foi previamente alocado na memória principal");	
				}
				else
					goto inicio1;
			}
		}
	}
}		
		
	
/*
 *	Na função de troca de nivel o dado na memoria, sempre vai verificar se o dado está na mem1 caso esteja vai passa-lo para mem2,
 * 	caso contrário retornará que o dado procurado não está em mem1.
*/
int trocaNivelDadoNaMemoria(Memoria* mem1,Memoria* mem2, int dado){
	if(verificaDadoNaMemoria(mem1,dado) == 1){
		retiraFila(mem1->dados_memoria);
		insereFila(mem2->dados_memoria,dado);
		return 1;
	}
	else if (verificaDadoNaMemoria(mem1,dado) == -1)
		return -1;
	else
		return -1;

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













