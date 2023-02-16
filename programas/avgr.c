#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../libppm/arq.h"
#include "../libppm/libppm.h"

double vermelho_medio(PPM* imagem) {
    double avg, n = 0;
    for (int i = 0; i < imagem->cabecalho->tamanho->altura; i++) {
        for (int j = 0; j < imagem->cabecalho->tamanho->largura; j++) {
            avg += imagem->pixel[i][j].red;
            n += 1.0;
        }
    }
    return avg / n;
}

int main() {
    system("ls imgs/Resultados > tmp/imagens");
    arquivo imagens = leitura_arq("tmp/imagens");
    FILE* arquivo_resultados = fopen("tmp/res.txt", "w");
    if (arquivo_resultados == NULL) {
        printf("Erro ao abrir arquivo de resultados");
        return 1;
    }
    PPM* img;
    double media;
    char string[200];
    for (int i = 0; i < imagens.linhas; i++) {
        sprintf(string, "convert 'imgs/Resultados/%s' -compress none 'imgs/%s.ppm'",
                imagens.linha[i], imagens.linha[i]);
        system(string);
        sprintf(string, "imgs/%s.ppm", imagens.linha[i]);
        img = PPM_leitura(string);
        media = vermelho_medio(img);
        PPM_libera(img);
        printf("media %d\n", i + 1);
        fprintf(arquivo_resultados, "%s - %lf\n", imagens.linha[i], media);
        sprintf(string, "rm 'imgs/%s.ppm'", imagens.linha[i]);
        system(string);
    }
    fclose(arquivo_resultados);
    libera_arq(imagens);
    return 0;
}