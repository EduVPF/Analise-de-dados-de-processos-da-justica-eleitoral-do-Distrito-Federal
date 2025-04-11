#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "processo.h"


int main() {
    Processo *processos = malloc(sizeof(Processo) * MAX_PROCESSOS);
    if (processos == NULL) {
        printf("Erro ao alocar memoria para os processos.\n");
        return 1;
    }

    int total = 0;
    char nome_arquivo[] = "entrada.csv";

    if (!carregar_processos(nome_arquivo, processos, &total)) {
        printf("Falha ao carregar o arquivo. Certifique-se de que '%s' está na mesma pasta.\n", nome_arquivo);
        free(processos);
        return 1;
    }

    printf("Total de processos carregados: %d\n", total);

    int opcao, classe, i;
    char nome_saida[100];
    do {
        printf("\n--- MENU ---\n");
        printf("1. Ordenar por ID (crescente) e salvar em CSV\n");
        printf("2. Ordenar por Data (decrescente) e salvar em CSV\n");
        printf("3. Contar processos por ID de Classe\n");
        printf("4. Contar assuntos únicos\n");
        printf("5. Listar processos com múltiplos assuntos\n");
        printf("6. Mostrar dias em tramitacao para cada processo\n");
        printf("0. Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                ordenar_por_id(processos, total);
                printf("Digite o nome do arquivo de saída: ");
                scanf("%s", nome_saida);
                if (!strstr(nome_saida, ".csv")) {
                strcat(nome_saida, ".csv");
                }
                salvar_em_csv(nome_saida, processos, total);
                break;            
            case 2:
            ordenar_por_data(processos, total);
                printf("Digite o nome do arquivo de saída: ");
                scanf(" %[^\n]", nome_saida);
                if (!strstr(nome_saida, ".csv")) {
                strcat(nome_saida, ".csv");
                }
                salvar_em_csv(nome_saida, processos, total);
                break;
            case 3:
                printf("Digite o ID da classe: ");
                scanf("%d", &classe);
                printf("Total de processos: %d\n", contar_por_classe(processos, total, classe));
                break;
            case 4:
                printf("Total de assuntos únicos: %d\n", contar_assuntos(processos, total));
                break;
            case 5:
                listar_multiplos_assuntos(processos, total);
                break;
            case 6:
                for (i = 0; i < total; i++) {
                    printf("ID: %d - Dias em tramitacao: %d\n", processos[i].id, dias_em_tramitacao(processos[i].data_ajuizamento));
                }
                break;
            case 0:
                printf("Encerrando...\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 0);

    free(processos);
    return 0;
}