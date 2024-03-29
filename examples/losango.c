#include <stdio.h>

#include "../libppm/libdesenho.h"
#include "../libppm/libppm.h"

int main() {
    Dimensao2D dimensoes = Dimensao2D_cria_estatico(1000, 1200);
    PPM* img = PPM_cria_com_dimensoes(dimensoes, 255, _cor_branco);

    Ponto ponto = Ponto_cria_estatico(500, 600);

    losango_cor_desenha(img, ponto, 100, 150, _cor_vermelho);

    PPM_grava("imgs/losango.ppm", img);
    PPM_libera(img);
    return 0;
}