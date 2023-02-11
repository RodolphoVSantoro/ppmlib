#include <stdio.h>
#include <time.h>

#include "ppmlib.h"

bool celula_contida_na_imagem(PPM* imagem, Ponto p) {
    return (p.x > 0 && p.x < imagem->cabecalho->tamanho->altura && p.y > 0 && p.y < imagem->cabecalho->tamanho->largura);
}

bool celula_tem_automata(PPM* imagem, Ponto p) {
    return cor_compara(imagem->pixel[p.x][p.y], _cor_preto);
}

void incrementa_se_vizinho_tem_automata(PPM* imagem, Ponto celula, int* a) {
    if (celula_contida_na_imagem(imagem, celula) && celula_tem_automata(imagem, celula)) {
        *a++;
    }
}

rgb nova_cor_celula_atual(PPM* imagem, Ponto celula, int automatas_vizinhos) {
    if (celula_tem_automata(imagem, celula)) {
        if (automatas_vizinhos < 2) {
            return _cor_branco;
        } else if (automatas_vizinhos > 3) {
            return _cor_branco;
        }
    } else if (automatas_vizinhos == 3) {
        return _cor_preto;
    }
    return imagem->pixel[celula.x][celula.y];
}

void conwayGame_of_Life(PPM* imagem) {
    int i, j;
    int automatas_vizinhos;
    for (i = 0; i < imagem->cabecalho->tamanho->altura; i++) {
        for (j = 0; j < imagem->cabecalho->tamanho->largura; j++) {
            automatas_vizinhos = 0;
            Ponto ponto_a_esquerda = Ponto_cria_estatico(i - 1, j);
            incrementa_se_pixel_tem_automata(imagem, ponto_a_esquerda, &automatas_vizinhos);

            Ponto ponto_esquerda_baixo = Ponto_cria_estatico(i - 1, j + 1);
            incrementa_se_pixel_tem_automata(imagem, ponto_esquerda_baixo, &automatas_vizinhos);

            Ponto ponto_esquerda_cima = Ponto_cria_estatico(i - 1, j - 1);
            incrementa_se_pixel_tem_automata(imagem, ponto_esquerda_cima, &automatas_vizinhos);

            Ponto ponto_a_direita = Ponto_cria_estatico(i + 1, j);
            incrementa_se_pixel_tem_automata(imagem, ponto_a_direita, &automatas_vizinhos);

            Ponto ponto_direita_baixo = Ponto_cria_estatico(i + 1, j + 1);
            incrementa_se_pixel_tem_automata(imagem, ponto_direita_baixo, &automatas_vizinhos);

            Ponto ponto_direita_cima = Ponto_cria_estatico(i + 1, j - 1);
            incrementa_se_pixel_tem_automata(imagem, ponto_direita_cima, &automatas_vizinhos);

            Ponto ponto_abaixo = Ponto_cria_estatico(i, j + 1);
            incrementa_se_pixel_tem_automata(imagem, ponto_abaixo, &automatas_vizinhos);

            Ponto ponto_acima = Ponto_cria_estatico(i, j - 1);
            incrementa_se_pixel_tem_automata(imagem, ponto_acima, &automatas_vizinhos);

            Ponto ponto_atual = Ponto_cria_estatico(i, j);
            imagem->pixel[i][j] = nova_cor_celula_atual(imagem, ponto_atual, automatas_vizinhos);
        }
    }
}

int random_com_range(int min, int max) {
    return rand() % (max - min + 1) + min;
}

