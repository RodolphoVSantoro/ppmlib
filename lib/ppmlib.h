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

#define graus2rad(graus) (graus * M_PI / 180.0)
#define rad2graus(radianos) (radianos * 180.0 / M_PI)

#define _cor_branco rgb_cria(255, 255, 255)
#define _cor_preto rgb_cria(0, 0, 0)
#define _cor_vermelho rgb_cria(255, 0, 0)
#define _cor_verde rgb_cria(0, 255, 0)
// https://www.htmlcsscolor.com/hex/00CC00
#define _cor_verde_livre_discurso rgb_cria(0, 205, 0)
#define _cor_azul rgb_cria(0, 0, 255)
#define _cor_cinza rgb_cria(127, 127, 127)
#define _cor_amarelo rgb_cria(255, 255, 0)
#define _cor_roxo rgb_cria(255, 0, 255)
#define _cor_azul_escuro rgb_cria(0, 0, 156)
#define _cor_marrom rgb_cria(92, 51, 23)
#define _cor_ciano rgb_cria(0, 255, 255)
#define _cor_laranja rgb_cria(255, 165, 0)
#define _cor_vermelho_escuro rgb_cria(140, 23, 23)

#ifndef ARQUIVO
#define ARQUIVO
struct Arquivo {
    char** linha;
    int linhas;
};
typedef struct Arquivo Arquivo;
#endif

enum BOOL {
    false = 0,
    true = 1
};
typedef enum BOOL bool;

enum DIRECAO {
    esquerda = 0,
    direita = 1,
    cima = 2,
    baixo = 3
};
typedef enum DIRECAO Direcao;

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

struct ArvoreBinaria {
    int x;
    struct ArvoreBinaria* esquerda;
    struct ArvoreBinaria* direita;
};
typedef struct ArvoreBinaria ArvoreBinaria;

struct LISTA_Ponto {
    Ponto ponto;
    struct LISTA_Ponto* proximo;
};
typedef struct LISTA_Ponto ListaPonto;

struct LISTA_PONTO_DUPLA {
    Ponto ponto;
    struct LISTA_PONTO_DUPLA* proximo;
    struct LISTA_PONTO_DUPLA* anterior;
};
typedef struct LISTA_PONTO_DUPLA ListaDuplaPonto;

struct LINHA {
    ListaPonto* primeiro;
    ListaPonto* ultimo;
};
typedef struct LINHA* Linha;

struct NODECOR {
    rgb cor;
    struct NODECOR* proximo;
    struct NODECOR* anterior;
};
typedef struct NODECOR NodeCor;

struct LISTA_COR {
    NodeCor* fim;
    NodeCor* inicio;
    int tamanho;
};
typedef struct LISTA_COR lista_cor;

typedef struct LISTA_COR* ListaCor;

enum BMPKEY {
    Key_BM = 1,
    Key_BW = 2,
    Key_PPM = 3,
    Key_BMP = 6
};
typedef enum BMPKEY BMPKey;

struct DIM2D {
    int largura;
    int altura;
};
typedef struct DIM2D Dimensao2D;

struct PPMHEADER {
    Dimensao2D* tamanho;
    int channelRange;
    BMPKey tipoBMP;
};
typedef struct PPMHEADER PPMHeader;

struct PPM {
    PPMHeader* cabecalho;
    rgb** pixel;
};
typedef struct PPM PPM;

struct poligono {
    ListaDuplaPonto* primeiro;
    Ponto* centro;
};
typedef struct poligono Poligono;

