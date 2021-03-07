#ifndef _PPM_LIB_
#define _PPM_LIB_
#ifndef M_PI
#    define M_PI (3.14159265358979323846)
#endif

#ifndef PHI
	#define PHI (1.618033988749894)
#endif

#ifndef NULL
	#define NULL 0
#endif

#define LFT 0
#define RGT 1
#define UP 2
#define DWN 3

#define graus2rad(graus) (graus * M_PI / 180.0)
#define rad2graus(radianos) (radianos * 180.0 / M_PI)

#define branco n2rgb(255,255,255)
#define preto n2rgb(0,0,0)
#define vermelho n2rgb(255,0,0)
#define verde n2rgb(0,255,0)
#define azul n2rgb(0,0,255)
#define cinza n2rgb(127,127,127)
#define amarelo n2rgb(255,255,0)
#define roxo n2rgb(255,0,255)
#define azul_escuro n2rgb(0,0,156)
#define marrom n2rgb(92,51,23)
#define ciano n2rgb(0,255,255)
#define laranja n2rgb(255,165,0)
#define vermelho_escuro n2rgb(140,23,23)
#define verde2 n2rgb(0,205,0)

#ifndef ARQUIVO
	#define ARQUIVO
	typedef struct Arquivo
	{
		char **linha;
		int linhas;
	}arquivo;
#endif

typedef enum BOOL{false=0,true=1}bool;

typedef unsigned char uchar;

typedef unsigned long long int lint;

typedef struct PONTO{
	int x, y;
}ponto;

typedef struct RGB
{
	uchar r,g,b;
}rgb;

typedef struct Arvbin{
	int x;
	struct Arvbin *e,*d;
}arvb;

typedef struct LISTA_PONTO
{
	ponto p;
	struct LISTA_PONTO *prox;
}lista_p;

typedef struct LISTA_PONTO_DUPLA
{
	ponto p;
	struct LISTA_PONTO_DUPLA *prox, *ant;
}lista_p2;

struct LINHA
{
	lista_p *prim, *ultimo;
};

typedef struct LINHA * linha;

typedef struct nodecor{
	rgb cor;
	struct nodecor *prox, *ant;
}nocor;

typedef struct listcor{
    nocor *fim,*ini;
    int n;
}lista_cor;

typedef lista_cor* listacor;

typedef struct cabecalhoPPM{
	int largura, altura, max;
	char key[3];
}*cppm;

typedef struct QT{
	struct QT *raiz;
	int x,y;
	struct QT *lft,*rgt,*up,*dwn;
}qt;

typedef struct QUADTREE{
	qt *raiz;
	rgb cor;
}quadtree;

typedef struct PPM
{
	cppm cab;
	rgb **cor;
}*ppm;

typedef struct poligono
{
	lista_p2 *prim;
	ponto *centro;
}poligon;

//manipulacao basica
void strcop(char *dest, char *ori);
int strcomp(char *s1, char *s2);
int aprox(float val);
int modulo(int n);
void troca(int *a, int *b);
float seno(float graus);
float coseno(float graus);
rgb n2rgb(unsigned char r, unsigned char g, unsigned char b);
rgb num2rgb(int n);
int rgb2num(rgb cor);
cppm cab_malloc(int altura, int largura, int max, char key[]);
ppm ppm_malloc();
ppm copia(ppm img);
cppm copia_cab(cppm cab);
rgb **rgb_malloc(cppm cab);
int **int_malloc(int altura, int largura);
void libera_int2d(int **mat, int altura);
void libera_ppm(ppm img);
void libera_rgb2d(ppm img);
arvb *cria_arvb();
arvb *cria_folha(int x);
arvb *insere_arvb_norepeat(arvb *r, int x);
arvb *libera_arvb(arvb *r);
void imp_arvbin_preord(arvb *r);
int arvb_qtdnodes(arvb *r);
ppm leitura(char fname[]);
void grava(char fname[], ppm img);
ponto cria_ponto(int x, int y);
double distancia(ponto a, ponto b);
ponto vira(ponto a, ponto b, float graus);
ponto midpoint(ponto a, ponto b);
ponto linear_interp(ponto a, ponto b, double ratio);
bool pontocmp(ponto p, ponto q);
bool corcmp(rgb a, rgb b);
int cores_dif(ppm img);
rgb randcor();

