#ifndef _PPM_LIB_
#define _PPM_LIB_

#ifndef M_PI
    #define M_PI (3.14159265358979323846)
#endif

#ifndef PHI
    #define PHI (1.618033988749894)
#endif

#ifndef NULL
    #define NULL 0
#endif

#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3

#define graus2rad(graus) (graus * M_PI / 180.0)
#define rad2graus(radianos) (radianos * 180.0 / M_PI)

#define branco rgb_cria(255, 255, 255)
#define preto rgb_cria(0, 0, 0)
#define vermelho rgb_cria(255, 0, 0)
#define verde rgb_cria(0, 255, 0)
// https://www.htmlcsscolor.com/hex/00CC00
#define verde_livre_discurso rgb_cria(0, 205, 0)
#define azul rgb_cria(0, 0, 255)
#define cinza rgb_cria(127, 127, 127)
#define amarelo rgb_cria(255, 255, 0)
#define roxo rgb_cria(255, 0, 255)
#define azul_escuro rgb_cria(0, 0, 156)
#define marrom rgb_cria(92, 51, 23)
#define ciano rgb_cria(0, 255, 255)
#define laranja rgb_cria(255, 165, 0)
#define vermelho_escuro rgb_cria(140, 23, 23)

#ifndef ARQUIVO
#define ARQUIVO
struct Arquivo {
    char **linha;
    int linhas;
};
typedef struct Arquivo Arquivo;
#endif

enum BOOL {
    false = 0,
    true = 1
};
typedef enum BOOL bool;

typedef unsigned char uchar;

typedef unsigned long long int lint;

struct Ponto {
    int x, y;
};
typedef struct Ponto Ponto;

struct RGB {
    uchar red, green, blue;
};
typedef struct RGB rgb;

struct ArvBin {
    int x;
    struct ArvBin *esquerda;
    struct ArvBin *direita;
};
typedef struct ArvBin ArvBin;

struct LISTA_Ponto {
    Ponto p;
    struct LISTA_Ponto *proximo;
};
typedef struct LISTA_Ponto ListaPonto;

struct LISTA_PONTO_DUPLA {
    Ponto ponto;
    struct LISTA_PONTO_DUPLA *proximo;
    struct LISTA_PONTO_DUPLA *anterior;
};
typedef struct LISTA_PONTO_DUPLA ListaDuplaPonto;

struct LINHA {
    ListaPonto *primeiro;
    ListaPonto *ultimo;
};
typedef struct LINHA *Linha;

struct NODECOR {
    rgb cor;
    struct NODECOR *proximo;
    struct NODECOR *anterior;
};
typedef struct NODECOR NodeCor;

struct LISTA_COR {
    NodeCor *fim;
    NodeCor *inicio;
    int tamanho;
};
typedef struct LISTA_COR lista_cor;

typedef struct LISTA_COR * ListaCor;

enum BMPKey {
    Key_BM = 1,
    Key_BW = 2,
    Key_PPM = 3,
    Key_BMP = 6
};
typedef enum BMPKey BMPKey;

struct DIM2D {
    int largura;
    int altura;
};
typedef struct DIM2D Dimensao2D;

struct PPMHEADER {
    Dimensao2D *tamanho;
    int channelRange;
    BMPKey tipoBMP;
};
typedef struct PPMHEADER *PPMHeader;

struct PPM {
    PPMHeader cabecalho;
    rgb **pixel;
};
typedef struct PPM *PPM;

struct poligono {
    ListaDuplaPonto *primeiro;
    Ponto *centro;
};
typedef struct poligono Poligono;

