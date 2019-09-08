#include <stdlib.h>
#include "leitor.h"
#include <string.h>

Leitor criar_leitor(const char* nome, int e)
{
    Leitor leitor;
    strcpy(leitor.nome, nome);
    leitor.restituicoes = malloc(sizeof(int) * e);
    leitor.devolucoes = malloc(sizeof(int) * e);
    leitor.num_restituicoes = 0;
    leitor.num_devolucoes = 0;

    return leitor;
}

void desalocar_memoria(Leitor* leitor)
{
    free((*leitor).restituicoes);
    free((*leitor).devolucoes);
}

const char* obter_nome(const Leitor* leitor)
{
    return (*leitor).nome;
}

void registrar_restituicao(Leitor* leitor, int i) 
{
    int num = (*leitor).num_restituicoes;
    (*leitor).restituicoes[num] = i;
    (*leitor).num_restituicoes += 1;
}

void registrar_devolucao(Leitor* leitor, int i)
{
    int num = (*leitor).num_devolucoes;
    (*leitor).devolucoes[num] = i;
    (*leitor).num_devolucoes += 1;
}

const int* obter_restituicoes(const Leitor* leitor)
{
    return (*leitor).restituicoes;
}

const int* obter_devolucoes(const Leitor* leitor)
{
    return (*leitor).devolucoes;
}

int obter_num_restituicoes(const Leitor* leitor)
{
    return (*leitor).num_restituicoes;
}

int obter_num_devolucoes(const Leitor* leitor)
{
    return (*leitor).num_devolucoes;
}
