#include "ppmlib.h"
#include <stdlib.h>
#include <stdio.h>

void libera_lista_p2(lista_p2 *l)
{
	free(l);
}

//Lista de Cor
listacor cria_listacor(){
  	listacor l = (listacor)malloc(sizeof(lista_cor));
  	l->fim = NULL;
  	l->ini = NULL;
  	l->n = 0;
  	return l;
}

void insere_listacor_norepeat(listacor l, rgb cor){
	nocor *per=l->ini;
	while(per!=NULL){
		if(corcmp(per->cor,cor))return;
		per=per->prox;
	}
	insere_listacor_fim(l,cor);
}

void insere_listacor_ini(listacor l, rgb cor){
	nocor *n = (nocor*)malloc(sizeof(nocor));
	n->cor = cor;
	if(l->ini!=NULL){
		l->ini->ant=n;
		n->prox=l->ini;
		n->ant=NULL;
		l->ini=n;
	}
	else{
		l->ini=l->fim=n;
		n->ant=n->prox=NULL;
	}
	l->n++;
}

void insere_listacor_fim(listacor l, rgb cor){
	nocor *n = (nocor*)malloc(sizeof(nocor));
	n->cor = cor;
	if(l->fim!=NULL){
		l->fim->prox=n;
		n->ant=l->fim;
		n->prox=NULL;
		l->fim=n;
	}
	else{
		l->ini=l->fim=n;
		n->ant=n->prox=NULL;	
	}
    l->n++;
}

void rm_listacor_ini(listacor l){
	nocor* per = l->ini;
	if(per!=NULL){
		l->ini=per->prox;
		if(l->ini=NULL)
			l->fim=NULL;
		free(per);
		l->n--;
	}
}

void rm_listacor_fim(listacor l){
	nocor* per = l->fim;
	if(per!=NULL){
		l->fim=per->ant;
		if(l->fim=NULL)
			l->ini=NULL;
		free(per);
		l->n--;
	}
}


int listacor_buscaIndice(listacor l, rgb cor){
	nocor *per=l->ini;
	int indice=0;
	while(per!=NULL){
		if(corcmp(per->cor,cor))
			return indice;
		indice++;
		per=per->prox;
	}
	return -1;
}

void libera_listacor(listacor l){
	nocor* per = l->ini;
	while(per!=NULL){
		l->ini = per->prox;
		free(per);
		per = l->ini;
	}
	l->fim = l->ini = NULL;
	l->n = 0;
}

/*
	Linhas sao listas de pontos com a finalidade
	de desenhar cada um desses pontos, um a um,

*/
linha aloca_linha()
{
	linha l = (linha)malloc(sizeof(struct LINHA));
	l->prim = NULL;
	l->ultimo = NULL;
}

bool linha_vazia(linha l)
{
	return (l->prim == NULL);
}

void put_linha(linha l, ponto p)
{
	lista_p *lp = (lista_p*)malloc(sizeof(lista_p));
	if(lp == NULL)
	{
		printf("Sem memoria\n");
		libera_linha(l);
		exit(1);
	}
	lp->p = p;
	lp->prox = NULL;
	if(linha_vazia(l))
	{
		l->prim = lp;
		l->ultimo = lp;
	}
	else
	{
		l->ultimo->prox = lp;
		l->ultimo = lp;
	}
}

void cria_linha(linha l, ponto p0, ponto pf)
{
	double i;
	if (p0.x - pf.x == 0)
	{
		if (p0.y > pf.y)
			troca(&p0.y, &pf.y);
		for (i = p0.y; i <= pf.y; i++)
			put_linha(l, cria_ponto(p0.x, i));
	}
	else
	{
		int dx, dy, c, antx = -1,anty=-1, ny;
		dx = p0.x - pf.x;
		dy = pf.y - p0.y;
		c = pf.x*p0.y - p0.x*pf.y;
		if (p0.x > pf.x)
			troca(&p0.x, &pf.x);
		for (i = p0.x; i <= pf.x; i+=0.05){
			ny = aprox(-((int)i*dy + c) / dx);
			if(ny!=anty || aprox(i)!=antx){
				put_linha(l, cria_ponto(aprox(i), ny));
				antx = aprox(i);
				anty = ny;
			}
		}
	}
}

