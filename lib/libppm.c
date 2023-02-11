#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ppmlib.h"

static FILE *fopen_s(char fname[], char modo[]) {
    FILE *arquivo = fopen(fname, modo);
    if (arquivo == NULL) {
        printf("Falha ao abrir o arquivo %s\n", fname);
        exit(1);
    }
    return arquivo;
}

void string_copia(char *destino, char *original) {
    int i;
    for (i = 0; original[i] != 0; i++) {
        destino[i] = original[i];
    }
    destino[i] = 0;
}

int string_compara(char *string1, char *string2) {
    int i;
    for (i = 0; string1[i] != 0 && string2[i] != 0; i++) {
        if (string1[i] < string2[i]) {
            return -1;
        } else if (string1[i] > string2[i]) {
            return 1;
        }
    }
    if (string1[i] == string2[i]) {
        return 0;
    } else if (string2[i] != 0) {
        return -1;
    } else {
        return 1;
    }
}

int aproximacao(float valor) {
    int valorTruncado = valor;
    float diferenca = valor - (float)valorTruncado;
    if (valor >= 0) {
        return diferenca >= 0.5 ? valorTruncado + 1 : valorTruncado;
    } else {
        return diferenca <= 0.5 ? valorTruncado - 1 : valorTruncado;
    }
}

int int_valor_absoluto(int n) {
    return n >= 0 ? n : -n;
}

void int_troca(int *a, int *b) {
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
}

float graus_seno(float graus) {
    return sin(graus2rad(graus));
}

float graus_coseno(float graus) {
    return cos(graus2rad(graus));
}

int int_potencia(int base, int expoente) {
    int resultado = 1;
    for (int i = 0; i < expoente; i++) {
        resultado *= base;
    }
    return resultado;
}

rgb rgb_cria(uchar red, uchar green, uchar blue) {
    rgb pixel;
    pixel.red = red;
    pixel.green = green;
    pixel.blue = blue;
    return pixel;
}

rgb int_to_rgb(int numero) {
    int red = numero % 256;
    numero = numero / 256;
    int green = numero % 256;
    numero = numero / 256;
    int blue = numero % 256;
    numero = numero / 256;
    return rgb_cria(red, green, blue);
}

int rgb_to_int(rgb cor) {
    return cor.red + 256 * (cor.green + 256 * cor.blue);
}

PPMHeader PPMHeader_cria(int altura, int largura, int channelRange, BMPKey tipoBMP) {
    PPMHeader cabecalho = (PPMHeader)malloc(sizeof(*cabecalho));
    if (cabecalho == NULL) {
        printf("Erro ao alocar cabecalho\n");
        exit(1);
    }
    cabecalho->tamanho = (Dimensao2D *)malloc(sizeof(*cabecalho->tamanho));
    if (cabecalho->tamanho == NULL) {
        printf("Erro ao alocar cabecalho\n");
        exit(1);
    }

    cabecalho->tamanho->altura = altura;
    cabecalho->tamanho->largura = largura;
    cabecalho->channelRange = channelRange;
    cabecalho->tipoBMP = tipoBMP;
    return cabecalho;
}

PPMHeader PPMHeader_copia(PPMHeader cabecalho_original) {
    PPMHeader cabecalho_novo = PPMHeader_cria(
        cabecalho_original->tamanho->altura,
        cabecalho_original->tamanho->largura,
        cabecalho_original->channelRange,
        cabecalho_original->tipoBMP);
    if (cabecalho_novo == NULL) {
        printf("Erro ao alocar cabecalho\n");
        exit(1);
    }
    return cabecalho_novo;
}

PPMHeader PPMHeader_libera(PPMHeader cabecalho) {
    free(cabecalho->tamanho);
    cabecalho->tamanho = NULL;
    free(cabecalho);
    cabecalho = NULL;
}

BMPKey key_to_string(char *key) {
    if (string_compara(key, "P3") == 0) {
        return Key_PPM;
    } else if (string_compara(key, "P1") == 0) {
        return Key_BW;
    }
    // else if(string_compara(key, "P2") == 0) {
    //	return Key_PGM;
    // }
    else if (string_compara(key, "BM") == 0) {
        return Key_BMP;
    } else {
        printf("Erro ao converter string para key\n");
        exit(1);
    }
}

const char *key_to_string(BMPKey key) {
    switch (key) {
        case Key_PPM:
            return "P3";
        case Key_BM:
            return "P1";
        case Key_BW:
        	return "P2";
        case Key_BMP:
            return "BM";
        default:
            printf("Erro ao converter key para string\n");
            exit(1);
    }
}

PPM ppm_cria() {
    PPM imagem = (PPM)malloc(sizeof(*imagem));
    if (imagem == NULL) {
        printf("Erro ao alocar imagem\n");
        exit(1);
    }

    imagem->cabecalho = cab_malloc(0, 0, 255, Key_PPM);
    if (imagem->cabecalho == NULL) {
        printf("Erro ao alocar imagem\n");
        exit(1);
    }

    imagem->pixel = NULL;

    return imagem;
}

