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
    if (data1.ano == 0)
        return 0;
    if (data1.ano < data2.ano)
        return 1;
    else if (data1.ano == data2.ano){
        if (data1.mes < data2.mes)
            return 1;
        else if (data1.mes == data2.mes) {
            if (data1.dia < data2.dia)
                return 1;
        }
    }
    return 0;
}
