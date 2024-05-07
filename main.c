#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char tabuleiro[3][3];
char jogador1[20], jogador2[20];
char jogadorAtual = 'X';

void inicializarTabuleiro() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            tabuleiro[i][j] = ' ';
        }
    }
}

void exibirTabuleiro() {
    printf("Jogador 1 (%s) | Jogador 2 (%s) \n", jogador1, jogador2);
    printf("-------------\n");
    for (int i = 0; i < 3; i++) {
        printf("|");
        for (int j = 0; j < 3; j++) {
            printf(" %c |", tabuleiro[i][j]);
        }
        printf("\n-------------\n");
    }
}

int verificarVitoria() {
    int vitoria = 0;

    //linhas
    for (int i = 0; i < 3; i++) {
        if (tabuleiro[i][0] == jogadorAtual && tabuleiro[i][1] == jogadorAtual && tabuleiro[i][2] == jogadorAtual) {
            vitoria = 1;
            break;
        }
    }

    //colunas
    if (!vitoria) {
        for (int j = 0; j < 3; j++) {
            if (tabuleiro[0][j] == jogadorAtual && tabuleiro[1][j] == jogadorAtual && tabuleiro[2][j] == jogadorAtual) {
                vitoria = 1;
                break;
            }
        }
    }

    //diagonais
    if (!vitoria) {
        if (tabuleiro[0][0] == jogadorAtual && tabuleiro[1][1] == jogadorAtual && tabuleiro[2][2] == jogadorAtual) {
            vitoria = 1;
        } else if (tabuleiro[0][2] == jogadorAtual && tabuleiro[1][1] == jogadorAtual && tabuleiro[2][0] == jogadorAtual) {
            vitoria = 1;
        }
    }

    //empate
    if (!vitoria) {
        int empate = 1;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (tabuleiro[i][j] == ' ') {
                    empate = 0;
                    break;
                }
            }
        }
        if (empate) {
            vitoria = -1;
        }
    }

    return vitoria;
}

int main() {
    int escolher;
    char jogador[20];
    do {
    printf("Digite 1 para jogar com dois jogadores\n");
    scanf("%d", &escolher);
    } while (escolher != 1);

    if (escolher == 1) {
        printf("Digite o nome do jogador 1 (representado pelo X): ");
        scanf("%s", jogador1);
        printf("Digite o nome do jogador 2 (representado pelo O): ");
        scanf("%s", jogador2);

        srand(time(NULL));

        int sorteio = rand() % 2;
        if (sorteio == 0) {
            jogadorAtual = 'X';
            printf("Quem começa é o jogador 1 (%s)\n", jogador1);
        } else {
            jogadorAtual = 'O';
            printf("Quem começa é o jogador 2 (%s)\n", jogador2);
        }

        inicializarTabuleiro();
        exibirTabuleiro();

        int linha, coluna;
        int resultado = 0;

        while (1) {
            printf("%s, digite a linha (1-3) e coluna (1-3) da sua jogada: ", (jogadorAtual == 'X') ? jogador1 : jogador2);
            if (scanf("%d %d", &linha, &coluna) != 2 || linha < 1 || linha > 3 || coluna < 1 || coluna > 3 || tabuleiro[linha - 1][coluna - 1] != ' ') {
                printf("Jogada inválida. Tente novamente.\n");
                while (getchar() != '\n');
            } else {
                tabuleiro[linha - 1][coluna - 1] = jogadorAtual;
                exibirTabuleiro();
                resultado = verificarVitoria();

                if (resultado == 1) {
                    printf("O jogador ");
                    if (jogadorAtual == 'X') {
                        printf("%s", jogador1);
                    } else {
                        printf("%s", jogador2);
                    }
                    printf(" venceu!\n");
                    break;
                } else if (resultado == -1) {
                    printf("Empate!\n");
                    break;
                }

                if (jogadorAtual == 'X') {
                    jogadorAtual = 'O';
                } else {
                    jogadorAtual = 'X';
                }
            }
        }
    } else if (escolher == 2) {
    } else {
        printf("Opção de jogo inválida. Digite 1.\n");
    }

    return 0;
}
