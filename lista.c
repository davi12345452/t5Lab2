#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
  Função que permite a criação de um nó, utilizando alocação dinâmica de memória
  para criar a lógica de uma lista simplemente encadeada
*/
NoLista *criar_no_lista(Funcionario funcionario) {
  NoLista *novo_no = (NoLista *)malloc(sizeof(NoLista));
  if (novo_no) {
    novo_no->funcionario = funcionario;
    novo_no->proximo = NULL;
  }
  return novo_no;
}

/*
  Inicializa a lista, criando um ponteiro para ela, porém sem alocar
  memória, já que está vazia
*/
NoLista *inicializar_lista() { return NULL; }

/*
  Função que permite a inserção de um nó de lista dentro da lista previamente
  definida, utilizando um elemento da estrutura funcionário e da função para
  criar nós de lista
*/
NoLista *inserir_lista(NoLista *cabeca, Funcionario funcionario) {
    NoLista *atual = cabeca;
    // Verifica se um funcionário com o mesmo CPF já existe
    while (atual != NULL) {
        if (strcmp(atual->funcionario.cpf, funcionario.cpf) == 0) {
            printf("Um funcionario com o CPF %s ja existe.\n", funcionario.cpf);
            return cabeca; // Retorna a lista inalterada
        }
        atual = atual->proximo;
    }
  
    // Se chegou aqui, significa que não há funcionário com o mesmo CPF
    NoLista *novo_no = criar_no_lista(funcionario);
    novo_no->proximo = cabeca;
    printf("| Funcionario cadastrado com sucesso!\n");
    return novo_no;
}


/*
  Função que permite remover um nó da lista, ou seja, um funcionário,
  através do CPF.
*/
NoLista *remover_lista(NoLista *cabeca, char *cpf) {
  NoLista *temp = cabeca, *prev = NULL;

  if (temp != NULL && strcmp(temp->funcionario.cpf, cpf) == 0) {
    cabeca = temp->proximo;
    free(temp);
    printf("Funcionario com CPF %s removido com sucesso.\n", cpf);
    return cabeca;
  }

  while (temp != NULL && strcmp(temp->funcionario.cpf, cpf) != 0) {
    prev = temp;
    temp = temp->proximo;
  }

  if (temp == NULL){
    printf("Funcionario com CPF %s nao encontrado.\n", cpf);
    return cabeca;
  }
  prev->proximo = temp->proximo;
  free(temp);
  printf("Funcionario com CPF %s removido com sucesso.\n", cpf);

  return cabeca;
}

/*
  Função de impressão, permite a exibição de todos os funcionários
  cadastrados na lista.
*/
void imprimir_lista(NoLista *cabeca) {
  NoLista *atual = cabeca;
  while (atual != NULL) {
    printf("| CPF: %s, Nome: %s, Salario: %.2f\n", atual->funcionario.cpf,
           atual->funcionario.nome, atual->funcionario.salario);
    atual = atual->proximo;
  }
}

/*
  Essa função é um pouco mais complexa, ela é utilizada para remover um
  funcionário assim que uma filial for removida, ou seja, quando a filial de um
  funcionário for removida da árvore de filiais, o programa chamará essa função
  e removerá os fun- cionários que estiverem com essa filial cadastrada.
*/
NoLista *remover_funcionarios_por_filial(NoLista *cabeca,
                                         NoArvore *no_filial_removido) {
  NoLista *atual = cabeca;
  NoLista *prev = NULL;
  int contador = 0;

  while (atual != NULL) {
    if (atual->funcionario.filial == no_filial_removido) {
      if (prev == NULL) {
        cabeca = atual->proximo;
        free(atual);
        atual = cabeca;
      } else {
        prev->proximo = atual->proximo;
        free(atual);
        atual = prev->proximo;
      }
      contador++;
    } else {
      prev = atual;
      atual = atual->proximo;
    }
  }

  printf("%d funcionario(s) removido(s) da filial removida.\n", contador);

  return cabeca;
}

/*
  Essa função server para liberar a memória alocada pelos nós de lista, ou seja,
  da lista em si. É utilizada no final do programa
*/
void liberar_lista(NoLista *cabeca) {
  NoLista *temp;
  while (cabeca != NULL) {
    temp = cabeca;
    cabeca = cabeca->proximo;
    free(temp);
  }
}