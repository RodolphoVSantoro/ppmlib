#include <math.h>

#include "internal_libppm.h"
#include "ppmlib.h"

static void r(PPM* imagem, Ponto a, Ponto b, double t) {
    t += 180.0;
    Ponto m = midpoint(a, b);
    double d = distancia(a, m);
    Ponto v = Ponto_vira(a, Ponto_cria_estatico(a.x, a.y + sqrt(d * d * (1 + seno(60.0)))), t);
    desCurva(imagem, a, v, b);
    if (distancia(a, v) > 10)
        r(imagem, b, m, t);
}

void espiral(PPM* imagem, Ponto a, Ponto b) {
    Ponto m = midpoint(a, b);
    int dx = (b.x - a.x);
    double d = distancia(a, m), t;
    if (dx == 0)
        t = 90.0;
    else {
        int fa = (b.y - a.y) / dx;
        t = rad2graus(atan(fa));
    }
    Ponto v = vira(a, Ponto_cria_estatico(a.x, a.y + sqrt(d * d * (1.0 + seno(60.0)))), t);
    desCurva(imagem, a, v, b);
    if (distancia(a, v) > 10)
        r(imagem, b, m, t);
}

void arvorebin(PPM* imagem, Ponto ponto, int t) {
    Ponto a = Ponto_cria_estatico(p.x - t, p.y - t / 2), b = Ponto_cria_estatico(p.x - t, p.y + t / 2);
    desLinha(imagem, ponto, a);
    desLinha(imagem, ponto, b);
    if (t > 1) {
        arvorebin(imagem, a, t / 2);
        arvorebin(imagem, b, t / 2);
    }
}

void arvoreter(PPM* imagem, Ponto ponto, int t) {
    Ponto a = Ponto_cria_estatico(p.x - t, p.y - t / 2), b = Ponto_cria_estatico(p.x - t, p.y), c = Ponto_cria_estatico(p.x - t, p.y + t / 2);
    desLinha(imagem, ponto, a);
    desLinha(imagem, ponto, b);
    desLinha(imagem, ponto, c);
    if (t > 1) {
        arvoreter(imagem, a, t / 3);
        arvoreter(imagem, b, t / 3);
        arvoreter(imagem, c, t / 3);
    }
}

void circRec(PPM* imagem, Ponto ponto, int raio) {
    desCirculo(imagem, ponto, raio);
    if (raio > 6) {
        circRec(imagem, Ponto_cria_estatico(p.x + raio, p.y), raio / 2);
        circRec(imagem, Ponto_cria_estatico(p.x - raio, p.y), raio / 2);
        circRec(imagem, Ponto_cria_estatico(p.x, p.y + raio), raio / 2);
        circRec(imagem, Ponto_cria_estatico(p.x, p.y - raio), raio / 2);
    }
}

void rec(PPM* imagem, Ponto ponto, int tamanho) {
    desCirculo(imagem, ponto, tam);
    tamanho /= 2;
    if (tamanho > 2) {
        rec(imagem, Ponto_cria_estatico(p.x - tamanho, p.y - tam), tam);
        rec(imagem, Ponto_cria_estatico(p.x - tamanho, p.y + tam), tam);
    }
}

void rec2(PPM* imagem, Ponto ponto, int tamanho) {
    desCirculo(imagem, ponto, tam);
    tamanho /= 2;
    if (tamanho > 10) {
        rec2(imagem, Ponto_cria_estatico(p.x - tamanho, p.y - tam), tam);
        rec2(imagem, Ponto_cria_estatico(p.x - tamanho, p.y + tam), tam);
        rec2(imagem, Ponto_cria_estatico(p.x + tamanho, p.y - tam), tam);
        rec2(imagem, Ponto_cria_estatico(p.x + tamanho, p.y + tam), tam);
    }
}

void rec3baixo(PPM* imagem, Ponto ponto, int tamanho) {
    desCirculo(imagem, ponto, tam);
    tamanho /= 2;
    if (tamanho > 2) {
        rec3baixo(imagem, Ponto_cria_estatico(p.x + tamanho, p.y - tam), tam);
        rec3baixo(imagem, Ponto_cria_estatico(p.x + tamanho, p.y + tam), tam);
    }
}

