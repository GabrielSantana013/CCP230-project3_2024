#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

int consultarSaldo(Usuario *ptrUsuario)
{
    FILE *ptrArquivo;
    Usuario usuario;
    size_t bytes = sizeof(Usuario);

    
    printf("Digite o CPF do investidor: ");
    fgets(ptrUsuario->cpf, sizeof(ptrUsuario->cpf), stdin);
    ptrUsuario->cpf[strcspn(ptrUsuario->cpf, "\n")] = '\0'; // Remove a nova linha

    int found = 0;
    ptrArquivo = fopen("clientes.bin", "rb");

    if (ptrArquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    // Lê os registros e verifica se o CPF existe
    while(fread(&usuario, bytes, 1, ptrArquivo) == 1)
    {
        if(strcmp(usuario.cpf, ptrUsuario->cpf) == 0)
        {
            printf("O saldo do usuario %s é de R$: %.2f\n", usuario.cpf, usuario.saldoReais);
            found = 1;
            break;
        }
    }

    if(!found)
    {
        printf("Usuário não encontrado.\n");
    }

    fclose(ptrArquivo);
    return 0;
}
