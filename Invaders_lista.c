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
    curs_set(FALSE);        /* Esconde o cursor */

    /* Verifica o tamanho do terminal */
    int linhas, colunas;
    getmaxyx(stdscr, linhas, colunas);

    if (linhas < LINHAS || colunas < COLUNAS) {
        endwin();
        printf("Seu terminal é muito pequeno. Abortando.\n");
        printf("Garanta que seu terminal tenha pelo menos 38 linhas por 100 colunas\n");
        printf("linhas atuais: %d\ncolunas atuais: %d\n", linhas, colunas);
        return 1;
    }

    /* Declaracao das listas */
    t_lista lista_aliens;
    t_lista lista_bombas;
    t_lista lista_barreira;
    t_lista lista_tiros;

    /* Declaracao dos objetos que nao sao listas */
    t_jogo nave_mae;
    t_jogo canhao;
    
    /* Declaracao e inicializacao das variaveis auxiliares */
    int controlador;
    int constante_tempo;
    int entr;
    int buff;
    int score;
    int periodos;
    constante_tempo = CONSTANTE_TEMPO;
    buff = 0;
    score = 0;
    nave_mae.vida = 0;
    periodos = 0;

    mensagem_inicial();

    /* Inicializacao das listas */
    inicializa_lista(&lista_aliens);
    inicializa_lista(&lista_barreira);
    inicializa_lista(&lista_tiros);
    inicializa_lista(&lista_bombas);

    /* Criacao dos elementos estaticos */
    cria_armadura(&lista_barreira);

    /* Inicialização da variavel controlador */
    controlador = CONTROLADOR;


    while (canhao.vida && periodos < 4) {

        esvazia_lista(&lista_bombas);
        esvazia_lista(&lista_tiros);
        cria_aliens(&lista_aliens);
        cria_canhao(&canhao);
        periodos++;

        while (canhao.vida && !lista_vazia(&lista_aliens)) {
        
            printa_tela(&lista_aliens, &lista_barreira, &lista_tiros, &canhao, &lista_bombas, &nave_mae);
    
            /* Escreve GREVE quando o buff esta ativo */
            if (buff) {
                mvprintw(1, COLUNAS / 2, "GREVE");
            }
    
            /* Escreve o placar na tela */
            placar(score);
    
            /*
             * Fixa a velocidade dos aliens 
             * Evita bugs 
             */
            if (lista_aliens.ini->chave.vel >= constante_tempo - lista_aliens.ini->chave.vel) {
                lista_aliens.ini->chave.vel =  constante_tempo - lista_aliens.ini->chave.vel;
            }
    
            /* Controla a velocidade de descida dos aliens */
            if ((controlador % (constante_tempo - lista_aliens.ini->chave.vel) == 0) && !buff) {
                checa_vidas(&lista_aliens, &lista_barreira, &nave_mae);
                verifica_posicao_barreira(&lista_aliens, &lista_barreira);
                move_alien(&lista_aliens);
            }
    
            /* Controla a taxa de nascimento da nave mae */
            if ((controlador % CONSTANTE_SPAWN == 0) && !nave_mae.vida) {
                cria_nave_mae(&nave_mae);
            }
            
            /* Controla a velocidade da nave mae */
            if ((controlador % CONSTANTE_MOV == 0) && (nave_mae.vida == 1)) {
                move_nave_mae(&nave_mae);
            }
            
            /* Controla a taxa de bombas */
            if (controlador % CONSTANTE_QUEDA == 0) {
                bombardeia(&lista_aliens, &lista_bombas);
            }
    
            /* Controla a velocidade das bombas */
            if (controlador % CONSTANTE_QUEDA_MOV == 0 && !lista_vazia(&lista_bombas)) {
                verifica_colisao_borda_bombas(&lista_bombas);
                verifica_colisao_bombas(&lista_bombas, &lista_barreira, &canhao);
                atualiza_bomba(&lista_bombas);
            }
    
            /* Atira */
            entr = getch();
            if (entr == ' ' && lista_tiros.tamanho < MAX_TIROS) {
                atira(&lista_tiros, &canhao);
            } else if (entr == 'q') {
                endwin();
                exit(1);
            }
    
            /* controla a velocidade e verifica os tiros */
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
    
            /* Não altera o controlador se o buff esta ativo */
            if (! buff) { 
                controlador -= 1;
            } else {
                buff -= 1;
            }
        }
        constante_tempo -= 10;
        mensagem_final(canhao.vida, score);
    }
    
    game_over(score, periodos);

    endwin();
    return 0;
}
