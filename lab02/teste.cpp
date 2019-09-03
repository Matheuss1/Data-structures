#include <stdio.h>
#include <string.h>

#define MAXCHAR_PNOME 30 // nº máximo de carateres para o nome do professor
#define MAXCHAR_CODIGO 6 // nº máximo de carateres para o código da disciplina

typedef struct {
	char nome[MAXCHAR_PNOME];
	float salario;
	char disciplina[MAXCHAR_CODIGO];
} Professor;

Professor criar_professor(const char nome[]);

int main()
{
    Professor a;
    char nome[10];
    scanf("%s", nome);
    a = criar_professor(nome);
    printf("%s\n", a.nome);
    Professor b;
    scanf("%s", nome);
    b = criar_professor(nome);
    printf("%s\n", b.nome);
}

Professor criar_professor(const char nome[])
{
    Professor professor;
    memcpy(professor.nome, nome, sizeof(nome));
    return professor;
}