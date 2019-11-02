#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>
#include "Invaders_lib.h"

void cria_tela (t_tela *t, int lin, int col) {
    int i;
    t->matrix = (int **) malloc(sizeof(int *) * lin);
    for (i = 0; i < lin; ++i) {
        t->matrix[i] = (int *) malloc(sizeof(int) * col);
    }
    t->linhas = lin;
    t->colunas = col;
    int j;
    for (i = 0; i < lin; ++i) {
        for (j = 0; j < col; ++j) {
            t->matrix[i][j] = 0;
        }
    }
    for (i = 0; i < lin; ++i) {
        t->matrix[i][0] = -1;
        t->matrix[i][col-1] = -1;
    }
    for (i = 0; i < col; ++i) {
        t->matrix[0][i] = -1;
        t->matrix[lin-1][i] = -1;
    }
}

void zera_tela (t_tela *t, int lin, int col) {
    int i, j;
    for (i = 1; i < lin-1; ++i) {
        for (j = 1; j < col-1; ++j) {
            t->matrix[i][j] = 0;
        }
    }
}

void print_tela_final (t_tela *t_a, t_tela *t_c, t_tela *t_t, t_tela *t_b, int lin, int col) {
    int i, j;
    for (i = 0; i < lin; ++i) {
        for (j = 0; j < col; ++j) {
            if (t_a->matrix[i][j] < 0) {
                mvprintw(i, j, "#");
            } else if (t_a->matrix[i][j] == 1) {
                mvprintw(i, j, "M");
            } else if (t_a->matrix[i][j] == 2) {
                mvprintw(i, j, "=");
            } else if (t_a->matrix[i][j] == 3) {
                mvprintw(i, j, "+");
            } else if (t_a->matrix[i][j] == 7) {
                mvprintw(i, j, "X");
            } else if (t_c->matrix[i][j] == 1) {
                mvprintw(i, j, "W");
            }
            else if (t_b->matrix[i][j] == 8) {
                mvprintw(i, j, "v");
            } else if (t_t->matrix[i][j] == 5) {
                mvprintw(i, j, "|");
            } else {
                mvprintw(i, j, " ");
            }
        }
    }
    refresh();
}

void cria_alien (t_unidade *alien, int r, int c) {
    alien->posx = r;
    alien->posy = c;
}

void cria_aliens (t_exercito *a) {
    int i, j;
    int k = 0;
    for (i = 2; i <= 6; i += 2) {
        for (j = 6; j <= COLUNAS - 6; j += 2) {
            cria_alien(&(a->aliens[k]), i, j);
            k++;
        }
    }
    a->tam = k;
}

void cria_barreira (t_tela *t_a, t_armadura *bar) {
    int i, j, k;
    k = 0;
    for (i = 30; i < 32; ++i) {
        for (j = 3; j < 6; ++j) {
            bar->barreira[k].posx = i;
            bar->barreira[k].posy = j;
            k += 1;  
        }
        for (j = 40; j < 43; ++j) {
            bar->barreira[k].posx = i;
            bar->barreira[k].posy = j;
            k += 1;
        }
        for (j = 8; j < 11; ++j) {
            bar->barreira[k].posx = i;
            bar->barreira[k].posy = j;
            k += 1;
        }
        for (j = 34; j < 37; ++j) {
            bar->barreira[k].posx = i;
            bar->barreira[k].posy = j;
            k += 1;
        }
        for (j = 28; j < 32; ++j) {
            bar->barreira[k].posx = i;
            bar->barreira[k].posy = j;
            k += 1;
        }
        for (j = 13; j < 16; ++j) {
            bar->barreira[k].posx = i;
            bar->barreira[k].posy = j;
            k += 1;
        }
    }
    bar->tam = k;
}

void escreve_barreira_tela (t_tela *t_a, t_armadura *bar) {
    int i;
    for (i = 0; i < bar->tam; ++i) {
        t_a->matrix[bar->barreira[i].posx][bar->barreira[i].posy] = 2;
    }
}

void escreve_aliens_tela (t_tela *t, t_exercito *a) {
    int i;
    for (i = 0; i < a->tam; ++i) {
        t->matrix[a->aliens[i].posx][a->aliens[i].posy] = 1;
    }
}

int checa_borda (t_tela *t, t_exercito *a) {
    int i;
    for (i = 0; i < a->tam; ++i) {
        if (t->matrix[a->aliens[i].posx][a->aliens[i].posy-1] < 0 || t->matrix[a->aliens[i].posx][a->aliens[i].posy+1] < 0) {
            return 1;
        }
    }
    return 0;
}

