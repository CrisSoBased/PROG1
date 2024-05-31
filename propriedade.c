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




void obterDataAtual(char *dataAtual) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(dataAtual, "%02d/%02d/%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
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
    char dataAtual[11];
    while (atual != NULL) {
        if (atual->info.idPropriedade == idPropriedade) {
            atual->info.aposcompra = tipo;
            atual->info.idcomprador = idComprador;
            atual->info.disponibilidade = 1;  // Passa a ser indisponível
            
            obterDataAtual(dataAtual);
            strcpy(atual->info.datacompra, dataAtual);
            printf("Propriedade com ID %d arrendada com sucesso.\n", idPropriedade);
            return;
            
        }
        atual = atual->seguinte;
    }
    printf("Propriedade com ID %d não encontrada.\n", idPropriedade);
}


int encontrarMaiorIdPropriedade(PROPRIEDADE_NODE *lista) {
    int maiorId = 0;
    PROPRIEDADE_NODE *atual = lista;

    // Percorre a lista para encontrar o maior idPropriedade
    while (atual != NULL) {
        if (atual->info.idPropriedade > maiorId) {
            maiorId = atual->info.idPropriedade;
        }
        atual = atual->seguinte;
    }

    return maiorId + 1;
}

void propriedadeFatura(PROPRIEDADE_NODE *lista, const char *data, int n, int m) {

    PROPRIEDADE_NODE *atual = lista;
    float faturadiaCasa = 0.0;
    float faturadiaApartamento = 0.0;
    float faturadiaEscritorio = 0.0;
    float faturadiaTerreno = 0.0;
    float faturamesCasa = 0.0;
    float faturamesApartamento = 0.0;
    float faturamesEscritorio = 0.0;
    float faturamesTerreno = 0.0;

    int dia, mes, ano;
    sscanf(data, "%d/%d/%d", &dia, &mes, &ano);

    while (atual != NULL) {
        int diaCompra, mesCompra, anoCompra;
        sscanf(atual->info.datacompra, "%d/%d/%d", &diaCompra, &mesCompra, &anoCompra);

        if (diaCompra == dia && mesCompra == mes && anoCompra == ano) {
            if (strcmp(atual->info.tipo, "casa") == 0) {
                if (atual->info.aposcompra == 1) {
                    faturadiaCasa += atual->info.preco;
                } else if (atual->info.aposcompra == 2) {
                    faturadiaCasa += atual->info.precoalugada;
                }
            } else if (strcmp(atual->info.tipo, "apartamento") == 0) {
                if (atual->info.aposcompra == 1) {
                    faturadiaApartamento += atual->info.preco;
                } else if (atual->info.aposcompra == 2) {
                    faturadiaApartamento += atual->info.precoalugada;
                }
            } else if (strcmp(atual->info.tipo, "escritorio") == 0) {
                if (atual->info.aposcompra == 1) {
                    faturadiaEscritorio += atual->info.preco;
                } else if (atual->info.aposcompra == 2) {
                    faturadiaEscritorio += atual->info.precoalugada;
                }
            } else if (strcmp(atual->info.tipo, "terreno") == 0) {
                if (atual->info.aposcompra == 1) {
                    faturadiaTerreno += atual->info.preco;
                } else if (atual->info.aposcompra == 2) {
                    faturadiaTerreno += atual->info.precoalugada;
                }
            }
        }

        if (mesCompra == mes && anoCompra == ano) {
            if (strcmp(atual->info.tipo, "casa") == 0) {
                if (atual->info.aposcompra == 1) {
                    faturamesCasa += atual->info.preco;
                } else if (atual->info.aposcompra == 2) {
                    faturamesCasa += atual->info.precoalugada;
                }
            } else if (strcmp(atual->info.tipo, "apartamento") == 0) {
                if (atual->info.aposcompra == 1) {
                    faturamesApartamento += atual->info.preco;
                } else if (atual->info.aposcompra == 2) {
                    faturamesApartamento += atual->info.precoalugada;
                }
            } else if (strcmp(atual->info.tipo, "escritorio") == 0) {
                if (atual->info.aposcompra == 1) {
                    faturamesEscritorio += atual->info.preco;
                } else if (atual->info.aposcompra == 2) {
                    faturamesEscritorio += atual->info.precoalugada;
                }
            } else if (strcmp(atual->info.tipo, "terreno") == 0) {
                if (atual->info.aposcompra == 1) {
                    faturamesTerreno += atual->info.preco;
                } else if (atual->info.aposcompra == 2) {
                    faturamesTerreno += atual->info.precoalugada;
                }
            }
        }

        atual = atual->seguinte;
    }

    if (n == 1) {
        FILE *file = fopen("faturacontas.txt", "w");
        if (file == NULL) {
            printf("Erro ao abrir o arquivo para escrita.\n");
            return;
        }

        if(m == 0){
            fprintf(file, "Faturamento no dia %s:\n", data);
            fprintf(file, "Casa: %.2f\n", faturadiaCasa);
            fprintf(file, "Apartamento: %.2f\n", faturadiaApartamento);
            fprintf(file, "Escritorio: %.2f\n", faturadiaEscritorio);
            fprintf(file, "Terreno: %.2f\n", faturadiaTerreno);

        }else if(m == 1){
            fprintf(file, "\nFaturamento no mês %02d/%04d:\n", mes, ano);
            fprintf(file, "Casa: %.2f\n", faturamesCasa);
            fprintf(file, "Apartamento: %.2f\n", faturamesApartamento);
            fprintf(file, "Escritorio: %.2f\n", faturamesEscritorio);
            fprintf(file, "Terreno: %.2f\n", faturamesTerreno);

        }
        

       

        fclose(file);
    } else {
        
        if(m == 0){
          
            printf("Faturamento no dia %s:\n", data);
            printf("Casa: %.2f\n", faturadiaCasa);
            printf("Apartamento: %.2f\n", faturadiaApartamento);
            printf("Escritorio: %.2f\n", faturadiaEscritorio);
            printf("Terreno: %.2f\n", faturadiaTerreno);
      
        }else if(m == 1){
      
            printf("\nFaturamento no mês %02d/%04d:\n", mes, ano);
            printf("Casa: %.2f\n", faturamesCasa);
            printf("Apartamento: %.2f\n", faturamesApartamento);
            printf("Escritorio: %.2f\n", faturamesEscritorio);
            printf("Terreno: %.2f\n", faturamesTerreno);
        }
        

        
    }
}