void rec3cima(PPM* imagem, Ponto ponto, int tamanho) {
    desCirculo(imagem, ponto, tam);
    tamanho /= 2;
    if (tamanho > 2) {
        rec3cima(imagem, Ponto_cria_estatico(p.x - tamanho, p.y - tam), tam);
        rec3cima(imagem, Ponto_cria_estatico(p.x - tamanho, p.y + tam), tam);
    }
}

void rec4(PPM* imagem, Ponto ponto, int tamanho) {
    desCirculo(imagem, ponto, tam);
    if (tamanho > 10) {
        rec4(imagem, Ponto_cria_estatico(p.x - tamanho, p.y), tamanho / 2);
        rec4(imagem, Ponto_cria_estatico(p.x + tamanho, p.y), tamanho / 2);
        rec4(imagem, Ponto_cria_estatico(p.x + tamanho, p.y + tam), tamanho / 2);
        rec4(imagem, Ponto_cria_estatico(p.x + tamanho, p.y - tam), tamanho / 2);
    }
}

void rec5(PPM* imagem, Ponto ponto, int tamanho, rgb cor) {
    desTrianguloCor(imagem, ponto, tamanho, tamanho, cor);
    if (tamanho > 10) {
        rec5(imagem, Ponto_cria_estatico(p.x - tamanho / 4, p.y), tamanho / 2, cor);
        rec5(imagem, Ponto_cria_estatico(p.x + tamanho / 4, p.y + tamanho / 4), tamanho / 2, cor);
        rec5(imagem, Ponto_cria_estatico(p.x + tamanho / 4, p.y - tamanho / 4), tamanho / 2, cor);
    }
}

void rec6(PPM* imagem, Ponto ponto, int tamanho) {
    desCirculo(imagem, ponto, tam);
    desenha_linha_cor(imagem, ponto, Ponto_cria_estatico(p.x - tamanho, p.y - tam), rgb_cria(rand() % 255, rand() % 255, rand() % 255));
    desenha_linha_cor(imagem, ponto, Ponto_cria_estatico(p.x - tamanho, p.y + tam), rgb_cria(rand() % 255, rand() % 255, rand() % 255));
    desenha_linha_cor(imagem, ponto, Ponto_cria_estatico(p.x + tamanho, p.y - tam), rgb_cria(rand() % 255, rand() % 255, rand() % 255));
    desenha_linha_cor(imagem, ponto, Ponto_cria_estatico(p.x + tamanho, p.y + tam), rgb_cria(rand() % 255, rand() % 255, rand() % 255));
    if (tamanho > 43) {
        rec6(imagem, Ponto_cria_estatico(p.x - tamanho * 3 / 2, p.y - tamanho * 3 / 2), tamanho / 2);
        rec6(imagem, Ponto_cria_estatico(p.x - tamanho * 3 / 2, p.y + tamanho * 3 / 2), tamanho / 2);
        rec6(imagem, Ponto_cria_estatico(p.x + tamanho * 3 / 2, p.y - tamanho * 3 / 2), tamanho / 2);
        rec6(imagem, Ponto_cria_estatico(p.x + tamanho * 3 / 2, p.y + tamanho * 3 / 2), tamanho / 2);
    }
}

void rec7(PPM* imagem, Ponto ponto, int tamanho, char direcao_x, char direcao_y) {
    if (direcao_x != 0 || direcao_y != 0) {
        if (direcao_x == -1)
            desLinha(imagem, ponto, Ponto_cria_estatico(p.x - tamanho, p.y));
        if (direcao_x == 1)
            desLinha(imagem, ponto, Ponto_cria_estatico(p.x + tamanho, p.y));
        if (direcao_y == -1)
            desLinha(imagem, ponto, Ponto_cria_estatico(p.x, p.y - tam));
        if (direcao_y == 1)
            desLinha(imagem, ponto, Ponto_cria_estatico(p.x, p.y + tam));
        if (tamanho < 1500) {
            if (direcao_x == -1)
                rec7(imagem, Ponto_cria_estatico(p.x - tamanho, p.y), tamanho * 1.1, 0, -1);
            if (direcao_x == 1)
                rec7(imagem, Ponto_cria_estatico(p.x + tamanho, p.y), tamanho * 1.1, 0, 1);
            if (direcao_y == -1)
                rec7(imagem, Ponto_cria_estatico(p.x, p.y - tam), tamanho * 1.1, 1, 0);
            if (direcao_y == 1)
                rec7(imagem, Ponto_cria_estatico(p.x, p.y + tam), tamanho * 1.1, -1, 0);
        }
    }
}

