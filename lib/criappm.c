#include <stdlib.h>

#include "ppmlib.h"

PPM ppm_cria(int altura, int largura, rgb cor) {
    PPM imagem = ppm_malloc();
    int i, j;
    imagem->cab->altura = altura;
    imagem->cab->largura = largura;
    imagem->cab->max = 255;
    strcop(imagem->cab->key, "P3");
    imagem->cor = rgb_malloc(imagem->cab);
    for (i = 0; i < altura; i++)
        for (j = 0; j < largura; j++)
            imagem->cor[i][j] = cor;
    return imagem;
}

// Cor

void desPontoCor(PPM imagem, Ponto ponto, rgb cor) {
    if (p.x >= 0 && p.x < imagem->cab->altura && p.y >= 0 && p.y < imagem->cab->largura) {
        imagem->cor[p.x][p.y] = cor;
    }
}

void desLinhaCor(PPM imagem, Ponto ponto_inicial, Ponto ponto_final, rgb cor) {
    double i;
    if (int_valor_absoluto(ponto_inicial.x - ponto_final.x) < imagem->cabecalho->tamanho->altura / 500) {
        if (ponto_inicial.y > ponto_final.y) {
            troca(&ponto_inicial.y, &ponto_final.y);
        }
        for (i = ponto_inicial.y; i <= ponto_final.y; i++) {
            ponto_cor_desenha(imagem, ponto_cria(ponto_inicial.x, i), cor);
        }
    } else {
        int delta_x, delta_y, c;
        delta_x = ponto_inicial.x - ponto_final.x;
        delta_y = ponto_final.y - ponto_inicial.y;
        c = ponto_final.x * ponto_inicial.y - ponto_inicial.x * pf.y;
        if (ponto_inicial.x > ponto_final.x) {
            troca(&ponto_inicial.x, &ponto_final.x);
        }
        for (i = ponto_inicial.x; i <= ponto_final.x; i += 0.05) {
            ponto_cor_desenha(imagem, ponto_cria(i, -(i * delta_y + c) / delta_x), cor);
        }
    }
}

void desCurvaCor(PPM imagem, Ponto p0, Ponto pm, Ponto pf, rgb cor) {
    Ponto ab, bc, ab2, bc2;
    double i, lim = distancia(p0, pm) + distancia(pf, pm);
    for (i = 0; i < lim; i++) {
        ab = linear_interpolation(p0, pm, i / lim);
        bc = linear_interpolation(pm, pf, i / lim);
        ab2 = linear_interpolation(p0, pm, (i + 1) / lim);
        bc2 = linear_interpolation(pm, pf, (i + 1) / lim);
        desLinhaCor(imagem, linear_interpolation(ab, bc, i / lim), linear_interpolation(ab2, bc2, (i + 1) / lim), cor);
    }
}

void insere_linhaCor(PPM imagem, Linha linha, rgb cor) {
    ListaPonto *per = linha->primeiro;
    while (!linha_vazia(linha)) {
        desPontoCor(imagem, linha->primeiro->p, cor);
        per = per->proximo;
        free(linha->primeiro);
        linha->primeiro = per;
    }
}

void desTrianguloCor(PPM imagem, Ponto centro, int altura, int base, rgb cor) {
    Ponto a, b, c;
    a = cria_ponto(centro.x + altura / 2, centro.y - base / 2);
    b = cria_ponto(centro.x - altura / 2, centro.y);
    c = cria_ponto(centro.x + altura / 2, centro.y + base / 2);
    desLinhaCor(imagem, a, b, cor);
    desLinhaCor(imagem, b, c, cor);
    desLinhaCor(imagem, c, a, cor);
}

void desRetanguloCor(PPM imagem, Ponto centro, int altura, int largura, rgb cor) {
    Ponto a, b, c, d;
    a = cria_ponto(centro.x - altura / 2, centro.y - largura / 2);
    b = cria_ponto(centro.x - altura / 2, centro.y + largura / 2);
    c = cria_ponto(centro.x + altura / 2, centro.y + largura / 2);
    d = cria_ponto(centro.x + altura / 2, centro.y - largura / 2);
    desLinhaCor(imagem, a, b, cor);
    desLinhaCor(imagem, a, c, cor);
    desLinhaCor(imagem, b, c, cor);
    desLinhaCor(imagem, d, a, cor);
}

