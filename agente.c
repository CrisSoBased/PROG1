#include "listas.h"



AGENTE* autenticarAgente(AGENTE_NODE *lista, const char *nome, const char *nif) {
    AGENTE_NODE *atual = lista;
    while (atual != NULL) {
        if (strcmp(atual->info.nome, nome) == 0 && strcmp(atual->info.nif, nif) == 0) {
            return &atual->info;  // Autenticação bem-sucedida, retorna ponteiro para AGENTE
        }
        atual = atual->seguinte;
    }
    return NULL;  // Falha na autenticação
}

AGENTE_NODE* adicionarAgente(AGENTE_NODE *lista, AGENTE novoAgente) {
    AGENTE_NODE *novo = (AGENTE_NODE*)malloc(sizeof(AGENTE_NODE));
    if (novo != NULL) {
        novo->info = novoAgente;
        novo->seguinte = lista;
    }
    return novo;
}


void listarAgentes(AGENTE_NODE *lista) {
    AGENTE_NODE *temp = lista;
    while (temp != NULL) {
        printf("ID: %d\n", temp->info.idAgente);
        printf("Nome: %s\n", temp->info.nome);
        printf("NIF: %s\n", temp->info.nif);
        printf("Morada: %s\n", temp->info.morada);
        printf("Telefone: %s\n", temp->info.ntelefone);
        printf("Data de Nascimento: %s\n", temp->info.datanascimento);
        printf("Tipo de Conta: %d\n\n", temp->info.tipoconta);
        temp = temp->seguinte;
    }
}

// Função para colocar um agente como indisponível
void tornarAgenteIndisponivel(AGENTE_NODE *lista, int idAgente) {
    AGENTE_NODE *temp = lista;
    while (temp != NULL) {
        if (temp->info.idAgente == idAgente) {
            temp->info.disponibilidade = 1; // Definir a disponibilidade como indisponível
            printf("Agente com ID %d agora está indisponível.\n", idAgente);
            return;
        }
        temp = temp->seguinte;
    }
    printf("Agente com ID %d não encontrado.\n", idAgente);
}

// Função auxiliar para comparar dois nomes de agentes
int compararNomes(const void *a, const void *b) {
    const AGENTE *agenteA = (const AGENTE *)a;
    const AGENTE *agenteB = (const AGENTE *)b;
    return strcmp(agenteA->nome, agenteB->nome);
}

// Função para listar agentes por ordem alfabética do nome
void listarAgentesPorNome(AGENTE_NODE *lista) {
    // Contar o número de agentes na lista
    int numAgentes = 0;
    AGENTE_NODE *temp = lista;
    while (temp != NULL) {
        numAgentes++;
        temp = temp->seguinte;
    }

    // Criar um array de agentes para facilitar a ordenação
    AGENTE *agentes = (AGENTE *)malloc(numAgentes * sizeof(AGENTE));
    if (agentes == NULL) {
        printf("Erro: Falha ao alocar memória.\n");
        return;
    }

    // Preencher o array de agentes com os dados da lista
    int i = 0;
    temp = lista;
    while (temp != NULL) {
        agentes[i++] = temp->info;
        temp = temp->seguinte;
    }

    // Ordenar o array de agentes por ordem alfabética do nome
    qsort(agentes, numAgentes, sizeof(AGENTE), compararNomes);

    // Exibir os agentes ordenados
    printf("Lista de Agentes por Ordem Alfabética do Nome:\n");
    for (i = 0; i < numAgentes; i++) {
        printf("ID: %d\n", agentes[i].idAgente);
        printf("Nome: %s\n", agentes[i].nome);
        printf("NIF: %s\n", agentes[i].nif);
        printf("Morada: %s\n", agentes[i].morada);
        printf("Telefone: %s\n", agentes[i].ntelefone);
        printf("Data de Nascimento: %s\n", agentes[i].datanascimento);
        printf("Tipo de Conta: %d\n\n", agentes[i].tipoconta);
    }

    // Liberar a memória alocada para o array de agentes
    free(agentes);
}


// Função auxiliar para converter data de nascimento (dd/mm/yyyy) para struct tm
int parseDataNascimento(const char *dataNascimento, struct tm *tm_nascimento) {
    if (sscanf(dataNascimento, "%d/%d/%d", &tm_nascimento->tm_mday, &tm_nascimento->tm_mon, &tm_nascimento->tm_year) != 3) {
        return -1;
    }
    tm_nascimento->tm_mon -= 1;  // Ajusta o mês (0-11)
    tm_nascimento->tm_year -= 1900;  // Ajusta o ano (desde 1900)
    tm_nascimento->tm_hour = 0;
    tm_nascimento->tm_min = 0;
    tm_nascimento->tm_sec = 0;
    tm_nascimento->tm_isdst = -1;  // Não considerar horário de verão

    return 0;
}

