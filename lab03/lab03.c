#include <stdio.h>
#include <stdlib.h>
#include "livro.h"
#include "leitor.h"

int main()
{
   char titulo[MAXCHAR_TITULO]; // string para a leitura do título
   char nome[MAXCHAR_LNOME];    // string para a leitura do nome

   Livro* livros = NULL;        // ponteiro para o vetor de livros
   Leitor* leitores = NULL;     // ponteiro para o vetor de leitores

   int m, n;
   scanf("%d%d", &m, &n);
   livros = malloc(m * sizeof(int*));
   leitores = malloc(n * sizeof(int*));

   int i; // auxiliar
   for (i = 0; i < m; i++) {
      scanf(" %[^\n]", titulo);
      char* lixo;
      Data data = criar_data( (int)strol(titulo, &lixo, 10), 
                              (int)strol(titulo+3, &lixo, 10),
                              (int)strol(titulo + 6, &lixo, 10));
      livros[i] = criar_livro(titulo[11], data);
   }
   for (i = 0; i < n; i++) {
      scanf(" %[^\n]", nome);
      leitores[i] = criar_leitor();
   }
   
   scanf(" %[^\n]", titulo); // faz leitura da data de consulta

   return 0;
}