// Manipulação básica
int int_potencia(int base, int expoente);
void string_copia(char* destino, char* origem);
int string_compara(char* string1, char* string2);
int aproximacao(float val);
int int_valor_absoluto(int n);
void int_troca(int* a, int* b);
float graus_seno(float graus);
float graus_coseno(float graus);
rgb rgb_cria(uchar red, uchar green, uchar blue);
rgb int_to_rgb(int numero);
int rgb_to_int(rgb cor);
Dimensao2D* Dimensao2D_cria(int largura, int altura);
Dimensao2D Dimensao2D_cria_estatico(int largura, int altura);
void Dimensao2D_libera(Dimensao2D* dimensao);
const char* key_to_string(BMPKey key);
BMPKey string_to_key(char* key);
PPMHeader* PPMHeader_cria(int altura, int largura, int max, char key[]);
PPMHeader* PPMHeader_copia(PPMHeader* cab);
PPMHeader* PPMHeader_libera(PPMHeader* cabecalho);
PPM* PPM_cria();
PPM* PPM_copia(PPM* imagem);
void PPM_libera(PPM* imagem);
rgb** rgb2d_malloc(Dimensao2D* tamanho);
void rgb2d_libera(rgb** pixel, Dimensao2D* tamanho);
int** int2d_malloc(Dimensao2D tamanho);
void int2d_libera(int** mat, int altura);
ArvoreBinaria* ArvoreBinaria_cria();
ArvoreBinaria* ArvoreBinaria_folha_cria(int x);
ArvoreBinaria* ArvoreBinaria_insere_sem_repeticao(ArvoreBinaria* r, int x);
ArvoreBinaria* ArvoreBinaria_libera(ArvoreBinaria* r);
void ArvoreBinaria_imprime_pre_ordem(ArvoreBinaria* r);
int ArvoreBinaria_quantidade_nodes(ArvoreBinaria* r);
PPM* PPM_leitura(const char* fname);
void PPM_grava(char fname[], PPM* imagem);
Ponto Ponto_cria_estatico(int x, int y);
double ponto2d_distancia(Ponto a, Ponto b);
Ponto ponto_vira(Ponto a, Ponto b, float graus);
Ponto midpoint(Ponto a, Ponto b);
Ponto linear_interpolation(Ponto a, Ponto b, double ratio);
bool Ponto_compara(Ponto p, Ponto q);
bool cor_compara(rgb a, rgb b);
int cores_diferentes(PPM* imagem);
rgb cor_aleatoria();

// Listas
void ListaDuplaPonto_libera(ListaDuplaPonto* l);
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
Linha Linha_aloca();                                            /*aloca lista de pontos vazia*/
bool Linha_vazia(Linha l);                                      /*verifica se a lista está vazia*/
void Linha_adiciona(Linha l, Ponto p);                          /*insere Ponto na lista*/
void Linha_cria(Linha l, Ponto pontoInicial, Ponto pontoFinal); /*insere pontos pertencentes a linha de ponto inicial até ponto final*/
void Linha_remove(Linha l, Ponto p);                            /*remove um Ponto da lista*/
void Libera_linha(Linha l);                                     /*remove todos os pontos*/
// Poligonos
Poligono* poligono_cria();
bool poligono_vazio(Poligono* pol);
void poligono_insere(Poligono* pol, Ponto p);
Ponto poligono_pop(Poligono* pol);
ListaDuplaPonto* poligono_busca(Poligono* pol, Ponto p);
void poligono_remove_ponto(Poligono* pol, Ponto p);
void poligono_libera(Poligono* pol);

// manipulacao com efeitos
PPM* cria_com_decomposicao(PPM* cab, bool r, bool g, bool b);
PPM* cria_com_rotacao(PPM* imagem, int graus);
PPM* cria_com_negativo(PPM* imagem);
PPM* cria_com_preto_e_branco(PPM* imagem);
PPM* cria_com_bitmap(PPM* imagem);
PPM* cria_com_blur(PPM* imagem, int** ker, int tamanhoKernel);
int** kernel_gaussiano(int tamanhoKernel);
PPM* cria_com_blur_gaussiano(PPM* imagem, int tamanhoKernel);
int** kernel_mint(int tamanhoKernel);
PPM* cria_com_blur_mint(PPM* imagem, int tamanhoKernel);
PPM* cria_com_amplia(PPM* imagem, int zoom);
// PPM* espelhar(PPM* imagem);
PPM* cria_com_join(PPM* imagem, PPM* imagem2);
PPM* cria_com_merge(PPM* imagem, PPM* imagem2);
PPM* cria_com_overlay(PPM* imagem, PPM* imagem2);
void grava_decomposto(char fname[], PPM* imagem, bool r, bool g, bool b);
void grava_rotacionado(char fname[], PPM* imagem, int graus);
void grava_negativo(char fname[], PPM* imagem);
void grava_preto_e_branco(char fname[], PPM* imagem);
void grava_bitmap(char fname[], PPM* imagem);
void grava_blur(char fname[], PPM* imagem, int** ker, int tamanhoKernel);
void grava_blur_gaussiano(char fname[], PPM* imagem, int tamanhoKernel);
void grava_blur_mint(char fname[], PPM* imagem, int tamanhoKernel);
void grava_espelhado(char fname[], PPM* imagem);
void aplica_decomposicao(PPM* imagem, bool r, bool g, bool b);
void aplica_rotacao(PPM* imagem, int graus);
void aplica_negativo(PPM* imagem);
void aplica_BW(PPM* imagem);
void aplica_BM(PPM* imagem);
void aplica_blur_gaussiano(PPM* imagem, int tamanhoKernel);
void aplica_blur_mint(PPM* imagem, int tamanhoKernel);
// void aplica_espelha(PPM *imagem);

