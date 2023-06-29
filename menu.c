#include "arvore.h"
#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

/*
  Essa função serve para inserir uma filial, através
  de dados fornecidos pelo usuário.
*/
static void inserir_filial(NoArvore **raiz_arvore) {
  Filial filial;
  printf("| Digite o codigo da filial: ");
  scanf("%d", &filial.codigo);
  printf("| Digite a razao social da filial: ");
  scanf(" %[^\n]", filial.razao_social);
  printf("| Digite o endereco da filial: ");
  scanf(" %[^\n]", filial.endereco);

  *raiz_arvore = inserir_arvore(*raiz_arvore, filial);
}

/*
  Essa função serve para chamar a função de remoção de
  filiais, através do código fornecido pelo usuário
*/
static void remover_filial(NoArvore **raiz_arvore, NoLista **cabeca_lista) {
    int codigo;
    printf("| Digite o codigo da filial a ser removida: ");
    scanf("%d", &codigo);

    NoArvore *no_filial_removido = encontrar_filial_por_codigo(*raiz_arvore, codigo);

    // Verificar se a filial foi encontrada
    if (no_filial_removido == NULL) {
        printf("Filial com codigo %d nao encontrada.\n", codigo);
        return; // Finaliza a função aqui já que a filial não foi encontrada
    }

    // Continuar removendo a filial e funcionários associados
    *raiz_arvore = remover_arvore(*raiz_arvore, codigo);
    *cabeca_lista = remover_funcionarios_por_filial(*cabeca_lista, no_filial_removido);
}


/*
  Essa função serve para chamar a função de inserção de funcionários
  na lista, através de dados fornecidos pelo usuário. Ela ainda verifica
  se existe ou não a filial que se deseja cadastrar o usuário, não permi
  tindo o cadastro caso ela não exista na árvore
*/
static void inserir_funcionario(NoArvore *raiz_arvore, NoLista **cabeca_lista) {
  Funcionario funcionario;
  int codigo_filial;

  printf("| Digite o CPF do funcionario: ");
  scanf(" %[^\n]", funcionario.cpf);
  printf("| Digite o nome do funcionario: ");
  scanf(" %[^\n]", funcionario.nome);
  printf("| Digite o codigo da filial em que o funcionario trabalha: ");
  scanf("%d", &codigo_filial);
  printf("| Digite o salario do funcionario: ");
  scanf("%f", &funcionario.salario);

  NoArvore *no_filial = encontrar_filial_por_codigo(raiz_arvore, codigo_filial);

  if (no_filial == NULL) {
    printf(
        "| Filial com codigo %d nao existe. Funcionario nao foi cadastrado.\n",
        codigo_filial);
  } else {
    funcionario.filial = no_filial;
    *cabeca_lista = inserir_lista(*cabeca_lista, funcionario);
    
  }
}

/*
  Essa função serve para chamar a função de remoção de
  funcionários, através do CPF fornecido pelo usuário
*/
static void remover_funcionario(NoLista **cabeca_lista) {
  char cpf[15];
  printf("| Digite o CPF do funcionario a ser removido: ");
  scanf(" %[^\n]", cpf);

  *cabeca_lista = remover_lista(*cabeca_lista, cpf);
}

/*
  Essa função permite a verificação e impressão de funcionários
  por filial, o usuário fornece o código da filial, devolvendo,
  os funcionários. Se não existir a filial, ele devolve que não
  encontrou a filial. Se a filial existir, porém não houver 
  funcionários cadastrados, ela também devolve que não encontrou
  funcionários.
*/
static void verificar_funcionarios_por_filial(NoArvore *raiz_arvore,
                                              NoLista *cabeca_lista) {
  int codigo_filial;
  printf("| Digite o codigo da filial para verificar funcionarios: ");
  scanf("%d", &codigo_filial);

  NoArvore *filial = encontrar_filial_por_codigo(raiz_arvore, codigo_filial);
  if (filial == NULL) {
    printf("| Filial nao encontrada.\n");
    return;
  }

  int encontrou = 0;
  NoLista *atual = cabeca_lista;
  while (atual != NULL) {
    if (atual->funcionario.filial == filial) {
      printf("| CPF: %s, Nome: %s, Salario: %.2f\n", atual->funcionario.cpf,
             atual->funcionario.nome, atual->funcionario.salario);
      encontrou = 1;
    }
    atual = atual->proximo;
  }

  if (!encontrou) {
    printf("| Nenhum funcionario encontrado para a filial de codigo %d.\n",
           codigo_filial);
  }
}

