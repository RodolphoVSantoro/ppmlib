#include "arq.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static FILE *fopen_or_crash(char fname[], char modo[]) {
    FILE *arquivo = fopen(fname, modo);
    if (arquivo == NULL) {
        printf("Falha ao abrir o arquivo %s\n", fname);
        exit(1);
    }
    return arquivo;
}

static int int_potencia(int b, int e) {
    int i, r = 1;
    for (i = 0; i < e; i++)
        r *= b;
    return r;
}

arquivo cria_arq(int numero_linhas) {
    arquivo f;
    f.linhas = numero_linhas;
    f.linha = (char **)malloc(sizeof(char *) * f.linhas);
    int i;
    for (i = 0; i < f.linhas; i++)
        f.linha[i] = NULL;
    return f;
}

arquivo leitura_arq(char nome[]) {
    int c = 1, linhas = 1, carac = 1, linha, x = 0;
    arquivo f;
    fchar fc;
    FILE *arq = fopen_or_crash(nome, "r");
    while (c != EOF) {
        c = fgetc(arq);
        if (c == '\n')
            linhas++;
    }
    fclose(arq);
    c = 0;
    f.linhas = linhas;
    f.linha = (char **)malloc(sizeof(char *) * linhas);
    arq = fopen_or_crash(nome, "r");
    for (linha = 0; linha < linhas; linha++) {
        fc = aloca_fchar();
        c = fgetc(arq);
        while (c != '\n' && c != EOF) {
            carac++;
            enfileira_char(fc, c);
            c = fgetc(arq);
        }
        f.linha[linha] = (char *)malloc(sizeof(char) * carac);
        while (!vazia_fchar(fc)) {
            f.linha[linha][x] = desenfileira_char(fc);
            x++;
        }
        f.linha[linha][x] = 0;
        libera_fchar(fc);
        carac = 1;
        x = 0;
    }
    fclose(arq);
    f.linhas--;
    return f;
}

void escrita(char fname[], arquivo f) {
    int x;
    FILE *arq = fopen_or_crash(fname, "w");
    for (x = 0; x < f.linhas - 1; x++) {
        fprintf(arq, "%s\n", f.linha[x]);
    }
    fprintf(arq, "%s", f.linha[f.linhas - 1]);
    fclose(arq);
}

void modlinha(arquivo f, char novo[], int linha) {
    if (linha > f.linhas) {
        printf("Fora do alcance\n");
        return;
    }
    if (f.linha[linha] != NULL)
        free(f.linha[linha]);
    f.linha[linha] = (char *)malloc(sizeof(char) * (strlen(novo) + 1));
    strcpy(f.linha[linha], novo);
}

void libera_arq(arquivo f) {
    int x;
    for (x = 0; x < f.linhas; x++)
        free(f.linha[x]);
    free(f.linha);
}

int str2int(char n[]) {
    char neg = 0;
    int i = 0, x = 0, p = strlen(n) - 1;
    for (; n[i] == '-' && n[i] != 0; i++) neg = !neg;
    for (; n[i] != 0; i++) {
        if (n[i] < 48 || n[i] > 57) return neg == 0 ? x / int_potencia(10, p + 1) : (x / int_potencia(10, p + 1)) * -1;
        x += ((int)(n[i] - 48)) * int_potencia(10, p);
        p--;
    }
    return neg == 0 ? x : -x / 10;
}

void int2str(int x, char n[]) {
    pchar p = aloca_pchar(sizeof(struct PILHACHAR));
    int i = 0, a;
    for (a = x; a > 0; a /= 10) push_char(p, a % 10 + '0');
    while (!vazia_pchar(p)) n[i++] = pop_char(p);
    n[i] = 0;
    libera_pchar(p);
}

/*////////////////////////////////////////////////////////////////////////////////////////*/

fchar aloca_fchar() {
    fchar f = (fchar)malloc(sizeof(struct FILACHAR));
    if (f == NULL) {
        printf("Sem memoria\n");
        exit(1);
    }
    f->ini = f->fim = NULL;
    return f;
}

char vazia_fchar(fchar f) {
    return (f->ini == NULL);
}

void enfileira_char(fchar f, char c) {
    lchar *n = (lchar *)malloc(sizeof(lchar));
    n->c = c;
    if (vazia_fchar(f))
        f->ini = n;
    else {
        f->fim->prox = n;
        n->prox = NULL;
    }
    f->fim = n;
}

char desenfileira_char(fchar f) {
    if (vazia_fchar(f)) {
        printf("fila vazia");
        return 0;
    }
    char c = f->ini->c;
    lchar *n = f->ini;
    f->ini = n->prox;
    free(n);
    return c;
}

void libera_fchar(fchar f) {
    lchar *n = f->ini;
    while (n != NULL) {
        f->ini = n->prox;
        free(n);
        n = f->ini;
    }
    f->fim = NULL;
    free(f);
}

/*////////////////////////////////////////////////////////////////////////////////////////*/

pchar aloca_pchar() {
    pchar p = (pchar)malloc(sizeof(struct PILHACHAR));
    p->top = NULL;
    return p;
}

char vazia_pchar(pchar p) {
    return (p->top == NULL);
}

void push_char(pchar p, char c) {
    lchar *n = (lchar *)malloc(sizeof(lchar));
    n->c = c;
    n->prox = p->top;
    p->top = n;
}

char pop_char(pchar p) {
    lchar *n = p->top;
    p->top = n->prox;
    char c = n->c;
    free(n);
    return c;
}

void libera_pchar(pchar p) {
    lchar *n = p->top;
    while (n != NULL) {
        p->top = n->prox;
        free(n);
        n = p->top;
    }
    free(p);
}

/*////////////////////////////////////////////////////////////////////////////////////////*/

char **split(char str[], char oc) {
    int i = 0, j = 0, n = 0, a = 0;
    char **strs;
    strs = (char **)malloc(sizeof(char *) * (ocorrencias(str, oc) + 2));
    for (; str[i] != 0; i++)
        if (str[i] == oc) {
            strs[n] = (char *)malloc(sizeof(char) * (i - j));
            for (; j < i; a++, j++)
                strs[n][a] = str[j];
            strs[n][a] = 0;
            a = 0;
            j++;
            n++;
        }
    strs[n] = (char *)malloc(sizeof(char) * (i - j));
    for (; str[j] != 0; j++, a++)
        strs[n][a] = str[j];
    strs[n][a] = 0;
    strs[n + 1] = NULL;
    return strs;
}

int ocorrencias(char str[], char oc) {
    int n = 0, i = 0;
    for (; str[i] != 0; i++)
        if (str[i] == oc)
            n++;
    return n;
}

void imp_char2(char **strs) {
    int i;
    for (i = 0; strs[i] != 0; i++)
        printf("%s\n", strs[i]);
}

void libera_char2(char **strs) {
    int i = 0;
    while (strs[i] != 0) {
        free(strs[i]);
        strs[i] = NULL;
        i++;
    }
    free(strs);
}