// Criação
PPM* PPM_cria_com_dimensoes(Dimensao2D tamanho, int channelRange, rgb corFundo);
// sem cor
#define desenha_ponto(imagem, ponto) desenha_ponto_cor(imagem, ponto, _cor_preto)
#define desenha_linha(imagem, pontoInicial, pontoFinal) desenha_linha_cor(imagem, pontoInicial, pontoFinal, _cor_preto)
#define desenha_curva(imagem, pontoInicial, pm, pontoFinal) desenha_lista_linha_cor(imagem, pontoInicial, pm, pontoFinal, _cor_preto)
#define insere_linha(imagem, l) insere_linha_cor(imagem, l, _cor_preto) /*desenha linha e remove os pontos da lista*/
#define desTriangulo(imagem, centro, altura, base) desenha_triangulo_cor(imagem, centro, altura, base, _cor_preto)
#define desRetangulo(imagem, centro, alturaR, larguraR) desenha_retangulo_cor(imagem, centro, alturaR, larguraR, _cor_preto)
#define desLosango(imagem, centro, altura, largura) desenha_losango_cor(imagem, centro, altura, largura, _cor_preto)
#define desTrapezio(imagem, centro, b1, b2, altura) desenha_trapezio_cor(imagem, centro, b1, b2, altura, _cor_preto)
#define desEstrela(imagem, p, x, y) desenha_estrela_cor(imagem, p, x, y, _cor_preto)
#define desCirculo(imagem, centro, raio) desenha_circulo_cor(imagem, centro, raio, _cor_preto)
#define desElipse(imagem, centro, altura, largura) desenha_elipse_cor(imagem, centro, altura, largura, _cor_preto)

// cor
void desenha_ponto_cor(PPM* imagem, Ponto pontoInicial, rgb cor);
void desenha_linha_cor(PPM* imagem, Ponto pontoInicial, Ponto pontoFinal, rgb cor);
void desenha_curva_cor(PPM* imagem, Ponto pontoInicial, Ponto pm, Ponto pontoFinal, rgb cor);
void desenha_lista_linha_cor(PPM* imagem, Linha l, rgb cor);
void desenha_triangulo_cor(PPM* imagem, Ponto centro, int altura, int base, rgb cor);
void desenha_retangulo_cor(PPM* imagem, Ponto centro, int alturaR, int larguraR, rgb cor);
void desenha_losango_cor(PPM* imagem, Ponto centro, int altura, int largura, rgb cor);
void desenha_trapezio_cor(PPM* imagem, Ponto centro, int b1, int b2, int altura, rgb cor);
void desenha_estrela_cor(PPM* imagem, Ponto p, int x, int y, rgb cor);
void desenha_circulo_cor(PPM* imagem, Ponto centro, int raio, rgb cor);
void desenha_elipse_cor(PPM* imagem, Ponto centro, int altura, int largura, rgb cor);

// preenchidos
#define desenha_curva_preenchido(imagem, pontoInicial, pm, pontoFinal) desenha_curva_cor_preenchido(imagem, pontoInicial, pm, pontoFinal, _cor_preto)
#define desenha_triangulo_preenchido(imagem, centro, altura, base) desenha_triangulo_cor_preenchido(imagem, centro, altura, base, _cor_preto)
#define desenha_retangulo_preenchido(imagem, centro, altura, largura) desenha_retangulo_cor_preenchido(imagem, centro, altura, largura, _cor_preto)
#define desenha_losango_preenchido(imagem, centro, altura, largura) desenha_losango_cor_preenchido(imagem, centro, altura, largura, _cor_preto)
#define desenha_circulo_preenchido(imagem, centro, raio) desenha_circulo_cor_preenchido(imagem, centro, raio, _cor_preto)

