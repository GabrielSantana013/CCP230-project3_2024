#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> //para gerar a seed de geração aleatória
#include "funcoes.h"

int atualizarCotacao()
{
    FILE *ptrArquivoCripto;
    Criptomoedas criptomoedas;

    int bytesCripto = sizeof(Criptomoedas);
    int menu, i = 0;

    ptrArquivoCripto = fopen("criptomoedas.bin", "rb+");

    if (ptrArquivoCripto == NULL)
    {
        perror("Erro ao abrir o arquivo.");
        return 1;
    }

    // Seleciona a criptomoeda para atualizar a cotação
    do
    {
        printf("\nEscolha a criptomoeda para atualizar a cotacao: \n");
        while (fread(&criptomoedas, bytesCripto, 1, ptrArquivoCripto) == 1)
        {
            printf("%d - %s\n", i + 1, criptomoedas.nomeCripto);
            i++;
        }
        scanf("%d", &menu);

    } while (menu < 1 || menu > (i+1));

    int foundCripto = 0;
    i = 0;

    rewind(ptrArquivoCripto);
    while (fread(&criptomoedas, bytesCripto, 1, ptrArquivoCripto) == 1)
    {
        i++;
        if(menu == i){
            foundCripto = 1;

            // Exibe a cotação antiga
            printf("\nO valor de cotacao da criptomoeda e de %.8lf para a moeda %s\n", criptomoedas.cotacao, criptomoedas.nomeCripto);

            // Gera a seed aleatória
            srand(time(NULL));

            float variacao = 0.0;

            do
            {
                /*
                Gera um valor aleatório entre -0.05 e 0.05 (ou seja, -5% e +5%)
                ((float)rand() / RAND_MAX) gera um valor entre 0 e 1
                Multiplicando por 0.10, temos um valor entre 0 e 0.10
                Subtraindo 0.05, temos um valor entre -0.05 e 0.05
                */
                variacao = ((float)rand() / RAND_MAX) * 0.10 - 0.05;

            } while (variacao == 0);

            float novaCotacao = criptomoedas.cotacao * (1 + variacao);

            // Exibe a cotação antiga, nova e a variação
            printf("\nCotacao antiga: %.8lf\n", criptomoedas.cotacao);
            printf("Nova cotacao: %.8lf\n", novaCotacao);
            printf("Variacao de %.2f%%\n\n", variacao * 100);

            // Atualiza a cotação no registro
            criptomoedas.cotacao = novaCotacao;

            // Posiciona o ponteiro no início do registro novamente
            fseek(ptrArquivoCripto, -bytesCripto, SEEK_CUR);

            // Sobrescreve o registro atualizado
            fwrite(&criptomoedas, bytesCripto, 1, ptrArquivoCripto);

            break;
        }
    }

    // Fecha o arquivo após a atualização ou se não encontrar a criptomoeda
    fclose(ptrArquivoCripto);

    // Verifica se a criptomoeda foi encontrada
    if (!foundCripto)
    {
        printf("Criptomoeda nao encontrada.\n");
        return 1;
    }

    return 0;
}