PPM ppm_copia(PPM imagem_original) {
    PPM imagem_nova = (PPM)malloc(sizeof(*imagem_nova));

    imagem_nova->cabecalho = (PPMHeader)malloc(sizeof(*imagem_nova->cabecalho));

    imagem_nova->cabecalho->tamanho = (Dimensao2D *)malloc(sizeof(*imagem_nova->cabecalho->tamanho));
    imagem_nova->cabecalho->tamanho->altura = imagem_original->cabecalho->tamanho->altura;
    imagem_nova->cabecalho->tamanho->largura = imagem_original->cabecalho->tamanho->largura;

    imagem_nova->cabecalho->channelRange = imagem_original->cabecalho->channelRange;

    imagem_nova->cabecalho->tipoBMP = imagem_original->cabecalho->tipoBMP;

    imagem_nova->pixel = rgb_malloc(imagem_nova->cabecalho);

    for (int i = 0; i < imagem_nova->cabecalho->tamanho->altura; i++) {
        memccpy(
            imagem_nova->pixel[i],
            imagem_original->pixel[i],
            imagem_nova->cabecalho->tamanho->largura,
            sizeof(**imagem_nova->pixel));
    }

    return imagem_nova;
}

void libera_ppm(PPM imagem) {
    rgb2d_libera(imagem);
    PPMHeader_libera(imagem->cabecalho);
    imagem->cabecalho = NULL;
    free(imagem);
    imagem = NULL;
}

rgb **rgb2d_malloc(Dimensao2D *tamanho) {
    rgb **Pixel2D = (rgb **)malloc(tamanho->altura * sizeof(*Pixel2D));
    if (Pixel2D == NULL) {
        printf("Falha ao alocar pixels\n");
        exit(1);
    }
    for (int i = 0; i < tamanho->altura; i++) {
        Pixel2D[i] = (rgb *)calloc(tamanho->largura, sizeof(**Pixel2D));
        if (Pixel2D[i] == NULL) {
            printf("Falha ao alocar pixels\n");
            exit(1);
        }
    }
    return Pixel2D;
}

void rgb2d_libera(PPM imagem) {
    if (imagem->pixel == NULL) {
        return;
    }
    for (int i = 0; i < imagem->cabecalho->tamanho->altura; i++) {
        free(imagem->pixel[i]);
        imagem->pixel[i] = NULL;
    }
    free(imagem->pixel);
    imagem->pixel = NULL;
}

int **int2d_malloc(int altura, int largura) {
    int **int2d = (int **)malloc(altura * sizeof(*int2d));
    if (int2d == NULL) {
        printf("Erro ao alocar array 2d de inteiros\n");
        exit(1);
    }
    for (int i = 0; i < altura; i++) {
        int2d[i] = (int *)malloc(sizeof(**int2d) * largura);
        if (int2d[i] == NULL) {
            printf("Erro ao alocar array 2d de inteiros\n");
            exit(1);
        }
    }
    return int2d;
}

void int2d_libera(int **int2d, int altura) {
    for (int i = 0; i < altura; i++) {
        free(int2d[i]);
        int2d[i] = NULL;
    }
    free(int2d);
}

ArvBin *ArvBin_cria() {
    return NULL;
}

ArvBin *folha_cria(int x) {
    ArvBin *novo = (ArvBin *)malloc(sizeof(*novo));
    novo->x = x;
    novo->direita = NULL;
    novo->esquerda = NULL;
    return novo;
}

ArvBin *ArvBin_insere_sem_repeticao(ArvBin *arvore, int x) {
    if (arvore == NULL) {
        return folha_cria(x);
    }
    if (x > arvore->x) {
        arvore->direita = ArvBin_insere_sem_repeticao(arvore->direita, x);
    }
    if (x < arvore->x) {
        arvore->esquerda = ArvBin_insere_sem_repeticao(arvore->direita, x);
    }
    return arvore;
}

ArvBin *ArvBin_libera(ArvBin *arvore) {
    if (arvore != NULL) {
        arvore->esquerda = ArvBin_libera(arvore->esquerda);
        arvore->direita = ArvBin_libera(arvore->direita);
        free(arvore);
    }
    return NULL;
}

void arvore_imprime_pre_ordem(ArvBin *arvore) {
    if (arvore != NULL) {
        printf("<%d ", arvore->x);
        arvore_imprime_pre_ordem(arvore->esquerda);
        arvore_imprime_pre_ordem(arvore->direita);
        printf(">");
    }
    if (arvore == NULL) {
        printf("<>");
    }
}

int ArvBin_quantidade_nodes(ArvBin *arvore) {
    if (arvore != NULL) {
        return 1 + ArvBin_quantidade_nodes(arvore->esquerda) + ArvBin_quantidade_nodes(arvore->direita);
    } else
        return 0;
}

