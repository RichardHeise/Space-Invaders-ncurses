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
    int entr;
    int buff;
    int score;
    buff = 0;
    score = 0;
    nave_mae.vida = 0;

    inicializa_lista(&lista_bombas);
    inicializa_lista(&lista_aliens);
    inicializa_lista(&lista_barreira);
    inicializa_lista(&lista_tiros);

    cria_armadura(&lista_barreira);
    cria_aliens(&lista_aliens);
    cria_canhao(&canhao);

    controlador = CONTROLADOR;

    /* mensagem_inicial(); */

    while (entr != 'q' && canhao.vida && !lista_vazia(&lista_aliens)) {

        printa_tela(&lista_aliens, &lista_barreira, &lista_tiros, &canhao, &lista_bombas, &nave_mae);

        placar(score);

        if (lista_aliens.ini->chave.vel >= 100) {
            lista_aliens.ini->chave.vel = 100;
        }

        if ((controlador % (CONSTANTE_TEMPO - lista_aliens.ini->chave.vel) == 0) && !buff) {
            checa_vidas(&lista_aliens, &lista_barreira, &nave_mae);
            verifica_posicao_barreira(&lista_aliens, &lista_barreira);
            move_alien(&lista_aliens);
        }

        if ((controlador % CONSTANTE_SPAWN == 0) && !nave_mae.vida) {
            cria_nave_mae(&nave_mae);
        }
        
        if ((controlador % CONSTANTE_MOV == 0) && (nave_mae.vida == 1)) {
            move_nave_mae(&nave_mae);
        }
        
        if (controlador % CONSTANTE_QUEDA == 0) {
            bombardeia(&lista_aliens, &lista_bombas);
        }

        if (controlador % CONSTANTE_QUEDA_MOV == 0 && !lista_vazia(&lista_bombas)) {
            verifica_colisao_borda_bombas(&lista_bombas);
            verifica_colisao_bombas(&lista_bombas, &lista_barreira, &canhao);
            atualiza_bomba(&lista_bombas);
        }

        entr = getch();
        if (entr == ' ' && lista_tiros.tamanho < MAX_TIROS) {
            atira(&lista_tiros, &canhao);
        }

        if (controlador % VEL_TIROS == 0 && !lista_vazia(&lista_tiros)) {
            if (nave_mae.vida) {    
                verifica_colisao_nave_mae(&lista_tiros, &nave_mae, &buff, &score);
            }
            verifica_colisao_alien(&lista_tiros, &lista_aliens, &score);
            verifica_colisao_barreira(&lista_tiros, &lista_barreira);
            verifica_colisao_borda_tiros(&lista_tiros);
            atualiza_tiros(&lista_tiros);
        }

        move_canhao(&canhao, entr);
        canhao.vida = canhao_vivo(&lista_aliens, &lista_bombas, &canhao);
        usleep(2500);

        if (! buff) { 
            controlador -= 1;
        } else {
            buff -= 1;
        }
    }
    endwin();
    return 0;
}