void desLosangoCor(PPM imagem, Ponto centro, int altura, int largura, rgb cor) {
    Ponto a, b, c, d;
    a = cria_ponto(centro.x, centro.y - largura / 2);
    b = cria_ponto(centro.x - altura / 2, centro.y);
    c = cria_ponto(centro.x, centro.y + largura / 2);
    d = cria_ponto(centro.x + altura / 2, centro.y);
    desLinhaCor(imagem, a, b, cor);
    desLinhaCor(imagem, b, c, cor);
    desLinhaCor(imagem, c, d, cor);
    desLinhaCor(imagem, d, a, cor);
}

void desTrapezioCor(PPM imagem, Ponto centro, int b1, int b2, int altura, rgb cor) {
    Ponto a, b, c, d;
    a = cria_ponto(centro.x - altura / 2, centro.y - b1 / 2);
    b = cria_ponto(centro.x - altura / 2, centro.y + b1 / 2);
    c = cria_ponto(centro.x + altura / 2, centro.y + b2 / 2);
    d = cria_ponto(centro.x + altura / 2, centro.y - b2 / 2);
    desLinhaCor(imagem, a, b, cor);
    desLinhaCor(imagem, b, c, cor);
    desLinhaCor(imagem, c, d, cor);
    desLinhaCor(imagem, d, a, cor);
}

void desEstrelaCor(PPM imagem, Ponto p, int x, int y, rgb cor) {
    Ponto v[12];
    int i;
    v[0] = cria_ponto(p.x - x, p.y);
    v[1] = cria_ponto(p.x - x / 2, p.y - y / 3);
    v[2] = cria_ponto(p.x - x / 2, p.y - y);
    v[3] = cria_ponto(p.x, p.y - 2 * y / 3);
    v[4] = cria_ponto(p.x + x / 2, p.y - y);
    v[5] = cria_ponto(p.x + x / 2, p.y - y / 3);
    v[6] = cria_ponto(p.x + x, p.y);
    v[7] = cria_ponto(p.x + x / 2, p.y + y / 3);
    v[8] = cria_ponto(p.x + x / 2, p.y + y);
    v[9] = cria_ponto(p.x, p.y + 2 * y / 3);
    v[10] = cria_ponto(p.x - x / 2, p.y + y);
    v[11] = cria_ponto(p.x - x / 2, p.y + y / 3);
    for (i = 0; i < 12; i++)
        desLinhaCor(imagem, v[i], v[(i + 1) % 12], cor);
}

void desCirculoCor(PPM imagem, Ponto centro, int raio, rgb cor) {
    int x = raio;
    int y = 0;
    int err = 0;
    while (x >= y) {
        desPontoCor(imagem, cria_ponto(centro.x + x, centro.y + y), cor);
        desPontoCor(imagem, cria_ponto(centro.x + y, centro.y + x), cor);
        desPontoCor(imagem, cria_ponto(centro.x - y, centro.y + x), cor);
        desPontoCor(imagem, cria_ponto(centro.x - x, centro.y + y), cor);
        desPontoCor(imagem, cria_ponto(centro.x - x, centro.y - y), cor);
        desPontoCor(imagem, cria_ponto(centro.x - y, centro.y - x), cor);
        desPontoCor(imagem, cria_ponto(centro.x + y, centro.y - x), cor);
        desPontoCor(imagem, cria_ponto(centro.x + x, centro.y - y), cor);
        y += 1;
        err += 1 + 2 * y;
        if (2 * (err - x) + 1 > 0) {
            x -= 1;
            err += 1 - 2 * x;
        }
    }
}

void desElipseCor(PPM imagem, Ponto centro, int altura, int largura, rgb cor) {
    Ponto p0 = cria_ponto(centro.x + altura / 2, centro.y - largura / 2);
    Ponto pf = cria_ponto(centro.x - altura / 2, centro.y + largura / 2);
    int a = abs(pf.x - p0.x);
    int b = abs(pf.y - p0.y);
    int b1 = b & 1;
    long dx = 4 * (1 - a) * b * b, dy = 4 * (b1 + 1) * a * a;
    long err = dx + dy + b1 * a * a;
    long e2;

    if (p0.x > pf.x) {
        p0.x = pf.x;
        pf.x += a;
    }
    if (p0.y > pf.y) {
        p0.y = pf.y;
    }
    p0.y += (b + 1) / 2;
    pf.y = p0.y - b1;
    a *= 8 * a;
    b1 = 8 * b * b;

    do {
        desPontoCor(imagem, cria_ponto(pf.x, p0.y), cor);
        desPontoCor(imagem, cria_ponto(p0.x, p0.y), cor);
        desPontoCor(imagem, cria_ponto(p0.x, pf.y), cor);
        desPontoCor(imagem, cria_ponto(pf.x, pf.y), cor);
        e2 = 2 * err;
        if (e2 <= dy) {
            p0.y++;
            pf.y--;
            err += dy += a;
        }
        if (e2 >= dx || 2 * err > dy) {
            p0.x++;
            pf.x--;
            err += dx += b1;
        }
    } while (p0.x <= pf.x);

    while (p0.y - pf.y < b) {
        desPontoCor(imagem, cria_ponto(p0.x - 1, p0.y), cor);
        desPontoCor(imagem, cria_ponto(pf.x + 1, p0.y++), cor);
        desPontoCor(imagem, cria_ponto(p0.x - 1, pf.y), cor);
        desPontoCor(imagem, cria_ponto(pf.x + 1, pf.y--), cor);
    }
}

