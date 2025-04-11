#ifndef PROCESSO_H
#define PROCESSO_H

#define MAX_PROCESSOS 20000
#define MAX_ASSUNTOS 10
#define MAX_NUM 30
#define MAX_DATA 25

#include <stdlib.h>  // necessário para malloc e free

typedef struct {
    int id;
    char numero[MAX_NUM];
    char data_ajuizamento[MAX_DATA];
    int id_classe;
    int id_assunto[MAX_ASSUNTOS];
    int qtd_assuntos;
    int ano_eleicao;
} Processo;

Processo* alocar_processos();
void liberar_processos(Processo *processos);
int carregar_processos(const char *nome_arquivo, Processo processos[], int *total);
void ordenar_por_id(Processo processos[], int total);
void ordenar_por_data(Processo processos[], int total);
int comparar_datas(const void *a, const void *b);
int contar_por_classe(Processo processos[], int total, int classe);
int contar_assuntos(Processo processos[], int total);
void listar_multiplos_assuntos(Processo processos[], int total);
int dias_em_tramitacao(const char *data);
void salvar_em_csv(const char *nome_arquivo, Processo processos[], int total);

#endif