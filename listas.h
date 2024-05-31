#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <locale.h>


typedef struct agente {
    int idAgente;
    char nome[50];
    char nif[10];               
    char morada[100];
    char ntelefone[15];         
    char datanascimento[11];    //"dd/mm/yyyy"
    int tipoconta;
    int disponibilidade; 
} AGENTE;


typedef struct cliente {
    int idCliente;
    char nome[50];
    char nif[10];               
    char ntelefone[15];
    char detalhesPropriedade[100];  
} CLIENTE;


typedef struct propriedade {
    int idPropriedade;          // Identificador único da propriedade
    char tipo[30];              // Tipo de propriedade (casa, apartamento, escritório e terreno.)
    char morada[100];           // Morada da propriedade
    float area;                 // Área da propriedade em metros quadrados
    float preco;                // Preço da propriedade
    int idAgente;               // Identificador do agente responsável
    int disponibilidade;        // Disponibilidade da propriedade (1 para disponível, 0 para indisponível)
    int idvendedor;
    int idcomprador;            // por defeito = 0
    int aposcompra;             // 0 = nada, 1 = comprada, 2 = alugada
    float precoalugada;
    char datacompra[20];        // por defeito 00/00/0000 
    int anosaluga;              // por defeito = 0
} PROPRIEDADE;

typedef struct visita {
    int idVisita;
    int idCliente;
    int idpropriedade;
    int idAgente;
    char dataHora[20];  // Formato "dd/mm/yyyy"
    char estado[20];    // defeito = "por aceitar", //"agendada", "realizada", "n compareceu"
    char relatorio[200];
    float preco;
    int aceite;         //0 = ainda nao foi aceite; 1 ja foi aceite
} VISITA;


typedef struct filaEspera {
    int idCliente;
    char nome[50];
    float duracaoEstimada;  // Duração estimada da visita em horas
    struct filaEspera *seguinte;
} FILA_ESPERA;

typedef struct agenteNode {
    AGENTE info;
    struct agenteNode *seguinte;
} AGENTE_NODE;

typedef struct propriedadeNode {
    PROPRIEDADE info;
    struct propriedadeNode *seguinte;
} PROPRIEDADE_NODE;

typedef struct clienteNode {
    CLIENTE info;
    struct clienteNode *seguinte;
} CLIENTE_NODE;

typedef struct visitaNode {
    VISITA info;
    struct visitaNode *seguinte;
} VISITA_NODE;





// Funções para manipulação da lista de agentes
AGENTE_NODE* adicionarAgente(AGENTE_NODE *lista, AGENTE novoAgente);
void listarAgentes(AGENTE_NODE *lista);
void listarAgentesPorNome(AGENTE_NODE *lista);
void listarAgentesPorIdade(AGENTE_NODE *lista);
void tornarAgenteIndisponivel(AGENTE_NODE *lista, int idAgente);
void gerarRelatorioAgentes(AGENTE_NODE *lista);
void atualizarAgente(AGENTE_NODE *listaAgentes, const char *nif, AGENTE agenteAtualizado);
AGENTE_NODE* removerAgente(AGENTE_NODE *listaAgentes, const char *nif);
int encontrarMaiorIdAgente(AGENTE_NODE *lista);
AGENTE encontrarAgentePorId(AGENTE_NODE *lista, int idAgente);
void listarAgentesDisponiveis(AGENTE_NODE *lista);
void tornarAgentedisponivel(AGENTE_NODE *lista, int idAgente);
// Funções auxiliares
int calcularIdade(const char *dataNascimento);
int compararIdades(const void *a, const void *b);
int compararNomes(const void *a, const void *b);
int parseDataNascimento(const char *dataNascimento, struct tm *tm_nascimento); // Adicionada
AGENTE* autenticarAgente(AGENTE_NODE *lista, const char *nome, const char *nif);