// Manipulação básica
int int_potencia(int base, int expoente);
void string_copia(char *destino, char *origem);
int string_compara(char *s1, char *s2);
int aproximacao(float val);
int int_valor_absoluto(int n);
void int_troca(int *a, int *b);
float graus_seno(float graus);
float graus_coseno(float graus);
rgb rgb_cria(uchar red, uchar green, uchar blue);
rgb int_to_rgb(int numero);
int rgb_to_int(rgb cor);
Dimensao2D dimensao2D_cria(int largura, int altura);
const char *key_to_string(BMPKey key);
BMPKey string_to_key(char *key);
PPMHeader PPMHeader_cria(int altura, int largura, int max, char key[]);
PPMHeader PPMHeader_copia(PPMHeader cab);
PPMHeader PPMHeader_libera(PPMHeader cabecalho);
PPM ppm_cria();
PPM ppm_copia(PPM img);
void ppm_libera(PPM img);
rgb **rgb2d_malloc(Dimensao2D *tamanho);
void rgb2d_libera(PPM img);
int **int2d_malloc(Dimensao2D tamanho);
void int2d_libera(int **mat, int altura);
ArvBin *ArvBin_cria();
ArvBin *folha_cria(int x);
ArvBin *ArvBin_insere_sem_repeticao(ArvBin *r, int x);
ArvBin *ArvBin_libera(ArvBin *r);
void ArvBin_imprime_pre_ordem(ArvBin *r);
int ArvBin_quantidade_nodes(ArvBin *r);
PPM ppm_leitura(char fname[]);
void ppm_grava(char fname[], PPM img);
Ponto ponto_cria(int x, int y);
double ponto2d_distancia(Ponto a, Ponto b);
Ponto ponto_vira(Ponto a, Ponto b, float graus);
Ponto midpoint(Ponto a, Ponto b);
Ponto linear_interpolation(Ponto a, Ponto b, double ratio);
bool ponto_compare(Ponto p, Ponto q);
bool cor_compara(rgb a, rgb b);
int cores_diferentes(PPM img);
rgb cor_aleatoria();

// Listas
void ListaDuplaPonto_libera(ListaDuplaPonto *l);
// Lista de Cor
ListaCor ListaCor_cria();
void ListaCor_insere_inicio(ListaCor lista, rgb cor);
void ListaCor_insere_fim(ListaCor lista, rgb cor);
void ListaCor_insere_sem_repeticao(ListaCor l, rgb cor);
void ListaCor_remove_inicio(ListaCor lista);
void ListaCor_remove_fim(ListaCor lista);
int ListaCor_busca_indice(ListaCor lista, rgb cor);
void ListaCor_libera(ListaCor lista);
// linhas
Linha Linha_aloca(); /*aloca lista de pontos vazia*/
bool Linha_vazia(Linha l); /*verifica se a lista está vazia*/
void Linha_adiciona(Linha l, Ponto p);             /*insere Ponto na lista*/
void Linha_cria(Linha l, Ponto p0, Ponto pf); /*insere pontos pertencentes a linha de ponto inicial até ponto final*/
void Linha_remove(Linha l, Ponto p);             /*remove um Ponto da lista*/
void Libera_linha(Linha l);                   /*remove todos os pontos*/
// Poligonos
Poligono *poligono_cria();
bool poligono_vazio(Poligono *pol);
void poligono_insere(Poligono *pol, Ponto p);
Ponto poligono_pop(Poligono *pol);
ListaDuplaPonto *poligono_busca(Poligono *pol, Ponto p);
void poligono_remove_ponto(Poligono *pol, Ponto p);
void poligono_libera(Poligono *pol);

// manipulacao com efeitos
PPM ppm_decompoe(PPM cab, bool r, bool g, bool b);
PPM ppm_gira(PPM img, int graus);
PPM ppm_negativo(PPM img);
PPM BW(PPM img);
PPM BM(PPM img);
PPM blur(PPM img, int **ker, int tamanhokernel);
int **gaussian(int tamanhokernel);
PPM blurgauss(PPM img, int tamanhokernel);
int **mint(int tamanhokernel);
PPM blurmint(PPM img, int tamanhokernel);
PPM amplia(PPM imagem, int zoom);
// PPM espelhar(PPM img);
PPM join(PPM img, PPM img2);
PPM merge(PPM img, PPM img2);
PPM overlay(PPM img, PPM img2);
void grava_decomp(char fname[], PPM img, bool r, bool g, bool b);
void grava_gira(char fname[], PPM img, int graus);
void grava_negativo(char fname[], PPM img);
void grava_BW(char fname[], PPM img);
void grava_BM(char fname[], PPM img);
void grava_blur(char fname[], PPM img, int **ker, int tamanhokernel);
void grava_blurgauss(char fname[], PPM img, int tamanhokernel);
void grava_blurmint(char fname[], PPM img, int tamanhokernel);
void grava_espelhado(char fname[], PPM img);
void mod_decomp(PPM *img, bool r, bool g, bool b);
void mod_gira(PPM *img, int graus);
void mod_negativo(PPM *img);
void mod_BW(PPM *img);
void mod_BM(PPM *img);
void mod_blurgauss(PPM *img, int tamanhokernel);
void mod_blurmint(PPM *img, int tamanhokernel);
void mod_espelha(PPM *img);

