#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "ppmlib.h"

static FILE* fopen_s(char fname[], char modo[])
{
	FILE *arq = fopen(fname,modo);
	if (arq == NULL)
	{
		printf("Falha ao abrir o arquivo %s\n", fname);
		exit(1);
	}
	return arq;
}

void strcop(char *dest, char *ori){
	int i;
	for(i=0;ori[i]!=0;i++)
		dest[i]=ori[i];
	dest[i]=0;
}

int strcomp(char *s1, char *s2)
{
	int i;
	for(i=0;s1[i]!=0 && s2[i]!=0;i++)
	{
		if(s1[i]<s2[i]) return -1;
		else if(s1[i]>s2[i]) return 1;
	}
	if(s1[i]==s2[i]) return 0;
	else if(s2[i]!=0) return -1;
	else return 1;
}

int aprox(float val)
{
	int x = val;
	if (val >= 0)
		return val - x >= 0.5 ? x + 1 : x;
	else
		return val - x <= 0.5 ? x - 1 : x;
}

int modulo(int n)
{
	return n >= 0 ? n : -n;
}

void troca(int *a, int *b)
{
	*a = *a + *b;
	*b = *a - *b;
	*a = *a - *b;
}

float seno(float graus)
{
	return sin(graus2rad(graus));
}

float coseno(float graus)
{
	return cos(graus2rad(graus));
}

int pot(int x, int e)
{
	int r = 1, i;
	for (i = 0; i < e; i++)
		r *= x;
	return r;
}

rgb n2rgb(unsigned char r, unsigned char g, unsigned char b)
{
	rgb pixel;
	pixel.r = r;
	pixel.g = g;
	pixel.b = b;
	return pixel;
}

rgb num2rgb(int n){
	int r = n%256;
	n=n/256;
	int g = n%256;
	n=n/256;
	int b = n%256;
	n=n/256;
	return n2rgb(r,g,b);
}

int rgb2num(rgb cor){
	return cor.r+256*(cor.g+256*cor.b);
}


cppm cab_malloc(int altura, int largura, int max, char key[]){
	cppm cab = (cppm)malloc(sizeof(struct cabecalhoPPM));
	cab->altura=altura;
	cab->largura=largura;
	cab->max=max;
	strcpy(cab->key,key);
	return cab;
}

ppm ppm_malloc(){
	ppm r=(ppm)malloc(sizeof(struct PPM));
	if(r==NULL){
		printf("Erro ao alocar imagem\n");
		exit(1);
	}
	r->cab=cab_malloc(0,0,255,"P3");
	if(r->cab==NULL){
		printf("Erro ao alocar imagem\n");
		exit(1);
	}
	r->cor=NULL;
	return r;
}

ppm copia(ppm img)
{
	int i, j;
	ppm r=(ppm)malloc(sizeof(struct PPM));
	r->cab=(cppm)malloc(sizeof(struct cabecalhoPPM));
	r->cab->altura = img->cab->altura;
	r->cab->largura = img->cab->largura;
	r->cab->max = img->cab->max;
	strcop(r->cab->key, img->cab->key);
	r->cor = rgb_malloc(r->cab);
	for (i = 0; i < r->cab->altura; i++)
		for (j = 0; j < r->cab->largura; j++)
			r->cor[i][j] = img->cor[i][j];
	return r;
}

rgb **rgb_malloc(cppm cab)
{
	rgb **cor;
	int i;
	cor = (rgb**)malloc(cab->altura*sizeof(rgb*));
	if (cor == NULL)
	{
		printf("Sem memoria\n");
		exit(1);
	}
	for (i = 0; i<cab->altura; i++)
	{
		cor[i] = (rgb*)malloc(cab->largura*sizeof(rgb));
		if (cor[i] == NULL)
		{
			printf("Sem memoria\n");
			exit(1);
		}
	}
	return cor;
}

int **int_malloc(int altura, int largura)
{
	int i;
	int **p = (int**)malloc(sizeof(int*)*altura);
	if(p == NULL)
	{
		printf("Sem memoria\n");
		exit(1);
	}
	for (i = 0; i < altura; i++)
	{
		p[i] = (int*)malloc(sizeof(int)*largura);
		if (p[i] == NULL)
		{
			printf("Sem memoria\n");
			exit(1);
		}
	}
	return p;
}

void libera_int2d(int **mat, int altura)
{
	int i;
	for(i=0;i<altura;i++){
		free(mat[i]);
		mat[i]=NULL;
	}
	free(mat);
}

cppm copia_cab(cppm cab)
{
	cppm cop=(cppm)malloc(sizeof(struct cabecalhoPPM));
	cop->altura = cab->altura;
	cop->largura = cab->largura;
	cop->max = cab->max;
	strcop(cop->key,cab->key);
	return cop;
}

void libera_ppm(ppm img)
{
	libera_rgb2d(img);
	free(img->cab);
	img->cab=NULL;
	free(img);
}

void libera_rgb2d(ppm img){
	if(img->cor!=NULL){
		int i;
		for (i = 0; i<img->cab->altura; i++)
		{
			free(img->cor[i]);
			img->cor[i] = NULL;
		}
		free(img->cor);
		img->cor = NULL;
	}
}