void move_aliens_baixo (t_exercito *a) {
    int i;
    for (i = 0; i < a->tam; ++i) {
        a->aliens[i].posx += 1;
    }
}

void move_aliens_esquerda (t_tela *t, t_exercito *a) {
    int i;
    for (i = 0; i < a->tam; ++i) { 
        a->aliens[i].posy -= 1;
    }
}

void move_aliens_direita (t_tela *t, t_exercito *a) {
    int i;
    int cont = 0; 
    for (i = 0; i < a->tam; ++i) { 
        a->aliens[i].posy += 1;
    }
}

void move_aliens (t_tela *t, t_exercito *a, int *vel) {
    if (checa_borda(t, a)) {
        move_aliens_baixo(a);
        *vel += 1;
    }
    if (a->aliens[0].posx % 2 == 0) {
        move_aliens_direita(t, a);
    } else {
        move_aliens_esquerda(t, a);
    }
}

void remove_vetor_alien (t_exercito *a, int i) {
    int k;
    for (k = i; k < a->tam; ++k) {
        a->aliens[k].posx = LINHAS;
        a->aliens[k].posy = COLUNAS;
        a->aliens[k] = a->aliens[k+1];
    }
    a->tam = a->tam - 1;
}

void solta_bombas (t_tela *t_b, t_arsenal *b, int k, t_unidade *alien) {
    b->bombas[k].vida = 1;
    b->bombas[k].posx = alien->posx+1;
    b->bombas[k].posy = alien->posy;
    t_b->matrix[b->bombas[k].posx][b->bombas[k].posy] = 8;
}

void cria_bombas (t_tela *t_b, t_arsenal *b, t_exercito *a) {
    int i, k;
    k = b->tam;
    for (i = 0; i < a->tam; ++i) {
        if (rand() % a->tam == 0) {
            solta_bombas(t_b, b, k, &a->aliens[i]);
            k += 1;
        }
    }
    b->tam = k;
}

void atualiza_bomba (t_tela *t_b, t_bomba *bom) {
    t_b->matrix[bom->posx][bom->posy] = 0;
    bom->posx = bom->posx + 1;
    t_b->matrix[bom->posx][bom->posy] = 8;   
}

void remove_vetor_bombas (t_arsenal *b, int i) {
    int k;
    for (k = i; k < b->tam - 1; k++) {
        b->bombas[k] = b->bombas[k+1];
    }
    b->tam -= 1;
}

void verifica_bomba (t_tela *t_b, t_tela *t_a, t_exercito *a, t_arsenal *b, t_armadura *bar, int *max) {
    int i, index;
    for (i = 0; i < b->tam; ++i) {
        if (b->bombas[i].posx+1 > (LINHAS - 2)) {
            t_b->matrix[b->bombas[i].posx][b->bombas[i].posy] = 0;
            b->bombas[i].vida = 0;
            remove_vetor_bombas(b, i);
            *max = *max - 1;
        } else if (b->bombas[i].vida && t_a->matrix[b->bombas[i].posx][b->bombas[i].posy] == 2) {
            t_a->matrix[b->bombas[i].posx][b->bombas[i].posy] = 3;
            t_b->matrix[b->bombas[i].posx][b->bombas[i].posy] = 0;
            index = acha_elemento(bar, b->bombas[i].posx, b->bombas[i].posy);
            remove_vetor_barreira(bar, index);
            b->bombas[i].vida = 0;
            remove_vetor_bombas(b, i);
            *max = *max - 1;
        } else {
            atualiza_bomba(t_b, &b->bombas[i]);
        }
    }
}

void remove_vetor_barreira (t_armadura *bar, int i) {
    int k;
    for (k = i; k < bar->tam; ++k) {
        bar->barreira[k].posx = LINHAS;
        bar->barreira[k].posy = COLUNAS;
        bar->barreira[k] = bar->barreira[k+1];
    }
    bar->tam = bar->tam - 1;
}

void remove_vetor_tiro (t_shot shots[]) {
    int k;
    for (k = 0; k < MAX_TIROS - 1; k++) {
        shots[k] = shots[k+1];
        shots[k+1].posx = LINHAS;
        shots[k+1].posy = COLUNAS;
        shots[k+1].vida = 0;
    }
}

