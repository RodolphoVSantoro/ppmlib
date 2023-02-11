#include "lib/ppmlib.h"

int main()
{
        int altura = 1080, largura = 1920;
        Dimensao2D tamanho = Dimensao2D_cria_estatico(altura, largura);
        int canal = 255;
        PPM* imagem = PPM_cria_com_dimensoes(tamanho, canal, _cor_verde_livre_discurso);
        Ponto c = Ponto_cria_estatico(altura / 2, largura / 2);
        desenha_losango_cor_preenchido(imagem, c, altura * 10 / 12, largura * 3 / 4, _cor_amarelo);
        desenha_circulo_cor_preenchido(imagem, c, altura * 99 / 324, _cor_azul);
        int** kernel = kernel_gaussiano(3);
        grava_blur("imgs/teste.ppm", imagem, kernel_gaussiano, 8);
        libera_ppm(imagem);
        return 0;
}