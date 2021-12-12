#ifndef LIKEMETHODS_H_INCLUDED
#define LIKEMETHODS_H_INCLUDED
#endif

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
    for(j = 0; j < 3; j++){
        for(i = 0; i < 2; i++){
            if(isValidChar(game[i][j]) && game[i][j] == game[i+1][j]) 
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


