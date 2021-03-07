#include "ppmlib.h"
#include <math.h>

static void r(ppm img, ponto a, ponto b, double t){
	t+=180.0;
	ponto m = midpoint(a,b);
	double d = distancia(a,m);
	ponto v = vira(a,cria_ponto(a.x,a.y+sqrt(d*d*(1+seno(60.0)))),t);
	desCurva(img,a,v,b);
	if(distancia(a,v)>10)
		r(img,b,m,t);
}

void espiral(ppm img, ponto a, ponto b){
	ponto m = midpoint(a,b);
	int dx=(b.x-a.x);
	double d = distancia(a,m),t;
	if(dx==0)
		t=90.0;
	else{
		int fa=(b.y-a.y)/dx;
		t = rad2graus(atan(fa));
	}
	ponto v = vira(a,cria_ponto(a.x,a.y+sqrt(d*d*(1.0+seno(60.0)))),t);
	desCurva(img,a,v,b);
	if(distancia(a,v)>10)
		r(img,b,m,t);
}

void arvorebin(ppm imagem, ponto p, int t)
{
	ponto a = cria_ponto(p.x - t, p.y - t / 2), b = cria_ponto(p.x - t, p.y + t / 2);
	desLinha(imagem, p, a);
	desLinha(imagem, p, b);
	if (t > 1)
	{
		arvorebin(imagem, a, t / 2);
		arvorebin(imagem, b, t / 2);
	}
}

void arvoreter(ppm imagem, ponto p, int t)
{
	ponto a = cria_ponto(p.x - t, p.y - t / 2), b = cria_ponto(p.x - t, p.y), c = cria_ponto(p.x - t, p.y + t / 2);
	desLinha(imagem, p, a);
	desLinha(imagem, p, b);
	desLinha(imagem, p, c);
	if (t > 1)
	{
		arvoreter(imagem, a, t / 3);
		arvoreter(imagem, b, t / 3);
		arvoreter(imagem, c, t / 3);
	}
}

void circRec(ppm img, ponto p, int raio)
{
	desCirculo(img, p, raio);
	if (raio > 6)
	{
		circRec(img, cria_ponto(p.x + raio, p.y), raio / 2);
		circRec(img, cria_ponto(p.x - raio, p.y), raio / 2);
		circRec(img, cria_ponto(p.x, p.y + raio), raio / 2);
		circRec(img, cria_ponto(p.x, p.y - raio), raio / 2);
	}
}

void rec(ppm imagem, ponto p, int tam)
{
	desCirculo(imagem, p, tam);
	tam /= 2;
	if (tam > 2)
	{
		rec(imagem, cria_ponto(p.x - tam, p.y - tam), tam);
		rec(imagem, cria_ponto(p.x - tam, p.y + tam), tam);
	}
}

void rec2(ppm imagem, ponto p, int tam)
{
	desCirculo(imagem, p, tam);
	tam /= 2;
	if (tam > 10)
	{
		rec2(imagem, cria_ponto(p.x - tam, p.y - tam), tam);
		rec2(imagem, cria_ponto(p.x - tam, p.y + tam), tam);
		rec2(imagem, cria_ponto(p.x + tam, p.y - tam), tam);
		rec2(imagem, cria_ponto(p.x + tam, p.y + tam), tam);
	}
}

void rec3baixo(ppm imagem, ponto p, int tam)
{
	desCirculo(imagem, p, tam);
	tam /= 2;
	if (tam > 2)
	{
		rec3baixo(imagem, cria_ponto(p.x + tam, p.y - tam), tam);
		rec3baixo(imagem, cria_ponto(p.x + tam, p.y + tam), tam);
	}
}

void rec3cima(ppm imagem, ponto p, int tam)
{
	desCirculo(imagem, p, tam);
	tam /= 2;
	if (tam > 2)
	{
		rec3cima(imagem, cria_ponto(p.x - tam, p.y - tam), tam);
		rec3cima(imagem, cria_ponto(p.x - tam, p.y + tam), tam);
	}
}

void rec4(ppm imagem, ponto p, int tam)
{
	desCirculo(imagem, p, tam);
	if (tam > 10)
	{
		rec4(imagem, cria_ponto(p.x - tam, p.y), tam / 2);
		rec4(imagem, cria_ponto(p.x + tam, p.y), tam / 2);
		rec4(imagem, cria_ponto(p.x + tam, p.y + tam), tam / 2);
		rec4(imagem, cria_ponto(p.x + tam, p.y - tam), tam / 2);
	}
}

void rec5(ppm img, ponto p, int tam, rgb cor)
{
	desTrianguloCor(img, p, tam, tam, cor);
	if (tam > 10)
	{
		rec5(img, cria_ponto(p.x - tam / 4, p.y), tam / 2, cor);
		rec5(img, cria_ponto(p.x + tam / 4, p.y + tam / 4), tam / 2, cor);
		rec5(img, cria_ponto(p.x + tam / 4, p.y - tam / 4), tam / 2, cor);
	}
}

