#include <stdio.h>
#include <stdlib.h>

#include "arq.h"
#include "ppmlib.h"

static FILE *fopen_s(char fname[], char modo[]) {
    FILE *arq = fopen(fname, modo);
    if (arq == NULL) {
        printf("Falha ao abrir o arquivo %s\n", fname);
        exit(1);
    }
    return arq;
}

ppm decomp(ppm img, bool r, bool g, bool b) {
    int i, j;
    ppm imgdec = ppm_malloc();
    imgdec->cab = copia_cab(img->cab);
    imgdec->cor = rgb_malloc(imgdec->cab);
    for (i = 0; i < imgdec->cab->altura; i++) {
        for (j = 0; j < imgdec->cab->largura; j++) {
            if (r == true)
                imgdec->cor[i][j].r = img->cor[i][j].r;
            else
                imgdec->cor[i][j].r = 0;
            if (g == true)
                imgdec->cor[i][j].g = img->cor[i][j].g;
            else
                imgdec->cor[i][j].g = 0;
            if (b == true)
                imgdec->cor[i][j].b = img->cor[i][j].b;
            else
                imgdec->cor[i][j].b = 0;
        }
    }
    return imgdec;
}

ppm gira(ppm img, int graus) {
    int n, i, j, a, b, vezes;
    ppm tmp = ppm_malloc(), res = copia(img);
    tmp->cor = NULL;
    tmp->cab = copia_cab(res->cab);
    if (graus == 0)
        return res;
    vezes = graus / 90;
    vezes = vezes % 4;
    for (n = 0; n < vezes; n++) {
        libera_rgb2d(tmp);
        troca(&tmp->cab->altura, &tmp->cab->largura);
        tmp->cor = rgb_malloc(tmp->cab);
        b = 0;
        for (i = 0; i < tmp->cab->altura; i++) {
            a = tmp->cab->largura - 1;
            for (j = 0; j < tmp->cab->largura; j++) {
                tmp->cor[i][j] = res->cor[a][b];
                a--;
            }
            b++;
        }
        res = copia(tmp);
    }
    libera_ppm(tmp);
    return res;
}

ppm negativo(ppm img) {
    int i, j;
    ppm r = copia(img);
    for (i = 0; i < r->cab->altura; i++) {
        for (j = 0; j < r->cab->largura; j++) {
            r->cor[i][j].r = 255 - img->cor[i][j].r;
            r->cor[i][j].g = 255 - img->cor[i][j].g;
            r->cor[i][j].b = 255 - img->cor[i][j].b;
        }
    }
    return r;
}

ppm BW(ppm img) {
    int i, j;
    int val = 0;
    ppm r = copia(img);
    for (i = 0; i < r->cab->altura; i++) {
        for (j = 0; j < r->cab->largura; j++) {
            val = (img->cor[i][j].r + img->cor[i][j].g + img->cor[i][j].b) / 3;
            r->cor[i][j].r = aprox(val);
            r->cor[i][j].g = aprox(val);
            r->cor[i][j].b = aprox(val);
        }
    }
    return r;
}

ppm BM(ppm img) {
    int i, j;
    int val = 0;
    ppm r = copia(img);
    for (i = 0; i < r->cab->altura; i++) {
        for (j = 0; j < r->cab->largura; j++) {
            val = ((img->cor[i][j].r + img->cor[i][j].g + img->cor[i][j].b) / 3) < 128 ? 0 : 255;
            r->cor[i][j].r = val;
            r->cor[i][j].g = val;
            r->cor[i][j].b = val;
        }
    }
    return r;
}

ppm blur(ppm img, int **ker, int tamanhokernel) {
    int i, j, a, b, n;
    float mediar, mediag, mediab;
    ppm r = ppm_malloc();
    r->cab = copia_cab(img->cab);
    r->cor = rgb_malloc(r->cab);
    for (i = 0; i < r->cab->altura; i++) {
        for (j = 0; j < r->cab->largura; j++) {
            mediar = 0;
            mediag = 0;
            mediab = 0;
            n = 0;
            for (a = -tamanhokernel / 2; a < tamanhokernel / 2; a++) {
                for (b = -tamanhokernel / 2; b < tamanhokernel / 2; b++) {
                    if (i + a >= 0 && i + a < r->cab->altura && j + b >= 0 && j + b < r->cab->largura) {
                        n += ker[a + (tamanhokernel / 2)][b + (tamanhokernel / 2)];
                        mediar += img->cor[i + a][j + b].r * ker[a + (tamanhokernel / 2)][b + (tamanhokernel / 2)];
                        mediag += img->cor[i + a][j + b].g * ker[a + (tamanhokernel / 2)][b + (tamanhokernel / 2)];
                        mediab += img->cor[i + a][j + b].b * ker[a + (tamanhokernel / 2)][b + (tamanhokernel / 2)];
                    }
                }
            }
            r->cor[i][j] = n2rgb((int)(mediar /= n), (int)(mediag /= n), (int)(mediab /= n));
        }
    }
    return r;
}

