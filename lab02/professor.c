#include "professor.h"
#include <string.h>

Professor criar_professor(const char nome[], float salario, const char disciplina[])
{
   Professor professor;
   strcpy(professor.nome, nome);
   professor.salario = salario;
   strcpy(professor.disciplina, disciplina);
   return professor;
}

Professor aplicar_aumento(Professor professor, float porcentagem)
{
   professor.salario *= (1.0+porcentagem); //  Obs.: Não modifique esta função!
   return professor;
}

void obter_nome(Professor professor, char nome[])
{
   strcpy(nome, professor.nome);
}

float obter_salario(Professor professor)
{
   return professor.salario;
}

void obter_disciplina(Professor professor, char disciplina[])
{
      strcpy(disciplina, professor.disciplina);
}