void rec6(ppm img, ponto p, int tam)
{
	desCirculo(img, p, tam);
	desLinhaCor(img, p, cria_ponto(p.x - tam, p.y - tam), n2rgb(rand() % 255, rand() % 255, rand() % 255));
	desLinhaCor(img, p, cria_ponto(p.x - tam, p.y + tam), n2rgb(rand() % 255, rand() % 255, rand() % 255));
	desLinhaCor(img, p, cria_ponto(p.x + tam, p.y - tam), n2rgb(rand() % 255, rand() % 255, rand() % 255));
	desLinhaCor(img, p, cria_ponto(p.x + tam, p.y + tam), n2rgb(rand() % 255, rand() % 255, rand() % 255));
	if (tam > 43)
	{
		rec6(img, cria_ponto(p.x - tam * 3 / 2, p.y - tam * 3 / 2), tam / 2);
		rec6(img, cria_ponto(p.x - tam * 3 / 2, p.y + tam * 3 / 2), tam / 2);
		rec6(img, cria_ponto(p.x + tam * 3 / 2, p.y - tam * 3 / 2), tam / 2);
		rec6(img, cria_ponto(p.x + tam * 3 / 2, p.y + tam * 3 / 2), tam / 2);
	}
}

void rec7(ppm img, ponto p, int tam, char dirx, char diry)
{
	if (dirx != 0 || diry != 0)
	{
		if (dirx == -1)
			desLinha(img, p, cria_ponto(p.x - tam, p.y));
		if (dirx == 1)
			desLinha(img, p, cria_ponto(p.x + tam, p.y));
		if (diry == -1)
			desLinha(img, p, cria_ponto(p.x, p.y - tam));
		if (diry == 1)
			desLinha(img, p, cria_ponto(p.x, p.y + tam));
		if (tam < 1500)
		{
			if (dirx == -1)
				rec7(img, cria_ponto(p.x - tam, p.y), tam * 1.1, 0, -1);
			if (dirx == 1)
				rec7(img, cria_ponto(p.x + tam, p.y), tam * 1.1, 0, 1);
			if (diry == -1)
				rec7(img, cria_ponto(p.x, p.y - tam), tam * 1.1, 1, 0);
			if (diry == 1)
				rec7(img, cria_ponto(p.x, p.y + tam), tam * 1.1, -1, 0);
		}
	}
}

void rec8(ppm img, ponto p, int tam)
{
	desLinha(img, p, cria_ponto(p.x + tam, p.y));
	tam /= 3;
	if (tam > 9)
	{
		//raiz de 2 = 1,732050808
		rec8(img, cria_ponto(p.x + 3 * tam / 2, p.y - tam*1.732050808 / 2), tam);
		rec8(img, cria_ponto(p.x + 2 * tam, p.y - tam), tam);
		rec8(img, cria_ponto(p.x + 3 * tam / 2, p.y + tam*1.732050808 / 2), tam);
		rec8(img, cria_ponto(p.x + 2 * tam, p.y + tam), tam);
	}
}

void EstRec(ppm img, ponto p, int raio)
{
	desElipse(img, p, raio, 16 * raio / 9);
	if (raio > 6)
	{
		EstRec(img, cria_ponto(p.x + raio, p.y), raio / 2);
		EstRec(img, cria_ponto(p.x - raio, p.y), raio / 2);
		EstRec(img, cria_ponto(p.x, p.y + raio), raio / 2);
		EstRec(img, cria_ponto(p.x, p.y - raio), raio / 2);
	}
}

void cantor(ppm img, ponto p, int tam)
{
	desLinha(img, p, cria_ponto(p.x, p.y + tam));
	if (tam > 9)
	{
		tam /= 7;
		cantor(img, cria_ponto(p.x + 50, p.y), tam);
		cantor(img, cria_ponto(p.x + 50, p.y + 2 * tam), tam);
		cantor(img, cria_ponto(p.x + 50, p.y + 4 * tam), tam);
		cantor(img, cria_ponto(p.x + 50, p.y + 6 * tam), tam);
	}
}

void apagakoch(ppm img, ponto p, ponto f)
{
	ponto
	s = cria_ponto((2 * p.x + f.x) / 3, (2 * p.y + f.y) / 3),
	t = cria_ponto((2 * f.x + p.x) / 3, (2 * f.y + p.y) / 3);
	desLinhaCor(img, s, t, n2rgb(255, 255, 255));
	if(distancia(p,f) >= 30)
	{
		apagakoch(img, p, s);
		apagakoch(img, t, f);
	}
}