// criacao
PPM cria_ppm(int altura, int largura, rgb cor);
// sem cor
#define desenha_ponto(imagem, p) desenha_ponto_cor(imagem, p, preto)
#define desenha_linha(imagem, p0, pf) desenha_linha_cor(imagem, p0, pf, preto)
#define desenha_curva(imagem, p0, pm, pf) desenha_lista_linha_cor(imagem, p0, pm, pf, preto)
#define insere_linha(imagem, l) insere_linha_cor(imagem, l, preto) /*desenha linha e remove os pontos da lista*/
#define desTriangulo(imagem, centro, altura, base) desenha_triangulo_cor(imagem, centro, altura, base, preto)
#define desRetangulo(imagem, centro, alturaR, larguraR) desenha_retangulo_cor(imagem, centro, alturaR, larguraR, preto)
#define desLosango(imagem, centro, altura, largura) desenha_losango_cor(imagem, centro, altura, largura, preto)
#define desTrapezio(imagem, centro, b1, b2, altura) desenha_trapezio_cor(imagem, centro, b1, b2, altura, preto)
#define desEstrela(imagem, p, x, y) desenha_estrela_cor(imagem, p, x, y, preto)
#define desCirculo(imagem, centro, raio) desenha_circulo_cor(imagem, centro, raio, preto)
#define desElipse(imagem, centro, altura, largura) desenha_elipse_cor(imagem, centro, altura, largura, preto)

// cor
void desenha_ponto_cor(PPM imagem, Ponto p0, rgb cor);
void desenha_linha_cor(PPM imagem, Ponto p0, Ponto pf, rgb cor);
void desenha_curva_cor(PPM imagem, Ponto p0, Ponto pm, Ponto pf, rgb cor);
void desenha_lista_linha_cor(PPM img, Linha l, rgb cor);
void desenha_triangulo_cor(PPM imagem, Ponto centro, int altura, int base, rgb cor);
void desenha_retangulo_cor(PPM imagem, Ponto centro, int alturaR, int larguraR, rgb cor);
void desenha_losango_cor(PPM imagem, Ponto centro, int altura, int largura, rgb cor);
void desenha_trapezio_cor(PPM imagem, Ponto centro, int b1, int b2, int altura, rgb cor);
void desenha_estrela_cor(PPM imagem, Ponto p, int x, int y, rgb cor);
void desenha_circulo_cor(PPM imagem, Ponto centro, int raio, rgb cor);
void desenha_elipse_cor(PPM imagem, Ponto centro, int altura, int largura, rgb cor);

// preenchidos
#define desenha_curva_preenchido(imagem, p0, pm, pf) desCurvaCorprn(imagem, p0, pm, pf, preto)
#define desenha_triangulo_preenchido(imagem, centro, altura, base) desTrianguloCorprn(imagem, centro, altura, base, preto)
#define desenha_retangulo_preenchido(imagem, centro, altura, largura) desRetanguloCorprn(imagem, centro, altura, largura, preto)
#define desenha_losango_preenchido(imagem, centro, altura, largura) desLosangoCorprn(imagem, centro, altura, largura, preto)
#define desenha_circulo_preenchido(imagem, centro, raio) desCirculoCorprn(imagem, centro, raio, preto)

// preenchidos com cor
void desenha_curva_cor_preenchido(PPM imagem, Ponto p0, Ponto pm, Ponto pf, rgb cor);
void desenha_triangulo_cor_preenchido(PPM imagem, Ponto centro, int altura, int base, rgb cor);
void desenha_retangulo_cor_preenchido(PPM imagem, Ponto centro, int altura, int largura, rgb cor);
void desenha_losango_cor_preenchido(PPM imagem, Ponto centro, int altura, int largura, rgb cor);
void desenha_circulo_cor_preenchido(PPM imagem, Ponto centro, int raio, rgb cor);

