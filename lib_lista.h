#include <stdio.h>
#include <stdlib.h>

typedef struct posicao {
    int posx;
    int posy;
    int tam;
} t_pos;

typedef struct jogo {
    int ID;
    int tipo;
    int posx;
    int posy;
    int vel;
    int vida;
    t_pos hitbox[15];
} t_jogo;

struct t_nodo {
    t_jogo chave;
    struct t_nodo *prox;
    struct t_nodo *ant;
};
typedef struct t_nodo t_nodo;

struct t_lista {
    t_nodo *ini;
    t_nodo *atual;
    t_nodo *fim;
    int tamanho;
};
typedef struct t_lista t_lista;

/*
    Cria uma lista vazia.
*/
int inicializa_lista(t_lista *l);

/*
    Se a lista está vazia, retorna 1. Do contrário retorna 0.
*/
int lista_vazia(t_lista *l);

/*
    Remove todos os elementos da lista e faz com que ela aponte para NULL.
*/
void destroi_lista(t_lista *l);

/*
    Insere item no início da lista.
    Se funcionar retorna 1, caso contário retorna 0.
*/
int insere_inicio_lista(t_jogo item, t_lista *l);

/*
    Retorna o tamanho da lista em *tam.
    Se funcionar retorna 1, senão retorna 0.
*/
int tamanho_lista(int *tam, t_lista *l);

/*
    Insere item no final da lista.
    Se funcionar retorna 1, senão retorna 0.
*/
int insere_fim_lista(t_jogo item, t_lista *l);

/*
    Insere item ordenadamente na lista.
    Se funcionar retorna 1, senão retorna 0.
*/
int insere_ordenado_lista(t_jogo item, t_lista *l);

/*
    Remove o primeiro elemento da lista e o retorna em item.
    Se funcionar retorna 1, senão retorna 0.
*/
int remove_inicio_lista(t_jogo *item, t_lista *l);

/*
    Remove o último elemento da lista e o retorna em item.
    Se funcionar retorna 1, senão retorna 0.
*/
int remove_fim_lista(t_jogo *item, t_lista *l);

/*
    Se o elemento chave existir na lista, o retorna em item.
    Se funcionar retorna 1, senão retorna 0.
    (elemento não encontrado também retorna zero).
*/
int remove_item_lista(t_jogo chave, t_jogo *item, t_lista *l);

/*
    Verifica se a chave pertence existe na lista.
    Se funcionar retorna 1, senão retorna 0.
*/
int pertence_lista(t_jogo chave, t_lista *l);

/* 
    Inicializa o ponteiro atual para o primeiro elemento da lista.
    Se funcionar retorna 1, senão retorna 0.
*/
int inicializa_atual_inicio(t_lista *l);

/* 
    Inicializa o ponteiro atual para o ultimo elemento da lista.
    Se funcionar retorna 1, senão retorna 0.
*/
int inicializa_atual_fim(t_lista *l);

/*
    Faz o ponteiro atual apontar para o próximo nodo da lista l e retorna 
    este ponteiro. Se atual estiver apontando para o último -- não 
    tem próximo -- retorna NULL.
*/
int incrementa_atual(t_lista *l);

/*
    Faz o ponteiro atual apontar para o nodo anterior da lista l e retorna 
    este ponteiro. Se atual estiver apontando para o primeiro -- isto é, não 
    tem anterior -- retorna NULL.
*/
int decrementa_atual(t_lista *l);

/*
    Retorna em item o valor contido na chave apontada pelo ponteiro atual. 
    Se atual não for válido a função retorna 0, senão retorna 1.
*/
int checa_item_atual(t_jogo *item, t_lista *l);

/*
    Remove o elemento apontado por atual da lista l e o retorna em item.
    Faz o atual apontar para o sucessor do nodo removido.
    Se funcionar retorna 1, senão retorna 0.
*/
int remove_item_atual(t_jogo *item, t_lista *l);

/*
    Remove todos os elementos da lista a partir do fim.
*/
void esvazia_lista(t_lista *l);

void imprime_lista(t_lista *l);
