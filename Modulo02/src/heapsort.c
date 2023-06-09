#include "stdlib.h"
#include "stdio.h"
#include "ordenacao.h"

typedef struct heap t_heap;

t_heap* criar_heap(int tam, TCompararHeapsort comparar);
int popular_heap(t_heap* h, void* elem);

struct heap{
    void* *elem;
    int ocupacao;
    int tamanho;
    int e_infinito;

    TCompararHeapsort comparar;
};

static void trocar(void* elem[], int i, int j){
    void* aux = elem[i];
    elem[i] = elem[j];
    elem[j] = aux;
}

static void desce_no_heap(t_heap* h, int k){

    int imaior = k;
    int i_esq = (k*2) + 1;
    int i_dir = (k*2) + 2;
    
    if ((i_esq < h->ocupacao) && (h->comparar(h->elem[imaior],h->elem[i_esq])<0)){
        imaior = i_esq;
    }
    if ((i_dir < h->ocupacao) && (h->comparar(h->elem[imaior],h->elem[ i_dir ])<0)){
        imaior = i_dir;
    }
    if (imaior!=k){
        trocar(h->elem, k, imaior);
        desce_no_heap(h,imaior);
    }

}

static void heapifica(t_heap* heap){
    int n = heap->ocupacao;
    int k = (n-1)/2;

    do{
        desce_no_heap(heap,k);
        k--;
 
    }while(k>0);
}

t_heap* criar_heap(int tam, TCompararHeapsort comparar){
    t_heap* h = malloc(sizeof(t_heap));
    h->tamanho = (tam>0?tam:2);
    h->e_infinito = (tam<=0?1:0);
    h->ocupacao = 0;
    h->elem = malloc(sizeof(void*)*h->tamanho);
    
    h->comparar = comparar;

    return h;
}


int popular_heap(t_heap* h, void* elem){
    int status = 0; // fals0

    if ((h->e_infinito) && (h->ocupacao == h->tamanho)){
        h->tamanho = h->tamanho*2;
        h->elem = realloc(h->elem,sizeof(void*)*h->tamanho);
    }
    if(h->ocupacao<h->tamanho){
        h->elem[h->ocupacao] = elem;
        h->ocupacao++;
        status = 1; // verdade
    }
    return status;
}

void destroy_heap(t_heap* h){
    free(h->elem);
    free(h);
}

void heap_sort(void* vetor[], int tam, TCompararHeapsort comparar){

    t_heap* h = criar_heap(tam, comparar);
    
    for(int i=0;i<tam;i++){
        popular_heap(h, vetor[i]);
    }

    heapifica(h); // construir o heap

    do{ // restabelecer a prop ordem 
        trocar(h->elem,0,h->ocupacao); // ordenando
        h->ocupacao--;
        desce_no_heap(h,0); // estabelece a ordem
    }while(h->ocupacao>1);

    for(int i=0;i<tam;i++){
        vetor[i] = h->elem[i];
    }

    destroy_heap(h);
}

