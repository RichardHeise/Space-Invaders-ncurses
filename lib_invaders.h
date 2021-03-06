#include "lib_lista.h"
#include "complementar.h"

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
void printa_alien (t_lista *aliens, int spr);

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
int verifica_borda_alien (t_lista *aliens);

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
void printa_armadura (t_lista *armadura);

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
void verifica_colisao_nave_mae (t_lista *tiros, t_jogo *ramiel, int *bf, int *s);

/*
    Verifica se o tiro acertou um alien 
*/
void verifica_colisao_alien (t_lista *tiros, t_lista *aliens,int *s);

/*
    Verifica se o tiro acertou a barreira
*/
void verifica_colisao_barreira (t_lista *tiros, t_lista *armadura);

/*
    Verifica se o tiro chegou a borda
*/
void verifica_colisao_borda_tiros (t_lista *tiros);
/*
    Escreve o tiro na tela
*/
void printa_tiro(t_lista *tiros);


/* Funcoes das bombas */

/*
    Cria uma bomba uma posicao abaixo do alien que a soltou
*/
void cria_bomba (t_jogo *bomba, t_jogo *alien);

/*
    Plural da funcao de cria_bomba()
    Faz com que os aliens sorteados soltem bombas
*/
void bombardeia (t_lista *aliens, t_lista *bombas);

/*
    Verifica se a bomba acertou a barreira
*/
void verifica_colisao_bombas (t_lista *bombas, t_lista *armadura, t_jogo *c);

/* 
    Verifica se uma bomba acertou a borda
*/
void verifica_colisao_borda_bombas (t_lista *bombas);

/*
    Escreve a bomba na tela
*/
void printa_bombas (t_lista *bombas);

/*
    Move a bomba pela tela
*/
void atualiza_bomba (t_lista *bombas);


/* Funcoes do canhao */

/*
    Cria um canhao a partir de uma posicao inicial pre-definida
*/
void cria_canhao (t_jogo *c);

/*
    Faz o canhao andar de acordo com a entrada(input)
*/
void move_canhao (t_jogo *c, int input);

/* 
    Verifica se o canhao esta vivo
*/
int canhao_vivo (t_lista *aliens, t_lista *bombas, t_jogo *c);


/* Funcoes da nave mae */

/*
    Cria uma nave mae em uma posicao pre-definida
*/
void cria_nave_mae (t_jogo *ramiel);

/*
    Desloca a nave mae pela tela
*/
void move_nave_mae (t_jogo *ramiel);

/*
    Verifica se a nave mae esta na borda
    Deleta aos poucos a hitbox

void verifica_borda_nave_mae (t_jogo *ramiel);

/*
    Cria a hitbox da nave mae 
    Usa a posicao inicial pre-definida em cria_nave_mae()
*/
void atualiza_hitbox_nave_mae (t_jogo *ramiel);

/*
    Deleta a nave mae da tela e faz a vida dela ser 0
*/
void mata_nave_mae (t_jogo *ramiel);

/*
    Escreve o corpo da nave mae na tela 
*/
void printa_nave_mae (t_jogo *ramiel, int spr);


/* Funcoes complementares */

/*
    Limpa e escreve os elementos na tela
*/
void printa_tela (t_lista *aliens, t_lista *armadura, t_lista *tiros, t_jogo *c, t_lista *bombas, t_jogo *ramiel, int spr);

/*
    Escreve a mensagem inicial
*/
void mensagem_inicial();

/*
    Escreve o placar na tela
*/
void placar(int s);

/*
    Verifica se o estado dos itens eh vivo ou morrendo 
*/
void checa_vidas (t_lista *aliens, t_lista *armadura, t_jogo *ramiel);

/*
    Desenha as explosoes na tela
*/
void printa_explosao(t_jogo *unidade);

/*
    Cria a borda do jogo 
*/
void cria_borda();

/*
    Escreve a mensagem de final de fase do jogo 
*/
void mensagem_final(int ganhou, int sc);

/*
    Escreve a mensagem de fim de jogo
*/
void game_over (int sc, int per);

/*
    Escreve uma entidade na tela
*/
void printa_unidade (t_jogo *unidade, int spr);

/*
    Reseta o jogo
*/
void reseta_jogo (t_lista *tiros, t_lista *bombas, t_lista *aliens, t_jogo *c, t_jogo *ramiel);

/*
    Escreve GREVE na tela se o buff esta ativo
*/
void greve (int bf);