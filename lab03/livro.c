#include "livro.h"
#include <string.h>

Livro criar_livro(const char* titulo, Data emprestimo)
{
    Livro livro;
    int i;
    for (i = 0; titulo[i] != '\0'; i++) {
        livro.titulo[i] = titulo[i];
    }
    livro.titulo[i] = '\0';
    livro.emprestimo = emprestimo;
    return livro;
}

Data obter_data_emprestimo(const Livro* livro)
{
    return (*livro).emprestimo;
}

const char* obter_titulo(const Livro* livro)
{
    return (*livro).titulo;
}