PPM ppm_leitura(char fname[]) {
    PPM imagem = ppm_cria();
    FILE *arquivo = fopen_s(fname, "r");

    const char *tipo = key_to_string(imagem->cabecalho->tipoBMP);
    fscanf(arquivo, "%s", tipo);
    if (string_compare(imagem->cabecalho->tipoBMP, "P3") != 0) {
        printf("O arquivo nao e um ppm");
        fclose(arquivo);
        arquivo = NULL;
        exit(1);
    }

    int c;
    while ((c = fgetc(arquivo)) == '#' || c == ' ' || c == '\n') {
        if (c == '#') {
            while ((c = fgetc(arquivo)) != '\n' && c != EOF)
                ;
        } else {
            while (((c = fgetc(arquivo)) == '\n' || c == ' ') && c != EOF)
                ;
            ungetc(c, arquivo);
        }
    }
    ungetc(c, arquivo);

    fscanf(
        arquivo,
        "%d %d",
        &imagem->cabecalho->tamanho->largura,
        &imagem->cabecalho->tamanho->altura);
    fscanf(arquivo, "%d", &imagem->cabecalho->channelRange);

    imagem->pixel = rgb_malloc(imagem->cabecalho);
    int red, green, blue;
    for (int i = 0; i < imagem->cabecalho->tamanho->altura; i++) {
        for (int j = 0; j < imagem->cabecalho->tamanho->largura; j++) {
            fscanf(arquivo, "%d", &red);
            imagem->pixel[i][j].red = red;
            fscanf(arquivo, "%d", &green);
            imagem->pixel[i][j].green = green;
            fscanf(arquivo, "%d", &blue);
            imagem->pixel[i][j].blue = blue;
        }
    }
    fclose(arquivo);
    arquivo = NULL;
    return imagem;
}

void ppm_grava(char fname[], PPM imagem) {
    FILE *arquivo = fopen_s(fname, "w");
    fprintf(
        arquivo,
        "P3\n#Created by ppmlib\n%d %d %d\n",
        imagem->cabecalho->tamanho->largura,
        imagem->cabecalho->tamanho->altura,
        imagem->cabecalho->channelRange);
    for (int i = 0; i < imagem->cabecalho->tamanho->altura; i++) {
        for (int j = 0; j < imagem->cabecalho->tamanho->largura; j++) {
            fprintf(
                arquivo,
                "%d %d %d\n",
                imagem->pixel[i][j].red,
                imagem->pixel[i][j].green,
                imagem->pixel[i][j].blue);
        }
    }
    fclose(arquivo);
    arquivo = NULL;
}

// Manipulacao Vetorial Basica

// pontos
Ponto cria_ponto(int x, int y) {
    Ponto p;
    p.x = x;
    p.y = y;
    return p;
}

int int_quadrado(int numero) {
    return numero * numero;
}

double ponto2d_distancia(Ponto a, Ponto b) {
    return sqrt(
        (float)int_quadrado(a.x - b.x) +
        (float)int_quadrado(a.y - b.y));
}

Ponto ponto_vira(Ponto a, Ponto b, float graus) {
    Ponto f;
    f.x = a.x + coseno(graus) * (b.x - a.x) + seno(graus) * (a.y - b.y);
    f.y = a.y + coseno(graus) * (b.y - a.y) + seno(graus) * (b.x - a.x);
    return f;
}

Ponto midpoint(Ponto a, Ponto b) {
    return cria_ponto((a.x + b.x) / 2, (a.y + b.y) / 2);
}

/*
interpolacao linear
acha o Ponto que divide a linha a->b em 1/ratio vezes
*/
Ponto linear_interpolation(Ponto a, Ponto b, double ratio) {
    return cria_ponto(a.x + (b.x - a.x) * ratio, a.y + (b.y - a.y) * ratio);
}

bool ponto_compara(Ponto p, Ponto q) {
    return (p.x == q.x && p.y == q.y);
}

bool cor_compara(rgb a, rgb b) {
    return (a.red == b.red && a.green == b.green && a.blue == b.blue);
}

int cores_diferentes(PPM imagem) {
    int total = 0;
    char *cores = (char *)malloc(sizeof(char) * 16777216);
    for (int i = 0; i < 16777215; i++) {
        cores[i] = 0;
    }
    for (int i = 0; i < imagem->cabecalho->tamanho->altura; i++) {
        for (int j = 0; j < imagem->cabecalho->tamanho->largura; j++) {
            int corNumero = rgb2num(imagem->pixel[i][j]);
            cores[corNumero] = 1;
        }
    }
    for (int i = 0; i < 16777216; i++) {
        total += cores[i];
    }
    free(cores);
    return total;
}

rgb cor_aleatoria() {
    rgb cor;
    cor.red = rand() % 256;
    cor.green = rand() % 256;
    cor.blue = rand() % 256;
    return cor;
}
