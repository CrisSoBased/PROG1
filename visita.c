#include "listas.h"

// Função para agendar uma visita
VISITA_NODE* agendarVisita(VISITA_NODE *lista, VISITA novaVisita) {
    VISITA_NODE *novo = (VISITA_NODE*)malloc(sizeof(VISITA_NODE));
    if (novo != NULL) {
        novo->info = novaVisita;
        novo->seguinte = lista;
    }
    return novo;  // Retorna a nova cabeça da lista
}

void listarVisitas(VISITA_NODE *lista) {
    VISITA_NODE *atual = lista;

    if (atual == NULL) {
        printf("Não há visitas cadastradas.\n");
        return;
    }


    while (atual != NULL) {
        printf("ID da Visita: %d\n", atual->info.idVisita);
        printf("ID do Cliente: %d\n", atual->info.idCliente);
        printf("ID da Propriedade: %d\n", atual->info.idpropriedade);
        printf("ID do Agente: %d\n", atual->info.idAgente);
        printf("Data e Hora: %s\n", atual->info.dataHora);
        printf("Estado: %s\n", atual->info.estado);
        printf("Relatório: %s\n", atual->info.relatorio);
        printf("Preço: %.2f\n", atual->info.preco);
        printf("Aceite: %d\n", atual->info.aceite);
        printf("------------------------------\n");
        atual = atual->seguinte;
    }
}

// Função para listar visitas por data
void listarVisitasPorData(VISITA_NODE *lista, const char *data) {
    VISITA_NODE *temp = lista;
    printf("Visitas agendadas para a data %s:\n", data);
    while (temp != NULL) {
        if (strncmp(temp->info.dataHora, data, 10) == 0) {
            printf("ID Visita: %d\n", temp->info.idVisita);
            printf("ID Cliente: %d\n", temp->info.idCliente);
            printf("ID Agente: %d\n", temp->info.idAgente);
            printf("ID Propriedade: %d\n", temp->info.idpropriedade);
            printf("Data e Hora: %s\n", temp->info.dataHora);
            printf("Estado: %s\n", temp->info.estado);
            printf("Relatório: %s\n", temp->info.relatorio);
            printf("Preço: %.2f\n\n", temp->info.preco);
        }
        temp = temp->seguinte;
    }
}

// Função para listar visitas por agente em uma data específica
void listarVisitasPorAgente(VISITA_NODE *lista, int idAgente, const char *data) {
    VISITA_NODE *temp = lista;
    printf("Visitas do agente %d na data %s:\n", idAgente, data);
    while (temp != NULL) {
        if (temp->info.idAgente == idAgente && strncmp(temp->info.dataHora, data, 10) == 0) {
            printf("ID Visita: %d\n", temp->info.idVisita);
            printf("ID Cliente: %d\n", temp->info.idCliente);
            printf("ID Propriedade: %d\n", temp->info.idpropriedade);
            printf("Data e Hora: %s\n", temp->info.dataHora);
            printf("Estado: %s\n", temp->info.estado);
            printf("Relatório: %s\n", temp->info.relatorio);
            printf("Preço: %.2f\n\n", temp->info.preco);
        }
        temp = temp->seguinte;
    }
}


// Função para saber o histórico de visitas a uma determinada propriedade
void historicoVisitasPropriedade(VISITA_NODE *lista, int idPropriedade) {
    VISITA_NODE *temp = lista;
    printf("Histórico de visitas para a propriedade %d:\n", idPropriedade);
    while (temp != NULL) {
        // Supondo que idPropriedade pode ser verificado no relatorio
        if (temp->info.idpropriedade == idPropriedade) {
            printf("ID Visita: %d\n", temp->info.idVisita);
            printf("ID Cliente: %d\n", temp->info.idCliente);
            printf("ID Agente: %d\n", temp->info.idAgente);
            printf("Data e Hora: %s\n", temp->info.dataHora);
            printf("Estado: %s\n", temp->info.estado);
            printf("Relatório: %s\n", temp->info.relatorio);
            printf("Preço: %.2f\n\n", temp->info.preco);
        }
        temp = temp->seguinte;
    }
}

// Função para simular a realização de uma visita
void simularVisita(VISITA_NODE *lista, int idAgente, const char *dataHora) {
    VISITA_NODE *temp = lista;
    while (temp != NULL) {
        if (temp->info.idAgente == idAgente && strcmp(temp->info.dataHora, dataHora) == 0) {
            strcpy(temp->info.estado, "realizada");
            printf("Visita com ID %d realizada com sucesso.\n", temp->info.idVisita);
            return;
        }
        temp = temp->seguinte;
    }
    printf("Visita não encontrada para o agente %d na data e hora %s.\n", idAgente, dataHora);
}

