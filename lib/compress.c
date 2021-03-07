#include "ppmlib.h"
#include <stdlib.h>
#include <stdio.h>

void ppmTodppm(char fname[],ppm img){
	listacor a = cria_listacor();
	int i,j,ind;
	int rep=0;
	rgb cor=img->cor[0][0];
	
	for(i=0;i<img->cab->altura;i++)
		for(j=0;j<img->cab->largura;j++)
			insere_listacor_norepeat(a,img->cor[i][j]);

	FILE *arq = fopen(fname,"w");
	fprintf(arq, "%d %d %d\n", img->cab->altura,img->cab->largura,a->n);
	nocor *per=a->ini;
	while(per!=NULL){
		fprintf(arq, "%d ", rgb2num(per->cor));
		per=per->prox;
	}
	fprintf(arq, "\n");

	for(i=0;i<img->cab->altura;i++){
		for(j=0;j<img->cab->largura;j++){
			if(corcmp(img->cor[i][j],cor))
				rep++;
			else{
				ind = listacor_buscaIndice(a,cor);
				fprintf(arq,"%d %d ",rep,ind);
				rep=1;
				cor=img->cor[i][j];
			}
		}
	}
	ind = listacor_buscaIndice(a,cor);
	fprintf(arq,"%d %d ",rep,ind);
	fclose(arq);
	libera_listacor(a);
}

ppm dppmToppm(char fname[]){
	ppm img = ppm_malloc();
	img->cab->max=255;
	int ncor,i=0,j=0,k=0,l,lim,qtd,ind;
	FILE *arq = fopen(fname,"r");
	fscanf(arq,"%d %d %d",&img->cab->altura,&img->cab->largura,&ncor);
	int *dicio = (int*)malloc(sizeof(int)*ncor);
	img->cor=rgb_malloc(img->cab);
	for(l=0;l<ncor;l++)
		fscanf(arq,"%d",&dicio[l]);
	lim=img->cab->altura*img->cab->largura;
	while(k<lim){
		fscanf(arq,"%d %d",&qtd,&ind);
		for(l=0;l<qtd;l++){
			img->cor[i][j]=num2rgb(dicio[ind]);
			j++;
			if(j>=img->cab->largura){
				j=0;
				i++;
			}
		}
		k+=qtd;
	}
	free(dicio);
	fclose(arq);
	return img;
}


void cria_ramos(int x, int y, qt *ramo, qt ***raizes, ppm img){

}

void cria_raizes(qt ***raizes, ppm img, int x, int y){
	qt *raiz = cria_raiz_qt(x,y);
	raizes[x][y]=raiz;
	if(corcmp(img->cor[x][y],img->cor[x][y-1])){
		if(y-1>0 && raizes[x][y-1]==NULL){
				qt *r=cria_ramo_qt(x, y-1, NULL, raiz, NULL, NULL);
				raizes[x][y-1]=raiz;
				cria_ramos(x,y-1,r,raizes,img);
		}
		else{
			if(raizes[x][y-1]==raizes[x][y]){

			}
			else{
				if()
			}
		}
	}
	if(y+1<img->cab->altura && raizes[x][y+1]==NULL){
		if(img->cor[x][y]==raizes[x][y+1]){
			qt *r=cria_ramo_qt(x, y+1, NULL, raiz, NULL, NULL);
			raizes[x][y+1]=raiz;
			cria_ramos(x,y+1,r,raizes,img);
		}
	}
	if(x-1>0 && raizes[x-1][y]==NULL){
		if(img->cor[x][y]==raizes[x-1][y]){
			qt *r=cria_ramo_qt(x-1, y, NULL, raiz, NULL, NULL);
			raizes[x-1][y]=raiz;
			cria_ramos(x-1,y,r,raizes,img);
		}
	}
	if(x+1<img->cab->largura && raizes[x+1][y]==NULL){
		if(img->cor[x][y]==raizes[x+1][y]){
			qt *r=cria_ramo_qt(x+1, y, NULL, raiz, NULL, NULL);
			raizes[x+1][y]=raiz;
			cria_ramos(x+1,y,r,raizes,img);
		}
	}
}

void ppmTorppm(char fname[], ppm img){
	int mx=img->cab->altura/2;
	int my=img->cab->largura/2;
	int i,j;
	qt ***raizes = (qt***)malloc(sizeof(qt**)*img->cab->altura);
	for(i=0;i<img->cab->altura;i++){
		raizes[i]=(qt**)malloc(sizeof(qt*)*img->cab->largura);
		for(j=0;j<img->cab->largura){
			raizes[i][j]=NULL;
		}
	}
	cria_qts(raizes,img,mx,my);
}

ppm rppmToppm(char fname[]){
	ppm img;
	return img;
}