void rec8(PPM* imagem, Ponto ponto, int tamanho) {
    desLinha(imagem, ponto, Ponto_cria_estatico(p.x + tamanho, p.y));
    tamanho /= 3;
    if (tamanho > 9) {
        // raiz de 2 = 1,732050808
        rec8(imagem, Ponto_cria_estatico(p.x + 3 * tamanho / 2, p.y - tamanho * 1.732050808 / 2), tam);
        rec8(imagem, Ponto_cria_estatico(p.x + 2 * tamanho, p.y - tam), tam);
        rec8(imagem, Ponto_cria_estatico(p.x + 3 * tamanho / 2, p.y + tamanho * 1.732050808 / 2), tam);
        rec8(imagem, Ponto_cria_estatico(p.x + 2 * tamanho, p.y + tam), tam);
    }
}

void EstRec(PPM* imagem, Ponto ponto, int raio) {
    desElipse(imagem, ponto, raio, 16 * raio / 9);
    if (raio > 6) {
        EstRec(imagem, Ponto_cria_estatico(p.x + raio, p.y), raio / 2);
        EstRec(imagem, Ponto_cria_estatico(p.x - raio, p.y), raio / 2);
        EstRec(imagem, Ponto_cria_estatico(p.x, p.y + raio), raio / 2);
        EstRec(imagem, Ponto_cria_estatico(p.x, p.y - raio), raio / 2);
    }
}

void cantor(PPM* imagem, Ponto ponto, int tamanho) {
    desLinha(imagem, ponto, Ponto_cria_estatico(p.x, p.y + tam));
    if (tamanho > 9) {
        tamanho /= 7;
        cantor(imagem, Ponto_cria_estatico(p.x + 50, p.y), tam);
        cantor(imagem, Ponto_cria_estatico(p.x + 50, p.y + 2 * tam), tam);
        cantor(imagem, Ponto_cria_estatico(p.x + 50, p.y + 4 * tam), tam);
        cantor(imagem, Ponto_cria_estatico(p.x + 50, p.y + 6 * tam), tam);
    }
}

void apagakoch(PPM* imagem, Ponto ponto, Ponto f) {
    Ponto
        s = Ponto_cria_estatico((2 * p.x + f.x) / 3, (2 * p.y + f.y) / 3),
        t = Ponto_cria_estatico((2 * f.x + p.x) / 3, (2 * f.y + p.y) / 3);
    desenha_linha_cor(imagem, s, t, rgb_cria(255, 255, 255));
    if (distancia(ponto, f) >= 30) {
        apagakoch(imagem, ponto, s);
        apagakoch(imagem, t, f);
    }
}

void koch(PPM* imagem, Ponto ponto, Ponto f) {
    Ponto
        s = Ponto_cria_estatico((2 * p.x + f.x) / 3, (2 * p.y + f.y) / 3),
        t = Ponto_cria_estatico((2 * f.x + p.x) / 3, (2 * f.y + p.y) / 3),
        v = vira(s, t, 60);
    if (distancia(ponto, f) > 30) {
        koch(imagem, ponto, s);
        koch(imagem, s, v);
        koch(imagem, v, t);
        koch(imagem, t, f);
    } else {
        desLinha(imagem, ponto, s);
        desLinha(imagem, s, v);
        desLinha(imagem, v, t);
        desLinha(imagem, t, f);
    }
}

void koch2(PPM* imagem, Ponto ponto, Ponto f) {
    Ponto
        s = Ponto_cria_estatico((2 * p.x + f.x) / 3, (2 * p.y + f.y) / 3),
        t = Ponto_cria_estatico((2 * f.x + p.x) / 3, (2 * f.y + p.y) / 3),
        v = vira(s, t, 300);
    if (distancia(ponto, f) > 30) {
        koch2(imagem, ponto, s);
        koch2(imagem, s, v);
        koch2(imagem, v, t);
        koch2(imagem, t, f);
    } else {
        desLinha(imagem, ponto, s);
        desLinha(imagem, s, v);
        desLinha(imagem, v, t);
        desLinha(imagem, t, f);
    }
}

