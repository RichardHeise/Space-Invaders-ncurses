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
#define MAX_TIROS 3

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

void atira (t_lista *tiros, t_jogo *c) {
    t_jogo tiro;
    tiro.vida = 1;
    tiro.posx = c->posx+1;
    tiro.posy = c->posy+1;
    tiro.tipo = TIRO;

    insere_fim_lista(tiro, tiros);
}

void atualiza_tiros (t_lista *tiros) {
    int i;
    inicializa_atual_inicio(tiros);
    for (i = 0; i < tiros->tamanho; ++i) {
        tiros->atual->chave.posx -= 1;
        incrementa_atual(tiros);
    }
}

void cria_alien (t_jogo *alien, int i, int j) {
    alien->vida = 1;
    alien->posx = i;
    alien->posy = j;
    alien->tipo = ALIEN_VET;

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

void cria_bomba (t_jogo *bomba, t_jogo *alien) {
    bomba->vida = 1;
    bomba->posx = alien->posx + 3;
    bomba->posy = alien->posy + 1;
    bomba->tipo = BOMBA;
}

void bombardeia (t_lista *aliens, t_lista *bombas) {
    int i;
    t_jogo bomba;
    inicializa_atual_inicio(aliens);
    for (i = 0; i < aliens->tamanho; ++i) {
        if (rand() % aliens->tamanho == 0) {
            cria_bomba(&bomba, &aliens->atual->chave);
            insere_fim_lista(bomba, bombas);
        }
        incrementa_atual(aliens);
    }
}

void atualiza_bomba (t_lista *bombas) {
    int i;
    inicializa_atual_inicio(bombas);
    for (i = 0; i < bombas->tamanho; ++i) {
        bombas->atual->chave.posx += 1;
        incrementa_atual(bombas);
    }
}

void printa_bombas (t_lista *bombas) {
    int i;
    inicializa_atual_inicio(bombas);
    for (i = 0; i < bombas->tamanho; ++i) {
        mvprintw(bombas->atual->chave.posx, bombas->atual->chave.posy, "v");
        incrementa_atual(bombas);
    }   
}

void verifica_colisao_bombas (t_lista *bombas, t_lista *armadura, t_jogo *c) {
    int i, j;
    inicializa_atual_inicio(bombas);
    t_jogo lixo;
    for (i = 0; i < bombas->tamanho; ++i) {
        inicializa_atual_inicio(armadura);
        for (j = 0; j < armadura->tamanho; ++j) {
            if (bombas->atual->chave.posx == armadura->atual->chave.posx && bombas->atual->chave.posy == armadura->atual->chave.posy) {
                remove_item_atual(&lixo, bombas);
                remove_item_atual(&lixo, armadura);
            }
            incrementa_atual(armadura);
        }
        incrementa_atual(bombas);
    }
}

void verifica_colisao_borda_bombas (t_lista *bombas) {
    int i;
    t_jogo lixo;
    inicializa_atual_inicio(bombas);
    for (i = 0; i < bombas->tamanho; ++i) {
        if (bombas->atual->chave.posx + 1 > 37) {
            remove_item_atual(&lixo, bombas);
        }
        incrementa_atual(bombas);
    }
}

void cria_canhao (t_jogo *c) {
    c->vida = 1;
    c->posx = 35;
    c->posy = 50;
    c->tipo = CANHAO;

    c->hitbox->tam = 9;
    
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

void printa_tiro(t_lista *tiros) {
    int i;
    inicializa_atual_inicio(tiros);
    for (i = 0; i < tiros->tamanho; ++i) {
        mvprintw(tiros->atual->chave.posx, tiros->atual->chave.posy, "|");
        incrementa_atual(tiros);
    }   
}

void printa_nave_mae (t_jogo *ramiel) {

    mvprintw(ramiel->hitbox[0].posx, ramiel->hitbox[0].posy, "W");
    mvprintw(ramiel->hitbox[1].posx, ramiel->hitbox[1].posy, "W");
    mvprintw(ramiel->hitbox[2].posx, ramiel->hitbox[2].posy, "W");
    mvprintw(ramiel->hitbox[3].posx, ramiel->hitbox[3].posy, "W");
    mvprintw(ramiel->hitbox[4].posx, ramiel->hitbox[4].posy, "W");
    mvprintw(ramiel->hitbox[5].posx, ramiel->hitbox[5].posy, "<");
    mvprintw(ramiel->hitbox[6].posx, ramiel->hitbox[6].posy, "=");
    mvprintw(ramiel->hitbox[7].posx, ramiel->hitbox[7].posy, "~");
    mvprintw(ramiel->hitbox[8].posx, ramiel->hitbox[8].posy, "=");
    mvprintw(ramiel->hitbox[9].posx, ramiel->hitbox[9].posy, ">");
    mvprintw(ramiel->hitbox[10].posx, ramiel->hitbox[10].posy, "U");
    mvprintw(ramiel->hitbox[11].posx, ramiel->hitbox[11].posy, "U");
    mvprintw(ramiel->hitbox[12].posx, ramiel->hitbox[12].posy, "U");
    mvprintw(ramiel->hitbox[13].posx, ramiel->hitbox[13].posy, "U");
    mvprintw(ramiel->hitbox[14].posx, ramiel->hitbox[14].posy, "U");
}

void printa_tela (t_lista *aliens, t_lista *armadura, t_lista *tiros, t_jogo *c, t_lista *bombas, t_jogo *ramiel) {
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
    inicializa_atual_inicio(aliens);
    for (i = 0; i < aliens->tamanho; ++i) {
        checa_item_atual(&alien, aliens);
        printa_alien_sprite(&alien);
        incrementa_atual(aliens);
    }
    printa_tiro(tiros);
    printa_bombas(bombas);
    printa_canhao_sprite(c);
    printa_armadura_sprite(armadura);
    printa_nave_mae(ramiel);
    
    refresh();
}

void atualiza_hitbox_nave_mae (t_jogo *ramiel) {
    int i, j, k;

    k = 0;
    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 5; ++j) {
            ramiel->hitbox[k].posx = ramiel->posx + i;
            ramiel->hitbox[k].posy = ramiel->posy + j;
            k++;
        }
    }
}

