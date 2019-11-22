/** TODOS OS DEFINES E SPRITES ESTAO AQUI */

/* APARENCIA DA NAVE MAE 1
    W^W^W
    (~=~)
    Uu_uU
*/
#define SPRITE_NAVE_MAE1 "W(U^=uW~_^=uW)U"

/* APARENCIA DA NAVE MAE 2
    ^W^W^
    (=~=)
    Uu_uU
*/
#define SPRITE_NAVE_MAE2 "^(UW=u^~_W=u^)U"

/*
    APARENCIA DO CANHAO
    /I\
    Q@Q
    \^/
*/
#define SPRITE_CANHAO "/I\\Q@Q\\^/"

/*
    APARENCIA DO ALIEN VETERANO
    @T@
    VET
    >O<
*/
#define SPRITE_ALIEN_VET1 "@T@VET>O<"

/*
    APARENCIA DO ALIEN VETERANO 2
    -T-
    VET
    <o>
*/
#define SPRITE_ALIEN_VET2 "-T-VET<o>"

/*
    APARENCIA DO ALIEN CALOURO1
    ^+^
    CAL
    [ ]
*/
#define SPRITE_ALIEN_CAL1 "^+^CAL[^]"

/*
    APARENCIA DO ALIEN CALOURO1
    0+0
    CAL
    ]^[
*/
#define SPRITE_ALIEN_CAL2 "0+0CAL]^["

/*
    APARENCIA DO ALIEN PERDIDO1
    0Y0
    BAT
    WVW
*/
#define SPRITE_ALIEN_PERDIDO1 "0Y0BATWVW"

/*
    APARENCIA DO ALIEN PERDIDO2
    XYX
    ATA
    /v\
*/
#define SPRITE_ALIEN_PERDIDO2 "XYXATA/v\\" 

/*
    Tamanho da tela
*/
#define LINHAS 38
#define COLUNAS 100

/* 
    Define as posicoes iniciais e finais dos aliens 
*/
#define INI_LIN_ALIEN 6
#define FIM_LIN_ALIEN 24
#define INI_COL_ALIEN 8
#define FIM_COL_ALIEN 86

/*
    Define as posicoes iniciais e finais da barreira
*/
#define INI_LIN_BAR 30
#define FIM_LIN_BAR 33
#define INI_COL_BAR 2
#define FIM_COL_BAR 8
/* 
    TIPOS
*/
#define ALIEN_VET 1
#define ALIEN_CAL 2
#define ALIEN_PERDIDO 3
#define NAVE_MAE 4
#define BARREIRA 5
#define CANHAO 6
#define TIRO 7
#define BOMBA 8

#define MAX_TIROS 3 /* Quantidade de tiros permitidos na tela */

/* 
    Estados
*/
#define VIVO 1
#define MORRENDO 9

/* 
   Esses valores sao responsaveis pela velocidade dos aliens
    aumente-os para DIMINUIR a velocidade de descida
*/
#define CONSTANTE_TEMPO 120 
#define CONTROLADOR 8000 

/*
    Esse valor eh responsavel pela taxa de nascimento da nave mae
    aumente para DIMINUIR a taxa
*/
#define CONSTANTE_SPAWN 1657 /* eh ideal que o valor seja primo devido a propriedades especificas */

/*
    Esse valor eh resposavel pela velocidade da nave mae
    aumente para DIMINUIR a velocidade
*/
#define CONSTANTE_MOV 51 /* eh ideal que o valor seja impar devido a propriedades especificas */

/*
    Esse valor eh responsavel pela velocidade das bombas
    aumente para DIMINUIR a velocidade
*/
#define CONSTANTE_QUEDA_MOV 67 

/*
    Esse valor eh responsavel pela taxa de bombas
    aumente para DIMINUIR a taxa
*/
#define CONSTANTE_QUEDA 315 /* eh ideal que o valor seja multiplo de 5 */

/* 
    Esse valor eh responsavel pela velocidade dos tiros
    aumente para DIMINUR a velocidade
*/
#define VEL_TIROS 12 /* eh ideal que o valor seja par e multiplo de 12 */
