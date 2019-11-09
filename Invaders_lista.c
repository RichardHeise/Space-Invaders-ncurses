#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include "lib_lista.h"

#define ALIEN_VET 1
#define ALIEN_CAL 2
#define NAVE_MAE 3
#define BARREIRA 4
#define CANHAO 5
#define TIRO 6
#define BOMBA 7

void cria_alien (t_jogo *alien, int i, int j) {
    int l, k, c;
    alien->vida = 1;
    alien->posx = i;
    alien->posy = j;
    alien->tipo = ALIEN_VET;
    
    alien->hitbox = malloc(sizeof(t_pos) * 9);

    k = 0;
    for (l = 0; l < 3; ++l) {
        for (c = 0; c < 3; ++c) {
            alien->hitbox[k].posx = alien->posx + l;
            alien->hitbox[k].posy = alien->posy + c;
            k++;
        }
    }
    alien->hitbox->tam = k;
}

void cria_aliens (t_lista *aliens) {
    int i, j;
    t_jogo alien;
    for (i = 6; i <= 24; i += 4) {
        for (j = 2; j <= 42; j += 4) {
            alien.ID = aliens->tamanho;
            cria_alien(&alien, i, j);
            insere_fim_lista(alien, aliens);
        }
    }
}

void printa_alien_sprite (t_jogo *alien) {
    if (alien->tipo == ALIEN_VET) {
        mvprintw(alien->hitbox[0].posx, alien->hitbox[0].posy, "@");
        mvprintw(alien->hitbox[1].posx, alien->hitbox[1].posy, "Y");
        mvprintw(alien->hitbox[2].posx, alien->hitbox[2].posy, "@");
        mvprintw(alien->hitbox[3].posx, alien->hitbox[3].posy, "V");
        mvprintw(alien->hitbox[4].posx, alien->hitbox[4].posy, "E");
        mvprintw(alien->hitbox[5].posx, alien->hitbox[5].posy, "T");
        mvprintw(alien->hitbox[6].posx, alien->hitbox[6].posy, "/");
        mvprintw(alien->hitbox[7].posx, alien->hitbox[7].posy, "|");
        mvprintw(alien->hitbox[8].posx, alien->hitbox[8].posy, "\\"); 
    }
}

void printa_tela (t_lista *l) {
    int i, j;
    t_jogo alien;
    inicializa_atual_inicio(l);
    for (i = 0; i < l->tamanho; ++i) {
        checa_item_atual(&alien, l);
        printa_alien_sprite(&alien);
        incrementa_atual(l);
    }
    refresh();
}

void move_aliens_direita (t_lista *aliens) {
    int i, j;
    inicializa_atual_inicio(aliens);
    for (j = 0; j < aliens->tamanho; ++j) {
        for (i = 0; i < aliens->atual->chave.hitbox->tam; ++i) {
            aliens->atual->chave.hitbox[i].posy += 1;
            aliens->atual->chave.posy += 1;
        }
        incrementa_atual(aliens);
    }
}

void move_aliens_esquerda (t_lista *aliens) {
    int i, j;
    inicializa_atual_inicio(aliens);
    for (j = 0; j < aliens->tamanho; ++j) {
        for (i = 0; i < aliens->atual->chave.hitbox->tam; ++i) {
            aliens->atual->chave.hitbox[i].posy -= 1;
            aliens->atual->chave.posy -= 1;
        }
        incrementa_atual(aliens);
    }
}

void move_aliens_baixo (t_lista *aliens) {
    int i, j;
    inicializa_atual_inicio(aliens);
    for (j = 0; j < aliens->tamanho; ++j) {
        for (i = 0; i < aliens->atual->chave.hitbox->tam; ++i) {
            aliens->atual->chave.hitbox[i].posx += 1;
            aliens->atual->chave.posx += 1;
            aliens->atual->chave.vel += 1;
        }
        incrementa_atual(aliens);
    }
}

int verifica_borda (t_lista *aliens) {
    int i;
    inicializa_atual_inicio(aliens);
    for (i = 0; i < aliens->tamanho; ++i) {
        if (aliens->atual->chave.posy + 3 >= 98 || aliens->atual->chave.posy - 1 == 0) {
            return 1;
        }
        incrementa_atual(aliens);
    }
    return 0;
}

void move_alien (t_lista *aliens) {
    
    if (verifica_borda(aliens)) {
        move_aliens_baixo(aliens);
    }

    inicializa_atual_inicio(aliens);
    if (aliens->atual->chave.posx % 2 == 0) {
        move_aliens_direita(aliens);
    } else {
        move_aliens_esquerda(aliens);
    }
}

int main () {
    initscr();              /* inicia a tela */
    cbreak();               /* desabilita o buffer de entrada */
    noecho();               /* não mostra os caracteres digitados */
    nodelay(stdscr, TRUE);  /* faz com que getch não aguarde a digitação */
    keypad(stdscr, TRUE);   /* permite a leitura das setas */
    curs_set(FALSE);     
    t_lista lista_alien;
    t_lista lista_bombas;
    t_lista lista_barreira;
    t_lista tiros;
    char entr;
    inicializa_lista(&lista_alien);
    cria_aliens(&lista_alien);
    // printf("beep");
    entr = getch();
    while (entr != 'q') {
        printa_tela(&lista_alien);
        usleep(250000);
        move_alien(&lista_alien);
        clear();
        entr = getch();
    }
    endwin();
    return 0;
}