//Listas
void libera_lista_p2(lista_p2 *l);
	//Lista de Cor
	listacor cria_listacor();
	void insere_listacor_ini(listacor l, rgb cor);
	void insere_listacor_fim(listacor l, rgb cor);
	void insere_listacor_norepeat(listacor l, rgb cor);
	void rm_listacor_ini(listacor l);
	void rm_listacor_fim(listacor l);
	int listacor_buscaIndice(listacor l, rgb cor);
	void libera_listacor(listacor l);
	//linhas
	linha aloca_linha(); /*aloca lista de pontos vazia*/
	bool linha_vazia(linha l);
	void put_linha(linha l, ponto p); /*insere ponto na lista*/
	void cria_linha(linha l, ponto p0, ponto pf); /*insere pontos pertencentes a linha de p0 ate pf*/
	void rmv_linha(linha l, ponto p); /*remove um ponto da lista*/
	void libera_linha(linha l); /*remove todos os pontos*/
	//Poligonos
	poligon* cria_poligono();
	bool poligono_vazio(poligon *pol);
	void insere_poligono(poligon *pol, ponto p);
	ponto pop_poligono(poligon *pol);
	lista_p2* busca_poligono(poligon *pol, ponto p);
	void rmv_poligono(poligon *pol, ponto p);
	void libera_poligono(poligon *pol);
	//quadtree
	quadtree cria_quadtree(rgb cor, int x, int y);
	qt *cria_raiz_qt(int x, int y);
	qt *cria_ramo_qt(int x, int y, qt *lft,qt *rgt,qt *up,qt *dwn);
	qt *busca_no_qt(int x, int y, qt *raiz);
	qt *bfqt(int x, int y, qt *ramo);
	void merge_ramo_qt(qt *ramo1, qt *ramo2,char dir);
	void libera_qt(qt *a);
	void libera_quadtree(quadtree q);

//manipulacao com efeitos
ppm decomp(ppm cab, bool r, bool g, bool b);
ppm gira(ppm img, int graus);
ppm negativo(ppm img);
ppm BW(ppm img);
ppm BM(ppm img);
ppm blur(ppm img,int **ker, int tamanhokernel);
int **gaussian(int tamanhokernel);
ppm blurgauss(ppm img, int tamanhokernel);
int **mint(int tamanhokernel);
ppm blurmint(ppm img, int tamanhokernel);
ppm amplia(ppm imagem, int zoom);
ppm espelhar(ppm img);
ppm join(ppm img, ppm img2);
ppm merge(ppm img, ppm img2);
ppm overlay(ppm img, ppm img2);
void grava_decomp(char fname[], ppm img, bool r, bool g, bool b);
void grava_gira(char fname[], ppm img, int graus);
void grava_negativo(char fname[], ppm img);
void grava_BW(char fname[], ppm img);
void grava_BM(char fname[], ppm img);
void grava_blur(char fname[], ppm img, int **ker, int tamanhokernel);
void grava_blurgauss(char fname[], ppm img, int tamanhokernel);
void grava_blurmint(char fname[], ppm img, int tamanhokernel);
void grava_espelhado(char fname[], ppm img);
void mod_decomp(ppm *img, bool r, bool g, bool b);
void mod_gira(ppm *img, int graus);
void mod_negativo(ppm *img);
void mod_BW(ppm *img);
void mod_BM(ppm *img);
void mod_blurgauss(ppm *img, int tamanhokernel);
void mod_blurmint(ppm *img, int tamanhokernel);
void mod_espelha(ppm *img);