// Funções para manipulação da lista de propriedades
PROPRIEDADE_NODE* adicionarPropriedade(PROPRIEDADE_NODE *lista, PROPRIEDADE novaPropriedade);
void listarPropriedades(PROPRIEDADE_NODE *lista);
void listarPropriedadesCompraCliente(PROPRIEDADE_NODE *lista, int idVendedor);
void listarPropriedadesCompradasporCliente(PROPRIEDADE_NODE *lista, int idComprador);
void listarPropriedadesVendaCliente(PROPRIEDADE_NODE *lista, int idVendedor);
void listarPropriedadesjaVendaCliente(PROPRIEDADE_NODE *lista, int idVendedor);
void removerPropriedade(PROPRIEDADE_NODE **lista, int idPropriedade);
void editarPropriedade(PROPRIEDADE_NODE *lista, int idPropriedade, PROPRIEDADE propriedadeAtualizada);
void propriedadeArrenda(PROPRIEDADE_NODE *lista, int idPropriedade, int tipo, int idComprador);
void propriedadeFatura(PROPRIEDADE_NODE *lista, const char *data, int n, int m);
int encontrarMaiorIdPropriedade(PROPRIEDADE_NODE *lista);
// Funções para manipulação da lista de clientes
CLIENTE_NODE* adicionarCliente(CLIENTE_NODE *lista, CLIENTE novoCliente);
void listarClientes(CLIENTE_NODE *lista);
void listarClientesPorNome(CLIENTE_NODE *lista);
void apresentarClientePorNIF(CLIENTE_NODE *lista, const char *nif);
CLIENTE_NODE* removerCliente(CLIENTE_NODE *lista, const char *nif);
void atualizarCliente(CLIENTE_NODE *lista, const char *nif, CLIENTE clienteAtualizado);
int encontrarMaiorIdCliente(CLIENTE_NODE *lista);
// Funções auxiliares para clientes
int compararNomesClientes(const void *a, const void *b);
CLIENTE autenticarCliente(CLIENTE_NODE *lista, const char *nome, const char *nif);
CLIENTE encontrarClientePorId(CLIENTE_NODE *lista, int idCliente);

// Funções para manipulação da lista de visitas
VISITA_NODE* agendarVisita(VISITA_NODE *lista, VISITA novaVisita);
void listarVisitasPorData(VISITA_NODE *lista, const char *data);
void listarVisitasPorAgente(VISITA_NODE *lista, int idAgente, const char *data);
void historicoVisitasPropriedade(VISITA_NODE *lista, int idPropriedade);
void simularVisita(VISITA_NODE *lista, int idAgente, const char *dataHora);
void listarVisitasNaoCompareceu(VISITA_NODE *lista, const char *data, int idCliente);
float faturamentoPorTipoPropriedade(VISITA_NODE *lista, const char *tipoPropriedade, const char *periodo); // "hoje" ou "mes"
int visitasRealizadasPorAgente(VISITA_NODE *lista, int idAgente, const char *periodo); // "mes"
void gerarRelatorioContas(VISITA_NODE *lista, const char *periodo); // "dia" ou "mes"
void listarVisitasPorCliente(VISITA_NODE *lista, int idCliente);
void aceitarVisita(VISITA_NODE *lista, int idVisita);
void listarVisitasPorClienteporaceitar(VISITA_NODE *lista, int idCliente);
void listarVisitasPorClienteaceitadas(VISITA_NODE *lista, int idCliente);
void listarVisitasPorAceitar(VISITA_NODE *listaVisitas, int idAgente);
void listarVisitasHoje(VISITA_NODE *lista);
void listarMinhasVisitasHoje(VISITA_NODE *lista, int idAgente);
void listarPropriedadeVisitasHoje(VISITA_NODE *lista, PROPRIEDADE_NODE* listaPropriedade, const char *tipo);
void listarVisitasPorDia(VISITA_NODE *lista, const char *data);
void listarMinhasVisitasPorDia(VISITA_NODE *lista, const char *data, int idAgente);
int encontrarMaiorIdVisita(VISITA_NODE *lista);
void listarVisitasPorTipoPropriedade(VISITA_NODE *listaVisitas, PROPRIEDADE_NODE *listaPropriedades, const char *tipoPropriedade, const char *data);
void listarVisitas(VISITA_NODE *lista);
void listarVisitasAceitarAgente(VISITA_NODE *listaVisitas, int idAgente);
void mudarEstadoVisita(VISITA_NODE *lista, int idVisita, const char *novoEstado);
// Funções para manipulação da fila de espera
FILA_ESPERA* adicionarClienteFilaEspera(FILA_ESPERA *fila, int idCliente, const char *nome, float duracaoEstimada);
FILA_ESPERA* removerProximoClienteFilaEspera(FILA_ESPERA *fila);
void listarClientesFilaEspera(FILA_ESPERA *fila);
void apresentarProximoClienteFilaEspera(FILA_ESPERA *fila);
float calcularTempoEsperaEstimado(FILA_ESPERA *fila);


