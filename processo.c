#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "processo.h"

int carregar_processos(const char *nome_arquivo, Processo processos[], int *total) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo.\n");
        return 0;
    }

    char linha[2048];
    int i = 0;
    fgets(linha, sizeof(linha), arquivo); // Ignora o cabeçalho

    while (fgets(linha, sizeof(linha), arquivo)) {
        Processo p; // Declaração do processo
        char *token = strtok(linha, ",");
        p.id = atoi(token); // Captura o ID

        token = strtok(NULL, ",");
        sscanf(token, "\"%[^\"]\"", p.numero); // Captura o número

        token = strtok(NULL, ",");
        strcpy(p.data_ajuizamento, token); // Captura a data de ajuizamento

        token = strtok(NULL, ",");
        sscanf(token, "{%d}", &p.id_classe); // Captura o ID da classe

        p.qtd_assuntos = 0;

        // Parsing do campo id_assunto
        token = strtok(NULL, ",");
        if (token && strchr(token, '{')) {
            char assuntos_raw[1024] = {0};
            strcpy(assuntos_raw, token);

            while (token && !strchr(token, '}')) {
                token = strtok(NULL, ",");
                if (token) {
                    strcat(assuntos_raw, ",");
                    strcat(assuntos_raw, token);
                }
            }

            char assuntos_limpos[1024] = {0};
            // Captura os valores dentro de "{...}" com aspas
            sscanf(assuntos_raw, "\"{%[^\"]}\"", assuntos_limpos);

            // Separa os valores por vírgula
            char *assunto_token = strtok(assuntos_limpos, ",");
            while (assunto_token != NULL && p.qtd_assuntos < MAX_ASSUNTOS) {
                p.id_assunto[p.qtd_assuntos++] = atoi(assunto_token);
                assunto_token = strtok(NULL, ",");
            }
        }

        token = strtok(NULL, ",");
        p.ano_eleicao = token ? atoi(token) : 0; // Captura o ano da eleição

        processos[i++] = p;
        if (i >= MAX_PROCESSOS) {
            printf("Aviso: limite de processos atingido.\n");
            break;
        }
    }

    fclose(arquivo);
    *total = i;
    return 1;
}



void ordenar_por_id(Processo processos[], int total) {
    for (int i = 0; i < total - 1; i++) {
        for (int j = i + 1; j < total; j++) {
            if (processos[i].id > processos[j].id) {
                Processo temp = processos[i];
                processos[i] = processos[j];
                processos[j] = temp;
            }
        }
    }
}

void ordenar_por_data(Processo *processos, int total) {
    qsort(processos, total, sizeof(Processo), comparar_datas);
}

int comparar_datas(const void *a, const void *b) {
    Processo *p1 = (Processo *)a;
    Processo *p2 = (Processo *)b;

    struct tm tm1 = {0}, tm2 = {0};
    sscanf(p1->data_ajuizamento, "%d-%d-%d %d:%d:%d",
           &tm1.tm_year, &tm1.tm_mon, &tm1.tm_mday,
           &tm1.tm_hour, &tm1.tm_min, &tm1.tm_sec);

    sscanf(p2->data_ajuizamento, "%d-%d-%d %d:%d:%d",
           &tm2.tm_year, &tm2.tm_mon, &tm2.tm_mday,
           &tm2.tm_hour, &tm2.tm_min, &tm2.tm_sec);

    tm1.tm_year -= 1900;
    tm1.tm_mon--;
    tm2.tm_year -= 1900;
    tm2.tm_mon--;

    time_t t1 = mktime(&tm1);
    time_t t2 = mktime(&tm2);

    return (int)(t2 - t1); // Decrescente
}

int contar_por_classe(Processo processos[], int total, int classe) {
    int count = 0;
    for (int i = 0; i < total; i++) {
        if (processos[i].id_classe == classe)
            count++;
    }
    return count;
}

int contar_assuntos(Processo processos[], int total) {
    int unicos[1000];
    int qtd_unicos = 0;

    for (int i = 0; i < total; i++) {
        for (int j = 0; j < processos[i].qtd_assuntos; j++) {
            int atual = processos[i].id_assunto[j];
            int repetido = 0;

            for (int k = 0; k < qtd_unicos; k++) {
                if (unicos[k] == atual) {
                    repetido = 1;
                    break;
                }
            }

            if (!repetido && qtd_unicos < 1000) {
                unicos[qtd_unicos++] = atual;
            }
        }
    }

    return qtd_unicos;
}

void listar_multiplos_assuntos(Processo processos[], int total) {
    int encontrados = 0;
    printf("Processos com mais de um assunto:\n");

    for (int i = 0; i < total; i++) {
        if (processos[i].qtd_assuntos > 1) {
            printf("ID: %d - Numero: %s - Quantidade de assuntos: %d - Assuntos: {",
                   processos[i].id, processos[i].numero, processos[i].qtd_assuntos);

            for (int j = 0; j < processos[i].qtd_assuntos; j++) {
                printf("%d%s", processos[i].id_assunto[j], j < processos[i].qtd_assuntos - 1 ? ", " : "");
            }
            printf("}\n");
            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf("Nenhum processo com mais de um assunto encontrado.\n");
    }
}


int dias_em_tramitacao(const char *data) {
    struct tm tm = {0};
    sscanf(data, "%d-%d-%d", &tm.tm_year, &tm.tm_mon, &tm.tm_mday);
    tm.tm_year -= 1900;
    tm.tm_mon -= 1;

    time_t data_inicio = mktime(&tm);
    time_t hoje = time(NULL);

    double segundos = difftime(hoje, data_inicio);
    return (int)(segundos / (60 * 60 * 24));
}

void salvar_em_csv(const char *nome_arquivo, Processo processos[], int total) {
    FILE *arquivo = fopen(nome_arquivo, "w");
    if (!arquivo) {
        printf("Erro ao salvar CSV.\n");
        return;
    }

    fprintf(arquivo, "\"id\",\"numero\",\"data_ajuizamento\",\"id_classe\",\"id_assunto\",\"ano_eleicao\"\n");
    for (int i = 0; i < total; i++) {
        fprintf(arquivo, "%d,\"%s\",%s,{", processos[i].id, processos[i].numero, processos[i].data_ajuizamento);
        
        for (int j = 0; j < processos[i].qtd_assuntos; j++) {
            fprintf(arquivo, "%d%s", processos[i].id_assunto[j], j < processos[i].qtd_assuntos - 1 ? ", " : "");
        }

        fprintf(arquivo, "},{%d},%d\n", processos[i].id_classe, processos[i].ano_eleicao);
    }

    fclose(arquivo);
}