void cria_nave_mae (t_jogo *ramiel) {
    ramiel->vida = 1;
    ramiel->posx = 1;
    ramiel->posy = 1;
    ramiel->tipo = NAVE_MAE;

    atualiza_hitbox_nave_mae(ramiel);
}

void move_nave_mae (t_jogo *ramiel) {
    if (ramiel->posy + 4 < 99) {
        ramiel->posy += 1;
    } else {
        ramiel->vida = 0;
    }
    atualiza_hitbox_nave_mae(ramiel);
}

void verifica_colisao_alien (t_lista *tiros, t_lista *aliens) {
    int i, j, k;
    t_jogo lixo;
    inicializa_atual_inicio(tiros);
    for (i = 0; i < tiros->tamanho; ++i) {
        inicializa_atual_inicio(aliens);
        for (j = 0; j < aliens->tamanho; ++j) {
            for (k = 0; k < aliens->atual->chave.hitbox->tam; ++k) {
                if (tiros->atual->chave.posx == aliens->atual->chave.hitbox[k].posx && tiros->atual->chave.posy == aliens->atual->chave.hitbox[k].posy) {
                    remove_item_atual(&lixo, tiros);
                    remove_item_atual(&lixo, aliens);
                    break;            
                }
            }
            incrementa_atual(aliens);
        }
        incrementa_atual(tiros);
    }
}

