#include <libdesenho.h>
#include <libefeito.h>
#include <libppm.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    Dimensao2D dimensoes = Dimensao2D_cria_estatico(2000, 2000);
    PPM* img = PPM_cria_com_dimensoes(dimensoes, 255, rgb_cria(51, 255, 255));

    Ponto ponto_i = Ponto_cria_estatico(500, 500);
    Ponto ponto_f = Ponto_cria_estatico(900, 900);

    for (int i = 0; i < 10; i++) {
        rgb cor = cor_aleatoria();
        fractal_dragon_cor_desenha(img, ponto_i, ponto_f, cor);
        ponto_i.x -= i * 30;
        ponto_i.y += i * 30;
    }

    ponto_i = Ponto_cria_estatico(900, 900);
    ponto_f = Ponto_cria_estatico(1400, 1400);

    for (int i = 0; i < 10; i++) {
        rgb cor = cor_aleatoria();
        fractal_dragon_cor_desenha(img, ponto_i, ponto_f, cor);
        ponto_i.x += i * 30;
        ponto_i.y -= i * 30;
    }

    efeito_aplica_blur_gaussiano(&img, 20);

    PPM_grava("imgs/dragon_blur.ppm", img);
    PPM_libera(img);
    return 0;
}