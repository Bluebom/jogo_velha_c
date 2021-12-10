#include<stdio.h>;
#include<stdlib.h>;
#include<locale.h>;
#include "likemethods.h";

/* SEPARANDO AS LOGICAS EM PEQUENAS FUNÇÕES, FAZENDO COMENTÁRIOS E CRIANDO VARIAVEIS COERENTES QUERO TRAZER O MÁXIMO DE BOAS PRÁTICAS PARA ESSE PROJETO */

// a ideia aqui é verifica se a posição que o usuário escolheu está vazia
int isVoidPosition(int x, int y){
    if(game[x][y] != 'X' && game[x][y] != 'O'){
        return 1;
    }
    printf("\n\n Opção inválida! \n\n");
    return 0;
}

// a ideia aqui é impedir que o usuário jogue uma posição que fuja do escopo
int isValidPosition(int x, int y) {
    // verifica a coordenada x (horizontal)
    if(x >= 0 && x < 3){
        // verifica a coordenada y (vertical)
        if(y >= 0 && y < 3){
            return 1;
        }
    }
    printf("\n\n Opção inválida! \n\n");
    return 0;
}

void printGame()
{
    int i, j;
    printf("\t  0   1   2\n");
    for(i = 0; i < 3; i++){
        printf("\t%d", i);
        for(j = 0; j < 3; j++){
            if(isValidChar(game[i][j])){
                if(j < 2)
                    printf(" %c |", game[i][j]);
                else
                    printf(" %c ", game[i][j]);
            }
            else{
                if(j < 2)
                    printf("   |");
                else
                    printf("   ");
            }
        }
        if(i < 2)
            printf("\n\t==============\n");
        else 
            printf("\n\n\n");
    }
}

void play() {
    int x, y, isValidChar, max = 0, won = 0, order = 1;
    do{
        do {
                printGame();
                printf("Digite a posição que deseja jogar (utilize o sistema de coordenadas (x,y) para jogar): \n");
                scanf(" %d%d", &x, &y);
                isValidChar = isValidPosition(x, y);
                if(isValidChar == 1)
                    isValidChar += isVoidPosition(x ,y);
            } while(isValidChar != 2);
        if(order == 1){
            game[x][y] = 'X';
            order--;
        }
        else{
            game[x][y] = 'O';
            order++;
        }
        max++;
        won += lineWin();
        won += columnWin();
        won += mainDiagonalWin();
        won += secondaryDiagonalWin();
    }while(won == 0 && max < 9);
    if(won !=  0){
        if(order != 1){
            printf("O jogador %s ganhou o jogo\n", playerOne);
        } else {
            printf("O jogador %s ganhou o jogo\n", playerTwo);
        }
    } else {
        printf("\nParece que deu empate...");
    }
}

int main(){
    setlocale(LC_ALL, "portuguese");

    int op = 1;

    printf("Jogador 1 digite seu nome: ");
    fgets(playerOne, 50, stdin);
    fflush(stdin);
    printf("Jogador 2 digite seu nome: ");
    fgets(playerTwo, 50, stdin);
    fflush(stdin);
    do{
        startMatriz();
        play();
        printf("\nDesejam jogar novamente?\n1 - sim\n2 - não\n");
        scanf("%d", &op);
    }while(op == 1);
    return 0;
}