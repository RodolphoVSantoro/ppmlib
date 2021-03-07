#include "ppmlib.h"

void vetRetangulo(poligon *pol, ponto centro, int altura, int largura)
{
	esvazia_poligono(pol);
	*(pol->centro)=centro;
	insere_poligono(pol, cria_ponto(centro.x - altura / 2, centro.y - largura / 2));
	insere_poligono(pol, cria_ponto(centro.x - altura / 2, centro.y + largura / 2));
	insere_poligono(pol, cria_ponto(centro.x + altura / 2, centro.y + largura / 2));
	insere_poligono(pol, cria_ponto(centro.x + altura / 2, centro.y - largura / 2));
}

void vetTriangulo(poligon *pol, ponto centro, int altura, int base)
{
	esvazia_poligono(pol);
	*(pol->centro)=centro;
	insere_poligono(pol, cria_ponto(centro.x + altura / 2, centro.y - base / 2));
	insere_poligono(pol, cria_ponto(centro.x - altura / 2, centro.y));
	insere_poligono(pol, cria_ponto(centro.x + altura / 2, centro.y + base / 2));
}

void vetLosango(poligon *pol, ponto centro, int altura, int largura)
{
	esvazia_poligono(pol);
	*(pol->centro)=centro;
	insere_poligono(pol, cria_ponto(centro.x, centro.y - largura / 2));
	insere_poligono(pol, cria_ponto(centro.x - altura / 2, centro.y));
	insere_poligono(pol, cria_ponto(centro.x, centro.y + largura / 2));
	insere_poligono(pol, cria_ponto(centro.x + altura / 2, centro.y));
}

void vetTrapezio(poligon *pol, ponto centro, int b1, int b2, int altura)
{
	esvazia_poligono(pol);
	*(pol->centro)=centro;
	insere_poligono(pol, cria_ponto(centro.x - altura / 2, centro.y - b1 / 2));
	insere_poligono(pol, cria_ponto(centro.x - altura / 2, centro.y + b1 / 2));
	insere_poligono(pol, cria_ponto(centro.x + altura / 2, centro.y + b2 / 2));
	insere_poligono(pol, cria_ponto(centro.x + altura / 2, centro.y - b2 / 2));
}

void vetEstrela(poligon *pol, ponto p, int x, int y)
{
	esvazia_poligono(pol);
	*(pol->centro)=p;
	insere_poligono(pol, cria_ponto(p.x - x, p.y));
	insere_poligono(pol, cria_ponto(p.x - x / 2, p.y - y / 3));
	insere_poligono(pol, cria_ponto(p.x - x / 2, p.y - y));
	insere_poligono(pol, cria_ponto(p.x, p.y - 2 * y / 3));
	insere_poligono(pol, cria_ponto(p.x + x / 2, p.y - y));
	insere_poligono(pol, cria_ponto(p.x + x / 2, p.y - y / 3));
	insere_poligono(pol, cria_ponto(p.x + x, p.y));
	insere_poligono(pol, cria_ponto(p.x + x / 2, p.y + y / 3));
	insere_poligono(pol, cria_ponto(p.x + x / 2, p.y + y));
	insere_poligono(pol, cria_ponto(p.x, p.y + 2 * y / 3));
	insere_poligono(pol, cria_ponto(p.x - x / 2, p.y + y));
	insere_poligono(pol, cria_ponto(p.x - x / 2, p.y + y / 3));
}

void vetTranslac(poligon *pol, int vertical, int horizontal)
{
	*(pol->centro)=cria_ponto(pol->centro->x+vertical,pol->centro->y+horizontal);
	lista_p2 *per;
	for(per=pol->prim;per!=NULL;per=per->prox)
	{
		per->p.x+=vertical;
		per->p.y+=horizontal;
	}
}

void vetRotac(poligon *pol, float graus)
{
	lista_p2 *per;
	for(per=pol->prim;per!=NULL;per=per->prox)
		per->p=vira(*(pol->centro),per->p,graus);
}

void vetEscala(poligon *pol, double escala)
{
	escala-=1.0;
	lista_p2 *per=pol->prim;
	while(per!=NULL)
	{
		per->p.x=(per->p.x - pol->centro->x)*escala+per->p.x;
		per->p.y=(per->p.y - pol->centro->y)*escala+per->p.y;
		per=per->prox;
	}
}

void desPoligono(ppm img, poligon *pol)
{
	lista_p2 *per=pol->prim->prox;
	desLinha(img,pol->prim->p,per->p);
	while(per->prox!=NULL)
	{
		desLinha(img,per->p,per->prox->p);
		per=per->prox;
		per->ant->ant=per->ant->prox=NULL;
		libera_lista_p2(per->ant);
		per->ant=NULL;
	}
	desLinha(img,per->p,pol->prim->p);
	libera_lista_p2(per);
	pol->prim->prox=NULL;
	libera_lista_p2(pol->prim);
	pol->prim=NULL;
}

void desPoligonoCor(ppm img, poligon *pol, rgb cor)
{
	lista_p2 *per=pol->prim->prox;
	desLinhaCor(img,pol->prim->p,per->p, cor);
	while(per->prox!=NULL)
	{
		desLinhaCor(img,per->p,per->prox->p, cor);
		per=per->prox;
		per->ant->ant=per->ant->prox=NULL;
		libera_lista_p2(per->ant);
		per->ant=NULL;
	}
	desLinhaCor(img,per->p,pol->prim->p, cor);
	libera_lista_p2(per);
	pol->prim->prox=NULL;
	libera_lista_p2(pol->prim);
	pol->prim=NULL;
}