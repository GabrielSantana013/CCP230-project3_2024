#include <stdio.h>
#include "funcoes.h"
#include <string.h>

int login(Usuario *ptrUsuario){

    FILE *ptrArquivo;
    Usuario usuario;
    
    ptrArquivo = fopen("clientes.bin", "rb");
    if (ptrArquivo == NULL) {
        perror("Erro ao abrir o arquivo para leitura");
        return 1;
    }

    while(fread(&usuario, sizeof(Usuario), 1, ptrArquivo) == 1)
    {
        if(strcmp(usuario.cpf, ptrUsuario->cpf) == 0 && strcmp(usuario.senha, ptrUsuario->senha) == 0)
        {
            fclose(ptrArquivo);
            return 1;
        }
    }

    return 0;

}