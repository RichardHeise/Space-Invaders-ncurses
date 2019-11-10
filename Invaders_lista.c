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

void atualiza_hitbox_unidade (t_jogo *uni) {
    int l, c, k;

    k = 0;
    for (l = 0; l < 3; ++l) {
        for (c = 0; c < 3; ++c) {
            uni->hitbox[k].posx = uni->posx + l;
            uni->hitbox[k].posy = uni->posy + c;
            k++;
        }
    }
}

void cria_alien (t_jogo *alien, int i, int j) {
    alien->vida = 1;
    alien->posx = i;
    alien->posy = j;
    alien->tipo = ALIEN_VET;

    alien->hitbox = malloc(sizeof(t_pos) * 9);
    alien->hitbox->tam = 9;
 
    atualiza_hitbox_unidade(alien);
}

void cria_aliens (t_lista *aliens) {
    int i, j;
    t_jogo alien;
    for (i = 6; i <= 24; i += 4) {
        for (j = 4; j <= 84; j += 8) {
            alien.ID = aliens->tamanho;
            cria_alien(&alien, i, j);
            insere_fim_lista(alien, aliens);
        }
    }
}

void cria_barreira (t_jogo *barreira, int i, int j) {
    barreira->vida = 1;
    barreira->posx = i;
    barreira->posy = j;
    barreira->tipo = BARREIRA;
}

void cria_armadura (t_lista *armadura) {
    int i, j;
    t_jogo barreira;
    inicializa_atual_inicio(armadura);
    for (i = 30; i < 33; ++i) {
        for (j = 2; j < 8; ++j) {
            barreira.ID = armadura->tamanho;
            cria_barreira(&barreira, i, j);
            insere_fim_lista(barreira, armadura);
        }
        for (j = 12; j < 18; ++j) {
            barreira.ID = armadura->tamanho;
            cria_barreira(&barreira, i, j);
            insere_fim_lista(barreira, armadura);
        }
        for (j = 22; j < 28; ++j) {
            barreira.ID = armadura->tamanho;
            cria_barreira(&barreira, i, j);
            insere_fim_lista(barreira, armadura);
        }
        for (j = 32; j < 38; ++j) {
            barreira.ID = armadura->tamanho;
            cria_barreira(&barreira, i, j);
            insere_fim_lista(barreira, armadura);
        }
        for (j = 62; j < 68; ++j) {
            barreira.ID = armadura->tamanho;
            cria_barreira(&barreira, i, j);
            insere_fim_lista(barreira, armadura);
        }
        for (j = 72; j < 78; ++j) {
            barreira.ID = armadura->tamanho;
            cria_barreira(&barreira, i, j);
            insere_fim_lista(barreira, armadura);
        }
        for (j = 82; j < 88; ++j) {
            barreira.ID = armadura->tamanho;
            cria_barreira(&barreira, i, j);
            insere_fim_lista(barreira, armadura);
        }
        for (j = 92; j < 98; ++j) {
            barreira.ID = armadura->tamanho;
            cria_barreira(&barreira, i, j);
            insere_fim_lista(barreira, armadura);
        }
    }
}