//criacao
ppm cria_ppm(int altura, int largura, rgb cor);
	//sem cor
	#define desPonto(imagem, p) desPontoCor(imagem, p, preto)
	#define desLinha(imagem, p0, pf) desLinhaCor(imagem, p0, pf, preto)
	#define desCurva(imagem, p0, pm, pf) desCurvaCor(imagem, p0, pm, pf, preto)
	#define insere_linha(imagem, l) insere_linhaCor(imagem, l, preto) /*desenha linha e remove os pontos da lista*/
	#define desTriangulo(imagem, centro, altura, base) desTrianguloCor(imagem, centro, altura, base, preto)
	#define desRetangulo(imagem, centro, alturaR, larguraR) desRetangulo(imagem, centro, alturaR, larguraR, preto)
	#define desLosango(imagem, centro, altura, largura) desLosangoCor(imagem, centro, altura, largura, preto)
	#define desTrapezio(imagem, centro, b1, b2, altura) desTrapezioCor(imagem, centro, b1, b2, altura, preto)
	#define desEstrela(imagem, p, x, y) desEstrelaCor(imagem, p, x, y, preto)
	#define desCirculo(imagem, centro, raio) desCirculoCor(imagem, centro, raio, preto)
	#define desElipse(imagem, centro, altura, largura) desElipseCor(imagem, centro, altura, largura, preto)

	//cor
	void desPontoCor(ppm imagem, ponto p0, rgb cor);
	void desLinhaCor(ppm imagem, ponto p0, ponto pf, rgb cor);
	void desCurvaCor(ppm imagem, ponto p0, ponto pm, ponto pf, rgb cor);
	void insere_linhaCor(ppm img, linha l, rgb cor);
	void desTrianguloCor(ppm imagem, ponto centro, int altura, int base, rgb cor);
	void desRetanguloCor(ppm imagem, ponto centro, int alturaR, int larguraR, rgb cor);
	void desLosangoCor(ppm imagem, ponto centro, int altura, int largura, rgb cor);
	void desTrapezioCor(ppm imagem, ponto centro, int b1, int b2, int altura, rgb cor);
	void desEstrelaCor(ppm imagem, ponto p, int x, int y, rgb cor);
	void desCirculoCor(ppm imagem, ponto centro, int raio, rgb cor);
	void desElipseCor(ppm imagem, ponto centro, int altura, int largura, rgb cor);

	//preenchidos
	#define desCurvaprn(imagem, p0, pm, pf) desCurvaCorprn(imagem, p0, pm, pf, preto)
	#define desTrianguloprn(imagem, centro, altura, base) desTrianguloCorprn(imagem, centro, altura, base, preto)
	#define desRetanguloprn(imagem, centro, altura, largura) desRetanguloCorprn(imagem, centro, altura, largura, preto)
	#define desLosangoprn(imagem, centro, altura, largura) desLosangoCorprn(imagem, centro, altura, largura, preto)
	#define desCirculoprn(imagem, centro, raio) desCirculoCorprn(imagem, centro, raio, preto)
	
	//preenchidos com cor
	void desCurvaCorprn(ppm imagem, ponto p0, ponto pm, ponto pf, rgb cor);
	void desTrianguloCorprn(ppm imagem, ponto centro, int altura, int base, rgb cor);
	void desRetanguloCorprn(ppm imagem, ponto centro, int altura, int largura, rgb cor);
	void desLosangoCorprn(ppm imagem, ponto centro, int altura, int largura, rgb cor);
	void desCirculoCorprn(ppm imagem, ponto centro, int raio, rgb cor);

