#ifndef _LIB_VETORIAL_H_
#define _LIB_VETORIAL_H_

#include "types.h"
#include "internal.h"

// Poligonos
Poligono* poligono_cria();
bool poligono_vazio(Poligono* pol);
void poligono_insere(Poligono* pol, Ponto p);
Ponto poligono_pop(Poligono* pol);
ListaDuplaPonto* poligono_busca(Poligono* pol, Ponto p);
void poligono_remove_ponto(Poligono* pol, Ponto p);
void poligono_libera(Poligono* pol);

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