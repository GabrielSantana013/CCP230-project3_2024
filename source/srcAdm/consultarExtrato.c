#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

int consultarExtrato(Usuario *ptrUsuario)
{

    FILE *ptrArquivoExtrato;
    Extrato extrato;

    printf("Digite o CPF do investidor: ");
    fgets(ptrUsuario->cpf, sizeof(ptrUsuario->cpf), stdin);
  

    ptrArquivoExtrato = fopen("extrato.bin", "rb");

    if (ptrArquivoExtrato == NULL)
    {
        ptrArquivoExtrato = fopen("extrato.bin", "wb");
    }
    else
    {
        int foundExtrato = 0;
        while (fread(&extrato, sizeof(Extrato), 1, ptrArquivoExtrato))
        {
            if (strcmp(extrato.CPF, ptrUsuario->cpf) == 0)
            {
                printf("CPF: %s\n", extrato.CPF);
                printf("Tipo de operacao: %s\n", extrato.tipoOperacao);

                char dataFormatada[20];
                //converte a data para string
                //tm é uma struct que armazena a data e hora, localtime converte o time_t para tm
                struct tm *tm_info = localtime(&extrato.data);
                //strftime converte a struct tm para string
                strftime(dataFormatada, sizeof(dataFormatada), "%d-%m-%Y %H:%M:%S", tm_info);
                printf("Data: %s\n", dataFormatada);
                printf("Valor: R$%.2f\n", extrato.valor);
                printf("Moeda negociada: %s\n", extrato.nomeMoeda);
                printf("Taxa da transacao: %.2f%%\n\n", extrato.taxaTransacao);
                foundExtrato = 1;
            }
        }

        if (foundExtrato == 0)
        {
            fclose(ptrArquivoExtrato);
            return 0;
        }

        fclose(ptrArquivoExtrato);
    }
    return 1;
}