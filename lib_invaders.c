#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include "lib_invaders.h"

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
    tiro.posx = c->posx-1;
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

    alien->hitbox->tam = 9;
 
    atualiza_hitbox_unidade(alien);
}

void cria_aliens (t_lista *aliens) {
    int i, j;
    t_jogo alien;
    for (j = INI_COL_ALIEN; j < FIM_COL_ALIEN; j += 8) {
        for (i = INI_LIN_ALIEN; i < FIM_LIN_ALIEN; i += 4) {
            alien.ID = aliens->tamanho;
            if (i == INI_LIN_ALIEN) {
                alien.tipo = ALIEN_VET;
            } else {
                alien.tipo = ALIEN_CAL;
            }
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
    for (i = INI_LIN_BAR; i < FIM_LIN_BAR; ++i) {
        for (j = INI_COL_BAR; j < FIM_COL_BAR; ++j) {
            barreira.ID = armadura->tamanho;
            cria_barreira(&barreira, i, j);
            insere_fim_lista(barreira, armadura);
        }
        for (j = 10 + INI_COL_BAR; j < 10 + FIM_COL_BAR; ++j) {
            barreira.ID = armadura->tamanho;
            cria_barreira(&barreira, i, j);
            insere_fim_lista(barreira, armadura);
        }
        for (j = 20 + INI_COL_BAR; j < 20 + FIM_COL_BAR; ++j) {
            barreira.ID = armadura->tamanho;
            cria_barreira(&barreira, i, j);
            insere_fim_lista(barreira, armadura);
        }
        for (j = 30 + INI_COL_BAR; j < 30 + FIM_COL_BAR; ++j) {
            barreira.ID = armadura->tamanho;
            cria_barreira(&barreira, i, j);
            insere_fim_lista(barreira, armadura);
        }
        for (j = 60 + INI_COL_BAR; j < 60 + FIM_COL_BAR; ++j) {
            barreira.ID = armadura->tamanho;
            cria_barreira(&barreira, i, j);
            insere_fim_lista(barreira, armadura);
        }
        for (j = 70 + INI_COL_BAR; j < 70 + FIM_COL_BAR; ++j) {
            barreira.ID = armadura->tamanho;
            cria_barreira(&barreira, i, j);
            insere_fim_lista(barreira, armadura);
        }
        for (j = 80 + INI_COL_BAR; j < 80 + FIM_COL_BAR; ++j) {
            barreira.ID = armadura->tamanho;
            cria_barreira(&barreira, i, j);
            insere_fim_lista(barreira, armadura);
        }
        for (j = 90 + INI_COL_BAR; j < 90 + FIM_COL_BAR; ++j) {
            barreira.ID = armadura->tamanho;
            cria_barreira(&barreira, i, j);
            insere_fim_lista(barreira, armadura);
        }
    }
}

void printa_explosao (t_jogo *unidade) {
    mvprintw(unidade->posx, unidade->posy,   "\\|*");
    mvprintw(unidade->posx+1, unidade->posy, "- -");
    mvprintw(unidade->posx+2, unidade->posy, "*|'");
}

void printa_alien (t_lista *aliens) {
    int i, x, y;
    t_jogo alien;
    inicializa_atual_inicio(aliens);
    for (i = 0; i < aliens->tamanho; ++i) {
        alien = aliens->atual->chave;
        if (alien.vida == 9) {
            printa_explosao(&alien);
        } else if (alien.tipo == ALIEN_VET) {
            mvprintw(alien.posx, alien.posy,   "@T@");
            mvprintw(alien.posx+1, alien.posy, "VET");
            mvprintw(alien.posx+2, alien.posy, ">O<");
        } else if (alien.tipo == ALIEN_CAL) {
            mvprintw(alien.posx, alien.posy,   "^+^");
            mvprintw(alien.posx+1, alien.posy, "CAL");
            mvprintw(alien.posx+2, alien.posy, "\\^/");
        }
        incrementa_atual(aliens);
    } 
}

void move_aliens_direita (t_lista *aliens) {
    int j;
    inicializa_atual_inicio(aliens);
    for (j = 0; j < aliens->tamanho; ++j) {
        aliens->atual->chave.posy += 1;
        atualiza_hitbox_unidade(&aliens->atual->chave);
        incrementa_atual(aliens);
    }
}

void move_aliens_esquerda (t_lista *aliens) {
    int j;
    inicializa_atual_inicio(aliens);
    for (j = 0; j < aliens->tamanho; ++j) {
        aliens->atual->chave.posy -= 1;
        atualiza_hitbox_unidade(&aliens->atual->chave);
        incrementa_atual(aliens);
    }
}

void move_aliens_baixo (t_lista *aliens) {
    int j;
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

    /** variaveis de facilitacao de leitura */
    t_jogo alien;
    t_jogo elemento;

    inicializa_atual_inicio(aliens);

    for (i = 0; i < aliens->tamanho; ++i) {
        alien = aliens->atual->chave;
        inicializa_atual_inicio(armadura);

        for (j = 0; j < armadura->tamanho; ++j) {
            elemento = armadura->atual->chave; 

            for (k = 0; k < aliens->atual->chave.hitbox->tam; ++k) {
                if (elemento.posx == alien.hitbox[k].posx && elemento.posy == alien.hitbox[k].posy) {
                    remove_item_atual(&lixo, armadura);    
                }
            }
            incrementa_atual(armadura);
        }
        incrementa_atual(aliens);
    }
}

int verifica_borda_alien (t_lista *aliens) {
    int i;
    inicializa_atual_inicio(aliens);
    for (i = 0; i < 5; ++i) {
        if (aliens->atual->chave.posy - 1 == 0) {
            return 1;
        }
        incrementa_atual(aliens);
    }
    inicializa_atual_fim(aliens);
    for (i = aliens->tamanho; i >= aliens->tamanho-5; --i) {
        if (aliens->atual->chave.posy + 2 == COLUNAS - 1) {
            return 1;
        }
        incrementa_atual(aliens);
    }
    return 0;
}

void move_alien (t_lista *aliens) {
    
    if (verifica_borda_alien(aliens)) {
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
    t_jogo lixo;

    /** variaveis de facilitacao de leitura */
    t_jogo bomba;
    t_jogo elemento;

    inicializa_atual_inicio(bombas);

    for (i = 0; i < bombas->tamanho; ++i) {
        inicializa_atual_inicio(armadura);
        bomba = bombas->atual->chave;

        for (j = 0; j < armadura->tamanho; ++j) {
            elemento = armadura->atual->chave;

            if (bomba.posx == elemento.posx && bomba.posy == elemento.posy) {
                remove_item_atual(&lixo, bombas);
                armadura->atual->chave.vida = 9;

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
        if (bombas->atual->chave.posx + 1 > LINHAS - 1) {
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
    mvprintw(c->posx, c->posy,   "/I\\"); 
    mvprintw(c->posx+1, c->posy, "Q@Q ");
    mvprintw(c->posx+2, c->posy, "\\^/");
}

void move_canhao (t_jogo *c, int input) {
    if (input == KEY_LEFT && c->posy - 2 >= 0) {
        c->posy -= 1;
    } else if (input == KEY_RIGHT && c->posy + 2 < COLUNAS - 1) {
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
    int x, y, i;

    char *sprite;

    sprite=SPRITE_NAVE_MAE;
    
    i = 0;
    if (ramiel->vida == 9) {
        printa_explosao(ramiel);
    } else {
        while (i < ramiel->hitbox->tam) {
            x = ramiel->hitbox[i].posx;
            y = ramiel->hitbox[i].posy;
            
            if (x >= 0 && x <= 38 && y >= 0 && y <= 99) {
                move(x, y);
                addch(sprite[i]);
            }
            i += 1;
        }
    }
}

void printa_armadura (t_lista *armadura) {
    int i;
    inicializa_atual_inicio(armadura);
    for (i = 0; i < armadura->tamanho; ++i) {
        if (armadura->atual->chave.vida == 9) {
            mvprintw(armadura->atual->chave.posx, armadura->atual->chave.posy, "+");
        } else {
            mvprintw(armadura->atual->chave.posx, armadura->atual->chave.posy, "=");
        }
        incrementa_atual(armadura);
    }
}

void cria_borda () {
    int i, j;
    for (i = 0; i < LINHAS; ++i) {
        mvprintw(i, 0, "#");
        mvprintw(i, COLUNAS, "#");
    }
    for (j = 0; j < COLUNAS; ++j) {
        mvprintw(0, j, "#");
        mvprintw(LINHAS, j, "#");
    }
}

void printa_tela (t_lista *aliens, t_lista *armadura, t_lista *tiros, t_jogo *c, t_lista *bombas, t_jogo *ramiel) {
    erase();
    cria_borda();
    printa_alien(aliens);
    printa_tiro(tiros);
    printa_bombas(bombas);
    printa_canhao_sprite(c);
    printa_armadura(armadura);
    if (ramiel->vida) {
        printa_nave_mae(ramiel);
    }
}

void checa_vidas (t_lista *aliens, t_lista *armadura, t_jogo *ramiel) {
    int i;
    t_jogo lixo;
    inicializa_atual_inicio(aliens);
    for (i = 0; i < aliens->tamanho; ++i) {
        if (aliens->atual->chave.vida == 9) {
            remove_item_atual(&lixo, aliens);
        } 
        incrementa_atual(aliens);
    }

    inicializa_atual_inicio(armadura);
    for (i = 0; i < armadura->tamanho; ++i) {
        if (armadura->atual->chave.vida == 9) {
            remove_item_atual(&lixo, armadura);
        }
        incrementa_atual(armadura);
    }

    if (ramiel->vida == 9) {
        mata_nave_mae(ramiel);
    }
}

void atualiza_hitbox_nave_mae (t_jogo *ramiel) {
    int i, j, k;
    k = 0;
    for (j = 0; j < 5; ++j) {
        for (i = 0; i < 3; ++i) {
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

    ramiel->hitbox->tam = 15;
    atualiza_hitbox_nave_mae(ramiel);
}

void move_nave_mae (t_jogo *ramiel) {
    if (ramiel->posy < COLUNAS) {
        ramiel->posy += 1;
    } else if (ramiel->posy + 1 >= COLUNAS) {
        mata_nave_mae(ramiel);
    }

    atualiza_hitbox_nave_mae(ramiel);
}

void mata_nave_mae (t_jogo *ramiel) {
    ramiel->posx = -10;
    ramiel->posy = -10;
    ramiel->vida = 0;

    atualiza_hitbox_nave_mae(ramiel);
}

void verifica_colisao_nave_mae (t_lista *tiros, t_jogo *ramiel, int *bf, int *s) {
    int i, k;
    t_jogo lixo;

    /** variaveis de facilitacao de leitura */
    t_jogo tiro;
    int pos_mae_x;
    int pos_mae_y;

    inicializa_atual_inicio(tiros);
    for (i = 0; i < tiros->tamanho; ++i) {
        tiro = tiros->atual->chave;
        for (k = 0; k < ramiel->hitbox->tam; ++k) {
            pos_mae_x = ramiel->hitbox[k].posx;
            pos_mae_y = ramiel->hitbox[k].posy;

            if (pos_mae_x == tiro.posx && pos_mae_y == tiro.posy && ramiel->vida == 1) {

                remove_item_atual(&lixo, tiros);
                ramiel->vida = 9;
                *bf = 750;
                *s += 50;
                break;
            }
        }
        incrementa_atual(tiros);
    }
}

void verifica_colisao_alien (t_lista *tiros, t_lista *aliens, int *s) {
    int i, j, k;
    t_jogo lixo;

    /** variaveis de facilitacao de leitura */
    t_jogo alien;
    t_jogo tiro;

    inicializa_atual_inicio(tiros);

    for (i = 0; i < tiros->tamanho; ++i) {
        inicializa_atual_inicio(aliens);
        tiro = tiros->atual->chave;

        for (j = 0; j < aliens->tamanho; ++j) {
            alien = aliens->atual->chave;

            for (k = 0; k < alien.hitbox->tam; ++k) {
                if (tiro.posx == alien.hitbox[k].posx && tiro.posy == alien.hitbox[k].posy && alien.vida == 1) {

                    remove_item_atual(&lixo, tiros);
                    aliens->atual->chave.vida = 9;
                    *s += 10;
                    break;
                }
            }
            incrementa_atual(aliens);
        }
        incrementa_atual(tiros);
    }
}

void verifica_colisao_barreira (t_lista *tiros, t_lista *armadura) {
    int i, j;
    t_jogo lixo;

    /** variaveis de facilitacao de leitura */
    t_jogo tiro;
    t_jogo barreira;

    inicializa_atual_inicio(tiros);
    for (i = 0; i < tiros->tamanho; ++i) {
        tiro = tiros->atual->chave;
        inicializa_atual_inicio(armadura);

        for (j = 0; j < armadura->tamanho; ++j) {
            barreira = armadura->atual->chave;

            if (tiro.posx == barreira.posx && tiro.posy == barreira.posy && barreira.vida == 1) {

                remove_item_atual(&lixo, tiros);
                armadura->atual->chave.vida = 9;
                break;
            }
            incrementa_atual(armadura);
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
    int i, k;
    t_jogo lixo;

    /** variaveis de facilitacao de leitura */
    t_jogo bomba;
    inicializa_atual_inicio(aliens);
    inicializa_atual_inicio(bombas);

    for (i = 0; i < bombas->tamanho; ++i) {
        inicializa_atual_inicio(bombas);
        bomba = bombas->atual->chave;

        for (k = 0; k < c->hitbox->tam; ++k) {

            if (bomba.posx == c->hitbox[k].posx && bomba.posy == c->hitbox[k].posy) {

                remove_item_atual(&lixo, bombas);
                return 0;
            }
        }
        incrementa_atual(bombas);
    }
    for (i = 0; i < aliens->tamanho; ++i) {
        if (aliens->atual->chave.posx + 2 == c->posx) { 
            return 0;
        }
        incrementa_atual(aliens);
    }
    return 1;
}

void mensagem_inicial () {
    char input;
    clear();
    while (! input) {
        mvprintw(LINHAS /2 - 7, COLUNAS /2 - 7, "Bem-vindo ao Calouro Invaders!");
        mvprintw(LINHAS /2 - 6, COLUNAS /2 - 7, "Aqui, você assumirá o papel da matéria de Progamação");
        mvprintw(LINHAS /2 - 5, COLUNAS /2 - 7, "Atire suas notas e derrube todos os calouros e veteranos");
        mvprintw(LINHAS /2 - 4, COLUNAS /2 - 7, "Que tentam desesperadamente alcançar a barreira!");
        mvprintw(LINHAS /2 - 3, COLUNAS /2 - 7, "Cuidado! Eles também revidam com textões e postagens no spotted!");
        mvprintw(LINHAS /2 - 2, COLUNAS /2 - 7, "Além disso, uma greve sempre sobrevoa nosso campus.");
        mvprintw(LINHAS /2 - 1, COLUNAS /2 - 7, "Se acertá-la os alunos pararão por alguns instante e suas notas sairão mais rapido! :)");
        mvprintw(LINHAS /2 + 6, COLUNAS /2, "SETAS movem a nave. Espaço atira.");
        mvprintw(LINHAS -3, COLUNAS -3, "Pressione qualquer tecla para continuar");
        refresh();
        input = getchar();
    }
    clear();
    refresh();
}

void mensagem_final (int ganhou, int sc) {
    char input;
    clear();
    if (ganhou) {
        while (! input) {
            mvprintw(LINHAS /2, COLUNAS /2 - 20, "Parabéns! Você conseguiu fazer com que todos os veteranos e calouros desse período pegassem DP!\n");
            refresh();
            usleep(3000000); 
            input = getchar();
        }
    }
}

void placar(int s) {
    mvprintw(0, 45, "Score: %d", s);
}

void game_over (int sc, int per) {
    clear();
    mvprintw(5, COLUNAS /2 - 20, "GAME OVER");
    if (per == 4) {
        mvprintw(LINHAS /2 - 2, COLUNAS /2, "Você sobreviveu ao máximo de períodos possíveis, ninguém mais aguenta pegar DP!: %d!", per);
    } else {
        mvprintw(LINHAS /2, COLUNAS /2, "Você sobreviveu a: %d períodos!", per);
    }
    mvprintw(LINHAS /2 - 1, COLUNAS /2, "E sua pontuação máxima foi de: %d", sc);
    refresh();
    usleep(3999999);
}

