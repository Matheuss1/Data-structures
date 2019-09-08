#include "data.h"

Data criar_data(int dia, int mes, int ano)
{
    Data data;
    data.dia = dia;
    data.mes = mes;
    data.ano = ano;
    return data;
}

int eh_nula(Data data)
{
    if (data.dia + data.mes + data.ano == 0)
        return 1;
    else
        return 0;
}

int eh_menor_que(Data data1, Data data2)
{
    return 0;
}
