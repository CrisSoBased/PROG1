#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listas.h"

// Variáveis globais para armazenar as listas
AGENTE_NODE *listaAgentes = NULL;
CLIENTE_NODE *listaClientes = NULL;
PROPRIEDADE_NODE *listaPropriedades = NULL;
VISITA_NODE *listaVisitas = NULL;
CLIENTE clienteAutenticado;  
AGENTE* agenteAutenticado = NULL;
FILA_ESPERA *filaEspera = NULL;



// Função para carregar a lista de agentes de um arquivo binário
AGENTE_NODE* carregarAgentes() {
    FILE *file = fopen("AGENTE.bin", "rb");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo AGENTE.bin");
        return NULL;
    }

    AGENTE_NODE *listaAgentes = NULL;
    AGENTE_NODE *ultimo = NULL;

    AGENTE tempAgente;
    while (fread(&tempAgente, sizeof(AGENTE), 1, file)) {
        AGENTE_NODE *novo = (AGENTE_NODE *)malloc(sizeof(AGENTE_NODE));
        if (novo == NULL) {
            perror("Erro ao alocar memória");
            fclose(file);
            return NULL;
        }
        novo->info = tempAgente;
        novo->seguinte = NULL;

        if (listaAgentes == NULL) {
            listaAgentes = novo;
        } else {
            ultimo->seguinte = novo;
        }
        ultimo = novo;
    }
    fclose(file);
    return listaAgentes;
}

// Função para carregar a lista de clientes de um arquivo binário
CLIENTE_NODE* carregarClientes() {
    FILE *file = fopen("CLIENTE.bin", "rb");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo CLIENTE.bin");
        return NULL;
    }

    CLIENTE_NODE *listaClientes = NULL;
    CLIENTE_NODE *ultimo = NULL;

    CLIENTE tempCliente;
    while (fread(&tempCliente, sizeof(CLIENTE), 1, file)) {
        CLIENTE_NODE *novo = (CLIENTE_NODE *)malloc(sizeof(CLIENTE_NODE));
        if (novo == NULL) {
            perror("Erro ao alocar memória");
            fclose(file);
            return NULL;
        }
        novo->info = tempCliente;
        novo->seguinte = NULL;

        if (listaClientes == NULL) {
            listaClientes = novo;
        } else {
            ultimo->seguinte = novo;
        }
        ultimo = novo;
    }
    fclose(file);
    return listaClientes;
}

// Função para carregar a lista de propriedades de um arquivo binário
PROPRIEDADE_NODE* carregarPropriedades() {
    FILE *file = fopen("PROPRIEDADE.bin", "rb");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo PROPRIEDADE.bin");
        return NULL;
    }

    PROPRIEDADE_NODE *listaPropriedades = NULL;
    PROPRIEDADE_NODE *ultimo = NULL;

    PROPRIEDADE tempPropriedade;
    while (fread(&tempPropriedade, sizeof(PROPRIEDADE), 1, file)) {
        PROPRIEDADE_NODE *novo = (PROPRIEDADE_NODE *)malloc(sizeof(PROPRIEDADE_NODE));
        if (novo == NULL) {
            perror("Erro ao alocar memória");
            fclose(file);
            return NULL;
        }
        novo->info = tempPropriedade;
        novo->seguinte = NULL;

        if (listaPropriedades == NULL) {
            listaPropriedades = novo;
        } else {
            ultimo->seguinte = novo;
        }
        ultimo = novo;
    }
    fclose(file);
    return listaPropriedades;
}

// Função para carregar a lista de visitas de um arquivo binário
VISITA_NODE* carregarVisitas() {
    FILE *file = fopen("VISITA.bin", "rb");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo VISITA.bin");
        return NULL;
    }

    VISITA_NODE *listaVisitas = NULL;
    VISITA_NODE *ultimo = NULL;

    VISITA tempVisita;
    while (fread(&tempVisita, sizeof(VISITA), 1, file)) {
        VISITA_NODE *novo = (VISITA_NODE *)malloc(sizeof(VISITA_NODE));
        if (novo == NULL) {
            perror("Erro ao alocar memória");
            fclose(file);
            return NULL;
        }
        novo->info = tempVisita;
        novo->seguinte = NULL;

        if (listaVisitas == NULL) {
            listaVisitas = novo;
        } else {
            ultimo->seguinte = novo;
        }
        ultimo = novo;
    }
    fclose(file);
    return listaVisitas;
}