// preenchidos com cor
void desenha_curva_cor_preenchido(PPM* imagem, Ponto pontoInicial, Ponto pm, Ponto pontoFinal, rgb cor);
void desenha_triangulo_cor_preenchido(PPM* imagem, Ponto centro, int altura, int base, rgb cor);
void desenha_retangulo_cor_preenchido(PPM* imagem, Ponto centro, int altura, int largura, rgb cor);
void desenha_losango_cor_preenchido(PPM* imagem, Ponto centro, int altura, int largura, rgb cor);
void desenha_circulo_cor_preenchido(PPM* imagem, Ponto centro, int raio, rgb cor);

// Minha Fonte
#define fonte_escreve_string(imagem, s, o, font_size) fonte_escreve_string_cor(imagem, s, o, font_size, _cor_preto)
#define fonte_escreve_char(imagem, c, o, size) fonte_escreve_char_cor(imagem, c, o, size, _cor_preto)
void fonte_escreve_string_cor(PPM* imagem, char string[], Ponto origem, int tamanho_fonte, rgb cor);
void fonte_escreve_char_cor(PPM* imagem, char c, Ponto o, int size, rgb cor);

// Fractais
void desenha_fractal_espiral(PPM* imagem, Ponto ponto1, Ponto ponto2);
void desenha_fractal_arvore_binaria(PPM* imagem, Ponto ponto, int tamanho);
void desenha_fractal_arvore_ternaria(PPM* imagem, Ponto ponto, int tamanho);
void desenha_fractal_circulo_recursivo(PPM* imagem, Ponto ponto, int raio);
void desenha_fractal_estrela_recursiva(PPM* imagem, Ponto ponto, int raio);
void desenha_fractal_cantor(PPM* imagem, Ponto ponto, int tamanho);
void desenha_fractal_koch(PPM* imagem, Ponto pontoInicial, Ponto pontoFinal);
void desenha_fractal_knuth_dragon(PPM* imagem, Ponto pontoInicial, Ponto pontoFinal);
void desenha_fractal_drag(PPM* imagem, Ponto pontoInicial, Ponto pontoFinal);
void desenha_fractal_dragcima(PPM* imagem, Ponto pontoInicial, Ponto pontoFinal);
void desenha_fractal_dragbaixo(PPM* imagem, Ponto pontoInicial, Ponto pontoFinal);
void desenha_fractal_pit(PPM* imagem, Ponto centro, int lado, float graus);

// Fractais sem nome
void desenha_fractal_rec(PPM* imagem, Ponto ponto, int tamanho);
void desenha_fractal_rec2(PPM* imagem, Ponto ponto, int tamanho);
void desenha_fractal_rec3baixo(PPM* imagem, Ponto ponto, int tamanho);
void desenha_fractal_rec3cima(PPM* imagem, Ponto ponto, int tamanho);
void desenha_fractal_rec4(PPM* imagem, Ponto ponto, int tamanho);
void desenha_fractal_rec5(PPM* imagem, Ponto ponto, int tamanho, rgb cor);
void desenha_fractal_rec6(PPM* imagem, Ponto ponto, int tamanho);
void desenha_fractal_rec7(PPM* imagem, Ponto ponto, int tamanho, char direcao_x, char direcao_y);
void desenha_fractal_rec8(PPM* imagem, Ponto ponto, int tamanho);

// Vetorial
void vetorial_retangulo(Poligono* poligono, Ponto centro, int altura, int largura);
void vetorial_triangulo(Poligono* poligono, Ponto centro, int altura, int base);
void vetorial_losango(Poligono* poligono, Ponto centro, int altura, int largura);
void vetorial_trapezio(Poligono* poligono, Ponto centro, int b1, int b2, int altura);
void vetorial_estrela(Poligono* poligono, Ponto ponto, int x, int y);
void vetorial_translada(Poligono* poligono, int vertical, int horizontal);
void vetorial_rotac(Poligono* poligono, float graus);
void vetorial_escala(Poligono* poligono, double escala);
void desenha_poligono(PPM* imagem, Poligono* poligono);
void desenha_poligono_cor(PPM* imagem, Poligono* poligono, rgb cor);

#endif