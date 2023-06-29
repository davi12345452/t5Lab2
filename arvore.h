#ifndef ARVORE_H
#define ARVORE_H

// Estrutura que define as características de uma filial
typedef struct Filial {
    int codigo;
    char razao_social[50];
    char endereco[100];
} Filial;

// Estrutura que define os nós de árvores utilizando a estrutura filial
// de maneira a criar uma ABB de filiais. 
typedef struct NoArvore {
    Filial filial;
    struct NoArvore* esquerda;
    struct NoArvore* direita;
} NoArvore;

// Defininição da funções relacionadas somente a manipulação da árvore/filiais/nós

NoArvore* inicializar_arvore();
NoArvore* criar_no_arvore(Filial filial);
NoArvore* inserir_arvore(NoArvore* raiz, Filial filial);
void imprimir_arvore_decrescente(NoArvore* raiz);
NoArvore* remover_arvore(NoArvore* raiz, int codigo);
NoArvore* encontrar_filial_por_codigo(NoArvore* raiz, int codigo);
void desalocar_arvore(NoArvore* raiz);

#endif