// Função para listar visitas em que o cliente não compareceu em um determinado dia
void listarVisitasNaoCompareceu(VISITA_NODE *lista, const char *data, int idCliente) {
    VISITA_NODE *temp = lista;
    printf("Visitas em que o cliente não compareceu na data %s:\n", data);
    while (temp != NULL) {
        if (strncmp(temp->info.dataHora, data, 10) == 0 && strcmp(temp->info.estado, "n compareceu") == 0 && temp->info.idCliente == idCliente) {
            printf("ID Visita: %d\n", temp->info.idVisita);
            printf("ID Cliente: %d\n", temp->info.idCliente);
            printf("ID Agente: %d\n", temp->info.idAgente);
            printf("Data e Hora: %s\n", temp->info.dataHora);
            printf("Relatório: %s\n", temp->info.relatorio);
            printf("Preço: %.2f\n\n", temp->info.preco);
        }
        temp = temp->seguinte;
    }
}

// Função para calcular o faturamento por tipo de propriedade
float faturamentoPorTipoPropriedade(VISITA_NODE *lista, const char *tipoPropriedade, const char *periodo) {
    VISITA_NODE *temp = lista;
    float totalFaturado = 0.0;
    char data[11];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    if (strcmp(periodo, "hoje") == 0) {
        snprintf(data, sizeof(data), "%02d/%02d/%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    } else if (strcmp(periodo, "mes") == 0) {
        snprintf(data, sizeof(data), "%02d/%04d", tm.tm_mon + 1, tm.tm_year + 1900);
    } else {
        printf("Período inválido.\n");
        return 0.0;
    }

    while (temp != NULL) {
        if ((strstr(temp->info.relatorio, tipoPropriedade) != NULL) &&
            (strncmp(temp->info.dataHora, data, strlen(data)) == 0)) {
            totalFaturado += temp->info.preco;
        }
        temp = temp->seguinte;
    }

    return totalFaturado;
}

// Função para saber quantas visitas realizou cada agente este mês
int visitasRealizadasPorAgente(VISITA_NODE *lista, int idAgente, const char *periodo) {
    VISITA_NODE *temp = lista;
    int contador = 0;
    char data[11];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    if (strcmp(periodo, "mes") == 0) {
        snprintf(data, sizeof(data), "%02d/%04d", tm.tm_mon + 1, tm.tm_year + 1900);
    } else {
        printf("Período inválido.\n");
        return 0;
    }

    while (temp != NULL) {
        if ((temp->info.idAgente == idAgente) &&
            (strncmp(temp->info.dataHora, data, strlen(data)) == 0) &&
            (strcmp(temp->info.estado, "realizada") == 0)) {
            contador++;
        }
        temp = temp->seguinte;
    }

    return contador;
}

// Função para gerar um relatório de contas por dia ou mês
void gerarRelatorioContas(VISITA_NODE *lista, const char *periodo) {
    VISITA_NODE *temp = lista;
    char data[11];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    if (strcmp(periodo, "dia") == 0) {
        snprintf(data, sizeof(data), "%02d/%02d/%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    } else if (strcmp(periodo, "mes") == 0) {
        snprintf(data, sizeof(data), "%02d/%04d", tm.tm_mon + 1, tm.tm_year + 1900);
    } else {
        printf("Período inválido.\n");
        return;
    }

    // Agrupar visitas por tipo de propriedade
    char tiposPropriedades[10][50];
    float totalPorTipo[10] = {0};
    int tipoIndex = 0;

    while (temp != NULL) {
        if (strncmp(temp->info.dataHora, data, strlen(data)) == 0) {
            // Verificar se o tipo de propriedade já foi registrado
            int i;
            int encontrado = 0;
            for (i = 0; i < tipoIndex; i++) {
                if (strstr(temp->info.relatorio, tiposPropriedades[i]) != NULL) {
                    totalPorTipo[i] += temp->info.preco;
                    encontrado = 1;
                    break;
                }
            }

            // Se não foi registrado, adicionar novo tipo
            if (!encontrado && tipoIndex < 10) {
                strncpy(tiposPropriedades[tipoIndex], temp->info.relatorio, 49);
                tiposPropriedades[tipoIndex][49] = '\0';  // Garantir terminação
                totalPorTipo[tipoIndex] = temp->info.preco;
                tipoIndex++;
            }
        }
        temp = temp->seguinte;
    }

    // Exibir relatório
    printf("Relatório de Contas (%s):\n", periodo);
    for (int i = 0; i < tipoIndex; i++) {
        printf("Tipo de Propriedade: %s\n", tiposPropriedades[i]);
        printf("Total Faturado: %.2f\n\n", totalPorTipo[i]);
    }
}

// Funções para manipulação da fila de espera

// Função para adicionar um cliente à fila de espera
FILA_ESPERA* adicionarClienteFilaEspera(FILA_ESPERA *fila, int idCliente, const char *nome, float duracaoEstimada) {
    FILA_ESPERA *novo = (FILA_ESPERA*)malloc(sizeof(FILA_ESPERA));
    if (novo != NULL) {
        novo->idCliente = idCliente;
        strcpy(novo->nome, nome);
        novo->duracaoEstimada = duracaoEstimada;
        novo->seguinte = fila;
    }
    return novo;
}

// Função para remover o próximo cliente da fila de espera
FILA_ESPERA* removerProximoClienteFilaEspera(FILA_ESPERA *fila) {
    if (fila == NULL) {
        printf("Fila de espera vazia.\n");
        return NULL;
    }

    FILA_ESPERA *temp = fila;
    fila = fila->seguinte;
    free(temp);
    return fila;
}

void listarVisitasPorClienteporaceitar(VISITA_NODE *lista, int idCliente) {
    VISITA_NODE *temp = lista;
    while (temp != NULL) {
        if (temp->info.idCliente == idCliente && temp->info.aceite == 0) {
            printf("ID Visita: %d\n", temp->info.idVisita);
            printf("ID Cliente: %d\n", temp->info.idCliente);
            printf("ID Agente: %d\n", temp->info.idAgente);
            printf("ID Propriedade: %d\n", temp->info.idpropriedade);
            printf("Data e Hora: %s\n", temp->info.dataHora);
            printf("Estado: %s\n", temp->info.estado);
            printf("Relatório: %s\n", temp->info.relatorio);
            printf("Preço: %.2f\n", temp->info.preco);
            printf("Aceite: %d\n", temp->info.aceite);
            printf("\n");
        }
        temp = temp->seguinte;
    }
}

void listarVisitasPorClienteaceitadas(VISITA_NODE *lista, int idCliente) {
    VISITA_NODE *temp = lista;
    while (temp != NULL) {
        if (temp->info.idCliente == idCliente && temp->info.aceite == 1) {
            printf("ID Visita: %d\n", temp->info.idVisita);
            printf("ID Cliente: %d\n", temp->info.idCliente);
            printf("ID Agente: %d\n", temp->info.idAgente);
            printf("ID Propriedade: %d\n", temp->info.idpropriedade);
            printf("Data e Hora: %s\n", temp->info.dataHora);
            printf("Estado: %s\n", temp->info.estado);
            printf("Relatório: %s\n", temp->info.relatorio);
            printf("Preço: %.2f\n", temp->info.preco);
            printf("Aceite: %d\n", temp->info.aceite);
            printf("\n");
        }
        temp = temp->seguinte;
    }
}
// Função para listar todos os clientes na fila de espera
void listarClientesFilaEspera(FILA_ESPERA *fila) {
    FILA_ESPERA *temp = fila;
    printf("Clientes na fila de espera:\n");
    while (temp != NULL) {
        printf("ID Cliente: %d\n", temp->idCliente);
        printf("Nome: %s\n", temp->nome);
        printf("Duração Estimada: %.2f horas\n\n", temp->duracaoEstimada);
        temp = temp->seguinte;
    }
}

// Função para apresentar o próximo cliente a ser atendido na fila de espera
void apresentarProximoClienteFilaEspera(FILA_ESPERA *fila) {
    if (fila != NULL) {
        printf("Próximo cliente a ser atendido:\n");
        printf("ID Cliente: %d\n", fila->idCliente);
        printf("Nome: %s\n", fila->nome);
        printf("Duração Estimada: %.2f horas\n", fila->duracaoEstimada);
    } else {
        printf("Fila de espera vazia.\n");
    }
}

// Função para calcular o tempo de espera estimado para todos os elementos da fila
float calcularTempoEsperaEstimado(FILA_ESPERA *fila) {
    float tempoTotal = 0.0;
    FILA_ESPERA *temp = fila;
    while (temp != NULL) {
        tempoTotal += temp->duracaoEstimada;
        temp = temp->seguinte;
    }
    return tempoTotal;
}


void listarVisitasPorCliente(VISITA_NODE *lista, int idCliente) {
    VISITA_NODE *atual = lista;
    int encontrou = 0;

    while (atual != NULL) {
        if (atual->info.idCliente == idCliente) {
            printf("ID Visita: %d\n", atual->info.idVisita);
            printf("ID Cliente: %d\n", atual->info.idCliente);
            printf("ID Agente: %d\n", atual->info.idAgente);
            printf("ID Propriedade: %d\n", atual->info.idpropriedade);
            printf("Data e Hora: %s\n", atual->info.dataHora);
            printf("Estado: %s\n", atual->info.estado);
            printf("Relatório: %s\n", atual->info.relatorio);
            printf("Preço: %.2f\n", atual->info.preco);
            printf("-------------------------------\n");
            encontrou = 1;
        }
        atual = atual->seguinte;
    }

    if (!encontrou) {
        printf("Nenhuma visita encontrada para o cliente com ID %d.\n", idCliente);
    }
}

void aceitarVisita(VISITA_NODE *lista, int idVisita) {
    VISITA_NODE *temp = lista;
    while (temp != NULL) {
        if (temp->info.idVisita == idVisita) {
            temp->info.aceite = 1;
            strcpy(temp->info.estado, "agendada"); // Atualiza o estado para "agendada"
            printf("Visita com ID %d aceita com sucesso.\n", idVisita);
            return;
        }
        temp = temp->seguinte;
    }
    printf("Visita com ID %d não encontrada.\n", idVisita);
}

void listarVisitasPorAceitar(VISITA_NODE *listaVisitas, int idAgente) {
    VISITA_NODE *atual = listaVisitas;
    int encontrouVisitas = 0;

    while (atual != NULL) {
        if (atual->info.idAgente == idAgente && atual->info.aceite == 0) {
            printf("ID Visita: %d\n", atual->info.idVisita);
            printf("ID Cliente: %d\n", atual->info.idCliente);
            printf("ID Agente: %d\n", atual->info.idAgente);
            printf("ID Propriedade: %d\n", atual->info.idpropriedade);
            printf("Data e Hora: %s\n", atual->info.dataHora);
            printf("Estado: %s\n", atual->info.estado);
            printf("Relatório: %s\n", atual->info.relatorio);
            printf("Preço: %.2f\n", atual->info.preco);
            printf("Aceite: %d\n", atual->info.aceite);
            printf("--------------------------\n");
            encontrouVisitas = 1;
        }
        atual = atual->seguinte;
    }

    if (!encontrouVisitas) {
        printf("Nenhuma visita por aceitar encontrada para o agente com ID %d.\n", idAgente);
    }
}

void mudarEstadoVisita(VISITA_NODE *lista, int idVisita, const char *novoEstado) {
    VISITA_NODE *temp = lista;
    while (temp != NULL) {
        if (temp->info.idVisita == idVisita) {
            strcpy(temp->info.estado, novoEstado); // Atualiza o estado da visita
            printf("Estado da visita com ID %d alterado para %s com sucesso.\n", idVisita, novoEstado);
            return;
        }
        temp = temp->seguinte;
    }
    printf("Visita com ID %d não encontrada.\n", idVisita);
}

void listarVisitasAceitarAgente(VISITA_NODE *listaVisitas, int idAgente) {
    VISITA_NODE *atual = listaVisitas;
    int encontrouVisitas = 0;

    while (atual != NULL) {
        if (atual->info.idAgente == idAgente && atual->info.aceite == 1) {
            printf("ID Visita: %d\n", atual->info.idVisita);
            printf("ID Cliente: %d\n", atual->info.idCliente);
            printf("ID Agente: %d\n", atual->info.idAgente);
            printf("ID Propriedade: %d\n", atual->info.idpropriedade);
            printf("Data e Hora: %s\n", atual->info.dataHora);
            printf("Estado: %s\n", atual->info.estado);
            printf("Relatório: %s\n", atual->info.relatorio);
            printf("Preço: %.2f\n", atual->info.preco);
            printf("Aceite: %d\n", atual->info.aceite);
            printf("--------------------------\n");
            encontrouVisitas = 1;
        }
        atual = atual->seguinte;
    }

    if (!encontrouVisitas) {
        printf("Nenhuma visita aceitada encontrada para o agente com ID %d.\n", idAgente);
    }
}

int encontrarMaiorIdVisita(VISITA_NODE *lista) {
    int maiorId = 0;
    VISITA_NODE *atual = lista;

    // Percorre a lista para encontrar o maior idVisita
    while (atual != NULL) {
        if (atual->info.idVisita > maiorId) {
            maiorId = atual->info.idVisita;
        }
        atual = atual->seguinte;
    }

    // Retorna o maior idVisita encontrado mais 1
    return maiorId + 1;
}

// Função auxiliar para obter a data atual em formato "dd/mm/yyyy"
void obterDataAtualdois(char *dataAtual) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(dataAtual, "%02d/%02d/%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}

// Função para listar visitas de hoje
void listarVisitasHoje(VISITA_NODE *lista) {
    char dataAtual[11];
    obterDataAtualdois(dataAtual);
    listarVisitasPorDia(lista, dataAtual);
}

void listarMinhasVisitasHoje(VISITA_NODE *lista, int idAgente) {
    char dataAtual[11];
    obterDataAtualdois(dataAtual);
    listarMinhasVisitasPorDia(lista, dataAtual, idAgente);
}

void listarPropriedadeVisitasHoje(VISITA_NODE *lista, PROPRIEDADE_NODE* listaPropriedade, const char *tipo) {
    char dataAtual[11];
    obterDataAtualdois(dataAtual);
    listarVisitasPorTipoPropriedade(lista, listaPropriedade, tipo, dataAtual);
}


// Função para listar visitas de um determinado dia
void listarVisitasPorDia(VISITA_NODE *lista, const char *data) {
    VISITA_NODE *atual = lista;
    printf("Visitas agendadas para o dia %s:\n", data);
    while (atual != NULL) {
        if (strncmp(atual->info.dataHora, data, 10) == 0) {
            printf("ID Visita: %d, ID Cliente: %d, ID Propriedade: %d, ID Agente: %d, Data e Hora: %s, Estado: %s\n", 
                    atual->info.idVisita, atual->info.idCliente, atual->info.idpropriedade, atual->info.idAgente, atual->info.dataHora, atual->info.estado);
        }
        atual = atual->seguinte;
    }
}

void listarMinhasVisitasPorDia(VISITA_NODE *lista, const char *data, int idAgente) {
    VISITA_NODE *atual = lista;
    printf("Visitas agendadas para o dia %s:\n", data);
    while (atual != NULL) {
        if (strncmp(atual->info.dataHora, data, 10) == 0 && atual->info.idAgente == idAgente) {
            printf("ID Visita: %d, ID Cliente: %d, ID Propriedade: %d, ID Agente: %d, Data e Hora: %s, Estado: %s\n", 
                    atual->info.idVisita, atual->info.idCliente, atual->info.idpropriedade, atual->info.idAgente, atual->info.dataHora, atual->info.estado);
        }
        atual = atual->seguinte;
    }
}

// Função para listar visitas por tipo de propriedade e data
void listarVisitasPorTipoPropriedade(VISITA_NODE *listaVisitas, PROPRIEDADE_NODE *listaPropriedades, const char *tipoPropriedade, const char *data) {
    VISITA_NODE *visitaAtual = listaVisitas;
    printf("Visitas agendadas para o tipo de propriedade '%s' no dia %s:\n", tipoPropriedade, data);

    while (visitaAtual != NULL) {
        // Verificar se a data da visita corresponde à data fornecida
        if (strncmp(visitaAtual->info.dataHora, data, 10) == 0) {
            // Procurar a propriedade correspondente à visita
            PROPRIEDADE_NODE *propriedadeAtual = listaPropriedades;
            while (propriedadeAtual != NULL) {
                if (propriedadeAtual->info.idPropriedade == visitaAtual->info.idpropriedade && 
                    strcmp(propriedadeAtual->info.tipo, tipoPropriedade) == 0) {
                    printf("ID Visita: %d, ID Cliente: %d, ID Propriedade: %d, ID Agente: %d, Data e Hora: %s, Estado: %s\n", 
                            visitaAtual->info.idVisita, visitaAtual->info.idCliente, visitaAtual->info.idpropriedade, visitaAtual->info.idAgente, 
                            visitaAtual->info.dataHora, visitaAtual->info.estado);
                    break;
                }
                propriedadeAtual = propriedadeAtual->seguinte;
            }
        }
        visitaAtual = visitaAtual->seguinte;
    }
}