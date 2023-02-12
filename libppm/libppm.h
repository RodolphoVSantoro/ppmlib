#ifndef _PPM_LIB_
#define _PPM_LIB_

#include "types.h"

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

// Manipulação básica
rgb rgb_cria(uchar red, uchar green, uchar blue);
rgb int_to_rgb(int numero);
int rgb_to_int(rgb cor);
Dimensao2D* Dimensao2D_cria(int largura, int altura);
Dimensao2D Dimensao2D_cria_estatico(int largura, int altura);
Dimensao2D* Dimensao2D_copia(Dimensao2D* dimensao_original);
void Dimensao2D_libera(Dimensao2D* dimensao);
const char* key_to_string(BMPKey key);
BMPKey string_to_key(char* key);
PPMHeader* PPMHeader_cria(int altura, int largura, int channelRange, BMPKey tipoBMP);
PPMHeader* PPMHeader_copia(PPMHeader* cab);
PPMHeader* PPMHeader_libera(PPMHeader* cabecalho);
PPM* PPM_cria();
PPM* PPM_copia(PPM* imagem);
PPM* PPM_temporaria_cria(PPM* imagem_original);
void PPM_libera(PPM* imagem);
rgb** rgb2d_malloc(Dimensao2D tamanho);
void rgb2d_libera(rgb** pixel, Dimensao2D tamanho);
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
double Ponto_distancia(Ponto a, Ponto b);
Ponto Ponto_vira(Ponto a, Ponto b, float graus);
Ponto midpoint(Ponto a, Ponto b);
Ponto linear_interpolation(Ponto a, Ponto b, double ratio);
bool Ponto_compara(Ponto p, Ponto q);
bool cor_compara(rgb cor_1, rgb cor_2);
int cores_diferentes(PPM* imagem);
rgb cor_aleatoria();
bool imagem_contem_Ponto(PPM* imagem, Ponto p);

#endif