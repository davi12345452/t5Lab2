#ifndef LISTA_H
#define LISTA_H

#include "arvore.h"

// Estrutura funcionário, que implementa todas as características necessárias
// além de utilizar um ponteiro para a filial do funcionário; 
typedef struct Funcionario {
    char cpf[15];
    char nome[50];
    NoArvore* filial;
    float salario;
} Funcionario;

// Estrutura de nó que permite a implementação de uma lista simplesmente encadeada
// de elementos do tipo funcionário.
typedef struct NoLista {
    Funcionario funcionario;
    struct NoLista* proximo;
} NoLista;

// Definição das funções utilizadas para manipular, criar, remover a lista ou os funcionários
NoLista* criar_no_lista(Funcionario funcionario);
NoLista* inicializar_lista();
NoLista* inserir_lista(NoLista* cabeca, Funcionario funcionario);
NoLista* remover_lista(NoLista* cabeca, char* cpf);
void imprimir_lista(NoLista* cabeca);
NoLista* remover_funcionarios_por_filial(NoLista* cabeca, NoArvore* no_filial_removido);
void liberar_lista(NoLista* cabeca);

#endif