arvb *cria_arvb(){
	return NULL;
}

arvb *cria_folha(int x){
	arvb *n = (arvb*)malloc(sizeof(arvb));
	n->x=x;
	n->e=n->d=NULL;
	return n;
}

arvb *insere_arvb_norepeat(arvb *r, int x){
	if(r==NULL) return cria_folha(x);
	if(x>r->x) r->d=insere_arvb_norepeat(r->d, x);
	if(x<r->x) r->e=insere_arvb_norepeat(r->d, x);
	return r;
}

arvb *libera_arvb(arvb *r){
	if(r!=NULL){
		r->e=libera_arvb(r->e);
		r->d=libera_arvb(r->d);
		free(r);
	}
	return NULL;
}

void imp_arvbin_preord(arvb *r){
	if(r!=NULL){
		printf("<%d ", r->x);
		imp_arvbin_preord(r->e);
		imp_arvbin_preord(r->d);
		printf(">");
	}
	if (r==NULL){
		printf("<>");
	}
}

int arvb_qtdnodes(arvb *r){
	if(r!=NULL){
		return 1+arvb_qtdnodes(r->e)+arvb_qtdnodes(r->d);
	}
	else return 0;
}

ppm leitura(char fname[])
{
	ppm img=ppm_malloc();
	int r, g, b, i, j, c;
	FILE *arq = fopen_s(fname, "r");
	fscanf(arq, "%s", img->cab->key);
	if (strcomp(img->cab->key, "P3") != 0)
	{
		printf("O arquivo nao e um ppm");
		fclose(arq);
		arq = NULL;
		exit(1);
	}
	while((c=fgetc(arq))=='#' || c==' ' || c=='\n')
		if(c == '#')
			while((c=fgetc(arq))!='\n' && c!=EOF);
		else{
			while(((c=fgetc(arq))=='\n' || c == ' ') && c!=EOF);
			ungetc(c, arq);
		}
	ungetc(c, arq);
	fscanf(arq, "%d %d", &img->cab->largura, &img->cab->altura);
	fscanf(arq, "%d", &img->cab->max);
	img->cor = rgb_malloc(img->cab);
	for (i = 0; i<img->cab->altura; i++)
	{
		for (j = 0; j<img->cab->largura; j++)
		{
			fscanf(arq, "%d", &r);
			fscanf(arq, "%d", &g);
			fscanf(arq, "%d", &b);
			img->cor[i][j].r = r;
			img->cor[i][j].g = g;
			img->cor[i][j].b = b;
		}
	}
	fclose(arq);
	arq = NULL;
	return img;
}

void grava(char fname[], ppm img)
{
	FILE *arq = fopen_s(fname, "w");
	int i, j;
	fprintf(arq, "P3\n#Created by ERR's ppmlib\n%d %d %d\n", img->cab->largura, img->cab->altura, img->cab->max);
	for (i = 0; i<img->cab->altura; i++)
		for (j = 0; j<img->cab->largura; j++)
			fprintf(arq, "%d %d %d\n", img->cor[i][j].r, img->cor[i][j].g, img->cor[i][j].b);
	fclose(arq);
	arq = NULL;
}

//Manipulacao Vetorial Basica

//pontos
ponto cria_ponto(int x, int y)
{
	ponto p;
	p.x = x;
	p.y = y;
	return p;
}

double distancia(ponto a, ponto b)
{
	return sqrt((float)pot((a.x - b.x), 2) + (float)pot((a.y - b.y), 2));
}

ponto vira(ponto a, ponto b, float graus)
{
	ponto f;
	f.x = a.x + coseno(graus)*(b.x - a.x) + seno(graus)*(a.y - b.y);
	f.y = a.y + coseno(graus)*(b.y - a.y) + seno(graus)*(b.x - a.x);
	return f;
}

ponto midpoint(ponto a, ponto b){
	return cria_ponto((a.x+b.x)/2,(a.y+b.y)/2);
}

/*
interpolacao linear
acha o ponto que divide a linha a->b em 1/ratio vezes
*/
ponto linear_interp(ponto a, ponto b, double ratio){
	return cria_ponto(a.x + (b.x-a.x)*ratio,a.y + (b.y-a.y)*ratio);
}

bool pontocmp(ponto p, ponto q){
	return (p.x==q.x && p.y==q.y);
}

bool corcmp(rgb a, rgb b){
	return (a.r==b.r && a.g==b.g && a.b==b.b);
}

int cores_dif(ppm img){
	int i, j, total=0;
	char *cores = (char*)malloc(sizeof(char)*16777216);
	for(i=0;i<16777215;i++)
		cores[i]=0;
	for(i=0;i<img->cab->altura;i++)
    	for(j=0;j<img->cab->largura;j++)
    		cores[rgb2num(img->cor[i][j])] = 1;
    for(i=0;i<16777216;i++) {
    	total+=cores[i];
	}
	free(cores);
	return total;
}

rgb randcor(){
	rgb cor;
	cor.r=rand()%256;
	cor.g=rand()%256;
	cor.b=rand()%256;
	return cor;
}