//Minha Fonte
	#define escreve_str(img, s,  o, font_size) escreve_strCor(img, s, o, font_size,preto)
	#define escreve_char(img, c, o, size) escreve_charCor(img, c, o, size, preto)
	void escreve_strCor(ppm img, char s[], ponto o, int font_size, rgb cor);
	void escreve_charCor(ppm img, char c,ponto o, int size, rgb cor);

	//minusculas
		//preto
		#define escreve_a(img, o, size) escreve_aCor(img,o,size,preto)
		#define escreve_b(img, o, size) escreve_bCor(img,o,size,preto)
		#define escreve_c(img, o, size) escreve_cCor(img,o,size,preto)
		#define escreve_d(img, o, size) escreve_dCor(img,o,size,preto)
		#define escreve_e(img, o, size) escreve_eCor(img,o,size,preto)
		#define escreve_f(img, o, size) escreve_fCor(img,o,size,preto)
		#define escreve_g(img, o, size) escreve_gCor(img,o,size,preto)
		#define escreve_h(img, o, size) escreve_hCor(img,o,size,preto)
		#define escreve_i(img, o, size) escreve_iCor(img,o,size,preto)
		#define escreve_j(img, o, size) escreve_jCor(img,o,size,preto)
		#define escreve_k(img, o, size) escreve_kCor(img,o,size,preto)
		#define escreve_l(img, o, size) escreve_lCor(img,o,size,preto)
		#define escreve_m(img, o, size) escreve_mCor(img,o,size,preto)
		#define escreve_n(img, o, size) escreve_nCor(img,o,size,preto)
		#define escreve_o(img, o, size) escreve_oCor(img,o,size,preto)
		#define escreve_p(img, o, size) escreve_pCor(img,o,size,preto)
		#define escreve_q(img, o, size) escreve_qCor(img,o,size,preto)
		#define escreve_r(img, o, size) escreve_rCor(img,o,size,preto)
		#define escreve_s(img, o, size) escreve_sCor(img,o,size,preto)
		#define escreve_t(img, o, size) escreve_tCor(img,o,size,preto)
		#define escreve_u(img, o, size) escreve_uCor(img,o,size,preto)
		#define escreve_v(img, o, size) escreve_vCor(img,o,size,preto)
		#define escreve_x(img, o, size) escreve_xCor(img,o,size,preto)
		#define escreve_z(img, o, size) escreve_zCor(img,o,size,preto)

		//cor
		void escreve_aCor(ppm img, ponto o, int size, rgb cor);
		void escreve_bCor(ppm img, ponto o, int size, rgb cor);
		void escreve_cCor(ppm img, ponto o, int size, rgb cor);
		void escreve_dCor(ppm img, ponto o, int size, rgb cor);
		void escreve_eCor(ppm img, ponto o, int size, rgb cor);
		void escreve_fCor(ppm img, ponto o, int size, rgb cor);
		void escreve_gCor(ppm img, ponto o, int size, rgb cor);
		void escreve_hCor(ppm img, ponto o, int size, rgb cor);
		void escreve_iCor(ppm img, ponto o, int size, rgb cor);
		void escreve_jCor(ppm img, ponto o, int size, rgb cor);
		void escreve_kCor(ppm img, ponto o, int size, rgb cor);
		void escreve_lCor(ppm img, ponto o, int size, rgb cor);
		void escreve_mCor(ppm img, ponto o, int size, rgb cor);
		void escreve_nCor(ppm img, ponto o, int size, rgb cor);
		void escreve_oCor(ppm img, ponto o, int size, rgb cor);
		void escreve_pCor(ppm img, ponto o, int size, rgb cor);
		void escreve_qCor(ppm img, ponto o, int size, rgb cor);
		void escreve_rCor(ppm img, ponto o, int size, rgb cor);
		void escreve_sCor(ppm img, ponto o, int size, rgb cor);
		void escreve_tCor(ppm img, ponto o, int size, rgb cor);
		void escreve_uCor(ppm img, ponto o, int size, rgb cor);
		void escreve_vCor(ppm img, ponto o, int size, rgb cor);
		void escreve_xCor(ppm img, ponto o, int size, rgb cor);
		void escreve_zCor(ppm img, ponto o, int size, rgb cor);
		
	//maiusculas
		//preto
		#define escreve_S(img, o, size) escreve_SCor(img, o, size, preto)
		#define escreve_V(img, o, size) escreve_VCor(img, o, size, preto)

		//cor
		void escreve_SCor(ppm img, ponto o, int size, rgb cor);
		void escreve_VCor(ppm img, ponto o, int size, rgb cor);

	//Simbolos

		//preto
		#define escreve_hifen(img, o, size) escreve_hifenCor(img, o, size, preto)

		//cor
		void escreve_hifenCor(ppm img, ponto o, int size, rgb cor);


//fractais
	void espiral(ppm img, ponto a, ponto b);
	void arvorebin(ppm imagem, ponto p, int t);
	void arvoreter(ppm imagem, ponto p, int t);
	void circRec(ppm img, ponto p, int raio);
	void rec(ppm imagem, ponto p, int tam);
	void rec2(ppm imagem, ponto p, int tam);
	void rec3baixo(ppm imagem, ponto p, int tam);
	void rec3cima(ppm imagem, ponto p, int tam);
	void rec4(ppm imagem, ponto p, int tam);
	void rec5(ppm imagem, ponto p, int tam, rgb cor);
	void rec6(ppm imagem, ponto p, int tam);
	void rec7(ppm imagem, ponto p, int tam, char dirx, char diry);
	void rec8(ppm imagem, ponto p, int tam);
	void EstRec(ppm img, ponto p, int raio);
	void cantor(ppm img, ponto p, int tam);
	void koch(ppm img, ponto p, ponto f);
	void knuth_dragon(ppm img, ponto p, ponto f);
	void drag(ppm img, ponto p, ponto f);
	void dragcima(ppm img, ponto p, ponto f);
	void dragbaixo(ppm img, ponto p, ponto f);
	void pit(ppm img,ponto c,int lado,float graus);

//vetppm
void vetRetangulo(poligon *pol, ponto centro, int altura, int largura);
void vetTriangulo(poligon *pol, ponto centro, int altura, int base);
void vetLosango(poligon *pol, ponto centro, int altura, int largura);
void vetTrapezio(poligon *pol, ponto centro, int b1, int b2, int altura);
void vetEstrela(poligon *pol, ponto p, int x, int y);
void vetTranslac(poligon *pol, int vertical, int horizontal);
void vetRotac(poligon *pol, float graus);
void vetEscala(poligon *pol, double escala);
void desPoligono(ppm img, poligon *pol);
void desPoligonoCor(ppm img, poligon *pol, rgb cor);

//compressao
void ppmTodppm(char fname[],ppm img);
ppm dppmToppm(char fname[]);

#endif