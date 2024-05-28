#include "listas.h"



CLIENTE autenticarCliente(CLIENTE_NODE *lista, const char *nome, const char *nif) {
    CLIENTE_NODE *atual = lista;
    while (atual != NULL) {
        if (strcmp(atual->info.nome, nome) == 0 && strcmp(atual->info.nif, nif) == 0) {
            return atual->info;  // Retorna o cliente autenticado
        }
        atual = atual->seguinte;
    }
    CLIENTE clienteNaoEncontrado;
    clienteNaoEncontrado.idCliente = -1;  // Define um ID inválido para indicar que o cliente não foi encontrado
    return clienteNaoEncontrado;  // Retorna um cliente com ID inválido
}

// Função para adicionar um cliente à lista
CLIENTE_NODE* adicionarCliente(CLIENTE_NODE *lista, CLIENTE novoCliente) {
    CLIENTE_NODE *novo = (CLIENTE_NODE*)malloc(sizeof(CLIENTE_NODE));
    if (novo != NULL) {
        novo->info = novoCliente;
        novo->seguinte = lista;
    }
    return novo;
}

// Função para listar clientes
void listarClientes(CLIENTE_NODE *lista) {
    CLIENTE_NODE *temp = lista;
    while (temp != NULL) {
        printf("ID: %d\n", temp->info.idCliente);
        printf("Nome: %s\n", temp->info.nome);
        printf("NIF: %s\n", temp->info.nif);
        printf("Telefone: %s\n", temp->info.ntelefone);
        printf("Detalhes da Propriedade de Interesse: %s\n\n", temp->info.detalhesPropriedade);
        temp = temp->seguinte;
    }
}

// Função auxiliar para comparar dois nomes de clientes
int compararNomesClientes(const void *a, const void *b) {
    const CLIENTE *clienteA = (const CLIENTE *)a;
    const CLIENTE *clienteB = (const CLIENTE *)b;
    return strcmp(clienteA->nome, clienteB->nome);
}

// Função para listar clientes por ordem alfabética do nome
void listarClientesPorNome(CLIENTE_NODE *lista) {
    // Contar o número de clientes na lista
    int numClientes = 0;
    CLIENTE_NODE *temp = lista;
    while (temp != NULL) {
        numClientes++;
        temp = temp->seguinte;
    }

    // Criar um array de clientes para facilitar a ordenação
    CLIENTE *clientes = (CLIENTE *)malloc(numClientes * sizeof(CLIENTE));
    if (clientes == NULL) {
        printf("Erro: Falha ao alocar memória.\n");
        return;
    }

    // Preencher o array de clientes com os dados da lista
    int i = 0;
    temp = lista;
    while (temp != NULL) {
        clientes[i++] = temp->info;
        temp = temp->seguinte;
    }

    // Ordenar o array de clientes por ordem alfabética do nome
    qsort(clientes, numClientes, sizeof(CLIENTE), compararNomesClientes);

    // Exibir os clientes ordenados
    printf("Lista de Clientes por Ordem Alfabética do Nome:\n");
    for (i = 0; i < numClientes; i++) {
        printf("ID: %d\n", clientes[i].idCliente);
        printf("Nome: %s\n", clientes[i].nome);
        printf("NIF: %s\n", clientes[i].nif);
        printf("Telefone: %s\n", clientes[i].ntelefone);
        printf("Detalhes da Propriedade de Interesse: %s\n\n", clientes[i].detalhesPropriedade);
    }

    // Liberar a memória alocada para o array de clientes
    free(clientes);
}

// Função para apresentar as informações de um cliente dado o seu NIF
void apresentarClientePorNIF(CLIENTE_NODE *lista, const char *nif) {
    CLIENTE_NODE *temp = lista;
    while (temp != NULL) {
        if (strcmp(temp->info.nif, nif) == 0) {
            printf("ID: %d\n", temp->info.idCliente);
            printf("Nome: %s\n", temp->info.nome);
            printf("NIF: %s\n", temp->info.nif);
            printf("Telefone: %s\n", temp->info.ntelefone);
            printf("Detalhes da Propriedade de Interesse: %s\n\n", temp->info.detalhesPropriedade);
            return;
        }
        temp = temp->seguinte;
    }
    printf("Cliente com NIF %s não encontrado.\n", nif);
}

// Função para remover um cliente da lista
CLIENTE_NODE* removerCliente(CLIENTE_NODE *lista, const char *nif) {
    CLIENTE_NODE *temp = lista;
    CLIENTE_NODE *anterior = NULL;

    while (temp != NULL) {
        if (strcmp(temp->info.nif, nif) == 0) {
            if (anterior == NULL) {
                lista = temp->seguinte;
            } else {
                anterior->seguinte = temp->seguinte;
            }
            free(temp);
            printf("Cliente com NIF %s removido com sucesso.\n", nif);
            return lista;
        }
        anterior = temp;
        temp = temp->seguinte;
    }
    printf("Cliente com NIF %s não encontrado.\n", nif);
    return lista;
}

// Função para atualizar um cliente na lista
void atualizarCliente(CLIENTE_NODE *lista, const char *nif, CLIENTE clienteAtualizado) {
    CLIENTE_NODE *temp = lista;
    while (temp != NULL) {
        if (strcmp(temp->info.nif, nif) == 0) {
            temp->info = clienteAtualizado;
            printf("Cliente com NIF %s atualizado com sucesso.\n", nif);
            return;
        }
        temp = temp->seguinte;
    }
    printf("Cliente com NIF %s não encontrado.\n", nif);
}
