#include <stdlib.h>
#include "leitor.h"
#include <string.h>

Leitor criar_leitor(const char* nome, int e)
{
    Leitor leitor;
    strcpy(leitor.nome, nome);
    
}

void desalocar_memoria(Leitor* leitor)
{
   /** ************************************************************************
    *               ATENÇÃO: É preciso implementar esta função!               *
    *********************************************************************** **/
}

const char* obter_nome(const Leitor* leitor)
{
   /** ************************************************************************
    *               ATENÇÃO: É preciso implementar esta função!               *
    *********************************************************************** **/
}

void registrar_restituicao(Leitor* leitor, int i)
{
   /** ************************************************************************
    *               ATENÇÃO: É preciso implementar esta função!               *
    *********************************************************************** **/
}

void registrar_devolucao(Leitor* leitor, int i)
{
   /** ************************************************************************
    *               ATENÇÃO: É preciso implementar esta função!               *
    *********************************************************************** **/
}

const int* obter_restituicoes(const Leitor* leitor)
{
   /** ************************************************************************
    *               ATENÇÃO: É preciso implementar esta função!               *
    *********************************************************************** **/
}

const int* obter_devolucoes(const Leitor* leitor)
{
   /** ************************************************************************
    *               ATENÇÃO: É preciso implementar esta função!               *
    *********************************************************************** **/
}

int obter_num_restituicoes(const Leitor* leitor)
{
   /** ************************************************************************
    *               ATENÇÃO: É preciso implementar esta função!               *
    *********************************************************************** **/
}

int obter_num_devolucoes(const Leitor* leitor)
{
   /** ************************************************************************
    *               ATENÇÃO: É preciso implementar esta função!               *
    *********************************************************************** **/
}