void printa_armadura_sprite (t_lista *barreira) {
    int i;
    inicializa_atual_inicio(barreira);
    for (i = 0; i < barreira->tamanho; ++i) {
        mvprintw(barreira->atual->chave.posx, barreira->atual->chave.posy, "=");
        incrementa_atual(barreira);
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

void move_aliens_direita (t_lista *aliens) {
    int i, j;
    inicializa_atual_inicio(aliens);
    for (j = 0; j < aliens->tamanho; ++j) {
        aliens->atual->chave.posy += 1;
        atualiza_hitbox_unidade(&aliens->atual->chave);
        incrementa_atual(aliens);
    }
}

void move_aliens_esquerda (t_lista *aliens) {
    int i, j;
    inicializa_atual_inicio(aliens);
    for (j = 0; j < aliens->tamanho; ++j) {
        aliens->atual->chave.posy -= 1;
        atualiza_hitbox_unidade(&aliens->atual->chave);
        incrementa_atual(aliens);
    }
}

void move_aliens_baixo (t_lista *aliens) {
    int i, j;
    inicializa_atual_inicio(aliens);
    for (j = 0; j < aliens->tamanho; ++j) {
        aliens->atual->chave.posx += 1;
        atualiza_hitbox_unidade(&aliens->atual->chave);
        incrementa_atual(aliens);
    }
    aliens->ini->chave.vel += 10;
}

void verifica_posicao_barreira (t_lista *aliens, t_lista *armadura) {
    int i, j, k;
    t_jogo lixo;
    inicializa_atual_inicio(aliens);
    for (i = 0; i < aliens->tamanho; ++i) {
        inicializa_atual_inicio(armadura);
        for (j = 0; j < armadura->tamanho; ++j) {
            for (k = 0; k < aliens->atual->chave.hitbox->tam; ++k) {
                if (armadura->atual->chave.posx == aliens->atual->chave.hitbox[k].posx && armadura->atual->chave.posy == aliens->atual->chave.hitbox[k].posy) {
                    remove_item_atual(&lixo, armadura);    
                }
            }
            incrementa_atual(armadura);
        }
        incrementa_atual(aliens);
    }
}

int verifica_borda (t_lista *aliens) {
    int i;
    inicializa_atual_inicio(aliens);
    for (i = 0; i < aliens->tamanho; ++i) {
        if (aliens->atual->chave.posy + 2 >= 99 || aliens->atual->chave.posy - 1 == 0) {
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

void cria_canhao (t_jogo *c) {
    c->vida = 1;
    c->posx = 35;
    c->posy = 50;
    c->tipo = CANHAO;

    c->hitbox = malloc (sizeof(t_jogo) * 9);
    
    atualiza_hitbox_unidade(c);
}

void printa_canhao_sprite (t_jogo *c) {
    mvprintw(c->hitbox[0].posx, c->hitbox[0].posy, "/"); 
    mvprintw(c->hitbox[1].posx, c->hitbox[1].posy, "A");
    mvprintw(c->hitbox[2].posx, c->hitbox[2].posy, "\\"); 
    mvprintw(c->hitbox[3].posx, c->hitbox[3].posy, "(");
    mvprintw(c->hitbox[4].posx, c->hitbox[4].posy, "@");
    mvprintw(c->hitbox[5].posx, c->hitbox[5].posy, ")");
    mvprintw(c->hitbox[6].posx, c->hitbox[6].posy, "^");
    mvprintw(c->hitbox[7].posx, c->hitbox[7].posy, "^");
    mvprintw(c->hitbox[8].posx, c->hitbox[8].posy, "^");
}

void move_canhao (t_jogo *c, char input) {
    if (input == 'a' && c->posy - 2 >= 0) {
        c->posy -= 1;
    } else if (input == 'd' && c->posy + 2 < 99) {
        c->posy += 1;
    }
    atualiza_hitbox_unidade(c);
}

void printa_tela (t_lista *l, t_lista *armadura, t_jogo *c) {
    int i, j;
    erase();
    for (i = 0; i < 38; ++i) {
        mvprintw(i, 0, "#");
        mvprintw(i, 100, "#");
    }
    for (j = 0; j < 100; ++j) {
        mvprintw(0, j, "#");
        mvprintw(38, j, "#");
    }
    t_jogo alien;
    inicializa_atual_inicio(l);
    for (i = 0; i < l->tamanho; ++i) {
        checa_item_atual(&alien, l);
        printa_alien_sprite(&alien);
        incrementa_atual(l);
    }
    printa_canhao_sprite(c);
    printa_armadura_sprite(armadura);
    refresh();
}

int canhao_vivo (t_lista *aliens) {
    int i;
    inicializa_atual_inicio(aliens);
    for (i = 0; i < aliens->tamanho; ++i) {
        if (aliens->atual->chave.posx + 2 == 35) { 
            return 0;
        }
        incrementa_atual(aliens);
    }
    return 1;
}

int main () {
    initscr();              /* inicia a tela */
    cbreak();               /* desabilita o buffer de entrada */
    noecho();               /* não mostra os caracteres digitados */
    nodelay(stdscr, TRUE);  /* faz com que getch não aguarde a digitação */
    keypad(stdscr, TRUE);   /* permite a leitura das setas */
    curs_set(FALSE);     
    t_lista lista_aliens;
    t_lista lista_bombas;
    t_lista lista_barreira;
    t_lista tiros;
    t_jogo canhao;
    int controlador;
    int constante;
    char entr;

    inicializa_lista(&lista_aliens);
    inicializa_lista(&lista_barreira);
    cria_armadura(&lista_barreira);
    cria_aliens(&lista_aliens);
    cria_canhao(&canhao);
    entr = getch();

    constante = 140;
    controlador = 8000;
    while (entr != 'q' && canhao.vida) {
        printa_tela(&lista_aliens, &lista_barreira, &canhao);
        if (controlador % (constante - lista_aliens.ini->chave.vel) == 0) {
            verifica_posicao_barreira(&lista_aliens, &lista_barreira);
            move_alien(&lista_aliens);
            canhao.vida = canhao_vivo(&lista_aliens);
        }
        entr = getch();
        move_canhao(&canhao, entr);
        usleep(2500);
        controlador -= 1;
    }
    endwin();
    return 0;
}