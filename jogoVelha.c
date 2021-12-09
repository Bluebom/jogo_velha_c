#include<stdio.h>;
#include<stdlib.h>;
#include<locale.h>;

// variavel global facilita o desenvolvimento do jogo por poder ser acessada facilmente por qualquer função
char game[3][3]; //Matriz
char playerOne[50] /* X */,playerTwo[50] /* O */; //Nome dos jogadores

void startMatriz()
{
    int i, j;
    // acessando linhas
    for(i = 0; i < 3; i ++)
    {
        // acessando colunas
        for(j = 0; j < 3; j++){
            game[i][j] = 'a';
        }
    }
}

/* SEPARANDO AS LOGICAS EM PEQUENAS FUNÇÃO, FAZENDO COMENTÁRIOS E CRIANDO VARIAVEIS COERENTES QUERO TRAZER O MÁXIMO DE BOAS PRÁTICAS PARA ESSE PROJETO */

// a ideia aqui é verifica se a posição que o usuário escolheu está vazia
int isVoidPosition(int x, int y){
    if(game[x][y] != 'X' && game[x][y] != 'O'){
        return 1;
    }
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
    return 0;
}

// A ideia aqui é validar se o caracter é válido
int isValidChar(char letra){
    if(letra == 'X' || letra == 'O')
        return 1;
    else
        return 0;
}

// a ideia aqui é verificar se a posição das linhas dá a algum dos jogadores a vitória
int lineWin(){
    int i, j, same = 1;
    for(i = 0; i < 3; i++){
        for(j = 0; j < 2; j++){
            if(isValidChar(game[i][j]) && game[i][j] == game[i][j+1])
                same++;
        }
            if(same == 3)
                return 1;
            same = 1;
    }
    return 0; // ngm venceu pelas linhas
}

// a ideia aqui é verificar se a posição das colunas dá a algum dos jogadores a vitória
int columnWin(){
    int i, j, same = 1;
    for(i = 0; i < 2; i++){
        for(j = 0; j < 3; j ++){
            if(isValidChar(game[i][j] && game[i][j] == game[i+1][j])) 
                same++;
        }
        if(same == 3)
            return 1;
        same = 1;
    }
    return 0; // ngm venceu pelas colunas
}

// a ideia aqui é verificar se a diagonal dá a algum dos jogadores a vitória
int mainDiagonalWin(){
    int i, same = 1;
    for(i = 0; i < 2; i++){
        if(isValidChar(game[i][i]) && game[i][i] == game[i+1][i+1]){
            same++;
        }
    }
    if(same == 3)
        return 1;
    return 0; //ngm ganha na diagonal
}

int secondaryDiagonalWin(){
    int i, j, same = 1;
    for(i = 0; i < 2; i++){
        if(isValidChar(game[i][2-i]) && game[i][2-i] == game[i+1][1-i]){
            same++;
        }
    }
    if(same == 3)
        return 1;
    return 0; //ngm ganha na diagonal
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