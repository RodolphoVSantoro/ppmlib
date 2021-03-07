#include <stdlib.h>
#include "ppmlib.h"

ppm cria_ppm(int altura, int largura, rgb cor)
{
	ppm imagem=ppm_malloc();
	int i, j;
	imagem->cab->altura = altura;
	imagem->cab->largura = largura;
	imagem->cab->max = 255;
	strcop(imagem->cab->key, "P3");
	imagem->cor = rgb_malloc(imagem->cab);
	for (i = 0; i < altura; i++)
		for (j = 0; j < largura; j++)
			imagem->cor[i][j] = cor;
	return imagem;
}

//Cor

void desPontoCor(ppm imagem, ponto p, rgb cor)
{
	if (p.x >= 0 && p.x < imagem->cab->altura && p.y >= 0 && p.y < imagem->cab->largura)
		imagem->cor[p.x][p.y] = cor;
}

void desLinhaCor(ppm imagem, ponto p0, ponto pf, rgb cor)
{
	double i;
	if (modulo(p0.x - pf.x) < imagem->cab->altura/500)
	{
		if (p0.y > pf.y)
			troca(&p0.y, &pf.y);
		for (i = p0.y; i <= pf.y; i++)
			desPontoCor(imagem, cria_ponto(p0.x, i), cor);
	}
	else
	{
		int dx, dy, c;
		dx = p0.x - pf.x;
		dy = pf.y - p0.y;
		c = pf.x*p0.y - p0.x*pf.y;
		if (p0.x > pf.x)
			troca(&p0.x, &pf.x);
		for (i = p0.x; i <= pf.x; i+=0.05)
			desPontoCor(imagem, cria_ponto(i, -(i*dy + c) / dx), cor);
	}
}

void desCurvaCor(ppm imagem, ponto p0, ponto pm, ponto pf, rgb cor){
	ponto ab,bc,ab2,bc2;
    double i,lim=distancia(p0,pm)+distancia(pf,pm);
    for (i=0; i<lim; i++){
    	ab=linear_interp(p0,pm,i/lim);
    	bc=linear_interp(pm,pf,i/lim);
    	ab2=linear_interp(p0,pm,(i+1)/lim);
    	bc2=linear_interp(pm,pf,(i+1)/lim);
		desLinhaCor(imagem,linear_interp(ab,bc,i/lim),linear_interp(ab2,bc2,(i+1)/lim),cor);
    }
}

void insere_linhaCor(ppm img, linha l, rgb cor){
	lista_p *per = l->prim;
	while(!linha_vazia(l)){
		desPontoCor(img, l->prim->p,cor);
		per = per->prox;
		free(l->prim);
		l->prim=per;
	}
}

void desTrianguloCor(ppm imagem, ponto centro, int altura, int base, rgb cor)
{
	ponto a, b, c;
	a = cria_ponto(centro.x + altura / 2, centro.y - base / 2);
	b = cria_ponto(centro.x - altura / 2, centro.y);
	c = cria_ponto(centro.x + altura / 2, centro.y + base / 2);
	desLinhaCor(imagem, a, b, cor);
	desLinhaCor(imagem, b, c, cor);
	desLinhaCor(imagem, c, a, cor);
}

void desRetanguloCor(ppm imagem, ponto centro, int altura, int largura, rgb cor)
{
	ponto a, b, c, d;
	a = cria_ponto(centro.x - altura / 2, centro.y - largura / 2);
	b = cria_ponto(centro.x - altura / 2, centro.y + largura / 2);
	c = cria_ponto(centro.x + altura / 2, centro.y + largura / 2);
	d = cria_ponto(centro.x + altura / 2, centro.y - largura / 2);
	desLinhaCor(imagem, a, b, cor);
	desLinhaCor(imagem, a, c, cor);
	desLinhaCor(imagem, b, c, cor);
	desLinhaCor(imagem, d, a, cor);
}

void desLosangoCor(ppm imagem, ponto centro, int altura, int largura, rgb cor)
{
	ponto a, b, c, d;
	a = cria_ponto(centro.x, centro.y - largura / 2);
	b = cria_ponto(centro.x - altura / 2, centro.y);
	c = cria_ponto(centro.x, centro.y + largura / 2);
	d = cria_ponto(centro.x + altura / 2, centro.y);
	desLinhaCor(imagem, a, b, cor);
	desLinhaCor(imagem, b, c, cor);
	desLinhaCor(imagem, c, d, cor);
	desLinhaCor(imagem, d, a, cor);
}

