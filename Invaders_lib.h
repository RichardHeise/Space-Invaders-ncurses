#define LINHAS 38
#define COLUNAS 50
#define MAX_TIROS 3
#define MAX_ELEMENTOS 1000

typedef struct s_shield {
    int posx;
    int posy;
} t_shield;

typedef struct s_armor {
    t_shield barreira[MAX_ELEMENTOS];
    int tam;
} t_armadura;

typedef struct s_unidade {
    int posx;
    int posy;
} t_unidade;

typedef struct s_exercito {
    t_unidade aliens[1000];
    int tam;
} t_exercito;

typedef struct s_shot {
    int posx;
    int posy;
    int vida;
} t_shot;

typedef struct s_tela {
    int **matrix;
    int linhas;
    int colunas;
} t_tela;

void cria_tela (t_tela *t, int lin, int col);

void zera_tela (t_tela *t, int lin, int col);

void print_tela_final (t_tela *t_a, t_tela *t_c, t_tela *t_t, int lin, int col);
void cria_alien (t_unidade *alien, int r, int c);

void cria_aliens (t_exercito *a);

void cria_barreira (t_tela *t_a, t_armadura *bar);

void escreve_barreira_tela (t_tela *t_a, t_armadura *bar);

void escreve_aliens_tela (t_tela *t, t_exercito *a);

int checa_borda (t_tela *t, t_exercito *a);

void move_aliens_baixo (t_exercito *a);

void move_aliens_esquerda (t_tela *t, t_exercito *a);

void move_aliens_direita (t_tela *t, t_exercito *a);
void move_aliens (t_tela *t, t_exercito *a, int *vel);

void remove_vetor_alien (t_exercito *a, int i);
void remove_vetor_barreira (t_armadura *bar, int i);

void remove_vetor_tiro (t_shot shots[]);
void atira (t_tela *t_t, t_shot *shot, int i, int j);

void atualiza_tiro (t_tela *t_t, t_shot s[]);
int acha_alien (t_exercito *a, int i, int j);

int acha_elemento (t_armadura *bar, int i, int j);

void verifica_tiro (t_tela *t_t, t_tela *t_a, t_exercito *a, t_shot shots[], t_armadura *bar, int *max);
void escreve_canhao_tela (t_tela *t_c, t_unidade *can);

void move_nave (t_tela *t_c, t_unidade *can, int input);

void verifica_posicao (t_tela *t_a, t_exercito *a, t_armadura *bar);

void atualiza_tela_alien (t_tela *t_a, t_exercito *a, t_armadura *bar, int *vel);

void atualiza_tela_canhao (t_tela *t_c, t_unidade *can, int input);

int canhao_vivo (t_exercito *a);