// Função para carregar a fila de espera de um arquivo binário
FILA_ESPERA* carregarFilaEspera() {
    FILE *file = fopen("FILA_ESPERA.bin", "rb");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo FILA_ESPERA.bin");
        return NULL;
    }

    FILA_ESPERA *filaEspera = NULL;
    FILA_ESPERA *ultimo = NULL;

    FILA_ESPERA tempFila;
    while (fread(&tempFila, sizeof(FILA_ESPERA), 1, file)) {
        FILA_ESPERA *novo = (FILA_ESPERA *)malloc(sizeof(FILA_ESPERA));
        if (novo == NULL) {
            perror("Erro ao alocar memória");
            fclose(file);
            return NULL;
        }
        *novo = tempFila;
        novo->seguinte = NULL;

        if (filaEspera == NULL) {
            filaEspera = novo;
        } else {
            ultimo->seguinte = novo;
        }
        ultimo = novo;
    }
    fclose(file);
    return filaEspera;
}

// Função para carregar todas as listas de arquivos binários
void carregarTodasListas(AGENTE_NODE **listaAgentes, CLIENTE_NODE **listaClientes, PROPRIEDADE_NODE **listaPropriedades, VISITA_NODE **listaVisitas, FILA_ESPERA **filaEspera) {
    *listaAgentes = carregarAgentes();
    *listaClientes = carregarClientes();
    *listaPropriedades = carregarPropriedades();
    *listaVisitas = carregarVisitas();
    *filaEspera = carregarFilaEspera();
}



void gravarAgentes(AGENTE_NODE *listaAgentes) {
    FILE *file = fopen("AGENTE.bin", "wb");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo AGENTE.bin");
        return;
    }

    AGENTE_NODE *temp = listaAgentes;
    while (temp != NULL) {
        fwrite(&(temp->info), sizeof(AGENTE), 1, file);
        temp = temp->seguinte;
    }
    fclose(file);
}

// Função para gravar a lista de clientes em binário
void gravarClientes(CLIENTE_NODE *listaClientes) {
    FILE *file = fopen("CLIENTE.bin", "wb");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo CLIENTE.bin");
        return;
    }

    CLIENTE_NODE *temp = listaClientes;
    while (temp != NULL) {
        fwrite(&(temp->info), sizeof(CLIENTE), 1, file);
        temp = temp->seguinte;
    }
    fclose(file);
}

// Função para gravar a lista de propriedades em binário
void gravarPropriedades(PROPRIEDADE_NODE *listaPropriedades) {
    FILE *file = fopen("PROPRIEDADE.bin", "wb");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo PROPRIEDADE.bin");
        return;
    }

    PROPRIEDADE_NODE *temp = listaPropriedades;
    while (temp != NULL) {
        fwrite(&(temp->info), sizeof(PROPRIEDADE), 1, file);
        temp = temp->seguinte;
    }
    fclose(file);
}

// Função para gravar a lista de visitas em binário
void gravarVisitas(VISITA_NODE *listaVisitas) {
    FILE *file = fopen("VISITA.bin", "wb");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo VISITA.bin");
        return;
    }

    VISITA_NODE *temp = listaVisitas;
    while (temp != NULL) {
        fwrite(&(temp->info), sizeof(VISITA), 1, file);
        temp = temp->seguinte;
    }
    fclose(file);
}

// Função para gravar a fila de espera em binário
void gravarFilaEspera(FILA_ESPERA *filaEspera) {
    FILE *file = fopen("FILA_ESPERA.bin", "wb");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo FILA_ESPERA.bin");
        return;
    }

    FILA_ESPERA *temp = filaEspera;
    while (temp != NULL) {
        fwrite(temp, sizeof(FILA_ESPERA), 1, file);
        temp = temp->seguinte;
    }
    fclose(file);
}