int **gaussian(int tamanhokernel) {
    int **ker = int_malloc(tamanhokernel, tamanhokernel);
    int i, j;
    for (i = 0; i < tamanhokernel; i++)
        for (j = 0; j < tamanhokernel; j++)
            ker[i][j] = pot(2, (tamanhokernel / 2) + 1 - (modulo(i - (tamanhokernel / 2)) + modulo(j - (tamanhokernel / 2))));
    return ker;
}

ppm blurgauss(ppm img, int tamanhokernel) {
    ppm r;
    int **ker = gaussian(tamanhokernel);
    r = blur(img, ker, tamanhokernel);
    libera_int2d(ker, tamanhokernel);
    return r;
}

int **mint(int tamanhokernel) {
    int **ker = int_malloc(tamanhokernel, tamanhokernel);
    int i, j;
    for (i = 0; i < tamanhokernel; i++)
        for (j = 0; j < tamanhokernel; j++)
            ker[i][j] = 1;
    return ker;
}

ppm blurmint(ppm img, int tamanhokernel) {
    int **ker = mint(tamanhokernel);
    ppm r = blur(img, ker, tamanhokernel);
    libera_int2d(ker, tamanhokernel);
    return r;
}

ppm amplia(ppm imagem, int zoom) {
    printf("2- %d\n", imagem->cab->altura);
    ppm r = ppm_malloc();
    r->cab = copia_cab(imagem->cab);
    r->cab->altura *= zoom;
    r->cab->largura *= zoom;
    r->cor = rgb_malloc(r->cab);
    int i, j, a, b;
    for (i = 0; i < imagem->cab->altura; i++)
        for (j = 0; j < imagem->cab->largura; j++)
            for (a = i * zoom; a < i * zoom + zoom; a++)
                for (b = j * zoom; b < j * zoom + zoom; b++)
                    r->cor[a][b] = imagem->cor[i][j];
    return r;
}

// ppm espelhar(ppm img)
// {
// 	ppm r = cria_ppm(100, 100, verde2);
// 	r->cab = copia_cab(img->cab);
// 	int i, j;
// 	r->cor = rgb_malloc(r->cab);
// 	for (i = 0; i< img->cab->altura; i++)
// 		for (j = 0; j < img->cab->largura; j++)
// 			r->cor[i][j] = img->cor[i][img->cab->largura - j - 1];
// 	return r;
// }

ppm join(ppm img, ppm img2) {
    ppm r = ppm_malloc();
    r->cab = copia_cab(img->cab);
    r->cab->altura = img->cab->altura;
    if (img2->cab->altura > img->cab->altura)
        r->cab->altura = img2->cab->altura;
    r->cab->largura = img->cab->largura + img2->cab->largura;
    r->cor = rgb_malloc(r->cab);
    int i, j;
    for (i = 0; i < r->cab->altura; i++)
        for (j = 0; j < r->cab->largura; j++)
            r->cor[i][j] = preto;
    for (i = 0; i < img->cab->altura; i++)
        for (j = 0; j < img->cab->largura; j++)
            r->cor[i][j] = img->cor[i][j];
    for (i = 0; i < img2->cab->altura; i++)
        for (j = 0; j < img2->cab->largura; j++)
            r->cor[i][j + img->cab->largura] = img2->cor[i][j];
    return r;
}

ppm merge(ppm img, ppm img2) {
    ppm r = ppm_malloc();
    r->cab = copia_cab(img->cab);
    r->cab->altura = img->cab->altura + img2->cab->altura;
    r->cab->largura = img->cab->largura;
    if (img2->cab->largura > img->cab->largura)
        r->cab->largura = img2->cab->largura;
    r->cor = rgb_malloc(r->cab);
    int i, j;
    for (i = 0; i < r->cab->altura; i++)
        for (j = 0; j < r->cab->largura; j++)
            r->cor[i][j] = preto;
    for (i = 0; i < img->cab->altura; i++)
        for (j = 0; j < img->cab->largura; j++)
            r->cor[i][j] = img->cor[i][j];
    for (i = 0; i < img2->cab->altura; i++)
        for (j = 0; j < img2->cab->largura; j++)
            r->cor[i + img->cab->altura][j] = img2->cor[i][j];
    return r;
}

