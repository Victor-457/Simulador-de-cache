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
#include <time.h>

typedef struct lista Lista;
typedef struct fila Fila;

struct lista{
	int dado;
	struct lista* prox;
};

struct fila{
	int tamanho,
		cont;
	Lista* ini;
	Lista* fim;
};

static Fila* cacheL1;
static int principal[16];
static int hit = 0;
static int miss = 0;

int DadoCache(Fila* f, int dado){

	int temp1,
		retorno = 0;
	Lista* lista = (Lista*)malloc(sizeof(Lista));
	
	if( f->fim == NULL){
		return 0;
	}
	
	lista = f->ini;

	temp1 = lista->dado;
	
	while(lista != NULL){
	
		if(temp1 == dado){
			retorno = 1;
			break;
		}
		Lista* temp2 = lista->prox;
		free(lista);
		lista = temp2;
	}

	return retorno;
}


void usaFifo(int seq[], int tam){
	int i;

	
	for( i=0; i<tam;i++){
		
		if(DadoCache(cacheL1,seq[i]) == 0)
		{

			
			if(cacheL1->cont == cacheL1->tamanho){

				int temp, dadotemp;

				temp = retornaDadoDaPrincipal(seq[i]); 			// Pega o dado na memoria principal
				dadotemp = retiraFila(cacheL1);  // Retira o primeiro da fila


				insereDadoNaPrincipal(dadotemp);					// Coloca o dado removido da cache na memoria principal

				insereFila(cacheL1,temp);			// Coloca o dado na cache

				seq[i] = 0;
			}

			else {

				int temp = retornaDadoDaPrincipal(seq[i]);			// Pega o dado na memoria principal

				insereFila(cacheL1,temp);			// Coloca o dado na cache

				seq[i] = 0;
			}

			miss++;
		}	
		
		else if(DadoCache(cacheL1,seq[i]) == 1){
			hit++;
			seq[i] = 0;
		}
		

		mostraCache();
		
		mostraMemoria();

		mostraSequenciaTeste(seq,tam);

		printf("Qtd. de hit : %d \n", hit);

		printf("Qtd. de miss : %d \n", miss);


	}
}


void geraSequenciaTeste(int seq[], int tam){
	
	int i, temp;
   	time_t t;
   
 	srand((unsigned) time(&t));

 	//printf("Sequencia teste : \n");

   	for( i = 0 ; i < tam ; i++ ) {
	  
		seq[i] = temp = 1 + rand() % 16;

	  //  printf("[%d] ", temp);
   }

   	//printf("\n\n");
}

int retornaDadoDaPrincipal(int dado){
	
	int i = 0,
		temp;

	while(i<16){

		if(principal[i] == dado){

			temp = principal[i];

			principal[i] = 0;

			return temp;
		}

		i++;
	}
}

void insereDadoNaPrincipal(int dado){
	
	int i = 0;

	while(i<16){

		if(principal[i] == 0){

			principal[i] = dado;
		}

		i++;
	}
}

void mostraMemoria(){
	int i =0;

	printf("Memoria principal : \n");

	while(i<16){
	 
		printf("[%d] ", principal[i]);
		i++;
	}

   	printf("\n\n");
}

void mostraSequenciaTeste(int seq[], int tam){

	int i =0;

	printf("Sequencia teste : \n");

	while(i<tam){
	 
		printf("[%d] ", seq[i]);
		i++;
	}

   	printf("\n\n");

}





Fila* criaMemoria(int tamMemoria){

	Fila* f = (Fila*)malloc(sizeof(Fila));

	f->ini = f->fim = NULL;

	f->tamanho = tamMemoria;
	f->cont = 0;
	
	return f;
}



void insereFila(Fila* f, int info){

	Lista* lista = (Lista*)malloc(sizeof(Lista));
	
	lista->dado = info;
	lista->prox = NULL;
	
	f->cont++;

	if( f->fim != NULL)
		f->fim->prox = lista;
	
	else
		f->ini = f->fim = lista;			
}

int filaVazia(Fila* f){

	if( f->ini == NULL){
		return 1;
	}

	else
		return 0;
}

int retiraFila(Fila* f){
	
	Lista* lista = (Lista*)malloc(sizeof(Lista));
	int temp;
	
	if( filaVazia(f) == 1){
		printf("erro");
	}
	
	lista = f->ini;

	temp = lista->dado;
	
	f->ini = lista->prox;
	
	if( f->ini == NULL)
		f->fim = NULL;
	
	free(lista);
	
	return temp;
}

void liberaFila(Fila* f){

	Lista* temp =(Lista*)malloc(sizeof(Lista));
	temp = f->ini;
	
	while(temp != NULL){
	
		Lista* temp2 = temp->prox;
		free(temp);
		temp = temp2;
	}
	
	free(f);
}

void mostraCache(){
	
	Lista* temp = cacheL1->ini;
	
	printf("Cache : \n");

	while(temp != NULL){
		
		printf("[%d] ", temp->dado);
		temp = temp->prox;
	}

	printf("\n\n");
}




int main(int argc, char **argv)
{

	int tam=2;

	printf("\nEntre com o tamanho da sequencia teste : ");

	scanf("%d",&tam);
  	printf("\n");

	int seqTest[tam];
	
	cacheL1 = criaMemoria(4);

	preencheMemoriaPrincipal();

	geraSequenciaTeste(seqTest,tam);

	//seqTest[0] =1;
	//seqTest[1] =1;

	mostraCache();
		
	mostraMemoria();

	mostraSequenciaTeste(seqTest,tam);

	printf("Qtd. de hit : %d \n", hit);

	printf("Qtd. de miss : %d \n", miss);
	
	usaFifo(seqTest,tam);

	liberaFila(cacheL1);

	return 0;
}
