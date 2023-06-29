#include "arvore.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
  Função que inicializa a árvore através de uma estrutura NoArvore. Ela cria um ponteiro,
  porém, sem alocar memória, já que está vazio. 
*/
NoArvore* inicializar_arvore() {
    return NULL;
}

/*
  Função que cria nós para a árvore, alocando o espaço necessário dinamicamente.
*/
NoArvore *criar_no_arvore(Filial filial) {
    NoArvore *novo_no = (NoArvore *)malloc(sizeof(NoArvore));
    if (novo_no) {
        novo_no->filial = filial;
        novo_no->esquerda = NULL;
        novo_no->direita = NULL;
    }
    return novo_no;
}

/*
 Insere nós, utilizando a função criar nós, seguindo a lógica de ABBs
*/
NoArvore *inserir_arvore(NoArvore *raiz, Filial filial) {
    if (!raiz) {
        return criar_no_arvore(filial);
    }

    if (filial.codigo < raiz->filial.codigo) {
        raiz->esquerda = inserir_arvore(raiz->esquerda, filial);
    } else if (filial.codigo > raiz->filial.codigo) {
        raiz->direita = inserir_arvore(raiz->direita, filial);
    }
    return raiz;
}

/*
  Função que imprime a árvore de maneira decrescente no console. 
*/
void imprimir_arvore_decrescente(NoArvore *raiz) {
    if (raiz) {
        imprimir_arvore_decrescente(raiz->direita);
        printf("| Codigo: %d, Razao Social: %s, Endereco: %s \n",
               raiz->filial.codigo, raiz->filial.razao_social,
               raiz->filial.endereco);
        imprimir_arvore_decrescente(raiz->esquerda);
    }
}


/*
  Função que busca o ponteiro do nó com valor mínimo. 
*/

static NoArvore *min_valor_no(NoArvore *no) {
  NoArvore *atual = no;
  while (atual && atual->esquerda != NULL) {
    atual = atual->esquerda;
  }
  return atual;
}

/*
  Essa função serve para remover nós de acordo com o seu código
*/
NoArvore *remover_arvore(NoArvore *raiz, int codigo) {
  if (!raiz)
    return raiz;

  if (codigo < raiz->filial.codigo) {
    raiz->esquerda = remover_arvore(raiz->esquerda, codigo);
  } else if (codigo > raiz->filial.codigo) {
    raiz->direita = remover_arvore(raiz->direita, codigo);
  } else {
    if (!raiz->esquerda) {
      NoArvore *temp = raiz->direita;
      free(raiz);
      return temp;
    } else if (!raiz->direita) {
      NoArvore *temp = raiz->esquerda;
      free(raiz);
      return temp;
    }

    NoArvore *temp = min_valor_no(raiz->direita);
    raiz->filial = temp->filial;
    raiz->direita = remover_arvore(raiz->direita, temp->filial.codigo);
  }
  return raiz;
}

/*
  Essa função encontra um nó/filial de acordo com o seu código.
*/
NoArvore *encontrar_filial_por_codigo(NoArvore *raiz, int codigo) {
  if (raiz == NULL || raiz->filial.codigo == codigo) {
    return raiz;
  }
  if (codigo < raiz->filial.codigo) {
    return encontrar_filial_por_codigo(raiz->esquerda, codigo);
  }
  return encontrar_filial_por_codigo(raiz->direita, codigo);
}

/*
  Essa função desaloca a memória atribuída aos nós da árvore, sendo
  utilizada no final do programa. 
*/
void desalocar_arvore(NoArvore *raiz) {
    if (raiz) {
        desalocar_arvore(raiz->esquerda);
        desalocar_arvore(raiz->direita);
        free(raiz);
    }
}