ppm overlay(ppm img, ppm img2) {
    ppm re = ppm_malloc();
    re->cab = copia_cab(img->cab);
    if (re->cab->altura < img2->cab->altura)
        re->cab->altura = img2->cab->altura;
    if (re->cab->largura < img2->cab->largura)
        re->cab->largura = img2->cab->largura;
    re->cor = rgb_malloc(re->cab);
    int i, j;
    int n, r, g, b;
    for (i = 0; i < re->cab->altura; i++)
        for (j = 0; j < re->cab->largura; j++) {
            n = r = g = b = 0;
            if (i < img->cab->altura && j < img->cab->largura) {
                n++;
                r = img->cor[i][j].r;
                g = img->cor[i][j].g;
                b = img->cor[i][j].b;
            }
            if (i < img2->cab->altura && j < img2->cab->largura) {
                n++;
                r += img2->cor[i][j].r;
                g += img2->cor[i][j].g;
                b += img2->cor[i][j].b;
            }
            re->cor[i][j] = n == 0 ? preto : n2rgb(r / n, g / n, b / n);
        }
    return re;
}

void grava_decomp(char fname[], ppm img, bool r, bool g, bool b) {
    FILE *arq = fopen_s(fname, "w");
    int i, j;
    fprintf(arq, "P3\n%d %d %d\n", img->cab->largura, img->cab->altura, img->cab->max);
    for (i = 0; i < img->cab->altura; i++) {
        for (j = 0; j < img->cab->largura; j++) {
            if (r == true)
                fprintf(arq, "%d ", img->cor[i][j].r);
            else
                fprintf(arq, "%d ", 0);
            if (g == true)
                fprintf(arq, "%d ", img->cor[i][j].g);
            else
                fprintf(arq, "%d ", 0);
            if (b == true)
                fprintf(arq, "%d\n", img->cor[i][j].b);
            else
                fprintf(arq, "%d\n", 0);
        }
    }
    fclose(arq);
    arq = NULL;
}

void grava_gira(char fname[], ppm img, int graus) {
    ppm gir = gira(img, graus);
    grava(fname, gir);
    libera_ppm(gir);
}

void grava_negativo(char fname[], ppm img) {
    FILE *arq = fopen_s(fname, "w");
    int i, j;
    fprintf(arq, "P3\n%d %d %d\n", img->cab->largura, img->cab->altura, img->cab->max);
    for (i = 0; i < img->cab->altura; i++)
        for (j = 0; j < img->cab->largura; j++)
            fprintf(arq, "%d %d %d\n ", 255 - img->cor[i][j].r, 255 - img->cor[i][j].g, 255 - img->cor[i][j].b);
    fclose(arq);
    arq = NULL;
}

void grava_BW(char fname[], ppm img) {
    FILE *arq = fopen_s(fname, "w");
    int i, j;
    int val = 0;
    fprintf(arq, "P3\n%d %d %d\n", img->cab->largura, img->cab->altura, img->cab->max);
    for (i = 0; i < img->cab->altura; i++)
        for (j = 0; j < img->cab->largura; j++) {
            val = aprox((img->cor[i][j].r + img->cor[i][j].g + img->cor[i][j].b) / 3);
            fprintf(arq, "%d %d %d\n ", val, val, val);
        }
    fclose(arq);
    arq = NULL;
}

void grava_BM(char fname[], ppm img) {
    FILE *arq = fopen_s(fname, "w");
    int i, j;
    int val = 0;
    fprintf(arq, "P3\n%d %d %d\n", img->cab->largura, img->cab->altura, img->cab->max);
    for (i = 0; i < img->cab->altura; i++)
        for (j = 0; j < img->cab->largura; j++) {
            val = ((img->cor[i][j].r + img->cor[i][j].g + img->cor[i][j].b) / 3) < 128 ? 0 : 255;
            ;
            fprintf(arq, "  %d %d %d \n ", val, val, val);
        }
    fclose(arq);
    arq = NULL;
}

