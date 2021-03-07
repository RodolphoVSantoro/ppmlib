#include "ppmlib.h"

int main()
{
	int al = 1080, la = 1920;
	ppm img = cria_ppm(al,la,verde2);
	ponto c = cria_ponto(al / 2, la / 2);
	desLosangoCorprn(img, c, al*10/12, la*3/4, amarelo);
	desCirculoCorprn(img, c, al*99/324, azul);
	grava_blur("imgs/teste.ppm", img, 8);
	libera_ppm(img);
	return 0;
}