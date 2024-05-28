#include "listas.h"


PROPRIEDADE_NODE* adicionarPropriedade(PROPRIEDADE_NODE *lista, PROPRIEDADE novaPropriedade) {
    PROPRIEDADE_NODE *novo = (PROPRIEDADE_NODE*)malloc(sizeof(PROPRIEDADE_NODE));
    if (novo != NULL) {
        novo->info = novaPropriedade;
        novo->seguinte = lista;
    }
    return novo;
}


void listarPropriedadesCompraCliente(PROPRIEDADE_NODE *lista, int idVendedor) {
    PROPRIEDADE_NODE *temp = lista;
    while (temp != NULL) {
        if (temp->info.disponibilidade == 0 && temp->info.idvendedor != idVendedor) {
            printf("ID: %d\n", temp->info.idPropriedade);
            printf("Tipo: %s\n", temp->info.tipo);
            printf("Morada: %s\n", temp->info.morada);
            printf("Área: %.2f m²\n", temp->info.area);
            printf("Preço: %.2f\n", temp->info.preco);
            printf("ID Agente: %d\n", temp->info.idAgente);
            printf("ID Vendedor: %d\n", temp->info.idvendedor);
            printf("ID Comprador: %d\n", temp->info.idcomprador);
            printf("Como se encontra: %d\n", temp->info.aposcompra);
            printf("Disponibilidade: %d\n\n", temp->info.disponibilidade);
        }
        temp = temp->seguinte;
    }
}

void listarPropriedadesCompradasporCliente(PROPRIEDADE_NODE *lista, int idComprador) {
    PROPRIEDADE_NODE *temp = lista;
    while (temp != NULL) {
        if (temp->info.disponibilidade == 1 && temp->info.idcomprador == idComprador) {
            printf("ID: %d\n", temp->info.idPropriedade);
            printf("Tipo: %s\n", temp->info.tipo);
            printf("Morada: %s\n", temp->info.morada);
            printf("Área: %.2f m²\n", temp->info.area);
            printf("Preço: %.2f\n", temp->info.preco);
            printf("ID Agente: %d\n", temp->info.idAgente);
            printf("ID Vendedor: %d\n", temp->info.idvendedor);
            printf("ID Comprador: %d\n", temp->info.idcomprador);
            printf("Como se encontra: %d\n", temp->info.aposcompra);
            printf("Disponibilidade: %d\n\n", temp->info.disponibilidade);
        }
        temp = temp->seguinte;
    }
}


void listarPropriedadesVendaCliente(PROPRIEDADE_NODE *lista, int idVendedor) {
    PROPRIEDADE_NODE *temp = lista;
    while (temp != NULL) {
        if (temp->info.disponibilidade == 0 && temp->info.idvendedor == idVendedor) {
            printf("ID: %d\n", temp->info.idPropriedade);
            printf("Tipo: %s\n", temp->info.tipo);
            printf("Morada: %s\n", temp->info.morada);
            printf("Área: %.2f m²\n", temp->info.area);
            printf("Preço: %.2f\n", temp->info.preco);
            printf("ID Agente: %d\n", temp->info.idAgente);
            printf("ID Vendedor: %d\n", temp->info.idvendedor);
            printf("ID Comprador: %d\n", temp->info.idcomprador);
            printf("Como se encontra: %d\n", temp->info.aposcompra);
            printf("Disponibilidade: %d\n\n", temp->info.disponibilidade);
        }
        temp = temp->seguinte;
    }
}

void listarPropriedadesjaVendaCliente(PROPRIEDADE_NODE *lista, int idVendedor) {
    PROPRIEDADE_NODE *temp = lista;
    while (temp != NULL) {
        if (temp->info.disponibilidade == 1 && temp->info.idvendedor == idVendedor) {
            printf("ID: %d\n", temp->info.idPropriedade);
            printf("Tipo: %s\n", temp->info.tipo);
            printf("Morada: %s\n", temp->info.morada);
            printf("Área: %.2f m²\n", temp->info.area);
            printf("Preço: %.2f\n", temp->info.preco);
            printf("ID Agente: %d\n", temp->info.idAgente);
            printf("ID Vendedor: %d\n", temp->info.idvendedor);
            printf("ID Comprador: %d\n", temp->info.idcomprador);
            printf("Como se encontra: %d\n", temp->info.aposcompra);
            printf("Disponibilidade: %d\n\n", temp->info.disponibilidade);
        }
        temp = temp->seguinte;
    }
}


void listarPropriedades(PROPRIEDADE_NODE *lista) {
    PROPRIEDADE_NODE *temp = lista;
    while (temp != NULL) {
        printf("ID: %d\n", temp->info.idPropriedade);
        printf("Tipo: %s\n", temp->info.tipo);
        printf("Morada: %s\n", temp->info.morada);
        printf("Área: %.2f m²\n", temp->info.area);
        printf("Preço: %.2f\n", temp->info.preco);
        printf("ID Agente: %d\n", temp->info.idAgente);
        printf("ID Vendedor: %d\n", temp->info.idvendedor);
        printf("ID Comprador: %d\n", temp->info.idcomprador);
        printf("Como se encontra: %d\n", temp->info.aposcompra);
        printf("Disponibilidade: %d\n\n", temp->info.disponibilidade);
        temp = temp->seguinte;
    }
}

void removerPropriedade(PROPRIEDADE_NODE **lista, int idPropriedade) {
    PROPRIEDADE_NODE *atual = *lista;
    PROPRIEDADE_NODE *anterior = NULL;

    while (atual != NULL) {
        if (atual->info.idPropriedade == idPropriedade) {
            if (anterior == NULL) {
                *lista = atual->seguinte;
            } else {
                anterior->seguinte = atual->seguinte;
            }
            free(atual);
            printf("Propriedade com ID %d removida com sucesso.\n", idPropriedade);
            return;
        }
        anterior = atual;
        atual = atual->seguinte;
    }
    printf("Propriedade com ID %d não encontrada.\n", idPropriedade);
}




void editarPropriedade(PROPRIEDADE_NODE *lista, int idPropriedade, PROPRIEDADE propriedadeAtualizada) {
    PROPRIEDADE_NODE *atual = lista;
    while (atual != NULL) {
        if (atual->info.idPropriedade == idPropriedade) {
            // Atualizar os dados da propriedade
            atual->info = propriedadeAtualizada;
            printf("Propriedade com ID %d atualizada com sucesso.\n", idPropriedade);
            return;
        }
        atual = atual->seguinte;
    }
    printf("Propriedade com ID %d não encontrada.\n", idPropriedade);
}

// Nova função propriedadearrenda
void propriedadeArrenda(PROPRIEDADE_NODE *lista, int idPropriedade, int tipo, int idComprador) {
    PROPRIEDADE_NODE *atual = lista;
    while (atual != NULL) {
        if (atual->info.idPropriedade == idPropriedade) {
            atual->info.aposcompra = tipo;
            atual->info.idcomprador = idComprador;
            atual->info.disponibilidade = 1;  // Passa a ser indisponível
            printf("Propriedade com ID %d arrendada com sucesso.\n", idPropriedade);
            return;
        }
        atual = atual->seguinte;
    }
    printf("Propriedade com ID %d não encontrada.\n", idPropriedade);
}