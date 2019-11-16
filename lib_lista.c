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

int insere_inicio_lista(t_jogo item, t_lista *l) {
    t_nodo *ptraux;
    ptraux = (t_nodo *) malloc (sizeof(t_nodo));
    if (ptraux == NULL)
        return 0;

    ptraux->chave = item;
    ptraux->ant = l->ini;
    ptraux->prox = l->ini->prox;
    ptraux->prox->ant = ptraux;
    l->ini->prox = ptraux;
    l->tamanho += 1;

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

int insere_ordenado_lista(t_jogo item, t_lista *l) {
    t_nodo *ptraux, *p;
    ptraux = (t_nodo *) malloc (sizeof(t_nodo));
    if (ptraux == NULL) {
        return 0;
    }

    l->fim->chave = item;
    p = l->ini->prox;
    while(p->chave.ID < item.ID) {
        p = p->prox;
    }
    ptraux->chave = item;
    ptraux->prox = p->ant->prox;
    ptraux->ant = p->ant;
    p->ant->prox = ptraux;
    ptraux->prox->ant = ptraux;
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

int remove_item_lista(t_jogo chave, t_jogo *item, t_lista *l) {
    t_nodo *p;
    if (lista_vazia(l)) {
        return 0;
    }
    l->fim->chave = chave;
    p = l->ini;
    while(p->prox->chave.ID != chave.ID) {
        p = p->prox;
    }
    if(p == l->fim->ant) {  /* Chegou na Sentinela e não achou a chave na lista */
        return 0;
    }
    p->prox = p->prox->prox;
    free(p->prox->ant);
    p->prox->ant = p;
    *item = chave;
    l->tamanho -= 1;

    return 1;
}

int pertence_lista(t_jogo chave, t_lista *l) {
    t_nodo *p;
    p = l->ini;
    l->fim->chave = chave;
    while(p->prox->chave.ID != chave.ID) {
        p = p->prox;
    }

    return (p->prox == l->fim) ? 0 : 1;
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

int decrementa_atual(t_lista *l) {
    if (lista_vazia(l) || l->atual == l->ini->prox) {
        return 0;
    }
    l->atual = l->atual->ant;

    return 1;
}

int checa_item_atual(t_jogo *item, t_lista *l) {
    if (lista_vazia(l)) {
        return 0;
    }
    *item = l->atual->chave;

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

void destroi_lista(t_lista *l) {
    int i, tam;
    t_jogo lixo;
    tam = l->tamanho;
    for (i = 0; i < tam; i += 1)
        remove_inicio_lista(&lixo, l);

    free(l->ini);
    free(l->fim);
}

void esvazia_lista(t_lista *l) {
    int i, tamanho;
    t_jogo item;
    tamanho_lista(&tamanho, l);
    for (i = 0; i < tamanho; i += 1) {
        remove_fim_lista(&item, l);
    }
}