// Formas preenchidas com cor
void desCurvaCorprn(PPM imagem, Ponto p0, Ponto pm, Ponto pf, rgb cor) {
    double lim = distancia(p0, pm) + distancia(pf, pm);
    double i;
    for (i = 0; i <= lim; i++) {
        desCurvaCor(imagem, p0, linear_interpolation(pm, midpoint(p0, pf), i / lim), pf, cor);
    }
}

void desTrianguloCorprn(PPM imagem, Ponto centro, int altura, int base, rgb cor) {
    Ponto a = cria_ponto(centro.x - altura / 2, centro.y);
    Ponto b = cria_ponto(centro.x + altura / 2, centro.y - base / 2);
    Ponto c = cria_ponto(centro.x + altura / 2, centro.y + base / 2);
    Linha linha = aloca_linha();
    ListaPonto linha2 = aloca_linhainha() primeiro;
    ListaPonto(l, aiinhalinhanha, b) primeiro;
    cria_linha(l2, a, inhalinha c);
    lista_p *p1 = l->prim;
    lista_p *p2 = l2->prim;
    while (p1 != NULL && p2 != NULL) {
        desLinhaCor(imagem, p1->p, p2->p, cor);
        p1 = p1->prox;
        p2 = p2->prox;
    }
    libera_linha(l);
    libera_linha(l2);
}

void desRetanguloCorprn(PPM imagem, Ponto centro, int altura, int largura, rgb cor) {
    Ponto c, d;
    Ponto a = cria_ponto(centro.x - altura / 2, centro.y + largura / 2);
    Ponto b = cria_ponto(centro.x - altura / 2, centro.y - largura / 2);
    Ponto c = a;
    Ponto d = b;

    while (c.x < centro.x + altura / 2) {
        desLinhaCor(imagem, c, d, cor);
        c.x++;
        d.x++;
    }
}

void desLosangoCorprn(PPM imagem, Ponto centro, int altura, int largura, rgb cor) {
    Ponto a = cria_ponto(centro.x, centro.y - largura / 2);
    Ponto b = cria_ponto(centro.x - altura / 2, centro.y);
    Ponto c = cria_ponto(centro.x, centro.y + largura / 2);
    Ponto d = cria_ponto(centro.x + altura / 2, centro.y);

    Linha linhainhas[4];
    ListaPonto *m, *ninhaprimeiro;
    ininhalinhat i;
    for (i = 0; i < 4; i++) {
        l[i] = aloca_linha();
    }

    cria_linha(l[0], a, b);
    cria_linha(l[1], b, c);
    cria_linha(l[2], a, d);
    cria_linha(l[3], c, d);

    for (i = 0; i <= 2; i += 2) {
        for (m = l[i]->prim, n = l[i + 1]->prim; m != NULL && n != NULL; n = n->prox, m = m->prox) {
            desLinhaCor(imagem, m->p, n->p, cor);
        }
    }
    for (i = 0; i < 4; i++) {
        libera_linha(l[i]);
    }
}

void desCirculoCorprn(PPM imagem, Ponto centro, int raio, rgb cor) {
    int x = raio;
    int y = 0;
    int err = 0;
    while (x >= y) {
        desLinhaCor(imagem, cria_ponto(centro.x - x, centro.y - y), cria_ponto(centro.x - x, centro.y + y), cor);
        desLinhaCor(imagem, cria_ponto(centro.x - y, centro.y - x), cria_ponto(centro.x - y, centro.y + x), cor);
        desLinhaCor(imagem, cria_ponto(centro.x + y, centro.y - x), cria_ponto(centro.x + y, centro.y + x), cor);
        desLinhaCor(imagem, cria_ponto(centro.x + x, centro.y - y), cria_ponto(centro.x + x, centro.y + y), cor);
        y += 1;
        err += 1 + 2 * y;
        if (2 * (err - x) + 1 > 0) {
            x -= 1;
            err += 1 - 2 * x;
        }
    }
}