void verifica_colisao_barreira (t_lista *tiros, t_lista *barreira) {
    int i, j;
    inicializa_atual_inicio(tiros);
    t_jogo lixo;
    for (i = 0; i < tiros->tamanho; ++i) {
        inicializa_atual_inicio(barreira);
        for (j = 0; j < barreira->tamanho; ++j) {
            if (tiros->atual->chave.posx == barreira->atual->chave.posx && tiros->atual->chave.posy == barreira->atual->chave.posy) {
                remove_item_atual(&lixo, tiros);
                mvprintw(barreira->atual->chave.posx, barreira->atual->chave.posy, "+");
                remove_item_atual(&lixo, barreira);
                break;
            }
            incrementa_atual(barreira);
        }
        incrementa_atual(tiros);
    }
}

void verifica_colisao_borda_tiros (t_lista *tiros) {
    int i;
    t_jogo lixo;
    inicializa_atual_inicio(tiros);
    for (i = 0; i < MAX_TIROS; ++i) {
        if (tiros->atual->chave.posx - 1 < 0) {
            remove_item_atual(&lixo, tiros);
        }
        incrementa_atual(tiros);
    }
}

int canhao_vivo (t_lista *aliens, t_lista *bombas, t_jogo *c) {
    int i, j, k;
    t_jogo lixo;
    inicializa_atual_inicio(aliens);
    inicializa_atual_inicio(bombas);
    for (i = 0; i < bombas->tamanho; ++i) {
        inicializa_atual_inicio(bombas);
        for (k = 0; k < c->hitbox->tam; ++k) {
            if (bombas->atual->chave.posx == c->hitbox[k].posx && bombas->atual->chave.posy == c->hitbox[k].posy) {
                remove_item_atual(&lixo, bombas);
                return 0;
            }
        }
        incrementa_atual(bombas);
    }
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
    t_lista lista_tiros;

    t_jogo nave_mae;
    t_jogo canhao;

    int controlador;
    int constante;
    char entr;

    inicializa_lista(&lista_bombas);
    inicializa_lista(&lista_aliens);
    inicializa_lista(&lista_barreira);
    inicializa_lista(&lista_tiros);

    cria_nave_mae(&nave_mae);
    cria_armadura(&lista_barreira);
    cria_aliens(&lista_aliens);
    cria_canhao(&canhao);

    entr = getch();

    constante = 120;
    controlador = 8000;

    while (entr != 'q' && canhao.vida && !lista_vazia(&lista_aliens)) {

        printa_tela(&lista_aliens, &lista_barreira, &lista_tiros, &canhao, &lista_bombas, &nave_mae);
        canhao.vida = canhao_vivo(&lista_aliens, &lista_bombas, &canhao);

        if (lista_aliens.ini->chave.vel >= 120) {
            lista_aliens.ini->chave.vel = 120;
        }

        if (controlador % 50 == 0 && nave_mae.vida) {
            move_nave_mae(&nave_mae);
        }

        if (controlador % (constante - lista_aliens.ini->chave.vel) == 0) {
            verifica_posicao_barreira(&lista_aliens, &lista_barreira);
            move_alien(&lista_aliens);
        }

        if (controlador % 260 == 0) {
            bombardeia(&lista_aliens, &lista_bombas);
        }

        if (controlador % 60 == 0 && !lista_vazia(&lista_bombas)) {
            verifica_colisao_borda_bombas(&lista_bombas);
            verifica_colisao_bombas(&lista_bombas, &lista_barreira, &canhao);
            atualiza_bomba(&lista_bombas);
        }

        entr = getch();
        if (entr == ' ' && lista_tiros.tamanho < 3) {
            atira(&lista_tiros, &canhao);
        }
        if (controlador % 10 == 0 && !lista_vazia(&lista_tiros)) {
            verifica_colisao_alien(&lista_tiros, &lista_aliens);
            verifica_colisao_barreira(&lista_tiros, &lista_barreira);
            verifica_colisao_borda_tiros(&lista_tiros);
            atualiza_tiros(&lista_tiros);
        }

        move_canhao(&canhao, entr);
        usleep(2500);
        controlador -= 1;
    }
    endwin();
    return 0;
}