// Função para gravar todas as listas em arquivos binários
void gravarTodasListas(AGENTE_NODE *listaAgentes, CLIENTE_NODE *listaClientes, PROPRIEDADE_NODE *listaPropriedades, VISITA_NODE *listaVisitas, FILA_ESPERA *filaEspera) {
    gravarAgentes(listaAgentes);
    gravarClientes(listaClientes);
    gravarPropriedades(listaPropriedades);
    gravarVisitas(listaVisitas);
    gravarFilaEspera(filaEspera);
}

void fazerLogin() {
    char nome[50];
    char nif[10];
    
    printf("Digite o nome: ");
    scanf("%s", nome);
    printf("Digite o NIF: ");
    scanf("%s", nif);
    
    CLIENTE cliente = autenticarCliente(listaClientes, nome, nif);
    if (cliente.idCliente != -1) {
        printf("Login realizado com sucesso!\n");
        clienteAutenticado = cliente;  
        menuClienteAutenticado(cliente.idCliente);
    } else {
        printf("Nome ou NIF incorretos. Tente novamente.\n");
    }
}


void fazerLoginAgente() {
    char nome[50];
    char nif[10];

    printf("Digite o nome: ");
    scanf("%s", nome);
    printf("Digite o NIF: ");
    scanf("%s", nif);

    AGENTE* agente = autenticarAgente(listaAgentes, nome, nif);
    if (agente != NULL) {
        printf("Login realizado com sucesso!\n");
        agenteAutenticado = agente;  
        menuAgenteAutenticado();  
    } else {
        printf("Nome ou NIF incorretos. Tente novamente.\n");
    }
}


