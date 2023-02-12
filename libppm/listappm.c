#include <stdio.h>
#include <stdlib.h>

#include "internal.h"
#include "libppm.h"
#include "types.h"

void ListaDuplaPonto_libera(ListaDuplaPonto *lista) {
    free(lista);
}

// Lista de Cor
ListaCor *ListaCor_cria() {
    ListaCor *lista = (ListaCor *)malloc(sizeof(*lista));
    lista->fim = NULL;
    lista->inicio = NULL;
    lista->tamanho = 0;
    return lista;
}

void ListaCor_insere_sem_repeticao(ListaCor *lista, rgb cor) {
    NodeCor *cursor = lista->inicio;
    while (cursor != NULL) {
        if (cor_compare(cursor->cor, cor)) {
            return;
        }
        cursor = cursor->proximo;
    }
    ListaCor_insere_fim(lista, cor);
}

void ListaCor_insere_inicio(ListaCor *lista, rgb cor) {
    NodeCor *novo = (NodeCor *)malloc(sizeof(NodeCor));
    novo->cor = cor;
    if (lista->inicio != NULL) {
        lista->inicio->anterior = novo;
        novo->proximo = lista->inicio;
        novo->anterior = NULL;
        lista->inicio = novo;
    } else {
        lista->fim = novo;
        lista->inicio = lista->fim;
        novo->proximo = NULL;
        novo->anterior = novo->proximo;
    }
    lista->tamanho++;
}

void ListaCor_insere_fim(ListaCor *lista, rgb cor) {
    NodeCor *novo = (NodeCor *)malloc(sizeof(NodeCor));
    novo->cor = cor;
    if (lista->fim != NULL) {
        lista->fim->proximo = novo;
        novo->anterior = lista->fim;
        novo->proximo = NULL;
        lista->fim = novo;
    } else {
        lista->inicio = lista->fim = novo;
        novo->proximo = NULL;
        novo->anterior = novo->proximo;
    }
    lista->tamanho++;
}

void ListaCor_remove_inicio(ListaCor lista) {
    NodeCor *cursor = lista->ini;
    if (cursor != NULL) {
        l->ini = cursor->proximo;
        if (l->ini == NULL)
            l->fim = NULL;
        free(cursor);
        l->n--;
    }
}

void rm_listacor_fim(listacor l) {
    nocor *per = l->fim;
    if (per != NULL) {
        l->fim = per->ant;
        if (l->fim == NULL)
            l->ini = NULL;
        free(per);
        l->n--;
    }
}

int listacor_buscaIndice(listacor l, rgb cor) {
    nocor *per = l->ini;
    int indice = 0;
    while (per != NULL) {
        if (corcmp(per->cor, cor))
            return indice;
        indice++;
        per = per->prox;
    }
    return -1;
}

