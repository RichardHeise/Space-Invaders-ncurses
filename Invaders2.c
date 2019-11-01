#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>

#define LINHAS 38
#define COLUNAS 50
#define MAX_TIROS 3

typedef struct s_unidade {
    int posx;
    int posy;
} t_unidade;

typedef struct s_exercito {
    t_unidade aliens[1000];
    int tam;
} t_exercito;

typedef struct s_shot {
    int posx;
    int posy;
    int vida;
} t_shot;

typedef struct s_tela {
    int **matrix;
    int linhas;
    int colunas;
} t_tela;

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

void print_tela_final (t_tela *t_a, t_tela *t_c, t_tela *t_t, int lin, int col) {
    int i, j;
    for (i = 0; i < lin; ++i) {
        for (j = 0; j < col; ++j) {
            if (t_a->matrix[i][j] < 0) {
                mvprintw(i, j, "#");
            } else if (t_a->matrix[i][j] == 1) {
                mvprintw(i, j, "M");
            } else if (t_a->matrix[i][j] == 7) {
                mvprintw(i, j, "X");
            } else if (t_c->matrix[i][j] == 1) {
                mvprintw(i, j, "W");
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

void verifica_tiro (t_tela *t_t, t_tela *t_a, t_exercito *a, t_shot shots[], int *max) {
    int i, index;
    for (i = 0; i < MAX_TIROS; ++i) {
        if (shots[i].posx-1 < 0) {
            shots[i].vida = 0;
            remove_vetor_tiro(shots);
            *max = *max - 1;
        } else if (shots[i].vida && t_a->matrix[shots[i].posx][shots[i].posy]) {
            t_t->matrix[shots[i].posx][shots[i].posy] = 0;
            t_a->matrix[shots[i].posx][shots[i].posy] = 7;
            index = acha_alien(a, shots[i].posx, shots[i].posy);
            remove_vetor_alien(a, index);
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

void atualiza_tela_alien (t_tela *t_a, t_exercito *a, int *vel) {
    zera_tela(t_a, LINHAS, COLUNAS);
    move_aliens(t_a, a, vel);
    escreve_aliens_tela(t_a, a);
}

void atualiza_tela_canhao (t_tela *t_c, t_unidade *can, int input) {
    zera_tela(t_c, LINHAS, COLUNAS);
    move_nave(t_c, can, input);
    escreve_canhao_tela(t_c, can);
}

int canhao_vivo (t_exercito *a) {
    int i;
    for (i = 0; i < a->tam; ++i) {
        if (a->aliens[i].posx == LINHAS - 2)
            return 0;
    }
    return 1;
}

int main () {
    initscr();              /* inicia a tela */
    cbreak();               /* desabilita o buffer de entrada */
    noecho();               /* não mostra os caracteres digitados */
    nodelay(stdscr, TRUE);  /* faz com que getch não aguarde a digitação */
    keypad(stdscr, TRUE);   /* permite a leitura das setas */
    curs_set(FALSE);        /* não mostra o cursor na tela */

    t_tela tela_tiro;
    t_tela tela_canhao;
    t_tela tela_aliens;
    t_exercito unidades;
    t_unidade canhao;
    t_shot tiros[MAX_TIROS];

    canhao.posx = LINHAS - 2;
    canhao.posy = COLUNAS / 2;

    int contador, controle, velocidade;
    char entr;
    int i;

    velocidade = 0;
    controle = 100;
    contador = 8000;

    for (i=0; i < MAX_TIROS; i++) {
        tiros[i].vida = 0;
        tiros[i].posx = LINHAS;
        tiros[i].posy = COLUNAS;
    }

    cria_tela(&tela_aliens, LINHAS, COLUNAS);
    cria_tela(&tela_canhao, LINHAS, COLUNAS);
    cria_tela(&tela_tiro, LINHAS, COLUNAS);
    cria_aliens(&unidades);
    atualiza_tela_alien(&tela_aliens, &unidades, &velocidade);

    i = 0;

    while (entr != 'q' && canhao_vivo(&unidades) && unidades.tam != 0) {
        print_tela_final(&tela_aliens, &tela_canhao, &tela_tiro, LINHAS, COLUNAS);
        if (contador % (controle - velocidade) == 0) {
            atualiza_tela_alien(&tela_aliens, &unidades, &velocidade);
        }
        entr = getch();
        if (entr == ' ' && i < MAX_TIROS) {
            atira(&tela_tiro, &tiros[i], canhao.posx, canhao.posy);
            i++;
        }
        if (contador % 12 == 0) {
            verifica_tiro(&tela_tiro, &tela_aliens, &unidades, tiros, &i);
            atualiza_tiro(&tela_tiro, tiros);
        }
        atualiza_tela_canhao(&tela_canhao, &canhao, entr);
        usleep(2500);
        contador -= 1;
    }
    endwin();
    return 0;
}
