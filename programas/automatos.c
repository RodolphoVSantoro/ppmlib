#include "ppmlib.h"
#include <time.h>
#include <stdio.h>

bool lim(ppm img, ponto p)
{
	return (p.x > 0 && p.x < img.cab.altura && p.y > 0 && p.y < img.cab.largura);
}

bool rgbcmp(rgb c1, rgb c2)
{
	return (c1.r == c2.r && c1.g == c2.g && c1.b == c2.b);
}

void conG_o_L(ppm img)
{
	int i, j;
	int a;
	for(i = 0;i < img.cab.altura; i++)
	{
		for(j = 0; j < img.cab.largura; j++)
		{
			a=0;
			if(lim(img,cria_ponto(i-1,j)))
				if(rgbcmp(img.cor[i-1][j],preto))
					a++;
			if(lim(img,cria_ponto(i-1,j+1)))
				if(rgbcmp(img.cor[i-1][j+1],preto))
					a++;
			if(lim(img,cria_ponto(i-1,j-1)))
				if(rgbcmp(img.cor[i-1][j-1],preto))
					a++;
			if(lim(img,cria_ponto(i+1,j)))
				if(rgbcmp(img.cor[i+1][j],preto))
					a++;
			if(lim(img,cria_ponto(i+1,j+1)))
				if(rgbcmp(img.cor[i+1][j+1],preto))
					a++;
			if(lim(img,cria_ponto(i+1,j-1)))
				if(rgbcmp(img.cor[i+1][j-1],preto))
					a++;
			if(lim(img,cria_ponto(i,j+1)))
				if(rgbcmp(img.cor[i][j+1],preto))
					a++;
			if(lim(img,cria_ponto(i,j-1)))
				if(rgbcmp(img.cor[i][j-1],preto))
					a++;
			if(rgbcmp(img.cor[i][j],preto))
			{
				if(a<2)
					img.cor[i][j] = branco;
				else
					if(a>3)
						img.cor[i][j] = branco;
			}
			else
				if(a==3)
					img.cor[i][j] = preto;
		}
	}
}

void setup_G_o_L(ppm img)
{
	int i, j, r, x=0;
	for(i = 0;i<img.cab.altura;i++)
		for(j = 0;j<img.cab.largura;j++)
		{
			r = rand() % (int)(img.cab.altura*img.cab.largura/30 + 1);
			if(r<6){
				x++;
				img.cor[i][j] = preto;
				switch(r){
					case 1:
						desPonto(img, cria_ponto(i-1,j));
						desPonto(img, cria_ponto(i+1,j));
						desPonto(img, cria_ponto(i,j-1));
						desPonto(img, cria_ponto(i,j+1));
					break;
					case 2:
						desPonto(img, cria_ponto(i+1,j));
						desPonto(img, cria_ponto(i+1,j+1));
						desPonto(img, cria_ponto(i,j+1));
					break;
					case 3:
						desPonto(img, cria_ponto(i+1,j));
						desPonto(img, cria_ponto(i+1,j+1));
						desPonto(img, cria_ponto(i,j+1));
						desPonto(img, cria_ponto(i+2,j+2));
						desPonto(img, cria_ponto(i+2,j+2));
						desPonto(img, cria_ponto(i+2,j+3));
						desPonto(img, cria_ponto(i+3,j+2));
						desPonto(img, cria_ponto(i+3,j+3));
					break;
					case 4:
						desPonto(img, cria_ponto(i+1,j));
						desPonto(img, cria_ponto(i,j+1));
						desPonto(img, cria_ponto(i+1,j+2));
						desPonto(img, cria_ponto(i+2,j+2));
						desPonto(img, cria_ponto(i+3,j+2));
						desPonto(img, cria_ponto(i+4,j+2));
						desPonto(img, cria_ponto(i+4,j+3));
					break;
					case 5:
						desPonto(img, cria_ponto(i,j+2));
						desPonto(img, cria_ponto(i,j+3));
						desPonto(img, cria_ponto(i,j+5));
						desPonto(img, cria_ponto(i+1,j+1));
						desPonto(img, cria_ponto(i-1,j+1));
						desPonto(img, cria_ponto(i+2,j+2));
						desPonto(img, cria_ponto(i-2,j+2));
						desPonto(img, cria_ponto(i+2,j+3));
						desPonto(img, cria_ponto(i-2,j+3));
						desPonto(img, cria_ponto(i+1,j+4));
						desPonto(img, cria_ponto(i-1,j+4));
						desPonto(img, cria_ponto(i,j+5));
					break;
				}
			}
		}
	printf("%d grupos\n", x);
}

int main()
{
	srand((unsigned)time(NULL));
	ppm img = cria_ppm(1080,1920,branco);
	setup_G_o_L(img);
	grava("imgs/init.ppm",img);
	int i = clock();
	int x;
	for(x=0;x<6000;x++){
		//printf("%d\n", x+1);
		conG_o_L(img);
		//sleep(1);
	}
	grava("imgs/CGOL.ppm", img);
	libera_ppm(img);
	printf("%d\n", (clock()-i)/CLOCKS_PER_SEC);
	return 0;
}