#include "internal_libppm.h"
#include "ppmlib.h"

void vetorial_retangulo(Poligono *poligono, Ponto centro, int altura, int largura) {
    poligono_esvazia(poligono);
    *(poligono->centro) = centro;
    poligono_insere(poligono, Ponto_cria_estatico(centro.x - altura / 2, centro.y - largura / 2));
    poligono_insere(poligono, Ponto_cria_estatico(centro.x - altura / 2, centro.y + largura / 2));
    poligono_insere(poligono, Ponto_cria_estatico(centro.x + altura / 2, centro.y + largura / 2));
    poligono_insere(poligono, Ponto_cria_estatico(centro.x + altura / 2, centro.y - largura / 2));
}

void vetorial_triangulo(Poligono *poligono, Ponto centro, int altura, int base) {
    poligono_esvazia(poligono);
    *(poligono->centro) = centro;
    poligono_insere(poligono, Ponto_cria_estatico(centro.x + altura / 2, centro.y - base / 2));
    poligono_insere(poligono, Ponto_cria_estatico(centro.x - altura / 2, centro.y));
    poligono_insere(poligono, Ponto_cria_estatico(centro.x + altura / 2, centro.y + base / 2));
}

void vetorial_losango(Poligono *poligono, Ponto centro, int altura, int largura) {
    poligono_esvazia(poligono);
    *(poligono->centro) = centro;
    poligono_insere(poligono, Ponto_cria_estatico(centro.x, centro.y - largura / 2));
    poligono_insere(poligono, Ponto_cria_estatico(centro.x - altura / 2, centro.y));
    poligono_insere(poligono, Ponto_cria_estatico(centro.x, centro.y + largura / 2));
    poligono_insere(poligono, Ponto_cria_estatico(centro.x + altura / 2, centro.y));
}

void vetorial_trapezio(Poligono *poligono, Ponto centro, int base1, int base2, int altura) {
    poligono_esvazia(poligono);
    *(poligono->centro) = centro;
    poligono_insere(poligono, Ponto_cria_estatico(centro.x - altura / 2, centro.y - base1 / 2));
    poligono_insere(poligono, Ponto_cria_estatico(centro.x - altura / 2, centro.y + base1 / 2));
    poligono_insere(poligono, Ponto_cria_estatico(centro.x + altura / 2, centro.y + base2 / 2));
    poligono_insere(poligono, Ponto_cria_estatico(centro.x + altura / 2, centro.y - base2 / 2));
}

void vetorial_estrela(Poligono *poligono, Ponto ponto, int x, int y) {
    poligono_esvazia(poligono);
    *(poligono->centro) = ponto;
    poligono_insere(poligono, Ponto_cria_estatico(ponto.x - x, ponto.y));
    poligono_insere(poligono, Ponto_cria_estatico(ponto.x - x / 2, ponto.y - y / 3));
    poligono_insere(poligono, Ponto_cria_estatico(ponto.x - x / 2, ponto.y - y));
    poligono_insere(poligono, Ponto_cria_estatico(ponto.x, ponto.y - 2 * y / 3));
    poligono_insere(poligono, Ponto_cria_estatico(ponto.x + x / 2, ponto.y - y));
    poligono_insere(poligono, Ponto_cria_estatico(ponto.x + x / 2, ponto.y - y / 3));
    poligono_insere(poligono, Ponto_cria_estatico(ponto.x + x, ponto.y));
    poligono_insere(poligono, Ponto_cria_estatico(ponto.x + x / 2, ponto.y + y / 3));
    poligono_insere(poligono, Ponto_cria_estatico(ponto.x + x / 2, ponto.y + y));
    poligono_insere(poligono, Ponto_cria_estatico(ponto.x, ponto.y + 2 * y / 3));
    poligono_insere(poligono, Ponto_cria_estatico(ponto.x - x / 2, ponto.y + y));
    poligono_insere(poligono, Ponto_cria_estatico(ponto.x - x / 2, ponto.y + y / 3));
}

void vetorial_translada(Poligono *poligono, int vertical, int horizontal) {
    *(poligono->centro) = Ponto_cria_estatico(poligono->centro->x + vertical, poligono->centro->y + horizontal);
    ListaDuplaPonto *cursor = poligono->primeiro;
    while (cursor != NULL) {
        cursor->ponto.x += vertical;
        cursor->ponto.y += horizontal;
        cursor = cursor->proximo;
    }
}

void vetorial_rotacao(Poligono *poligono, float graus) {
    ListaDuplaPonto *cursor;
    for (cursor = poligono->primeiro; cursor != NULL; cursor = cursor->proximo)
        cursor->ponto = Ponto_vira(*(poligono->centro), cursor->ponto, graus);
}

void vetorial_escala(Poligono *poligono, double escala) {
    escala -= 1.0;
    ListaDuplaPonto *cursor = poligono->primeiro;
    while (cursor != NULL) {
        cursor->ponto.x = (cursor->ponto.x - poligono->centro->x) * escala + cursor->ponto.x;
        cursor->ponto.y = (cursor->ponto.y - poligono->centro->y) * escala + cursor->ponto.y;
        cursor = cursor->proximo;
    }
}

void desenha_poligono(PPM imagem, Poligono *poligono) {
    ListaDuplaPonto *cursor = poligono->primeiro->proximo;
    desenha_linha(imagem, poligono->primeiro->ponto, cursor->ponto);
    while (cursor->proximo != NULL) {
        desenha_linha(imagem, cursor->ponto, cursor->proximo->ponto);
        cursor = cursor->proximo;
        cursor->anterior->anterior = cursor->anterior->proximo = NULL;
        libera_lista_p2(cursor->anterior);
        cursor->anterior = NULL;
    }
    desLinha(imagem, cursor->ponto, poligono->primeiro->ponto);
    libera_lista_p2(cursor);
    poligono->primeiro->proximo = NULL;
    libera_lista_p2(poligono->primeiro);
    poligono->primeiro = NULL;
}

void desenha_poligono_cor(PPM *imagem, Poligono *poligono, rgb cor) {
    ListaDuplaPonto *cursor = poligono->primeiro->proximo;
    desenha_linha_cor(imagem, poligono->primeiro->ponto, cursor->ponto, cor);
    while (cursor->proximo != NULL) {
        desenha_linha_cor(imagem, cursor->ponto, cursor->proximo->ponto, cor);
        cursor = cursor->proximo;
        cursor->anterior->anterior = cursor->anterior->proximo = NULL;
        libera_lista_p2(cursor->anterior);
        cursor->anterior = NULL;
    }
    desenha_linha_cor(imagem, cursor->ponto, poligono->primeiro->ponto, cor);
    libera_lista_p2(cursor);
    poligono->primeiro->proximo = NULL;
    libera_lista_p2(poligono->primeiro);
    poligono->primeiro = NULL;
}