/*
  Essa função imprime uma lista de funcionários, seu CPF e nome e
  a razão social da filial à qual está vinculado. 
*/
static void imprimirVinculo(NoLista *lista) {
  NoLista *atual = lista;
  while (atual != NULL) {
    printf("| CPF: %s, Nome: %s, Razao Social: %s\n", atual->funcionario.cpf,
           atual->funcionario.nome,
           atual->funcionario.filial->filial.razao_social);
    atual = atual->proximo;
  }
}

/*
  Essa uma função de UI de menu, ela é uma função INT que fornece
  uma interface de menu ao usuário, permitindo a entrada de dados
  e devolvendo esses dados, que no caso é a opção escolhida. 
*/
static int exibirMenu() {
  int opc;
  printf("+---------------------------------------+\n");
  printf("| %-37s |\n", "PROGRAMA DE CADASTRO");
  printf("+---------------------------------------+\n");
  printf("| %-2d. %-33s |\n", 1, "Inserir filial");
  printf("| %-2d. %-33s |\n", 2, "Remover filial");
  printf("| %-2d. %-33s |\n", 3, "Imprimir filiais");
  printf("| %-2d. %-33s |\n", 4, "Inserir funcionario");
  printf("| %-2d. %-33s |\n", 5, "Remover funcionario");
  printf("| %-2d. %-33s |\n", 6, "Imprimir funcionarios");
  printf("| %-2d. %-33s |\n", 7, "Verificar funcionarios por filial");
  printf("| %-2d. %-33s |\n", 8, "Vinculo funcionario/filial");
  printf("| %-2d. %-33s |\n", 9, "Sair");
  printf("+---------------------------------------+\n");
  printf("| Escolha uma opcao: ");
  scanf("%d", &opc);
  printf("+---------------------------------------+\n");
  return opc;
}

/*
  Essa função implementa o program, recebe a àrvore e a lista, chamando o
  menu com a opção desejada, fornecendo o desejado pelo usuário. Ela é 
  feita em loop, encerrando-se somente com o desejo do usuário. 
*/
static void logicaPrograma(NoArvore *arvore, NoLista *lista) {
  int opcao;

  do {
    opcao = exibirMenu();
    switch (opcao) {
    case 1:
      inserir_filial(&arvore);
      break;
    case 2:
      remover_filial(&arvore, &lista);
      break;
    case 3:
      imprimir_arvore_decrescente(arvore);
      break;
    case 4:
      inserir_funcionario(arvore, &lista);
      break;
    case 5:
      remover_funcionario(&lista);
      break;
    case 6:
      imprimir_lista(lista);
      break;
    case 7:
      verificar_funcionarios_por_filial(arvore, lista);
      break;
    case 8:
      imprimirVinculo(lista);
      break;
    case 9:
      printf("| Saindo...\n");
      break;
    default:
      printf("| Opcao invalida.\n");
    }
  } while (opcao != 9);
}

/*
  Essa é a função é o programa final em si, inicializa a árvore e a lista,
  chamando a lógica do programa e, ao terminar, desaloca a memória utilizada
*/
void exibir_menu() {
  NoArvore *arvore = inicializar_arvore();
  NoLista *lista = inicializar_lista();
  logicaPrograma(arvore, lista);
  desalocar_arvore(arvore);
  liberar_lista(lista);
}
