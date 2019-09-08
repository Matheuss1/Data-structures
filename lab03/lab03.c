#include <stdio.h>
#include <stdlib.h>
#include "livro.h"
#include "leitor.h"

void fazer_registro(Leitor* leitor, int i);
int converte_data(const char* data);
int converte_ano(const char* data);

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

   int i, j; // auxiliares
   // -------------------- criacao livros --------------------------
   for (i = 0; i < m; i++) {
      scanf(" %[^\n]", titulo);
      Data data = criar_data( converte_data(titulo), 
                              converte_data(titulo+3),
                              converte_data(titulo + 6));
      livros[i] = criar_livro(&titulo[11], data);
   }

   // ------------------ criacao leitores -------------------------
   for (i = 0; i < n; i++) {
      int e; // numero de emprestimos + restituicoes
      scanf(" %s", nome);
      scanf("%d", &e);
      leitores[i] = criar_leitor(nome, e);

      for (j = 0; j < e; j++) {
         int codigo;
         scanf("%d", &codigo);
         fazer_registro(&leitores[i], codigo);
      }
   }
   
   scanf(" %[^\n]", titulo); // faz leitura da data de consulta

   return 0;
}

void fazer_registro(Leitor* leitor, int i)
{
   if (i < 0)
      registrar_devolucao(leitor, abs(i));
   else
      registrar_restituicao(leitor, abs(i));
}

int converte_data(const char* data)
{
   int a = ( (*data) - '0' ) * 10;
   int b = ( ( *(data + 1) ) - '0' );
   return a + b;
}
int converte_ano(const char* data)
{
   int a = (*data - '0' ) * 1000;
   int b = (*(data + 1) - '0' ) * 100;
   int c = (*(data + 2) - '0' ) * 10;
   int d = *(data + 3) - '0';

   return a+b+c+d;
}