void desTrapezioCor(ppm imagem, ponto centro, int b1, int b2, int altura, rgb cor)
{
	ponto a, b, c, d;
	a = cria_ponto(centro.x - altura / 2, centro.y - b1 / 2);
	b = cria_ponto(centro.x - altura / 2, centro.y + b1 / 2);
	c = cria_ponto(centro.x + altura / 2, centro.y + b2 / 2);
	d = cria_ponto(centro.x + altura / 2, centro.y - b2 / 2);
	desLinhaCor(imagem, a, b, cor);
	desLinhaCor(imagem, b, c, cor);
	desLinhaCor(imagem, c, d, cor);
	desLinhaCor(imagem, d, a, cor);
}

void desEstrelaCor(ppm imagem, ponto p, int x, int y, rgb cor)
{
	ponto v[12];
	int i;
	v[0] = cria_ponto(p.x - x, p.y);
	v[1] = cria_ponto(p.x - x / 2, p.y - y / 3);
	v[2] = cria_ponto(p.x - x / 2, p.y - y);
	v[3] = cria_ponto(p.x, p.y - 2 * y / 3);
	v[4] = cria_ponto(p.x + x / 2, p.y - y);
	v[5] = cria_ponto(p.x + x / 2, p.y - y / 3);
	v[6] = cria_ponto(p.x + x, p.y);
	v[7] = cria_ponto(p.x + x / 2, p.y + y / 3);
	v[8] = cria_ponto(p.x + x / 2, p.y + y);
	v[9] = cria_ponto(p.x, p.y + 2 * y / 3);
	v[10] = cria_ponto(p.x - x / 2, p.y + y);
	v[11] = cria_ponto(p.x - x / 2, p.y + y / 3);
	for (i = 0; i < 12; i++)
		desLinhaCor(imagem, v[i], v[(i + 1) % 12], cor);
}

void desCirculoCor(ppm imagem, ponto centro, int raio, rgb cor)
{
	int x = raio;
	int y = 0;
	int err = 0;
	while (x >= y)
	{
		desPontoCor(imagem, cria_ponto(centro.x + x, centro.y + y), cor);
		desPontoCor(imagem, cria_ponto(centro.x + y, centro.y + x), cor);
		desPontoCor(imagem, cria_ponto(centro.x - y, centro.y + x), cor);
		desPontoCor(imagem, cria_ponto(centro.x - x, centro.y + y), cor);
		desPontoCor(imagem, cria_ponto(centro.x - x, centro.y - y), cor);
		desPontoCor(imagem, cria_ponto(centro.x - y, centro.y - x), cor);
		desPontoCor(imagem, cria_ponto(centro.x + y, centro.y - x), cor);
		desPontoCor(imagem, cria_ponto(centro.x + x, centro.y - y), cor);
		y += 1;
		err += 1 + 2 * y;
		if (2 * (err - x) + 1 > 0)
		{
			x -= 1;
			err += 1 - 2 * x;
		}
	}
}

void desElipseCor(ppm imagem, ponto centro, int altura, int largura, rgb cor)
{
	ponto p0 = cria_ponto(centro.x + altura / 2, centro.y - largura / 2), pf = cria_ponto(centro.x - altura / 2, centro.y + largura / 2);
	int a = abs(pf.x - p0.x), b = abs(pf.y - p0.y), b1 = b & 1;
	long dx = 4 * (1 - a)*b*b, dy = 4 * (b1 + 1)*a*a;
	long err = dx + dy + b1 * a * a, e2;

	if (p0.x > pf.x) { p0.x = pf.x; pf.x += a; }
	if (p0.y > pf.y) p0.y = pf.y;
	p0.y += (b + 1) / 2; pf.y = p0.y - b1;
	a *= 8 * a; b1 = 8 * b*b;

	do {
		desPontoCor(imagem, cria_ponto(pf.x, p0.y), cor);
		desPontoCor(imagem, cria_ponto(p0.x, p0.y), cor);
		desPontoCor(imagem, cria_ponto(p0.x, pf.y), cor);
		desPontoCor(imagem, cria_ponto(pf.x, pf.y), cor);
		e2 = 2 * err;
		if (e2 <= dy) { p0.y++; pf.y--; err += dy += a; }
		if (e2 >= dx || 2 * err > dy) { p0.x++; pf.x--; err += dx += b1; }
	} while (p0.x <= pf.x);

	while (p0.y - pf.y < b) {
		desPontoCor(imagem, cria_ponto(p0.x - 1, p0.y), cor);
		desPontoCor(imagem, cria_ponto(pf.x + 1, p0.y++), cor);
		desPontoCor(imagem, cria_ponto(p0.x - 1, pf.y), cor);
		desPontoCor(imagem, cria_ponto(pf.x + 1, pf.y--), cor);
	}
}