void atira (t_tela *t_t, t_shot *shot, int i, int j) {
    shot->posx = i-1;
    shot->posy = j;
    shot->vida = 1;
    t_t->matrix[shot->posx][shot->posy] = 5;
}

void atualiza_tiro (t_tela *t_t, t_shot s[]) {
    int i, k;
    k = 0;
    for (i=0; i < MAX_TIROS; ++i) {
        if (s[i].vida) {
            t_t->matrix[s[i].posx][s[i].posy] = 0;
            s[i].posx = s[i].posx - 1;
            t_t->matrix[s[i].posx][s[i].posy] = 5;
            k++;
        }
    }   
    if (! k) {
        zera_tela(t_t, LINHAS, COLUNAS);
    }
}

int acha_alien (t_exercito *a, int i, int j) {
    int k;
    for (k = 0; k < a->tam; ++k) {
        if (a->aliens[k].posx == i && a->aliens[k].posy == j) {
            return k;
        }
    }
}

int acha_elemento (t_armadura *bar, int i, int j) {
    int k;
    for (k = 0; k < bar->tam; ++k) {
        if (bar->barreira[k].posx == i && bar->barreira[k].posy == j) {
            return k;
        }
    }
}

void verifica_tiro (t_tela *t_t, t_tela *t_a, t_exercito *a, t_shot shots[], t_armadura *bar, int *max) {
    int i, index;
    for (i = 0; i < MAX_TIROS; ++i) {
        if (shots[i].posx-1 < 0) {
            shots[i].vida = 0;
            remove_vetor_tiro(shots);
            *max = *max - 1;
        } else if (shots[i].vida && t_a->matrix[shots[i].posx][shots[i].posy] == 1) {
            t_t->matrix[shots[i].posx][shots[i].posy] = 0;
            t_a->matrix[shots[i].posx][shots[i].posy] = 7;
            index = acha_alien(a, shots[i].posx, shots[i].posy);
            remove_vetor_alien(a, index);
            shots[i].vida = 0;
            remove_vetor_tiro(shots);
            *max = *max - 1;
        } else if (shots[i].vida && t_a->matrix[shots[i].posx][shots[i].posy] == 2) {
            t_t->matrix[shots[i].posx][shots[i].posy] = 0;
            t_a->matrix[shots[i].posx][shots[i].posy] = 3;
            index = acha_elemento(bar, shots[i].posx, shots[i].posy);
            remove_vetor_barreira(bar, index);
            shots[i].vida = 0;
            remove_vetor_tiro(shots);
            *max = *max - 1;
        }
    }
}

void escreve_canhao_tela (t_tela *t_c, t_unidade *can) {
    t_c->matrix[can->posx][can->posy] = 1;
}

void move_nave (t_tela *t_c, t_unidade *can, int input) {
    if (input == 'a' && can->posy-1 > 0) {
        can->posy -= 1;
    } else if (input == 'd' && can->posy+1 < COLUNAS - 1) {
        can->posy += 1;
    } 
}

void verifica_posicao (t_tela *t_a, t_exercito *a, t_armadura *bar) {
    int i, j, index;
    for (i = 0; i < a->tam; ++i) {
        for (j = 0; j < bar->tam; ++j) {
            if (a->aliens[i].posx == bar->barreira[j].posx && a->aliens[i].posy == bar->barreira[j].posy) {
                index = acha_elemento(bar, bar->barreira[j].posx, bar->barreira[j].posy);
                remove_vetor_barreira(bar, index);
            }
        }
    }
}

void atualiza_tela_alien (t_tela *t_a, t_exercito *a, t_armadura *bar, int *vel) {
    zera_tela(t_a, LINHAS, COLUNAS);
    move_aliens(t_a, a, vel);
    verifica_posicao(t_a, a, bar);
    escreve_aliens_tela(t_a, a);
}

void atualiza_tela_canhao (t_tela *t_c, t_unidade *can, int input) {
    zera_tela(t_c, LINHAS, COLUNAS);
    move_nave(t_c, can, input);
    escreve_canhao_tela(t_c, can);
}

int canhao_vivo (t_exercito *a, t_arsenal *b, t_unidade *can) {
    int i;
    for (i = 0; i < a->tam; ++i) {
        if (a->aliens[i].posx == LINHAS - 2)
            return 0;
    }
    for ( i = 0; i < b->tam; ++i) {
        if (b->bombas[i].posx == can->posx && b->bombas[i].posy == can->posy) {
            return 0;
        }
    }
    return 1;
}