void koch(ppm img, ponto p, ponto f)
{
	ponto 
	s = cria_ponto((2 * p.x + f.x) / 3, (2 * p.y + f.y) / 3),
	t = cria_ponto((2 * f.x + p.x) / 3, (2 * f.y + p.y) / 3),
	v = vira(s, t, 60);
	if (distancia(p, f) > 30)
	{
		koch(img, p, s);
		koch(img, s, v);
		koch(img, v, t);
		koch(img, t, f);
	}
	else
	{
		desLinha(img, p, s);
		desLinha(img, s, v);
		desLinha(img, v, t);
		desLinha(img, t, f);
	}
}

void koch2(ppm img, ponto p, ponto f)
{
	ponto 
	s = cria_ponto((2 * p.x + f.x) / 3, (2 * p.y + f.y) / 3),
	t = cria_ponto((2 * f.x + p.x) / 3, (2 * f.y + p.y) / 3),
	v = vira(s, t, 300);
	if (distancia(p, f) > 30)
	{
		koch2(img, p, s);
		koch2(img, s, v);
		koch2(img, v, t);
		koch2(img, t, f);
	}
	else
	{
		desLinha(img, p, s);
		desLinha(img, s, v);
		desLinha(img, v, t);
		desLinha(img, t, f);
	}
}

void dragon(ppm img, ponto p, ponto f)
{
	ponto c = cria_ponto(
	aprox((f.x*((2*1.732050808-1)/2)+3*p.x)/(3+((2*1.732050808-1)/2))), 
	aprox((f.y*((2*1.732050808-1)/2)+3*p.y)/(3+((2*1.732050808-1)/2)))
	);
	if(distancia(p,f)>10)
	{
		c = vira(f,c,45);
		dragcima(img, p, c);
		dragbaixo(img, c, f);
	}
}

void dragcima(ppm img, ponto p, ponto f)
{
	ponto c = cria_ponto(
	aprox((f.x*((2*1.732050808-1)/2)+3*p.x)/(3+((2*1.732050808-1)/2))), 
	aprox((f.y*((2*1.732050808-1)/2)+3*p.y)/(3+((2*1.732050808-1)/2)))
	);
	if(distancia(p,f)>10)
	{
		c = vira(f,c,45);
		dragcima(img, p, c);
		dragbaixo(img, c, f);
	}
	else
	{
		desLinha(img, p, c);
		desLinha(img, c, f);
	}
}

void dragbaixo(ppm img, ponto p, ponto f)
{
	ponto c = cria_ponto(
	aprox((f.x*((2*1.732050808-1)/2)+3*p.x)/(3+((2*1.732050808-1)/2))), 
	aprox((f.y*((2*1.732050808-1)/2)+3*p.y)/(3+((2*1.732050808-1)/2)))
	);
	if(distancia(p,f)>10)
	{
		c = vira(f,c,315);
		dragcima(img, p, c);
		dragbaixo(img, c, f);
	}
	else
	{
		desLinha(img, p, c);
		desLinha(img, c, f);
	}
}

void dragonLevy(ppm img, ponto p, ponto f)
{
	ponto c = cria_ponto(
	aprox((f.x*((2*1.732050808-1)/2)+3*p.x)/(3+((2*1.732050808-1)/2))), 
	aprox((f.y*((2*1.732050808-1)/2)+3*p.y)/(3+((2*1.732050808-1)/2)))
	);
	if(distancia(p,f)>10)
	{
		c = vira(f,c,45);
		dragonLevy(img,p,c);
		dragonLevy(img,c,f);
	}
	else
	{
		desLinha(img, p, c);
		desLinha(img, c, f);
	}
}

void fc(ppm img, ponto a, ponto b)
{
	ponto c = cria_ponto((3*a.x+b.x)/4,(3*a.y+b.y)/4),
	d = vira(a,c,90);
	c = vira(a,c,270);
	ponto e = cria_ponto((a.x+3*b.x)/4,(a.y+3*b.y)/4),
	f = vira(b,e,90);
	e = vira(b,e,270);
	desLinha(img,a,b);
	if(distancia(a,b)>10)
	{
		fc(img, c, d);
		fc(img, e, f);
	}
}

void pit(ppm img, ponto c, int lado, float graus)
{
	poligon *pol = cria_poligono();
	vetRetangulo(pol,c,lado,lado);
	vetRotac(pol,graus);
	desPoligono(img,pol);
	libera_poligono(pol);
	ponto 
	e=cria_ponto(c.x-(lado*(2.236067977)/2.0),c.y),
	d=cria_ponto(c.x-(lado*(2.236067977)/2.0),c.y);
	e=vira(c,e,graus-26.5);
	d=vira(c,d,graus+26.5);
	if(lado>20)
	{
		pit(img,d,lado*(1.414213562/2.0),graus+45);
		pit(img,e,lado*(1.414213562/2.0),graus-45);
	}
}