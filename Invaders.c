#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <unistd.h> 
#include "Invaders_lib.h"

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
    t_tela tela_bombas;
    t_tela tela_geofront;
    t_ramiel nave_mae;
    t_exercito unidades;
    t_unidade canhao;
    t_shot tiros[MAX_TIROS];
    t_arsenal bombas;
    t_armadura barreira;

    canhao.posx = LINHAS - 2;
    canhao.posy = COLUNAS / 2;

    int contador, controle, velocidade, score;
    char entr;
    int i, j, buff;

    velocidade = 0;
    controle = 125;
    contador = 8000;

    for (i=0; i < MAX_TIROS; i++) {
        tiros[i].vida = 0;
        tiros[i].posx = LINHAS;
        tiros[i].posy = COLUNAS;
    }

    buff = 0;
    cria_tela(&tela_aliens, LINHAS, COLUNAS);
    cria_tela(&tela_canhao, LINHAS, COLUNAS);
    cria_tela(&tela_tiro, LINHAS, COLUNAS);
    cria_tela(&tela_bombas, LINHAS, COLUNAS);
    cria_tela(&tela_geofront, LINHAS, COLUNAS);
    cria_barreira(&tela_aliens, &barreira);
    cria_aliens(&unidades);
    atualiza_tela_alien(&tela_aliens, &unidades, &barreira, &velocidade, &buff);

    bombas.tam = 0;
    i = 0;
    j = 0;

    mensagem_inicial();
    
    while (entr != 'q' && canhao_vivo(&unidades, &bombas, &canhao) && unidades.tam != 0) {
        print_tela_final(&tela_aliens, &tela_canhao, &tela_tiro, &tela_bombas, &tela_geofront, LINHAS, COLUNAS);
        if (contador % (controle - velocidade) == 0) {
            atualiza_tela_alien(&tela_aliens, &unidades, &barreira, &velocidade, &buff);
        }
        if (rand() % 1637 == 0 && !nave_mae.vida) {
            spawna_nave_mae(&tela_aliens, &nave_mae);
        }
        if (contador % 100 == 0 && nave_mae.vida) {
            atualiza_nave_mae(&tela_geofront, &nave_mae);
        }
        if (contador % 285 == 0) {
            cria_bombas(&tela_bombas, &bombas, &unidades);
        }
        if (contador % 35 == 0) {
            verifica_bomba(&tela_bombas, &tela_aliens, &unidades, &bombas, &barreira, &j);
        }
        entr = getch();
        if (entr == ' ' && i < MAX_TIROS) {
            atira(&tela_tiro, &tiros[i], canhao.posx, canhao.posy);
            i++;
        }
        if (contador % 12 == 0) {
            verifica_colisoes(&tela_tiro, &tela_aliens, &tela_geofront, &unidades, tiros, &barreira, &nave_mae, &buff, &i, &score);
            atualiza_tiro(&tela_tiro, tiros);
        }
        atualiza_tela_canhao(&tela_canhao, &canhao, entr);
        escreve_barreira_tela(&tela_aliens, &barreira);
        usleep(2500);
        if (! buff) {
            contador -= 1;
        } else {
            buff -= 1;
            zera_tela(&tela_geofront, LINHAS, COLUNAS);
        }
    }

    mensagem_final(unidades.tam, score);

    endwin();
    return 0;
}
