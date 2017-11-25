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
static int memoriaPrincipal[16];
static int hit = 0;
static int miss = 0;

Fila* criaFila(int tamMemoria){

	Fila* f = (Fila*)malloc(sizeof(Fila));

	f->ini = f->fim = NULL;
	f->tamanho = tamMemoria;
	f->cont = 0;
	
	return f;
}

int insereFila(Fila* f, int info){

	int temp;
	Lista* lista = (Lista*)malloc(sizeof(Lista));
	
	lista->dado = info;					// armazena a informação
	lista->prox = NULL; 				// ultimo nó
	
	if(f->cont <= f->tamanho)
	{
		if( f->fim != NULL)				// verifica se a lista não estava vazia
			f->fim->prox = lista;
	
		else							// estava vazia
			f->ini = f->fim = lista;
		
		f->cont ++;

		return -1;
	}

	else{ 		
		
		temp = retiraFila(f);			// Troca o primeiro elemento da fila pelo que se deseja inserir

		if( f->fim != NULL)				// verifica se a lista não estava vazia
			f->fim->prox = lista;		
	
		return temp;					// Retorna o elemento que foi substituido

	}

}

int retiraFila(Fila* f){
	
	int temp;
	
	Lista* lista = (Lista*)malloc(sizeof(Lista));

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

void criaMemoriaPrincipal(){
   	// 	printf("Memoria principal : \n");
   
   	for(int i = 0; i < 16; i++)
   	{ 
		memoriaPrincipal[i] = i +1;
	//	printf("[%d] ", principal[i]);
   	} 	
   	//printf("\n\n");
}

void geraSequenciaTeste(int seq[], int tam){
	
   	time_t t;   
 	srand((unsigned) time(&t));
 	//printf("Sequencia teste : \n");

   	for(int i = 0; i < tam; i++)
   	{ 
		seq[i] = 1 + rand() % 16;
	  //  printf("[%d] ", seq[i]);
   	}
   	//printf("\n\n");
}

void insereMemoria(int dado){

	for(int i = 0; i < 16; i++)
   	{
   		if(memoriaPrincipal[i] == 0){
	
			memoriaPrincipal[i] = dado;
			break;
   		}
   	}
}

void fifo(int seqTeste[], int tam){

	int temporaria;

	for(int i = 0; i<tam; i++)
	{
		if(!hiti(cacheL1,seqTeste[i])){

			temporaria = insereFila(cacheL1,seqTeste[i]);		// Adiciona o elemento na cache

			if(temporaria != -1){
				insereMemoria(temporaria);						// Adiciona o elemento substituido na cache na memoria principal
			}
			
			seqTeste[i] = 0;									// Remove o primeiro elemento da sequencia de teste
			miss++;												// incrementa o contador de miss

			for(int j =0; j<16; j++){
				if(memoriaPrincipal[j] == seqTeste [i]){
					memoriaPrincipal[j] = 0;
					printf("Aqui\n");
				}
			}
		}	
		
		else{

			hit++;												// incrementa o contador de hit
			seqTeste[i] = 0; 									// Remove o primeiro elemento da sequencia de teste
		}
	}
}

int hiti(Fila* f, int dado1){

	Lista* temp =(Lista*)malloc(sizeof(Lista));
	
	temp = f->ini;
	
	while(temp != NULL){
	
		Lista* temp2 = temp->prox;
		
		if(temp->dado == dado1){
			return 1;
		}
		
		temp = temp2;
	}

	return 0;
}


void mostraMemoria(){
	
	printf("Memoria principal : \n");

	for(int i=0; i<16; i++)
	 	printf("[%d] ", memoriaPrincipal[i]);

   	printf("\n\n");
}

void mostraSeqTeste(int seq[], int tam){
	
	printf("Sequencia teste : \n");

	for(int i=0; i<tam; i++)
	 	printf("[%d] ", seq[i]);

   	printf("\n\n");
}



int main(int argc, char **argv)
{

	int tam;
	time_t t; 
	srand((unsigned) time(&t));

	printf("\nEntre com o tamanho da sequencia teste : ");

	scanf("%d",&tam);
  	printf("\n");

	int seqTest[tam];
	
	cacheL1 = criaFila(4);

	criaMemoriaPrincipal(); 	  
 	
   	for(int i = 0; i < tam; i++)
   		seqTest[i] = 1 + rand() % 16;
   	

	//geraSequenciaTeste(seqTest,tam);

	fifo(seqTest,tam);

	mostraMemoria();

	
   	for(int i = 0; i < tam; i++)
   		printf("%d\n",seqTest[i]);
   	

	printf("\n\nQtd. de hit : %d \n", hit);

	printf("Qtd. de miss : %d \n", miss);
	
	

	liberaFila(cacheL1);

	return 0;
}
