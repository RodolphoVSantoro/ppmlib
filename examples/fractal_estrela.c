#include <stdlib.h>
#include <time.h>

#include "../libppm/libdesenho.h"
#include "../libppm/libppm.h"

int main() {
    srand(time(NULL));
    Dimensao2D tamanho = Dimensao2D_cria_estatico(1080, 1920);
    PPM *imagem = PPM_cria_com_dimensoes(tamanho, 255, _cor_branco);
    Ponto centro = Ponto_cria_estatico(540, 960);
    rgb cor = cor_aleatoria();
    fractal_estrela_recursiva_cor_desenha(imagem, centro, 500, cor);
    PPM_grava("imgs/fractalEstrelaRecursiva.ppm", imagem);
    PPM_libera(imagem);
}