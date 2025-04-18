#include <stdio.h>
#include <stdlib.h>
#include "processo.h"

int main(void) {
    // Parte 4: nome fixo do CSV
    const char *arquivo = "processo_043_202409032338.csv";

    int n;
    char *header;
    Processo *vet = lerProcessos(arquivo, &n, &header);

    int op;
    do {
        printf("\n=== Menu ===\n");
        \n
        printf("1) Ordenar por ID e gerar CSV\n");
        printf("2) Ordenar por DATA e gerar CSV\n");
        printf("3) Contar por ID_CLASSE\n");
        printf("4) Contar ID_ASSUNTOS UNICOS\n");
        printf("5) LISTAR PROCESSO com >1 assunto\n");
        printf("6) DIAS EM TRAMITACAO de um processo\n");
        printf("0) Sair\n");
        \n
        printf("Escolha: ");
        if (scanf("%d", &op) != 1) { scanf("%*s"); continue; }

        switch (op) {
            case 1:
                ordenarPorId(vet, n);
                escreverOrdenadoId(vet, n, header, "ordenado_por_id.csv");
                printf("Arquivo 'ordenado_por_id.csv' criado.\n");
                break;
            case 2:
                ordenarPorData(vet, n);
                escreverOrdenadoData(vet, n, header, "ordenado_por_data.csv");
                printf("Arquivo 'ordenado_por_data.csv' criado.\n");
                break;
            case 3: {
                int cl;
                printf("Informe id_classe: ");
                scanf("%d", &cl);
                printf("Total: %d\n", contarPorClasse(vet, n, cl));
                break;
            }
            case 4:
                printf("Assuntos únicos: %d\n", contarAssuntosUnicos(vet, n));
                break;
            case 5:
                listarProcessosMultiplosAssuntos(vet, n);
                break;
            case 6: {
                long id;
                printf("Informe ID do processo: ");
                scanf("%ld", &id);
                for (int i = 0; i < n; i++) {
                    if (vet[i].id == id) {
                        printf("%d dias em tramitação\n",
                               diasEmTramitacao(vet[i].data_ajuizamento));
                        break;
                    }
                }
                break;
            }
        }
    } while (op != 0);

    liberarProcessos(vet, n, header);
    return 0;
}
