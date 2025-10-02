#include <stdio.h>

#define TAM 10       // tabuleiro 10x10
#define NAVIO 3      // navio = 3
#define HABILIDADE 5 // habilidade = 5
#define TAM_NAVIO 3  // navio sempre 3 casas

// preenche o tabuleiro todo com água
void inicializarTabuleiro(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            tabuleiro[i][j] = 0;
}

// mostra o tabuleiro no console
void exibirTabuleiro(int tabuleiro[TAM][TAM]) {
    printf("\n=== TABULEIRO ===\n\n");

    printf("   ");
    for (int j = 0; j < TAM; j++)
        printf("%2d ", j);
    printf("\n");

    for (int i = 0; i < TAM; i++) {
        printf("%2d ", i);
        for (int j = 0; j < TAM; j++)
            printf("%2d ", tabuleiro[i][j]);
        printf("\n");
    }
}

// checa se dá pra colocar o navio na posição sem sair do tabuleiro ou bater em outro
int podePosicionar(int tabuleiro[TAM][TAM], int linha, int coluna, int orientacao) {
    if (orientacao == 0) { // horizontal
        if (coluna + TAM_NAVIO > TAM) return 0;
        for (int j = 0; j < TAM_NAVIO; j++)
            if (tabuleiro[linha][coluna + j] == NAVIO) return 0;
    } else if (orientacao == 1) { // vertical
        if (linha + TAM_NAVIO > TAM) return 0;
        for (int i = 0; i < TAM_NAVIO; i++)
            if (tabuleiro[linha + i][coluna] == NAVIO) return 0;
    } else if (orientacao == 2) { // diagonal ↘
        if (linha + TAM_NAVIO > TAM || coluna + TAM_NAVIO > TAM) return 0;
        for (int k = 0; k < TAM_NAVIO; k++)
            if (tabuleiro[linha + k][coluna + k] == NAVIO) return 0;
    } else if (orientacao == 3) { // diagonal ↙
        if (linha + TAM_NAVIO > TAM || coluna - (TAM_NAVIO - 1) < 0) return 0;
        for (int k = 0; k < TAM_NAVIO; k++)
            if (tabuleiro[linha + k][coluna - k] == NAVIO) return 0;
    }
    return 1;
}

// marca o navio no tabuleiro
void posicionarNavio(int tabuleiro[TAM][TAM], int linha, int coluna, int orientacao) {
    if (!podePosicionar(tabuleiro, linha, coluna, orientacao)) {
        printf("Não deu pra colocar o navio em (%d,%d)\n", linha, coluna);
        return;
    }

    if (orientacao == 0) for (int j = 0; j < TAM_NAVIO; j++) tabuleiro[linha][coluna + j] = NAVIO;
    else if (orientacao == 1) for (int i = 0; i < TAM_NAVIO; i++) tabuleiro[linha + i][coluna] = NAVIO;
    else if (orientacao == 2) for (int k = 0; k < TAM_NAVIO; k++) tabuleiro[linha + k][coluna + k] = NAVIO;
    else if (orientacao == 3) for (int k = 0; k < TAM_NAVIO; k++) tabuleiro[linha + k][coluna - k] = NAVIO;
}

// aplica a habilidade no tabuleiro, respeitando limites e sem apagar navios
void aplicarHabilidade(int tabuleiro[TAM][TAM], int habilidade[][5], int tamHabilidade, int origemLinha, int origemColuna) {
    int offset = tamHabilidade / 2; // ponto central da habilidade

    for (int i = 0; i < tamHabilidade; i++) {
        for (int j = 0; j < tamHabilidade; j++) {
            int linhaTab = origemLinha - offset + i;
            int colTab = origemColuna - offset + j;

            if (linhaTab >= 0 && linhaTab < TAM && colTab >= 0 && colTab < TAM) {
                if (habilidade[i][j] == 1 && tabuleiro[linhaTab][colTab] == 0)
                    tabuleiro[linhaTab][colTab] = HABILIDADE;
            }
        }
    }
}

// cria a forma de cone
void criarCone(int cone[5][5]) {
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            cone[i][j] = (j >= 2 - i && j <= 2 + i) ? 1 : 0;
}

// cria a forma de cruz
void criarCruz(int cruz[5][5]) {
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            cruz[i][j] = (i == 2 || j == 2) ? 1 : 0;
}

// cria a forma de octaedro/losango
void criarOctaedro(int octa[5][5]) {
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            octa[i][j] = (j == 2 || i + j == 2 || j - i == 2) ? 1 : 0;
}

int main() {
    int tabuleiro[TAM][TAM];

    inicializarTabuleiro(tabuleiro); // começa tudo vazio

    // coloca os 4 navios
    posicionarNavio(tabuleiro, 2, 3, 0); // horizontal
    posicionarNavio(tabuleiro, 5, 7, 1); // vertical
    posicionarNavio(tabuleiro, 0, 0, 2); // diagonal ↘
    posicionarNavio(tabuleiro, 1, 8, 3); // diagonal ↙

    // cria as habilidades
    int cone[5][5], cruz[5][5], octa[5][5];
    criarCone(cone);
    criarCruz(cruz);
    criarOctaedro(octa);

    // aplica habilidades no tabuleiro
    aplicarHabilidade(tabuleiro, cone, 5, 2, 2);
    aplicarHabilidade(tabuleiro, cruz, 5, 6, 6);
    aplicarHabilidade(tabuleiro, octa, 5, 4, 7);

    exibirTabuleiro(tabuleiro); // mostra tudo

    return 0;
}