void rmv_linha(linha l, ponto p)
{
	lista_p *a,*per = l->prim;
	while(per!=NULL && (p.x != per->p.x || p.y != per->p.y))
	{
		a = per;
		per = per->prox;
	}
	if(per != NULL)
	{
		if(l->ultimo == per)
			l->ultimo = a;
		if(a != NULL)
		{
			a->prox = per->prox;
			free(per);
		}
		else
		{
			l->prim = per->prox;
			free(per);
		}
	}
}

void libera_linha(linha l)
{
	lista_p *a,*p = l->prim;
	while(p!=NULL)
	{
		a = p;
		p = p->prox;
		free(a);
	}
	free(l);
}

/*
	-Poligonos
	Sao estruturas com um ponteiro para o inicio
	de um lista de pontos, com a finalidade de
	desenhar um poligono que passa por esses 
	pontos na ordem
*/

poligon* cria_poligono()
{
	poligon* pol = (poligon*)malloc(sizeof(poligon));
	pol->prim = NULL;
	pol->centro = (ponto*)malloc(sizeof(ponto));
	return pol;
}

bool poligono_vazio(poligon *pol)
{
	return (pol->prim==NULL);
}

void insere_poligono(poligon *pol, ponto p)
{
	lista_p2 *no = (lista_p2*)malloc(sizeof(lista_p2));
	if(no==NULL)
	{
		printf("Sem memoria\n");
		libera_poligono(pol);
		exit(1);
	}
	no->p=p;
	no->prox=pol->prim;
	no->ant=NULL;
	if(!poligono_vazio(pol))
		pol->prim->ant=no;
	pol->prim=no;
}

ponto pop_poligono(poligon *pol)
{
	if(poligono_vazio(pol))
	{
		printf("Poligono vazio\n");
		return;
	}
	else
	{
		ponto p = pol->prim->p;
		lista_p2 *tmp=pol->prim;
		pol->prim=pol->prim->prox;
		free(tmp);
		if(pol->prim!=NULL)
			pol->prim->ant=NULL;
		return p;
	}
}

lista_p2* busca_poligono(poligon *pol, ponto p)
{
	lista_p2 *per=pol->prim;
	while(per!=NULL)
	{
		if(pontocmp(per->p,p)) break;
		per=per->prox;
	}
	return per;	
}

void rmv_poligono(poligon *pol, ponto p)
{
	lista_p2 *tmp=busca_poligono(pol, p);
	if(tmp!=NULL){
		if(tmp->ant!=NULL)
			tmp->ant->prox=tmp->prox;
		if(tmp->prox!=NULL)
			tmp->prox->ant=tmp->ant;
		if(tmp==pol->prim)
			pol->prim=tmp->prox;
		free(tmp);
	}
}

void esvazia_poligono(poligon *pol)
{
	while(!poligono_vazio(pol))
		pop_poligono(pol);
}

void copia_poligono(poligon *src, poligon *dest)
{
	esvazia_poligono(dest);
	lista_p2 *per=src->prim;
	while(per!=NULL){
		insere_poligono(dest,per->p);
		per=per->prox;
	}
	dest->centro=src->centro;
}

void libera_poligono(poligon *pol)
{
	if(pol==NULL)
		return;
	lista_p2 *per;
	for(per=pol->prim;per!=NULL;per=pol->prim)
	{
		pol->prim=per->prox;
		free(per);
	}
	free(pol->centro);
	free(pol);
}

