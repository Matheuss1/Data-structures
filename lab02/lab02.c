#include <stdio.h>

#include "aluno.h"
#include "professor.h"

#define MAX_M 100 // nº máximo de professores
#define MAX_N 200 // nº máximo de alunos

void processar_aumento(Professor professores[], Aluno alunos[], int m, int n);

int main()
{
    /** ***********************************************************************
    *          ATENÇÃO: A função principal não deve ser modificada!           *
    *********************************************************************** **/

   Professor professores[MAX_M];  // vetor para o conjunto de professores
   Aluno alunos[MAX_N];           // vetor para o conjunto de alunos

   char nome[MAXCHAR_PNOME], disciplina[MAXCHAR_CODIGO];
   float salario, desempenho;
   int registro_academico, num_disciplinas;

   int m, n;

   scanf("%d", &m); // lê o nº de professores

   for (int i = 0; i < m; ++i) { // segue com a leitura dos professores
      scanf(" %s %f %s", nome, &salario, disciplina);
      professores[i] = criar_professor(nome, salario, disciplina);
   }

	scanf("%d", &n);  // lê o nº de alunos

   for (int i = 0; i < n; ++i) { // segue com a leitura dos alunos

      scanf("%d %f %d", &registro_academico, &desempenho, &num_disciplinas);
      alunos[i] = criar_aluno(registro_academico, desempenho);

      while (num_disciplinas > 0) {
         scanf(" %s", disciplina);
         alunos[i] = adicionar_disciplina(alunos[i], disciplina);
         num_disciplinas -= 1;
      }
   }

	processar_aumento(professores, alunos, m, n); // processa a bonificação

   for (int i = 0; i < m; ++i) { // segue com a impressão da saída
      obter_nome(professores[i], nome);
      printf("%s %.2f\n", nome, obter_salario(professores[i]));
   }

	return 0;
}

/**
 * Esta função recebe como parâmetro um conjunto de variáveis que abstraem a
 * entrada do problema e realiza a bonificação salarial dos professores
 * conforme especificado no enunciado da tarefa.
 */

void processar_aumento(Professor professores[], Aluno alunos[], int m, int n)
{

   /** ************************************************************************
    *               ATENÇÃO: É preciso implementar esta função!               *
    *********************************************************************** **/

    // Esta função não devem acessar diretamente os campos de uma TAD (i.e.,
    // os campos das estruturas do Professor ou Aluno, tais como 'disciplina').

    // Para a implementação desta função você deverá fazer a chamada de funções
    // que operação sobre os TADs (conforme os protótipos definidos nos arquivos
    // de cabeçalho).

    // Para a bonificação salarial, deverá chamar a função 'aplicar_aumento'.
    // Obs.: a função devolve uma variável do tipo Professor na qual aplicou-se
    // a bonificação salarial. No entanto, ESTÁ PROIBIDO A IMPRESSÃO DA SAÍDA
    // NO ESCOPO DESTA FUNÇÃO. Você deverá sobrescrever a variável do vetor
    // 'professores' que corresponde ao professor com a bonificação salarial.
   int i, j;
   char disciplina[MAXCHAR_CODIGO];
   for (i = 0; i < m; i++) {
      obter_disciplina(professores[i], disciplina);
      float desempenho = 11.0;
      for (j = 0; j < n; j++) {
         if(validar_matricula(alunos[j], disciplina)) {
            if (desempenho > obter_desempenho(alunos[j])) {
               desempenho = obter_desempenho(alunos[j]);
            }
         }
      }
      if (desempenho >= 8.5 && desempenho < 9.0)
         professores[i] = aplicar_aumento(professores[i], 0.05);
      else if (desempenho >= 9.0 && desempenho < 10.0)
         professores[i] = aplicar_aumento(professores[i], 0.1);
      else if (desempenho == 10.0)
         professores[i] = aplicar_aumento(professores[i], 0.15);
   }
}
