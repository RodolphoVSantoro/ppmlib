#include "lib/ppmlib.h"
#include "lib/arq.h"
#include <string.h>

double avgr(ppm img){
	int i,j;
	double avg,n=0;
	for(i=0;i<img->cab->altura;i++){
		for(j=0;j<img->cab->largura;j++){
			avg+=img->cor[i][j].r;
			n+=1.0;
		}
	}
	return avg/n;
}

int main()
{
	system("ls imgs/Resultados > tmp/imagens");
	arquivo imagens = leitura_arq("tmp/imagens");
	int i;
	FILE *res = fopen("tmp/res.txt","w");
	ppm img;
	double media;
	char s[200];
	for(i=0;i<imagens.linhas;i++){
		sprintf(s,"convert 'imgs/Resultados/%s' -compress none 'imgs/%s.ppm'",imagens.linha[i],imagens.linha[i]);
		system(s);
		sprintf(s,"imgs/%s.ppm",imagens.linha[i]);
		img=leitura(s);
		media=avgr(img);
		libera_ppm(img);
		printf("media %d\n", i+1);
		fprintf(res, "%s - %lf\n", imagens.linha[i], media);
		sprintf(s,"rm 'imgs/%s.ppm'",imagens.linha[i]);
		system(s);
	}
	fclose(res);
	libera_arq(imagens);
	return 0;
}