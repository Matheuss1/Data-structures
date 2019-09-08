#include <stdio.h>
#include <stdlib.h>
#include "livro.h"
#include "leitor.h"

void fazer_registro(Leitor* leitor, int i);
int converte_data(const char* data);
int converte_ano(const char* data);
Data nova_data(const char* string_data);
void consultar_restituicoes(Leitor* leitores, Livro* livros, int i, Data consulta, int* mostrar_nome);
void consultar_devolucoes(Leitor* leitores, Livro* livros, int i, Data consulta, int* mostrar_nome);

int main()
{
   char titulo[MAXCHAR_TITULO]; // string para a leitura do título
   char nome[MAXCHAR_LNOME];    // string para a leitura do nome

   Livro* livros = NULL;        // ponteiro para o vetor de livros
   Leitor* leitores = NULL;     // ponteiro para o vetor de leitores

   int m, n;
   scanf("%d%d", &m, &n);
   livros = malloc(m * sizeof(Livro));
   leitores = malloc(n * sizeof(Leitor));

   int i, j; // auxiliares
   char string_data[11];
   // -------------------- criacao livros --------------------------
   for (i = 0; i < m; i++) {
      scanf("%s", string_data);
      scanf(" %[^\n]", titulo);
      scanf("%*c");
      Data data = nova_data(string_data);
      livros[i] = criar_livro(titulo, data);
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
   scanf(" %[^\n]", string_data); // faz leitura da data de consulta
   Data consulta = nova_data(string_data);
   for (i = 0; i < n; i++) {
      int mostrar_nome = 0;
      consultar_restituicoes(leitores, livros, i, consulta, &mostrar_nome);
      consultar_devolucoes(leitores, livros, i, consulta, &mostrar_nome);
   }

   return 0;
}


void fazer_registro(Leitor* leitor, int i)
{
   if (i < 0)
      registrar_devolucao(leitor, abs(i));
   else
      registrar_restituicao(leitor, abs(i));
}

int converte_data(const char* data) //converte as strings dia e mes para int
{
   int a = ( (*data) - '0' ) * 10;
   int b = ( ( *(data + 1) ) - '0' );
   return a + b;
}
int converte_ano(const char* data) //converte a string ano para int
{
   int a = (*data - '0' ) * 1000;
   int b = (*(data + 1) - '0' ) * 100;
   int c = (*(data + 2) - '0' ) * 10;
   int d = *(data + 3) - '0';
   return a+b+c+d;
}

Data nova_data(const char* string_data) {
   return criar_data(converte_data(string_data),
                     converte_data(string_data+3),
                     converte_ano(string_data + 6));
}
void consultar_restituicoes(Leitor* leitores, Livro* livros, int i, Data consulta, int* mostrar_nome) {
   int j;
   int num_livro;
   for (j = 0; j < obter_num_restituicoes(&leitores[i]); j++) {
      num_livro = obter_restituicoes(&leitores[i])[j];
      if (eh_menor_que(livros[num_livro - 1].emprestimo, consulta)) {
         if (*mostrar_nome == 0) {
            printf("%s\n", obter_nome(&leitores[i]));
            *mostrar_nome = 1;
         }
         printf("Restituição: %s\n", livros[num_livro - 1].titulo);
      }
   }
}
void consultar_devolucoes(Leitor* leitores, Livro* livros, int i, Data consulta, int* mostrar_nome) {
   int num_livro;
   int j;
   for (j = 0; j < obter_num_devolucoes(&leitores[i]); j++) {
      num_livro = obter_devolucoes(&leitores[i])[j];
      if (eh_menor_que(livros[num_livro - 1].emprestimo, consulta)) {
         if (*mostrar_nome == 0) {
            printf("%s\n", obter_nome(&leitores[i]));
            *mostrar_nome = 1;
         }
         printf("Devolução: %s\n", livros[num_livro - 1].titulo);
      }
   }
}