int calcularIdade(const char *dataNascimento) {
    struct tm tm_nascimento = {0};

    if (parseDataNascimento(dataNascimento, &tm_nascimento) != 0) {
        printf("Erro: Formato de data inválido.\n");
        return -1;
    }

    time_t tempoNascimento = mktime(&tm_nascimento);
    time_t tempoAtual = time(NULL);

    if (tempoNascimento == -1 || tempoAtual == -1) {
        printf("Erro: Não foi possível obter o tempo.\n");
        return -1;
    }

    double diferencaSegundos = difftime(tempoAtual, tempoNascimento);
    int idade = (int)(diferencaSegundos / (365.25 * 24 * 3600));

    return idade;
}

// Função auxiliar para comparar duas idades de agentes
int compararIdades(const void *a, const void *b) {
    const AGENTE *agenteA = (const AGENTE *)a;
    const AGENTE *agenteB = (const AGENTE *)b;
    // Aqui, usamos a função auxiliar calcularIdade para obter a idade
    int idadeA = calcularIdade(agenteA->datanascimento);
    int idadeB = calcularIdade(agenteB->datanascimento);
    return idadeA - idadeB;
}

// Função para listar agentes, ordenados por idade ascendente
void listarAgentesPorIdade(AGENTE_NODE *lista) {
    // Contar o número de agentes na lista
    int numAgentes = 0;
    AGENTE_NODE *temp = lista;
    while (temp != NULL) {
        numAgentes++;
        temp = temp->seguinte;
    }

    // Criar um array de agentes para facilitar a ordenação
    AGENTE *agentes = (AGENTE *)malloc(numAgentes * sizeof(AGENTE));
    if (agentes == NULL) {
        printf("Erro: Falha ao alocar memória.\n");
        return;
    }

    // Preencher o array de agentes com os dados da lista
    int i = 0;
    temp = lista;
    while (temp != NULL) {
        agentes[i++] = temp->info;
        temp = temp->seguinte;
    }

    // Ordenar o array de agentes por idade ascendente
    qsort(agentes, numAgentes, sizeof(AGENTE), compararIdades);

    // Exibir os agentes ordenados por idade
    printf("Lista de Agentes por Idade Ascendente:\n");
    for (i = 0; i < numAgentes; i++) {
        printf("ID: %d\n", agentes[i].idAgente);
        printf("Nome: %s\n", agentes[i].nome);
        printf("NIF: %s\n", agentes[i].nif);
        printf("Morada: %s\n", agentes[i].morada);
        printf("Telefone: %s\n", agentes[i].ntelefone);
        printf("Data de Nascimento: %s\n", agentes[i].datanascimento);
        printf("Tipo de Conta: %d\n\n", agentes[i].tipoconta);
    }

    // Liberar a memória alocada para o array de agentes
    free(agentes);
}


// Função para gerar um relatório de agentes em um arquivo de texto
void gerarRelatorioAgentes(AGENTE_NODE *lista) {
    const char *nomeArquivo = "relatorio_agentes.txt";
    FILE *arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", nomeArquivo);
        return;
    }

    AGENTE_NODE *temp = lista;
    while (temp != NULL) {
        fprintf(arquivo, "ID: %d\n", temp->info.idAgente);
        fprintf(arquivo, "Nome: %s\n", temp->info.nome);
        fprintf(arquivo, "NIF: %s\n", temp->info.nif);
        fprintf(arquivo, "Morada: %s\n", temp->info.morada);
        fprintf(arquivo, "Telefone: %s\n", temp->info.ntelefone);
        fprintf(arquivo, "Data de Nascimento: %s\n", temp->info.datanascimento);
        fprintf(arquivo, "Tipo de Conta: %d\n\n", temp->info.tipoconta);
        temp = temp->seguinte;
    }

    fclose(arquivo);
    printf("Relatório de agentes gerado com sucesso no arquivo %s.\n", nomeArquivo);
}

void atualizarAgente(AGENTE_NODE *listaAgentes, const char *nif, AGENTE agenteAtualizado) {
    AGENTE_NODE *atual = listaAgentes;

    // Percorre a lista até encontrar o agente com o NIF correspondente
    while (atual != NULL) {
        if (strcmp(atual->info.nif, nif) == 0) {
            // Atualiza as informações do agente
            atual->info = agenteAtualizado;
            printf("Agente com NIF %s atualizado com sucesso.\n", nif);
            return;
        }
        atual = atual->seguinte;
    }
    printf("Agente com NIF %s não encontrado.\n", nif);
}

AGENTE_NODE* removerAgente(AGENTE_NODE *listaAgentes, const char *nif) {
    AGENTE_NODE *atual = listaAgentes;
    AGENTE_NODE *anterior = NULL;

    // Percorre a lista até encontrar o agente com o NIF correspondente
    while (atual != NULL) {
        if (strcmp(atual->info.nif, nif) == 0) {
            // Remove o agente da lista
            if (anterior == NULL) {
                // O agente a ser removido é o primeiro da lista
                listaAgentes = atual->seguinte;
            } else {
                // O agente a ser removido não é o primeiro da lista
                anterior->seguinte = atual->seguinte;
            }
            free(atual);
            printf("Agente com NIF %s removido com sucesso.\n", nif);
            return listaAgentes;
        }
        anterior = atual;
        atual = atual->seguinte;
    }
    printf("Agente com NIF %s não encontrado.\n", nif);
    return listaAgentes;
}