//Formas preenchidas com cor
void desCurvaCorprn(ppm imagem, ponto p0, ponto pm, ponto pf, rgb cor){
	double i,lim=distancia(p0,pm)+distancia(pf,pm);
	for(i=0;i<=lim;i++)
		desCurvaCor(imagem,p0,linear_interp(pm,midpoint(p0,pf),i/lim),pf,cor);
}

void desTrianguloCorprn(ppm imagem, ponto centro, int altura, int base, rgb cor)
{
	ponto a, b, c;
	a = cria_ponto(centro.x - altura / 2, centro.y);
	b = cria_ponto(centro.x + altura / 2, centro.y - base / 2);
	c = cria_ponto(centro.x + altura / 2, centro.y + base / 2);
	linha l = aloca_linha(), l2 = aloca_linha();
	cria_linha(l, a, b);
	cria_linha(l2, a, c);
	lista_p *p1 = l->prim, *p2 = l2->prim;
	while(p1!=NULL && p2!=NULL)
	{
		desLinhaCor(imagem, p1->p, p2->p, cor);
		p1 = p1->prox;
		p2 = p2->prox;
	}
	libera_linha(l);
	libera_linha(l2);
}

void desRetanguloCorprn(ppm imagem, ponto centro, int altura, int largura, rgb cor)
{
	ponto a, b, c, d;
	a = cria_ponto(centro.x - altura / 2, centro.y + largura / 2);
	b = cria_ponto(centro.x - altura / 2, centro.y - largura / 2);
	for(c = a, d = b; c.x < centro.x + altura / 2; c.x++,d.x++)
		desLinhaCor(imagem, c, d, cor);
}

void desLosangoCorprn(ppm imagem, ponto centro, int altura, int largura, rgb cor)
{
	int i;
	ponto a, b, c, d;
	linha l[4];
	lista_p *m,*n;
	a = cria_ponto(centro.x, centro.y - largura / 2);
	b = cria_ponto(centro.x - altura / 2, centro.y);
	c = cria_ponto(centro.x, centro.y + largura / 2);
	d = cria_ponto(centro.x + altura / 2, centro.y);
	for(i=0;i<4;i++)
		l[i] = aloca_linha();
	cria_linha(l[0], a, b);
	cria_linha(l[1], b, c);
	cria_linha(l[2], a, d);
	cria_linha(l[3], c, d);
	for (i = 0; i <= 2; i+=2)
		for(m=l[i]->prim,n=l[i+1]->prim;m!=NULL && n!=NULL;n=n->prox,m=m->prox)
			desLinhaCor(imagem, m->p, n->p, cor);
	for(i=0;i<4;i++)
		libera_linha(l[i]);
}

void desCirculoCorprn(ppm imagem, ponto centro, int raio, rgb cor)
{
	int x = raio;
	int y = 0;
	int err = 0;
	while (x >= y)
	{
		desLinhaCor(imagem, cria_ponto(centro.x - x, centro.y - y), cria_ponto(centro.x - x, centro.y + y), cor);
		desLinhaCor(imagem, cria_ponto(centro.x - y, centro.y - x), cria_ponto(centro.x - y, centro.y + x), cor);
		desLinhaCor(imagem, cria_ponto(centro.x + y, centro.y - x), cria_ponto(centro.x + y, centro.y + x), cor);
		desLinhaCor(imagem, cria_ponto(centro.x + x, centro.y - y), cria_ponto(centro.x + x, centro.y + y), cor);
		y += 1;
		err += 1 + 2 * y;
		if (2 * (err - x) + 1 > 0)
		{
			x -= 1;
			err += 1 - 2 * x;
		}
	}
}
