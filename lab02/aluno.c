#include "aluno.h"
#include <string.h>

Aluno criar_aluno(int registro_academico, float desempenho)
{
    Aluno aluno;
    aluno.registro_academico = registro_academico;
    aluno.desempenho = desempenho;
    aluno.num_disciplinas = 0;
    return aluno;
}

Aluno adicionar_disciplina(Aluno aluno, const char disciplina[])
{
    int index = aluno.num_disciplinas;
    strcpy(aluno.disciplinas[index], disciplina);
    aluno.num_disciplinas += 1;
    return aluno;
}

float obter_desempenho(Aluno aluno)
{
    return aluno.desempenho;
}

int validar_matricula(Aluno aluno, const char disciplina[])
{
    int i, auxiliar = 0;
    for (i = 0; i < aluno.num_disciplinas; i++) {
        auxiliar = strcmp(disciplina, aluno.disciplinas[i]);
        if (auxiliar == 0)
            return 1;
    }
    return 0;
}