// Minha Fonte
#define fonte_escreve_string(img, s, o, font_size) escreve_strCor(img, s, o, font_size, preto)
#define fonte_escreve_char(img, c, o, size) escreve_charCor(img, c, o, size, preto)
void fonte_escreve_string_cor(PPM img, char s[], Ponto o, int font_size, rgb cor);
void fonte_escreve_char_cor(PPM img, char c, Ponto o, int size, rgb cor);

// Minúsculas
// preto
#define fonte_escreve_a(img, o, size) fonte_escreve_a_cor(img, o, size, preto)
#define fonte_escreve_b(img, o, size) fonte_escreve_b_cor(img, o, size, preto)
#define fonte_escreve_c(img, o, size) fonte_escreve_c_cor(img, o, size, preto)
#define fonte_escreve_d(img, o, size) fonte_escreve_d_cor(img, o, size, preto)
#define fonte_escreve_e(img, o, size) fonte_escreve_e_cor(img, o, size, preto)
#define fonte_escreve_f(img, o, size) fonte_escreve_f_cor(img, o, size, preto)
#define fonte_escreve_g(img, o, size) fonte_escreve_g_cor(img, o, size, preto)
#define fonte_escreve_h(img, o, size) fonte_escreve_h_cor(img, o, size, preto)
#define fonte_escreve_i(img, o, size) fonte_escreve_i_cor(img, o, size, preto)
#define fonte_escreve_j(img, o, size) fonte_escreve_j_cor(img, o, size, preto)
#define fonte_escreve_k(img, o, size) fonte_escreve_k_cor(img, o, size, preto)
#define fonte_escreve_l(img, o, size) fonte_escreve_l_cor(img, o, size, preto)
#define fonte_escreve_m(img, o, size) fonte_escreve_m_cor(img, o, size, preto)
#define fonte_escreve_n(img, o, size) fonte_escreve_n_cor(img, o, size, preto)
#define fonte_escreve_o(img, o, size) fonte_escreve_o_cor(img, o, size, preto)
#define fonte_escreve_p(img, o, size) fonte_escreve_p_cor(img, o, size, preto)
#define fonte_escreve_q(img, o, size) fonte_escreve_q_cor(img, o, size, preto)
#define fonte_escreve_r(img, o, size) fonte_escreve_r_cor(img, o, size, preto)
#define fonte_escreve_s(img, o, size) fonte_escreve_s_cor(img, o, size, preto)
#define fonte_escreve_t(img, o, size) fonte_escreve_t_cor(img, o, size, preto)
#define fonte_escreve_u(img, o, size) fonte_escreve_u_cor(img, o, size, preto)
#define fonte_escreve_v(img, o, size) fonte_escreve_v_cor(img, o, size, preto)
#define fonte_escreve_x(img, o, size) fonte_escreve_x_cor(img, o, size, preto)
#define fonte_escreve_z(img, o, size) fonte_escreve_z_cor(img, o, size, preto)

// cor
void fonte_escreve_a_cor(PPM img, Ponto o, int size, rgb cor);
void fonte_escreve_b_cor(PPM img, Ponto o, int size, rgb cor);
void fonte_escreve_c_cor(PPM img, Ponto o, int size, rgb cor);
void fonte_escreve_d_cor(PPM img, Ponto o, int size, rgb cor);
void fonte_escreve_e_cor(PPM img, Ponto o, int size, rgb cor);
void fonte_escreve_f_cor(PPM img, Ponto o, int size, rgb cor);
void fonte_escreve_g_cor(PPM img, Ponto o, int size, rgb cor);
void fonte_escreve_h_cor(PPM img, Ponto o, int size, rgb cor);
void fonte_escreve_i_cor(PPM img, Ponto o, int size, rgb cor);
void fonte_escreve_j_cor(PPM img, Ponto o, int size, rgb cor);
void fonte_escreve_k_cor(PPM img, Ponto o, int size, rgb cor);
void fonte_escreve_l_cor(PPM img, Ponto o, int size, rgb cor);
void fonte_escreve_m_cor(PPM img, Ponto o, int size, rgb cor);
void fonte_escreve_n_cor(PPM img, Ponto o, int size, rgb cor);
void fonte_escreve_o_cor(PPM img, Ponto o, int size, rgb cor);
void fonte_escreve_p_cor(PPM img, Ponto o, int size, rgb cor);
void fonte_escreve_q_cor(PPM img, Ponto o, int size, rgb cor);
void fonte_escreve_r_cor(PPM img, Ponto o, int size, rgb cor);
void fonte_escreve_s_cor(PPM img, Ponto o, int size, rgb cor);
void fonte_escreve_t_cor(PPM img, Ponto o, int size, rgb cor);
void fonte_escreve_u_cor(PPM img, Ponto o, int size, rgb cor);
void fonte_escreve_v_cor(PPM img, Ponto o, int size, rgb cor);
void fonte_escreve_x_cor(PPM img, Ponto o, int size, rgb cor);
void fonte_escreve_z_cor(PPM img, Ponto o, int size, rgb cor);