void dragon(PPM* imagem, Ponto ponto, Ponto f) {
    Ponto c = Ponto_cria_estatico(
        aprox((f.x * ((2 * 1.732050808 - 1) / 2) + 3 * p.x) / (3 + ((2 * 1.732050808 - 1) / 2))),
        aprox((f.y * ((2 * 1.732050808 - 1) / 2) + 3 * p.y) / (3 + ((2 * 1.732050808 - 1) / 2))));
    if (distancia(ponto, f) > 10) {
        c = vira(f, c, 45);
        dragcima(imagem, ponto, c);
        dragbaixo(imagem, c, f);
    }
}

void dragcima(PPM* imagem, Ponto ponto, Ponto f) {
    Ponto c = Ponto_cria_estatico(
        aprox((f.x * ((2 * 1.732050808 - 1) / 2) + 3 * p.x) / (3 + ((2 * 1.732050808 - 1) / 2))),
        aprox((f.y * ((2 * 1.732050808 - 1) / 2) + 3 * p.y) / (3 + ((2 * 1.732050808 - 1) / 2))));
    if (distancia(ponto, f) > 10) {
        c = vira(f, c, 45);
        dragcima(imagem, ponto, c);
        dragbaixo(imagem, c, f);
    } else {
        desLinha(imagem, ponto, c);
        desLinha(imagem, c, f);
    }
}

void dragbaixo(PPM* imagem, Ponto ponto, Ponto f) {
    Ponto c = Ponto_cria_estatico(
        aprox((f.x * ((2 * 1.732050808 - 1) / 2) + 3 * p.x) / (3 + ((2 * 1.732050808 - 1) / 2))),
        aprox((f.y * ((2 * 1.732050808 - 1) / 2) + 3 * p.y) / (3 + ((2 * 1.732050808 - 1) / 2))));
    if (distancia(ponto, f) > 10) {
        c = vira(f, c, 315);
        dragcima(imagem, ponto, c);
        dragbaixo(imagem, c, f);
    } else {
        desLinha(imagem, ponto, c);
        desLinha(imagem, c, f);
    }
}

void dragonLevy(PPM* imagem, Ponto ponto, Ponto f) {
    Ponto c = Ponto_cria_estatico(
        aprox((f.x * ((2 * 1.732050808 - 1) / 2) + 3 * p.x) / (3 + ((2 * 1.732050808 - 1) / 2))),
        aprox((f.y * ((2 * 1.732050808 - 1) / 2) + 3 * p.y) / (3 + ((2 * 1.732050808 - 1) / 2))));
    if (distancia(ponto, f) > 10) {
        c = vira(f, c, 45);
        dragonLevy(imagem, ponto, c);
        dragonLevy(imagem, c, f);
    } else {
        desLinha(imagem, ponto, c);
        desLinha(imagem, c, f);
    }
}

void fc(PPM* imagem, Ponto a, Ponto b) {
    Ponto c = Ponto_cria_estatico((3 * a.x + b.x) / 4, (3 * a.y + b.y) / 4),
          d = vira(a, c, 90);
    c = vira(a, c, 270);
    Ponto e = Ponto_cria_estatico((a.x + 3 * b.x) / 4, (a.y + 3 * b.y) / 4),
          f = vira(b, e, 90);
    e = vira(b, e, 270);
    desLinha(imagem, a, b);
    if (distancia(a, b) > 10) {
        fc(imagem, c, d);
        fc(imagem, e, f);
    }
}

void pit(PPM imagem, Ponto c, int lado, float graus) {
    Poligono* poligono = cria_poligono();
    vetRetangulo(poligono, c, lado, lado);
    vetRotac(poligono, graus);
    desPoligono(imagem, poligono);
    libera_poligono(poligono);
    Ponto e = Ponto_cria_estatico(c.x - (lado * (2.236067977) / 2.0), c.y);
    Ponto d = Ponto_cria_estatico(c.x - (lado * (2.236067977) / 2.0), c.y);
    e = Ponto_vira(c, e, graus - 26.5);
    d = Ponto_vira(c, d, graus + 26.5);
    if (lado > 20) {
        pit(imagem, d, lado * (1.414213562 / 2.0), graus + 45);
        pit(imagem, e, lado * (1.414213562 / 2.0), graus - 45);
    }
}