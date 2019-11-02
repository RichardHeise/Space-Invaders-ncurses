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
    t_exercito unidades;
    t_unidade canhao;
    t_shot tiros[MAX_TIROS];
    t_arsenal bombas;
    t_armadura barreira;

    canhao.posx = LINHAS - 2;
    canhao.posy = COLUNAS / 2;

    int contador, controle, velocidade;
    char entr;
    int i, j;

    velocidade = 0;
    controle = 200;
    contador = 8000;

    for (i=0; i < MAX_TIROS; i++) {
        tiros[i].vida = 0;
        tiros[i].posx = LINHAS;
        tiros[i].posy = COLUNAS;
    }

    cria_tela(&tela_aliens, LINHAS, COLUNAS);
    cria_tela(&tela_canhao, LINHAS, COLUNAS);
    cria_tela(&tela_tiro, LINHAS, COLUNAS);
    cria_tela(&tela_bombas, LINHAS, COLUNAS);
    cria_barreira(&tela_aliens, &barreira);
    cria_aliens(&unidades);
    atualiza_tela_alien(&tela_aliens, &unidades, &barreira, &velocidade);

    bombas.tam = 0;
    i = 0;
    j = 0;
    while (entr != 'q' && canhao_vivo(&unidades, &bombas, &canhao) && unidades.tam != 0) {
        print_tela_final(&tela_aliens, &tela_canhao, &tela_tiro, &tela_bombas, LINHAS, COLUNAS);
        if (contador % (controle - velocidade) == 0) {
            atualiza_tela_alien(&tela_aliens, &unidades, &barreira, &velocidade);
        }
        if (contador % 302 == 0) {
            cria_bombas(&tela_bombas, &bombas, &unidades);
        }
        if (contador % 30 == 0) {
            verifica_bomba(&tela_bombas, &tela_aliens, &unidades, &bombas, &barreira, &j);
        }
        entr = getch();
        if (entr == ' ' && i < MAX_TIROS) {
            atira(&tela_tiro, &tiros[i], canhao.posx, canhao.posy);
            i++;
        }
        if (contador % 12 == 0) {
            verifica_tiro(&tela_tiro, &tela_aliens, &unidades, tiros, &barreira, &i);
            atualiza_tiro(&tela_tiro, tiros);
        }
        atualiza_tela_canhao(&tela_canhao, &canhao, entr);
        escreve_barreira_tela(&tela_aliens, &barreira);
        usleep(2500);
        contador -= 1;
    }
    endwin();
    return 0;
}