static void escreve_arvb_preord(FILE *arq, arvb *a){
	if(a!=NULL){
		fprintf(arq, "%d ", a->x);
		escreve_arvb_preord(arq,a->e);
		escreve_arvb_preord(arq,a->d);
	}
}

static void arv_buscaIndice_preord(arvb *a, int x, int *ind){
	if(a!=NULL){
		(*ind)++;
		if(a->x==x)return;
		arv_buscaIndice_preord(a->e,x,ind);
		arv_buscaIndice_preord(a->d,x,ind);
	}
}

quadtree cria_quadtree(rgb cor, int x, int y){
	quadtree q;
	q->cor=cor;
	q->raiz=cria_raiz_qt(x,y);
	return q;
}

qt *cria_raiz_qt(int x, int y){
	qt a* = (quadtree*)malloc(sizeof(qt));
	a->raiz=a;
	a->lft=a->rgt=a->up=a->dwn=NULL;
	a->x=x;
	a->y=y;
	return a;
}

qt *cria_ramo_qt(int x, int y, qt *lft,qt *rgt,qt *up,qt *dwn){
	qt a* = (qt*)malloc(sizeof(qt));
	a->raiz=NULL;
	
	a->lft=lft;
	lft->rgt=a;

	a->rgt=rgt;
	rgt->lft=a;

	a->up = up;
	up->dwn =a;
	
	a->dwn=dwn;
	dwn->up= a;
	
	a->x=x;
	a->y=y;
	
	if(lft!=NULL) a->raiz=lft->raiz;
	if(rgt!=NULL) a->raiz=rgt->raiz;
	if(up !=NULL) a->raiz= up->raiz;
	if(dwn!=NULL) a->raiz=dwn->raiz;

	if(raiz==NULL) a->raiz=a;
	
	return a;
}

qt *busca_no_qt(int x, int y, qt *raiz){
	qt *r=NULL,*tmp;
	if(raiz->x==x && raiz->y==y)
		return raiz;
	else{
		tmp = bfqt(x,y,raiz->lft);
		if(tmp!=NULL)
			r=tmp;
		tmp = bfqt(x,y,raiz->rgt);
		if(tmp!=NULL)
			r=tmp;
		tmp = bfqt(x,y,raiz->up);
		if(tmp!=NULL)
			r=tmp;
		tmp = bfqt(x,y,raiz->dwn);
		if(tmp!=NULL)
		 	r=tmp;
	}
	return r;
}

qt *bfqt(int x, int y, qt *ramo){
	if(ramo!=NULL && ramo!=ramo->raiz){
		if(ramo->x==x && ramo->y==y)
			return ramo;
		else{
			qt *r,*tmp;
			tmp = bfqt(x,y,raiz->lft);
			if(tmp!=NULL)
				r=tmp;
			tmp = bfqt(x,y,raiz->rgt);
			if(tmp!=NULL)
				r=tmp;
			tmp = bfqt(x,y,raiz->up);
			if(tmp!=NULL)
				r=tmp;
			tmp = bfqt(x,y,raiz->dwn);
			if(tmp!=NULL)
			 	r=tmp;
		}
		return r;
	}
}

void merge_ramo_qt(qt *ramo1, qt *ramo2,char dir){
	switch(dir){
		case LFT:
			ramo1->lft=ramo2;
			ramo2->rgt=ramo1;
		break;
		case RGT:
			ramo1->rgt=ramo2;
			ramo2->lft=ramo1;
		break;
		case UP:
			ramo1->up=ramo2;
			ramo2->dwn=ramo1;
		break;
		case DWN:
			ramo1->dwn=ramo2;
			ramo2->up=ramo1;
		break;
	}
}

void libera_qt(qt *a){
	if(a!=NULL){
		libera_qt(a->lft);
		libera_qt(a->rgt);
		libera_qt(a->up);
		libera_qt(a->dwn);
		free(a);
	}
}

void libera_quadtree(quadtree q){
	libera_qt(q->raiz);
}