// Maiúsculas

// preto
#define escreve_S(img, o, size) escreve_S_cor(img, o, size, preto)
#define escreve_V(img, o, size) escreve_V_cor(img, o, size, preto)

// cor
void escreve_S_cor(PPM img, Ponto o, int size, rgb cor);
void escreve_V_cor(PPM img, Ponto o, int size, rgb cor);

// Símbolos

// preto
#define escreve_hifen(img, o, size) escreve_hifen_cor(img, o, size, preto)

// Cor
void escreve_hifen_cor(PPM img, Ponto o, int size, rgb cor);

// Fractais
void desenha_fractal_espiral(PPM img, Ponto ponto1, Ponto ponto2);
void desenha_fractal_arvore_binaria(PPM imagem, Ponto ponto, int tamanho);
void desenha_fractal_arvore_ternaria(PPM imagem, Ponto ponto, int tamanho);
void desenha_fractal_circRec(PPM img, Ponto ponto, int raio);
void desenha_fractal_estrela_recursiva(PPM imagem, Ponto ponto, int raio);
void desenha_fractal_cantor(PPM imagem, Ponto ponto, int tamanho);
void desenha_fractal_koch(PPM imagem, Ponto ponto, Ponto f);
void desenha_fractal_knuth_dragon(PPM imagem, Ponto ponto, Ponto f);
void desenha_fractal_drag(PPM imagem, Ponto ponto, Ponto f);
void desenha_fractal_dragcima(PPM imagem, Ponto ponto, Ponto f);
void desenha_fractal_dragbaixo(PPM imagem, Ponto ponto, Ponto f);
void desenha_fractal_pit(PPM imagem, Ponto c, int lado, float graus);

// Fractais sem nome
void desenha_fractal_rec(PPM imagem, Ponto ponto, int tamanho);
void desenha_fractal_rec2(PPM imagem, Ponto ponto, int tamanho);
void desenha_fractal_rec3baixo(PPM imagem, Ponto ponto, int tamanho);
void desenha_fractal_rec3cima(PPM imagem, Ponto ponto, int tamanho);
void desenha_fractal_rec4(PPM imagem, Ponto ponto, int tamanho);
void desenha_fractal_rec5(PPM imagem, Ponto ponto, int tamanho, rgb cor);
void desenha_fractal_rec6(PPM imagem, Ponto ponto, int tamanho);
void desenha_fractal_rec7(PPM imagem, Ponto ponto, int tamanho, char direcao_x, char direcao_y);
void desenha_fractal_rec8(PPM imagem, Ponto ponto, int tamanho);

// Vetorial
void vetorial_retangulo(Poligono *poligono, Ponto centro, int altura, int largura);
void vetorial_triangulo(Poligono *poligono, Ponto centro, int altura, int base);
void vetorial_losango(Poligono *poligono, Ponto centro, int altura, int largura);
void vetorial_trapezio(Poligono *poligono, Ponto centro, int b1, int b2, int altura);
void vetorial_estrela(Poligono *poligono, Ponto ponto, int x, int y);
void vetorial_translada(Poligono *poligono, int vertical, int horizontal);
void vetorial_rotac(Poligono *poligono, float graus);
void vetorial_escala(Poligono *poligono, double escala);
void desenha_poligono(PPM img, Poligono *poligono);
void desenha_poligono_cor(PPM img, Poligono *poligono, rgb cor);

#endif