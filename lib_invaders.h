#include "lib_lista.h"

#define ALIEN_VET 1
#define ALIEN_CAL 2
#define NAVE_MAE 3
#define BARREIRA 4
#define CANHAO 5
#define TIRO 6
#define BOMBA 7
#define MAX_TIROS 3
#define LINHAS 38
#define COLUNAS 100

/* Funcoes do aliens */

void atualiza_hitbox_unidade (t_jogo *uni);


/*
    Cria alien dando-o posicao inicial, vida, tipo e hitbox
    Recebe um alien e dois parametros que serao as posicoes iniciais
*/
void cria_alien (t_jogo *alien, int i, int j);

/*
    Plural da funcao cria_alien():
    Executa as acoes de cria_alien() para uma lista de aliens
*/
void cria_aliens (t_lista *aliens);

/*
    Escreve na tela o corpo de cada alien
*/
void printa_alien_sprite (t_jogo *alien);

/*
    Decide para que lado os aliens vao se mover
*/
void move_alien (t_lista *aliens);

/*
    Desloca todos os alien para direita
*/
void move_aliens_direita (t_lista *aliens);

/*
    Desloca todos os alien para a esquerda
*/
void move_aliens_esquerda (t_lista *aliens);

/*
    Desloca todos os aliens uma linha a baixo
*/
void move_aliens_baixo (t_lista *aliens);

/*
    Verifica se os aliens da primeira coluna 
    ou da ultima estao na borda da tela 
*/
int verifica_borda (t_lista *aliens);

/* Funcoes da barreira */

/*
    Cria um elemento da barreira dando-o posicao inicial, vida e tipo
    Recebe uma barreira e dois parametros que serao as posicoes iniciais
*/    
void cria_barreira (t_jogo *barreira, int i, int j);

/* 
    Plural da funcao cria_barreira():
    Executa as acoes de cria_barreira() para uma lista de barreira
*/
void cria_armadura (t_lista *armadura);

/*
    Escreve na tela o corpo de cada barreira 
*/
void printa_armadura_sprite (t_lista *barreira);

/*
    Verifica se um alien esta comendo a barreira
*/
void verifica_posicao_barreira (t_lista *aliens, t_lista *armadura);


/* Funcoes do tiro */

/*
    Cria um tiro uma posicao acima do canhao
    Insere o tiro criado na lista de tiros
*/
void atira (t_lista *tiros, t_jogo *c);

/*
    Faz o tiro andar pela tela 
*/
void atualiza_tiros (t_lista *tiros);

/*
    Verifica se o tiro acertou a nave mae
*/
void verifica_colisao_nave_mae (t_lista *tiros, t_jogo *ramiel);

/*
    Verifica se o tiro acertou um alien 
*/
void verifica_colisao_alien (t_lista *tiros, t_lista *aliens);

/*
    Verifica se o tiro acertou a barreira
*/
void verifica_colisao_barreira (t_lista *tiros, t_lista *barreira);

/*
    Verifica se o tiro chegou a borda
*/
void verifica_colisao_borda_tiros (t_lista *tiros);



void printa_bombas (t_lista *bombas);

void verifica_colisao_bombas (t_lista *bombas, t_lista *armadura, t_jogo *c);

void verifica_colisao_borda_bombas (t_lista *bombas);

void cria_canhao (t_jogo *c);

void printa_canhao_sprite (t_jogo *c);

void move_canhao (t_jogo *c, int input);

void printa_tiro(t_lista *tiros);

void printa_nave_mae (t_jogo *ramiel);

void printa_tela (t_lista *aliens, t_lista *armadura, t_lista *tiros, t_jogo *c, t_lista *bombas, t_jogo *ramiel);

void atualiza_hitbox_nave_mae (t_jogo *ramiel);

void cria_nave_mae (t_jogo *ramiel);

void move_nave_mae (t_jogo *ramiel);

void mata_nave_mae (t_jogo *ramiel);

void cria_bomba (t_jogo *bomba, t_jogo *alien);


void bombardeia (t_lista *aliens, t_lista *bombas);

void atualiza_bomba (t_lista *bombas);

int canhao_vivo (t_lista *aliens, t_lista *bombas, t_jogo *c);

void mensagem_inicial();;