void menuAgenteAutenticado() {
    int opcao;
    char dataEscolhida[11];
    int idPropriedade, idCliente;
    char tipoPropriedade[50];
    char nomeCliente[50];
    float duracaoEstimada;
    FILA_ESPERA *fila = NULL;

    do {
        printf("\nMenu Agente Autenticado\n");
        printf("1. Ver visitas por aceitar\n");
        printf("2. Listar todas as visitas de hoje e de um determinado dia\n");
        printf("3. Listar todas as minhas visitas de hoje e de um determinado dia\n");
        printf("4. Listar todas as visitas de hoje e de um determinado dia por tipo de propriedade\n");
        printf("5. Saber o histórico de visitas a uma determinada propriedade\n");
        printf("6. Listar as visitas em que o cliente não compareceu para um determinado dia\n");
        printf("7. Saber, por cada tipo de propriedade, quanto foi faturado hoje e este mês\n");
        printf("8. Gerar um relatório por dia e por mês de contas\n");
        printf("9. Adicionar cliente a fila de espera\n");
        printf("10. Listar todos os clientes na fila de espera e a respetiva duração estimada da visita\n");
        printf("11. Apresentar o próximo cliente a ser atendido\n");
        printf("12. Calcular o tempo de espera estimado para todos os elementos da fila\n");
        printf("13. Voltar para trás\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();  // Limpar o buffer do teclado

        switch (opcao) {
            case 1:
                listarVisitasPorAceitar(listaVisitas, agenteAutenticado->idAgente);
                break;
            case 2:
                printf("Visitas de hoje\n");
                listarVisitasHoje(listaVisitas);
                printf("Insira a data desejada (dd/mm/yyyy): ");
                scanf("%10s", dataEscolhida);
                listarVisitasPorDia(listaVisitas, dataEscolhida);
                break;
            case 3:
                printf("Minhas Visitas de hoje\n");
                listarMinhasVisitasHoje(listaVisitas, agenteAutenticado->idAgente);
                printf("Insira a data desejada (dd/mm/yyyy): ");
                scanf("%10s", dataEscolhida);
                listarMinhasVisitasPorDia(listaVisitas, dataEscolhida, agenteAutenticado->idAgente);
                break;
            case 4:
                printf("Insira o tipo de propriedade: ");
                scanf("%49s", tipoPropriedade);
                printf("Visitas de hoje para este tipo de propriedade\n");
                listarPropriedadeVisitasHoje(listaVisitas, listaPropriedades, tipoPropriedade);
                printf("Insira a data desejada (dd/mm/yyyy): ");
                scanf("%10s", dataEscolhida);
                listarVisitasPorTipoPropriedade(listaVisitas, listaPropriedades, tipoPropriedade, dataEscolhida);
                break;
            case 5:
                printf("Insira o ID da propriedade: ");
                scanf("%d", &idPropriedade);
                historicoVisitasPropriedade(listaVisitas, idPropriedade);
                break;
            case 6:
                printf("Insira a data desejada (dd/mm/yyyy): ");
                scanf("%10s", dataEscolhida);
                printf("Insira o ID do cliente: ");
                scanf("%d", &idCliente);
                listarVisitasNaoCompareceu(listaVisitas, dataEscolhida, idCliente);
                break;
            case 7:
                printf("Ainda não implementado\n");
                break;
            case 8:
                printf("Ainda não implementado\n");
                break;
            case 9:
                printf("Insira o ID do cliente: ");
                scanf("%d", &idCliente);
                printf("Insira o nome do cliente: ");
                scanf("%49s", nomeCliente);
                printf("Insira a duração estimada da visita (em horas): ");
                scanf("%f", &duracaoEstimada);
                fila = adicionarClienteFilaEspera(fila, idCliente, nomeCliente, duracaoEstimada);
                printf("Cliente adicionado à fila de espera.\n");
                break;
            case 10:
                listarClientesFilaEspera(fila);
                break;
            case 11:
                apresentarProximoClienteFilaEspera(fila);
                break;
            case 12:
                printf("Tempo de espera estimado para todos os clientes: %.2f horas\n", calcularTempoEsperaEstimado(fila));
                break;
            case 13:
                printf("Voltando para o menu anterior...\n");
                menuAgente();
                return;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 13);
}


void menuClienteAutenticado() {
    int opcao, idPropriedade, tipo;
    PROPRIEDADE novaPropriedade;

    do {
        printf("\nMenu Cliente Autenticado\n");
        printf("1. Ver detalhes da conta\n");
        printf("2. Editar detalhes da conta\n");
        printf("3. Eliminar conta\n");
        printf("4. Vender propriedade\n");
        printf("5. Alugar propriedade\n");
        printf("6. Comprar propriedade\n");
        printf("7. Ver minhas propriedades a venda\n");
        printf("8. Ver minhas propriedades já vendidas\n");
        printf("9. Ver propriedades que aluguei ou comprei\n");
        printf("10. Ver Visitas agendadas aceites\n");
        printf("11. Ver Visitas agendadas por aceitar\n");
        printf("12. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Detalhes da conta...\n");
                apresentarClientePorNIF(listaClientes, clienteAutenticado.nif);
                break;
            case 2:
                printf("Editar detalhes da conta...\n");
                char nif[20];
                CLIENTE clienteAtualizado;
                printf("Digite o NIF do cliente a atualizar: ");
                scanf("%s", nif);
                printf("Digite o novo nome do cliente: ");
                scanf("%s", clienteAtualizado.nome);
                printf("Digite o novo telefone do cliente: ");
                scanf("%s", clienteAtualizado.ntelefone);
                printf("Digite os novos detalhes da propriedade de interesse: ");
                scanf("%s", clienteAtualizado.detalhesPropriedade);
                // Atualizar o cliente na lista
                atualizarCliente(listaClientes, nif, clienteAtualizado);
                break;
            case 3:
                removerCliente(listaClientes, clienteAutenticado.nif);
                break;
            case 4:
                printf("Adicionar nova propriedade para venda...\n");
                // Capturar os detalhes da nova propriedade
                printf("ID da Propriedade: ");
                scanf("%d", &novaPropriedade.idPropriedade);
                printf("Tipo: ");
                scanf("%s", novaPropriedade.tipo);
                printf("Morada: ");
                scanf("%s", novaPropriedade.morada);
                printf("Área: ");
                scanf("%f", &novaPropriedade.area);
                printf("Preço: ");
                scanf("%f", &novaPropriedade.preco);
                novaPropriedade.idAgente = 0;  // Defina o ID do agente apropriado
                novaPropriedade.disponibilidade = 0;
                novaPropriedade.idvendedor = clienteAutenticado.idCliente;
                novaPropriedade.idcomprador = 0;
                novaPropriedade.aposcompra = 0;
                listaPropriedades = adicionarPropriedade(listaPropriedades, novaPropriedade);
                break;
            case 5:
                printf("Alugar propriedade...\n");
                printf("ID da Propriedade: ");
                scanf("%d", &idPropriedade);
                propriedadeArrenda(listaPropriedades, idPropriedade, 2, clienteAutenticado.idCliente);
                break;
            case 6:
                printf("Comprar propriedade...\n");
                printf("ID da Propriedade: ");
                scanf("%d", &idPropriedade);
                propriedadeArrenda(listaPropriedades, idPropriedade, 1, clienteAutenticado.idCliente);
                break;
            case 7:
                printf("Ver minhas propriedades à venda...\n");
                listarPropriedadesVendaCliente(listaPropriedades, clienteAutenticado.idCliente);
                break;
            case 8:
                printf("Ver minhas propriedades já vendidas...\n");
                listarPropriedadesjaVendaCliente(listaPropriedades, clienteAutenticado.idCliente);
                break;
            case 9:
                printf("Ver propriedades que aluguei ou comprei...\n");
                listarPropriedadesCompradasporCliente(listaPropriedades, clienteAutenticado.idCliente);
                break;
            case 10:
                printf("Ver Visitas aceites agendadas...\n");
                listarVisitasPorClienteaceitadas(listaPropriedades, clienteAutenticado.idCliente);

                break;
            case 11:
                printf("Ver Visitas por aceitar agendadas...\n");
                listarVisitasPorClienteporaceitar(listaPropriedades, clienteAutenticado.idCliente);
                break;
            case 12:
                printf("Saindo...\n");
                printMenuInicial();
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 12);
}
// Função para criar uma nova conta de cliente
void criarConta() {
    CLIENTE novoCliente;
    
    printf("Digite o ID do Cliente: ");
    scanf("%d", &novoCliente.idCliente);
    printf("Digite o nome: ");
    scanf("%s", novoCliente.nome);
    printf("Digite o NIF: ");
    scanf("%s", novoCliente.nif);
    printf("Digite o número de telefone: ");
    scanf("%s", novoCliente.ntelefone);
    printf("Digite os detalhes da propriedade: ");
    scanf("%s", novoCliente.detalhesPropriedade);
    
    listaClientes = adicionarCliente(listaClientes, novoCliente);
    printf("Conta criada com sucesso!\n");
}


void printMenuInicial() {
    printf("Bem-vindo a Rent Propriedade\n");
    printf("1. Entrar como Admin\n");
    printf("2. Entrar como Agente\n");
    printf("3. Entrar como Cliente\n");
    printf("4. Sair\n");
}

void menuAdmin() {
    int opcao;
    do {
        printf("\nMenu Admin\n");
        printf("1. Gerir Clientes\n");
        printf("2. Gerir Agentes\n");
        printf("3. Gerir Propriedades\n");
        printf("4. Gerir Visitas\n");
        printf("5. Voltar\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                menuGerirClientes();
                break;
            case 2:
                menuGerirAgentes();
                break;
            case 3:
                menuGerirPropriedades();
                break;
            case 4:
                menuGerirVisitas();
                break;
            case 5:
                printf("Voltando ao menu inicial...\n");
                printMenuInicial();
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 5);
}

void menuCliente() {
    int opcao;
    do {
        printf("\nMenu Cliente\n");
        printf("1. Fazer Login\n");
        printf("2. Criar Conta\n");
        printf("3. Voltar\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                fazerLogin();
                break;
            case 2:
                criarConta();
                break;
            case 3:
                printf("Voltando ao menu inicial...\n");
                printMenuInicial();
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 3);
}

void menuAgente() {
    int opcao;
    do {
        printf("\nMenu Agente\n");
        printf("1. Fazer Login\n");
        printf("2. Voltar\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                fazerLogin();
                break;
            case 2:
                printf("Voltando ao menu inicial...\n");
                printMenuInicial();
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 2);
}


// Função menuGerirClientes
void menuGerirClientes() {
    int opcao;

    do {
        printf("\nMenu Gerir Clientes\n");
        printf("1. Criar Cliente\n");
        printf("2. Atualizar Cliente\n");
        printf("3. Remover Cliente\n");
        printf("4. Listar Clientes por Ordem Alfabética\n");
        printf("5. Apresentar Informações de um Cliente\n");
        printf("6. Voltar\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                CLIENTE novoCliente;
                printf("Digite o nome do cliente: ");
                scanf("%s", novoCliente.nome);
                printf("Digite o NIF do cliente: ");
                scanf("%s", novoCliente.nif);
                printf("Digite o telefone do cliente: ");
                scanf("%s", novoCliente.ntelefone);
                printf("Digite os detalhes da propriedade de interesse: ");
                scanf("%s", novoCliente.detalhesPropriedade);
                // Adicionar o cliente à lista
                listaClientes = adicionarCliente(listaClientes, novoCliente);
                break;
            }
            case 2: {
                char nif[20];
                CLIENTE clienteAtualizado;
                printf("Digite o NIF do cliente a atualizar: ");
                scanf("%s", nif);
                printf("Digite o novo nome do cliente: ");
                scanf("%s", clienteAtualizado.nome);
                printf("Digite o novo telefone do cliente: ");
                scanf("%s", clienteAtualizado.ntelefone);
                printf("Digite os novos detalhes da propriedade de interesse: ");
                scanf("%s", clienteAtualizado.detalhesPropriedade);
                // Atualizar o cliente na lista
                atualizarCliente(listaClientes, nif, clienteAtualizado);
                break;
            }
            case 3: {
                char nif[20];
                printf("Digite o NIF do cliente a remover: ");
                scanf("%s", nif);
                // Remover o cliente da lista
                listaClientes = removerCliente(listaClientes, nif);
                break;
            }
            case 4:
                // Listar clientes por ordem alfabética
                listarClientesPorNome(listaClientes);
                break;
            case 5: {
                char nif[20];
                printf("Digite o NIF do cliente: ");
                scanf("%s", nif);
                // Apresentar informações do cliente
                apresentarClientePorNIF(listaClientes, nif);
                break;
            }
            case 6:
                printf("Voltando ao menu anterior...\n");
                menuAdmin();
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 6);
}



void menuGerirAgentes() {
    int opcao;

    do {
        printf("\nMenu Gerir Agentes\n");
        printf("1. Criar Agente\n");
        printf("2. Remover Agente\n");
        printf("3. Editar Agente\n");
        printf("4. Listar Agentes por Ordem Alfabética\n");
        printf("5. Listar Agentes por Idade Ascendente\n");
        printf("6. Colocar Agente como Indisponível\n");
        printf("7. Gerar Relatório de Agentes\n");
        printf("8. Voltar\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                AGENTE novoAgente;
                printf("Digite o nome do agente: ");
                scanf("%s", novoAgente.nome);
                printf("Digite o NIF do agente: ");
                scanf("%s", novoAgente.nif);
                printf("Digite a morada do agente: ");
                scanf("%s", novoAgente.morada);
                printf("Digite o telefone do agente: ");
                scanf("%s", novoAgente.ntelefone);
                printf("Digite a data de nascimento (dd/mm/yyyy): ");
                scanf("%s", novoAgente.datanascimento);
                printf("Digite o tipo de conta do agente: ");
                scanf("%d", &novoAgente.tipoconta);
                novoAgente.disponibilidade = 0; // Disponível por padrão

                // Adicionar o agente à lista
                listaAgentes = adicionarAgente(listaAgentes, novoAgente);
                break;
            }
            case 2: {
                char nif[20];
                printf("Digite o NIF do agente a remover: ");
                scanf("%s", nif);

                // Remover o agente da lista
                listaAgentes = removerAgente(listaAgentes, nif);
                break;
            }
            case 3: {
                char nif[20];
                AGENTE agenteAtualizado;
                printf("Digite o NIF do agente a editar: ");
                scanf("%s", nif);
                printf("Digite o novo nome do agente: ");
                scanf("%s", agenteAtualizado.nome);
                printf("Digite a nova morada do agente: ");
                scanf("%s", agenteAtualizado.morada);
                printf("Digite o novo telefone do agente: ");
                scanf("%s", agenteAtualizado.ntelefone);
                printf("Digite a nova data de nascimento (dd/mm/yyyy): ");
                scanf("%s", agenteAtualizado.datanascimento);
                printf("Digite o novo tipo de conta do agente: ");
                scanf("%d", &agenteAtualizado.tipoconta);

                // Atualizar o agente na lista
                atualizarAgente(listaAgentes, nif, agenteAtualizado);
                break;
            }
            case 4:
                // Listar agentes por ordem alfabética
                listarAgentesPorNome(listaAgentes);
                break;
            case 5:
                // Listar agentes por idade ascendente
                listarAgentesPorIdade(listaAgentes);
                break;
            case 6: {
                int idAgente;
                printf("Digite o ID do agente a colocar como indisponível: ");
                scanf("%d", &idAgente);

                // Colocar o agente como indisponível
                tornarAgenteIndisponivel(listaAgentes, idAgente);
                break;
            }
            case 7:
                // Gerar relatório de agentes
                gerarRelatorioAgentes(listaAgentes);
                break;
            case 8:
                printf("Voltando ao menu anterior...\n");
                menuAdmin();

                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 8);
}

// Função menuGerirPropriedades
void menuGerirPropriedades() {
    int opcao;

    do {
        printf("\nMenu Gerir Propriedades\n");
        printf("1. Criar Propriedade\n");
        printf("2. Editar Propriedade\n");
        printf("3. Remover Propriedade\n");
        printf("4. Listar Propriedades\n");
        printf("5. Voltar\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                PROPRIEDADE novaPropriedade;
                printf("Digite o tipo da propriedade: ");
                scanf("%s", novaPropriedade.tipo);
                printf("Digite a morada da propriedade: ");
                scanf("%s", novaPropriedade.morada);
                printf("Digite a área da propriedade (m²): ");
                scanf("%f", &novaPropriedade.area);
                printf("Digite o preço da propriedade: ");
                scanf("%f", &novaPropriedade.preco);
                printf("Digite o ID do agente responsável: ");
                scanf("%d", &novaPropriedade.idAgente);
                printf("Digite o ID do Vendedor: ");
                scanf("%d", &novaPropriedade.idvendedor);
                novaPropriedade.disponibilidade = 0; // Disponível por padrão
                novaPropriedade.aposcompra = 0; 
                // Adicionar a propriedade à lista
                listaPropriedades = adicionarPropriedade(listaPropriedades, novaPropriedade);
                break;
            }
            case 2: {
                int idPropriedade;
                PROPRIEDADE propriedadeAtualizada;
                printf("Digite o ID da propriedade a editar: ");
                scanf("%d", &idPropriedade);
                printf("Digite o novo tipo da propriedade: ");
                scanf("%s", propriedadeAtualizada.tipo);
                printf("Digite a nova morada da propriedade: ");
                scanf("%s", propriedadeAtualizada.morada);
                printf("Digite a nova área da propriedade (m²): ");
                scanf("%f", &propriedadeAtualizada.area);
                printf("Digite o novo preço da propriedade: ");
                scanf("%f", &propriedadeAtualizada.preco);
                printf("Digite o novo ID do agente responsável: ");
                scanf("%d", &propriedadeAtualizada.idAgente);
                printf("Digite o novo ID do Vendedor: ");
                scanf("%d", &propriedadeAtualizada.idvendedor);
                propriedadeAtualizada.disponibilidade = 0; // Manter disponível por padrão
                propriedadeAtualizada.aposcompra = 0;
                // Atualizar a propriedade na lista
                editarPropriedade(listaPropriedades, idPropriedade, propriedadeAtualizada);
                break;
            }
            case 3: {
                int idPropriedade;
                printf("Digite o ID da propriedade a remover: ");
                scanf("%d", &idPropriedade);

                // Remover a propriedade da lista
                removerPropriedade(&listaPropriedades, idPropriedade);
                break;
            }
            case 4:
                // Listar propriedades
                listarPropriedades(listaPropriedades);
                break;
            case 5:
                printf("Voltando ao menu anterior...\n");
                menuAdmin();
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 5);
}


void menuGerirVisitas() {
    int opcao;

    do {
        printf("\nMenu Gerir Visitas\n");
        printf("1. Listar Visitas de Hoje e de um Determinado Dia\n");
        printf("2. Listar Visitas de Hoje e de um Determinado Dia para um Agente\n");
        printf("3. Listar Visitas de Hoje e de um Determinado Dia por Tipo de Propriedade\n");
        printf("4. Histórico de Visitas a uma Propriedade\n");
        printf("5. Simular Realização de uma Visita\n");
        printf("6. Listar Visitas em que o Cliente não Compareceu\n");
        printf("7. Faturamento por Tipo de Propriedade\n");
        printf("8. Visitas Realizadas por Agente\n");
        printf("9. Gerar Relatório de Contas\n");
        printf("10. Voltar\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                char data[20];
                printf("Digite a data (DD/MM/AAAA): ");
                scanf("%s", data);
                listarVisitasPorData(listaVisitas, data);
                break;
            }
            case 2: {
                int idAgente;
                char data[20];
                printf("Digite o ID do agente: ");
                scanf("%d", &idAgente);
                printf("Digite a data (DD/MM/AAAA): ");
                scanf("%s", data);
                listarVisitasPorAgente(listaVisitas, idAgente, data);
                break;
            }
            case 3: {
                char tipoPropriedade[50];
                char data[20];
                printf("Digite o tipo de propriedade: ");
                scanf("%s", tipoPropriedade);
                printf("Digite a data (DD/MM/AAAA): ");
                scanf("%s", data);
                listarVisitasPorTipoPropriedade(listaVisitas,listaPropriedades ,tipoPropriedade, data);
                break;
            }
            case 4: {
                int idPropriedade;
                printf("Digite o ID da propriedade: ");
                scanf("%d", &idPropriedade);
                historicoVisitasPropriedade(listaVisitas, idPropriedade);
                break;
            }
            case 5: {
                int idAgente;
                char dataHora[20];
                printf("Digite o ID do agente: ");
                scanf("%d", &idAgente);
                printf("Digite a data e hora (DD/MM/AAAA HH:MM): ");
                scanf("%s", dataHora);
                simularVisita(listaVisitas, idAgente, dataHora);
                break;
            }
            case 6: {
                int idCliente;
                char data[20];
                printf("Digite a data (DD/MM/AAAA): ");
                scanf("%s", data);
                printf("Digite o id cliente: ");
                scanf("%d", &idCliente);
                listarVisitasNaoCompareceu(listaVisitas, data, idCliente);
                break;
            }
            case 7: {
                char tipoPropriedade[50];
                char periodo[10];
                printf("Digite o tipo de propriedade: ");
                scanf("%s", tipoPropriedade);
                printf("Digite o período (hoje/mes): ");
                scanf("%s", periodo);
                float faturamento = faturamentoPorTipoPropriedade(listaVisitas, tipoPropriedade, periodo);
                printf("Faturamento para o tipo de propriedade %s no período %s: %.2f\n", tipoPropriedade, periodo, faturamento);
                break;
            }
            case 8: {
                int idAgente;
                char periodo[10];
                printf("Digite o ID do agente: ");
                scanf("%d", &idAgente);
                printf("Digite o período (mes): ");
                scanf("%s", periodo);
                int visitas = visitasRealizadasPorAgente(listaVisitas, idAgente, periodo);
                printf("Visitas realizadas pelo agente %d no período %s: %d\n", idAgente, periodo, visitas);
                break;
            }
            case 9: {
                char periodo[10];
                printf("Digite o período (dia/mes): ");
                scanf("%s", periodo);
                gerarRelatorioContas(listaVisitas, periodo);
                break;
            }
            case 10:
                printf("Voltando ao menu anterior...\n");
                menuAdmin();
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 10);
}

int main() {
	carregarTodasListas(&listaAgentes, &listaClientes, &listaPropriedades, &listaVisitas, &filaEspera);
    int opcao;
	do {
		printMenuInicial();
		printf("Escolha uma opção: ");
		scanf("%d", &opcao);


		switch (opcao) {
			case 1:
				menuAdmin();
				break;
			case 2:
                menuAgente();
				break;
			case 3:
				menuCliente();
				break;
			case 4:
				printf("Encerrando o programa...\n");
				break;
			default:
				printf("Opção inválida. Tente novamente.\n");
		}
	} while (opcao != 4);

	return 0;
}