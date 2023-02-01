#ifndef ARQ_H
#define ARQ_H

#ifndef ARQUIVO
	#define ARQUIVO
	typedef struct Arquivo
	{
		char **linha;
		int linhas;
	}arquivo;
#endif

typedef struct list_char
{
	char c;
	struct list_char *prox;
}lchar;

struct FILACHAR
{
	lchar *ini,*fim;
};

typedef struct FILACHAR *fchar;

struct PILHACHAR
{
	lchar *top;
};

typedef struct PILHACHAR *pchar;

arquivo cria_arq(int Numlinhas);
arquivo leitura_arq(char nome[]);
void escrita(char fname[], arquivo f);
void modlinha(arquivo f, char novo[], int linha);
void libera_arq(arquivo f);
int str2int(char n[]);
void int2str(int x, char n[]);

/*
////////////////////////////////////////////////////////////////////
Fila de char
*/

fchar aloca_fchar();
char vazia_fchar(fchar f);
void enfileira_char(fchar f, char c);
char desenfileira_char(fchar f);
void libera_fchar(fchar f);

/*
////////////////////////////////////////////////////////////////////
Pilha de char
*/

pchar aloca_pchar();
char vazia_pchar(pchar p);
void push_char(pchar p, char c);
char pop_char(pchar p);
void libera_pchar(pchar p);

/*
////////////////////////////////////////////////////////////////////
Matriz 2d de char
*/

char** split(char str[], char oc);
int ocorrencias(char str[], char oc);
void imp_char2(char **strs);
void libera_char2(char **strs);

#endif