void grava_blur(char fname[], ppm img, int **ker, int tamanhokernel) {
    FILE *arq = fopen_s(fname, "w");
    int i, j, a, b, n, k;
    rgb c;
    float mediar, mediag, mediab;
    fprintf(arq, "P3\n%d %d %d\n", img->cab->largura, img->cab->altura, img->cab->max);
    for (i = 0; i < img->cab->altura; i++) {
        for (j = 0; j < img->cab->largura; j++) {
            mediar = 0;
            mediag = 0;
            mediab = 0;
            n = 0;
            for (a = -tamanhokernel / 2; a < tamanhokernel / 2; a++) {
                for (b = -tamanhokernel / 2; b < tamanhokernel / 2; b++) {
                    if (i + a >= 0 && i + a < img->cab->altura && j + b >= 0 && j + b < img->cab->largura) {
                        c = img->cor[i + a][j + b];
                        k = ker[a + (tamanhokernel / 2)][b + (tamanhokernel / 2)];
                        n += k;
                        mediar += c.r * k;
                        mediag += c.g * k;
                        mediab += c.b * k;
                    }
                }
            }
            fprintf(arq, " %d %d %d\n", (int)(mediar /= n), (int)(mediag /= n), (int)(mediab /= n));
        }
    }
}

void grava_blurgauss(char fname[], ppm img, int tamanhokernel) {
    int **ker = gaussian(tamanhokernel);
    grava_blur(fname, img, ker, tamanhokernel);
    libera_int2d(ker, tamanhokernel);
}

void grava_blurmint(char fname[], ppm img, int tamanhokernel) {
    int **ker = mint(tamanhokernel);
    grava_blur(fname, img, ker, tamanhokernel);
    libera_int2d(ker, tamanhokernel);
}

void grava_espelhado(char fname[], ppm img) {
    FILE *arq = fopen_s(fname, "w");
    int i, j;
    rgb cor;
    fprintf(arq, "P3\n%d %d %d\n", img->cab->largura, img->cab->altura, img->cab->max);
    for (i = 0; i < img->cab->altura; i++)
        for (j = 0; j < img->cab->largura; j++) {
            cor = img->cor[i][img->cab->largura - j - 1];
            fprintf(arq, " %d %d %d \n", cor.r, cor.g, cor.b);
        }
    fclose(arq);
    arq = NULL;
}

void mod_decomp(ppm *img, bool r, bool g, bool b) {
    int i, j;
    for (i = 0; i < (*img)->cab->altura; i++)
        for (j = 0; j < (*img)->cab->largura; j++) {
            if (r == false)
                (*img)->cor[i][j].r = 0;
            if (g == false)
                (*img)->cor[i][j].g = 0;
            if (b == false)
                (*img)->cor[i][j].b = 0;
        }
}

void mod_gira(ppm *img, int graus) {
    ppm tmp = gira((*img), graus);
    libera_ppm((*img));
    *img = tmp;
}

void mod_negativo(ppm *img) {
    int i, j;
    for (i = 0; i < (*img)->cab->altura; i++)
        for (j = 0; j < (*img)->cab->largura; j++) {
            (*img)->cor[i][j].r = 255 - (*img)->cor[i][j].r;
            (*img)->cor[i][j].g = 255 - (*img)->cor[i][j].g;
            (*img)->cor[i][j].b = 255 - (*img)->cor[i][j].b;
        }
}

void mod_BW(ppm *img) {
    int i, j;
    double val;
    for (i = 0; i < (*img)->cab->altura; i++)
        for (j = 0; j < (*img)->cab->largura; j++) {
            val = ((*img)->cor[i][j].r + (*img)->cor[i][j].g + (*img)->cor[i][j].b) / 3;
            (*img)->cor[i][j].r = aprox(val);
            (*img)->cor[i][j].g = aprox(val);
            (*img)->cor[i][j].b = aprox(val);
        }
}

void mod_BM(ppm *img) {
    int i, j, c;
    double val;
    for (i = 0; i < (*img)->cab->altura; i++)
        for (j = 0; j < (*img)->cab->largura; j++) {
            val = ((*img)->cor[i][j].r + (*img)->cor[i][j].g + (*img)->cor[i][j].b) / 3;
            c = val >= 128 ? 255 : 0;
            (*img)->cor[i][j] = n2rgb(c, c, c);
        }
}

void mod_blurgauss(ppm *img, int tamanhokernel) {
    int **ker = gaussian(tamanhokernel);
    ppm tmp = blur(*img, ker, tamanhokernel);
    libera_ppm(*img);
    *img = tmp;
}

void mod_blurmint(ppm *img, int tamanhokernel) {
    int **ker = mint(tamanhokernel);
    ppm tmp = blur(*img, ker, tamanhokernel);
    libera_ppm(*img);
    *img = tmp;
}

// void mod_espelha(ppm *img)
// {
// 	ppm tmp = espelhar(*img);
// 	libera_ppm(*img);
// 	*img = tmp;
// }