void libera_listacor(listacor l) {
    nocor *per = l->ini;
    while (per != NULL) {
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
linha aloca_linha() {
    linha l = (linha)malloc(sizeof(struct LINHA));
    l->prim = NULL;
    l->ultimo = NULL;
    return l;
}

bool linha_vazia(linha l) {
    return (l->prim == NULL);
}

void put_linha(linha l, ponto p) {
    lista_p *lp = (lista_p *)malloc(sizeof(lista_p));
    if (lp == NULL) {
        printf("Sem memoria\n");
        Linha_libera(l);
        exit(1);
    }
    lp->p = p;
    lp->prox = NULL;
    if (linha_vazia(l)) {
        l->prim = lp;
        l->ultimo = lp;
    } else {
        l->ultimo->prox = lp;
        l->ultimo = lp;
    }
}

void cria_linha(linha l, ponto p0, ponto pf) {
    double i;
    if (p0.x - pf.x == 0) {
        if (p0.y > pf.y)
            troca(&p0.y, &pf.y);
        for (i = p0.y; i <= pf.y; i++)
            put_linha(l, cria_ponto(p0.x, i));
    } else {
        int dx, dy, c, antx = -1, anty = -1, ny;
        dx = p0.x - pf.x;
        dy = pf.y - p0.y;
        c = pf.x * p0.y - p0.x * pf.y;
        if (p0.x > pf.x)
            troca(&p0.x, &pf.x);
        for (i = p0.x; i <= pf.x; i += 0.05) {
            ny = aprox(-((int)i * dy + c) / dx);
            if (ny != anty || aprox(i) != antx) {
                put_linha(l, cria_ponto(aprox(i), ny));
                antx = aprox(i);
                anty = ny;
            }
        }
    }
}

void rmv_linha(linha l, ponto p) {
    lista_p *a, *per = l->prim;
    while (per != NULL && (p.x != per->p.x || p.y != per->p.y)) {
        a = per;
        per = per->prox;
    }
    if (per != NULL) {
        if (l->ultimo == per)
            l->ultimo = a;
        if (a != NULL) {
            a->prox = per->prox;
            free(per);
        } else {
            l->prim = per->prox;
            free(per);
        }
    }
}

void Linha_libera(linha l) {
    lista_p *a, *p = l->prim;
    while (p != NULL) {
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

poligon *cria_poligono() {
    poligon *pol = (poligon *)malloc(sizeof(poligon));
    pol->prim = NULL;
    pol->centro = (ponto *)malloc(sizeof(ponto));
    return pol;
}

bool poligono_vazio(poligon *pol) {
    return (pol->prim == NULL);
}

void insere_poligono(poligon *pol, ponto p) {
    lista_p2 *no = (lista_p2 *)malloc(sizeof(lista_p2));
    if (no == NULL) {
        printf("Sem memoria\n");
        libera_poligono(pol);
        exit(1);
    }
    no->p = p;
    no->prox = pol->prim;
    no->ant = NULL;
    if (!poligono_vazio(pol))
        pol->prim->ant = no;
    pol->prim = no;
}

ponto pop_poligono(poligon *pol) {
    if (poligono_vazio(pol)) {
        printf("Poligono vazio\n");
        return cria_ponto(-1, -1);
    } else {
        ponto p = pol->prim->p;
        lista_p2 *tmp = pol->prim;
        pol->prim = pol->prim->prox;
        free(tmp);
        if (pol->prim != NULL)
            pol->prim->ant = NULL;
        return p;
    }
}

lista_p2 *busca_poligono(poligon *pol, ponto p) {
    lista_p2 *per = pol->prim;
    while (per != NULL) {
        if (pontocmp(per->p, p)) break;
        per = per->prox;
    }
    return per;
}

void rmv_poligono(poligon *pol, ponto p) {
    lista_p2 *tmp = busca_poligono(pol, p);
    if (tmp != NULL) {
        if (tmp->ant != NULL)
            tmp->ant->prox = tmp->prox;
        if (tmp->prox != NULL)
            tmp->prox->ant = tmp->ant;
        if (tmp == pol->prim)
            pol->prim = tmp->prox;
        free(tmp);
    }
}

void esvazia_poligono(poligon *pol) {
    while (!poligono_vazio(pol))
        pop_poligono(pol);
}

void copia_poligono(poligon *src, poligon *dest) {
    esvazia_poligono(dest);
    lista_p2 *per = src->prim;
    while (per != NULL) {
        insere_poligono(dest, per->p);
        per = per->prox;
    }
    dest->centro = src->centro;
}

void libera_poligono(poligon *pol) {
    if (pol == NULL)
        return;
    lista_p2 *per;
    for (per = pol->prim; per != NULL; per = pol->prim) {
        pol->prim = per->prox;
        free(per);
    }
    free(pol->centro);
    free(pol);
}

static void escreve_arvb_preord(FILE *arq, ArvoreBinaria *arvore) {
    if (a != NULL) {
        fprintf(arq, "%d ", a->x);
        escreve_arvb_preord(arq, arvore->esquerda);
        escreve_arvb_preord(arq, arvore->direita);
    }
}

static void arv_buscaIndice_preord(arvb *a, int x, int *ind) {
    if (a != NULL) {
        (*ind)++;
        if (a->x == x) return;
        arv_buscaIndice_preord(a->e, x, ind);
        arv_buscaIndice_preord(a->d, x, ind);
    }
}
