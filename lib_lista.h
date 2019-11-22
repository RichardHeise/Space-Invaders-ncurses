#include <stdio.h>
#include <stdlib.h>

/**
 * Estrutura que possui posicao no eixo X, Y e tamanho
 */
typedef struct posicao {
    int posx;
    int posy;
    int tam;
} t_pos;

/**
 * Estrutura de atributos das entidades do jogo
 */
typedef struct jogo {
    int ID;
    int tipo;
    int posx;
    int posy;
    int vel;
    int vida;
    t_pos hitbox[15];
} t_jogo;

/**
 * Estrutura do nodo da lista
 */
struct t_nodo {
    t_jogo chave;
    struct t_nodo *prox;
    struct t_nodo *ant;
};
typedef struct t_nodo t_nodo;

/**
 * Estrutura da lista
 */
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
    Insere item no final da lista.
    Se funcionar retorna 1, senão retorna 0.
*/
int insere_fim_lista(t_jogo item, t_lista *l);

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
    Remove o elemento apontado por atual da lista l e o retorna em item.
    Faz o atual apontar para o sucessor do nodo removido.
    Se funcionar retorna 1, senão retorna 0.
*/
int remove_item_atual(t_jogo *item, t_lista *l);

/*
    Remove todos os elementos da lista a partir do fim.
*/
void esvazia_lista(t_lista *l);