void setup_Conway_Game_of_Life(PPM* imagem) {
    int grupos = 0;
    int i, j;
    for (i = 0; i < imagem->cabecalho->tamanho->altura; i++)
        for (j = 0; j < imagem->cabecalho->tamanho->largura; j++) {
            int max_random = imagem->cabecalho->tamanho->altura * imagem->cabecalho->tamanho->largura / 30;
            int random_number = random_com_range(0, max_random);
            if (random_number < 6) {
                grupos++;
                imagem->pixel[i][j] = _cor_preto;
                switch (random_number) {
                    case 1:
                        desenha_ponto(imagem, Ponto_cria_estatico(i - 1, j));
                        desenha_ponto(imagem, Ponto_cria_estatico(i + 1, j));
                        desenha_ponto(imagem, Ponto_cria_estatico(i, j - 1));
                        desenha_ponto(imagem, Ponto_cria_estatico(i, j + 1));
                        break;
                    case 2:
                        desenha_ponto(imagem, Ponto_cria_estatico(i + 1, j));
                        desenha_ponto(imagem, Ponto_cria_estatico(i + 1, j + 1));
                        desenha_ponto(imagem, Ponto_cria_estatico(i, j + 1));
                        break;
                    case 3:
                        desenha_ponto(imagem, Ponto_cria_estatico(i + 1, j));
                        desenha_ponto(imagem, Ponto_cria_estatico(i + 1, j + 1));
                        desenha_ponto(imagem, Ponto_cria_estatico(i, j + 1));
                        desenha_ponto(imagem, Ponto_cria_estatico(i + 2, j + 2));
                        desenha_ponto(imagem, Ponto_cria_estatico(i + 2, j + 2));
                        desenha_ponto(imagem, Ponto_cria_estatico(i + 2, j + 3));
                        desenha_ponto(imagem, Ponto_cria_estatico(i + 3, j + 2));
                        desenha_ponto(imagem, Ponto_cria_estatico(i + 3, j + 3));
                        break;
                    case 4:
                        desenha_ponto(imagem, Ponto_cria_estatico(i + 1, j));
                        desenha_ponto(imagem, Ponto_cria_estatico(i, j + 1));
                        desenha_ponto(imagem, Ponto_cria_estatico(i + 1, j + 2));
                        desenha_ponto(imagem, Ponto_cria_estatico(i + 2, j + 2));
                        desenha_ponto(imagem, Ponto_cria_estatico(i + 3, j + 2));
                        desenha_ponto(imagem, Ponto_cria_estatico(i + 4, j + 2));
                        desenha_ponto(imagem, Ponto_cria_estatico(i + 4, j + 3));
                        break;
                    case 5:
                        desenha_ponto(imagem, Ponto_cria_estatico(i, j + 2));
                        desenha_ponto(imagem, Ponto_cria_estatico(i, j + 3));
                        desenha_ponto(imagem, Ponto_cria_estatico(i, j + 5));
                        desenha_ponto(imagem, Ponto_cria_estatico(i + 1, j + 1));
                        desenha_ponto(imagem, Ponto_cria_estatico(i - 1, j + 1));
                        desenha_ponto(imagem, Ponto_cria_estatico(i + 2, j + 2));
                        desenha_ponto(imagem, Ponto_cria_estatico(i - 2, j + 2));
                        desenha_ponto(imagem, Ponto_cria_estatico(i + 2, j + 3));
                        desenha_ponto(imagem, Ponto_cria_estatico(i - 2, j + 3));
                        desenha_ponto(imagem, Ponto_cria_estatico(i + 1, j + 4));
                        desenha_ponto(imagem, Ponto_cria_estatico(i - 1, j + 4));
                        desenha_ponto(imagem, Ponto_cria_estatico(i, j + 5));
                        break;
                }
            }
        }
    printf("%d grupos\n", x);
}

int main() {
    srand((unsigned)time(NULL));
    Dimensao2D tamanho = Dimensao2D_cria_estatico(1000, 1000);
    int canal = 255;
    PPM* imagem = PPM_cria_com_dimensoes(tamanho, canal, _cor_branco);
    setup_Conway_Game_of_Life(imagem);
    grava("img/init.ppm", imagem);
    int i = clock();
    int x;
    for (x = 0; x < 6000; x++) {
        // printf("%d\n", x+1);
        conwayGame_of_Life(imagem);
        // sleep(1);
    }
    grava("img/CGoL.ppm", imagem);
    libera_ppm(imagem);
    printf("%d\n", (clock() - i) / CLOCKS_PER_SEC);
    return 0;
}
