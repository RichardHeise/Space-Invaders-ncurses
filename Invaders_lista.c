#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include "lib_invaders.h"

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
    int entr;

    inicializa_lista(&lista_bombas);
    inicializa_lista(&lista_aliens);
    inicializa_lista(&lista_barreira);
    inicializa_lista(&lista_tiros);

    cria_armadura(&lista_barreira);
    cria_aliens(&lista_aliens);
    cria_canhao(&canhao);

    entr = getch();

    constante = 120;
    controlador = 10000;

    while (entr != 'q' && canhao.vida && !lista_vazia(&lista_aliens)) {

        printa_tela(&lista_aliens, &lista_barreira, &lista_tiros, &canhao, &lista_bombas, &nave_mae);
        canhao.vida = canhao_vivo(&lista_aliens, &lista_bombas, &canhao);

        if (lista_aliens.ini->chave.vel >= 100) {
            lista_aliens.ini->chave.vel = 100;
        }

        if (controlador % 1875 == 0 && !nave_mae.vida) {
            cria_nave_mae(&nave_mae);
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

        verifica_colisao_nave_mae(&lista_tiros, &nave_mae);
        move_canhao(&canhao, entr);
        usleep(2500);
        controlador -= 1;
    }
    endwin();
    return 0;
}
