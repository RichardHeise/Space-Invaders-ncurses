#include "lib_lista.h"

int inicializa_lista(t_lista *l) {

    t_nodo *prim, *ult;

    prim = (t_nodo *) malloc (sizeof(t_nodo));
    if (prim == NULL)
        return 0;

    ult = (t_nodo *) malloc (sizeof(t_nodo));
    if (ult == NULL) {
        free(prim);
        return 0;
    }

    l->ini = prim;
    prim->prox = ult;
    prim->ant = NULL;
    l->fim = ult;
    ult->prox = NULL;
    ult->ant = prim;
    l->atual = NULL;
    l->tamanho = 0;

    return 1;
}

int lista_vazia(t_lista *l) {
    if (l->tamanho)
        return 0;
    return 1;
}

int tamanho_lista(int *tam, t_lista *l) {
    *tam = l->tamanho;

    return 1;
}

int insere_fim_lista(t_jogo item, t_lista *l) {
    t_nodo *ptraux;
    ptraux = (t_nodo *) malloc (sizeof(t_nodo));
    if (ptraux == NULL)
        return 0;

    ptraux->chave = item;
    ptraux->prox = l->fim;
    ptraux->ant = l->fim->ant;
    l->fim->ant->prox = ptraux;
    l->fim->ant = ptraux;
    l->tamanho += 1;

    return 1;
}

int remove_inicio_lista(t_jogo *item, t_lista *l) {
    if (lista_vazia(l)) {
        return 0;
    }
    *item = l->ini->prox->chave;
    l->ini->prox = l->ini->prox->prox;
    free(l->ini->prox->ant);
    l->ini->prox->ant = l->ini;
    l->tamanho -= 1;

    return 1;
}

int remove_fim_lista(t_jogo *item, t_lista *l) {
    if (lista_vazia(l)) {
        return 0;
    }
    *item = l->fim->ant->chave;
    l->fim->ant = l->fim->ant->ant;
    free(l->fim->ant->prox);
    l->fim->ant->prox = l->fim;
    l->tamanho -= 1;

    return 1;
}


int inicializa_atual_inicio(t_lista *l) {
    if (lista_vazia(l)) {
        return 0;
    }
    l->atual = l->ini->prox;

    return 1;
}

int inicializa_atual_fim(t_lista *l) {
    if (lista_vazia(l)) {
        return 0;
    }
    l->atual = l->fim->ant;

    return 1;
}

int incrementa_atual(t_lista *l) {
    if (lista_vazia(l) || l->atual == l->fim->ant) {
        return 0;
    }
    l->atual = l->atual->prox;

    return 1;
}

int remove_item_atual(t_jogo *item, t_lista *l) {
    if (lista_vazia(l)) {
        return 0;
    }
    t_nodo *p;
    p = l->atual;
    *item = l->atual->chave;
    l->atual->ant->prox = l->atual->prox;
    l->atual->prox->ant = l->atual->ant;

    if (l->atual->prox == l->fim) {
        l->atual = l->atual->ant;
    } else {
        l->atual = l->atual->prox;
    }
    free(p);
    l->tamanho -= 1;

    return 1;
}

void esvazia_lista(t_lista *l) {
    int i, tamanho;
    t_jogo item;
    tamanho_lista(&tamanho, l);
    for (i = 0; i < tamanho; i += 1) {
        remove_fim_lista(&item, l);
    }
}

