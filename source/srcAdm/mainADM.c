#include <funcoes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

  // cria criptos ao iniciar modulo de adm
  FILE *ptrArquivo;

  ptrArquivo = fopen("criptomoedas.bin", "rb");
  if (ptrArquivo == NULL) // só cria se não existir
  {
    ptrArquivo = fopen("criptomoedas.bin", "wb");
    if (ptrArquivo == NULL) {
      perror("Erro ao abrir o arquivo");
      return 1;
    } else {
      const char *nomesCriptos[] = {"Bitcoin", "Ethereum", "Ripple"};
      const float taxasCompra[] = {2.0, 1.0, 1.0};
      const float taxasVenda[] = {3.0, 2.0, 1.0};
      const float cotacoes[] = {50000, 20000, 10};

      for (int i = 0; i < 3; i++) {
        Criptomoedas criptomoedas;
        strcpy(criptomoedas.nomeCripto, nomesCriptos[i]);
        criptomoedas.cotacao = cotacoes[i];
        criptomoedas.txCompra = taxasCompra[i];
        criptomoedas.txVenda = taxasVenda[i];
        fwrite(&criptomoedas, sizeof(Criptomoedas), 1, ptrArquivo);
      }
    }
  }
  fclose(ptrArquivo);

    // bloco para cadastrar o ADM caso não exista o arquivo clientes.bin
    FILE *ptrArquivoClientes;
    Usuario adm, *ptrADM;
    ptrADM = &adm;
    ptrArquivoClientes = fopen("clientes.bin", "rb+");
 
    if (ptrArquivoClientes == NULL)
    {
        ptrArquivoClientes = fopen("clientes.bin", "wb+");
        if (ptrArquivoClientes == NULL)
        {
            printf("Erro ao abrir o arquivo.\n");
            exit(1);
        }
        else
        {
            strcpy(adm.cpf, "12312312312");
            strcpy(adm.senha, "admin\n");
            adm.saldoReais = 0;
            adm.qttExtrato = 0;
            int retorno = cadastro(ptrADM);
        }
    }
    fclose(ptrArquivoClientes);

    printf("\nDigite seu CPF: ");
    fgets(ptrADM->cpf, sizeof(ptrADM->cpf), stdin);

    if (strlen(ptrADM->cpf) == 11) { // Limpa o buffer apenas se o CPF tiver 11 caracteres
        limpaBuffer();
    }

    printf("Digite sua senha: ");
    fgets(ptrADM->senha, sizeof(ptrADM->senha), stdin);

    if(strcmp(ptrADM->cpf, "12312312312") != 0 || strcmp(ptrADM->senha, "admin\n") != 0)
    {
        printf("CPF ou senha invalidos.\n\n");
        return -1;
    }

    int status = login(ptrADM); // 1 = logado, 0 = não logado
    
    if (status)
    {
        printf("\nLogin realizado com sucesso!\n");
    }
    else
    {
        printf("CPF ou senha invalidos.\n\n");
        return -1;
    }

  int retorno;

  do {
    Usuario usuario, *ptrUsuario;
    ptrUsuario = &usuario;
    int status = 0;

    retorno = exibirMenuADM();

    switch (retorno) {
    case 1:
      limpaBuffer();
      status = cadastroInvestidor(ptrUsuario);
      if (status) {
        printf("Algum erro ocorreu durante a operacao. Por favor, tente "
               "novamente.\n\n");
      }
      break;
    case 2:
      limpaBuffer();
      status = excluirInvestidor(ptrUsuario);
      if (status) {
        printf("Algum erro ocorreu durante a operacao. Por favor, tente "
               "novamente.\n\n");
      }
      break;
    case 3:
      limpaBuffer();
      status = cadastroCripto();
      if (status) {
        printf("Algum erro ocorreu durante a operacao. Por favor, tente "
               "novamente.\n\n");
      }
      break;
    case 4:
      limpaBuffer();
      excluirCripto();
      break;
    case 5:
      limpaBuffer();
      consultarSaldo(ptrUsuario);
      break;
    case 6:
      limpaBuffer();
      consultarExtrato(ptrUsuario);
      break;
    case 7:
      status = atualizarCotacao();
      if (status) {
        printf("Algum erro ocorreu durante a operacao. Por favor, tente "
               "novamente.\n\n");
      }
      break;
    case 8:
      printf("Saindo...\n");
      break;
    default:
      break;
    }
  } while (retorno != 8);

  return 0;
}