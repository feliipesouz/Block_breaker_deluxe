#include<stdio.h>
#include<iso646.h>
#include"conio.h"
#include<stdlib.h>
#include<time.h>
#include<unistd.h>

#define LINHA 8
#define COLUNA 11
#define R 1
#define C 5
#define RB 1
#define CB 2

void montaArray(char board[LINHA][COLUNA]){
  for(int i=0; i<LINHA; i++){
    for(int j=0; j<COLUNA; j++){
      if((i>0) and (i<4) and (j>1) and (j<9)){
        board[i][j] = '#';
      } else if((i == 7) and (j>2) and (j<8)){
        board[i][j] = '*';
      }else if((i == 6) and (j == 5)){
        board[i][j] = 'O';
      }else{
        board[i][j] = '.';
      }
    }
  }
}

void printaArray(char board[LINHA][COLUNA]){
  system("@cls||clear");
  for(int i=0; i<LINHA; i++){
    for(int j=0; j<COLUNA; j++){
      if(j != 10){
        printf("%c", board[i][j]);
        printf(" ");
      }else{
        printf("%c\n", board[i][j]);
      }
    }
  }
}

void posicoesArray(int position_board[R][C]){
  for(int i=0; i<R; i++){
    for(int j=0; j<C; j++){
      position_board[R][C] = 0;
    }
  }
}

void posicaoArrayBarra(char board[LINHA][COLUNA], int position_board[R][C]){
  int cont = 0;
  for(int i=0; i<LINHA; i++){
    for(int j=0; j<COLUNA; j++){
      if(board[i][j] == '*'){
        position_board[0][cont] = j;
        cont++;
      }   
    }
  }
}

void posicaoBarra(char board[LINHA][COLUNA], int position_ball[RB][CB]){
  for(int i=0; i<LINHA; i++){
    for(int j=0; j<COLUNA; j++){
      if(board[i][j] == 'O'){
        position_ball[0][0] = i;
        position_ball[0][1] = j;
      }
    }
  }
}

void mudarArray(char board[LINHA][COLUNA], int position_ball[RB][CB], int position_board[R][C]){
  for(int i=0; i<LINHA; i++){
    for(int j=0; j<COLUNA; j++){
      if(i == position_ball[0][0] and j == position_ball[0][1]){
        board[i][j] = 'O';
      }else if((i>0) and (i<4) and (j>1) and (j<9)){
        board[i][j] = '#';
      } else if((i == 7) and (j>= position_board[0][0]) and (j<= position_board[0][4])){
        board[i][j] = '*';
      }else{
        board[i][j] = '.';
      }
    }
  }
}

void moverBarra(char board[LINHA][COLUNA], int position_board[R][C], char key){
  if (key == 'A' or key == 'a'){
    int cont = 0;
    if(position_board[0][0] != 0){
      for(int j = 0; j<5; j++){
        board[7][position_board[0][cont]] = '.';
        position_board[0][cont] = position_board[0][cont] - 1;
        board[7][position_board[0][cont]] = '*';
        cont++;
      }
    }
  }else if(key == 'D' or key == 'd'){
    int cont = 4;
    if(position_board[0][4] != 10){
      for(int j = 0; j<5; j++){
        board[7][position_board[0][cont]] = '.';
        position_board[0][cont] = position_board[0][cont] + 1;
        board[7][position_board[0][cont]] = '*';
        cont--;
      }
    }
  }
}

void moverBola(char board[LINHA][COLUNA], int position_ball[RB][CB], int previous_position_ball[RB][CB], int position_board[R][C]){
  int row_ball = 6;
  int column_ball = 5;

  int previous_row_ball = 6;
  int previous_column_ball = 5;

  int cont = 0;
  while(1){
    char key;
    if (_kbhit()){
      key =_getch();
      if(key == 'Q' or key == 'q'){
        break;
      }
      posicaoArrayBarra(board, position_board);
      moverBarra(board, position_board, key);
    }
    if(row_ball == 0){
      previous_row_ball = row_ball;
      row_ball += 1;
      if(column_ball == 0){
        previous_column_ball = column_ball;
        column_ball += 1;
      }else if(column_ball == 10){
        previous_column_ball = column_ball;
        column_ball -= 1;
      }else{
        if((previous_column_ball == column_ball) or (column_ball == 5)){
          previous_column_ball = column_ball;
        }else if(previous_column_ball < column_ball){
          previous_column_ball = column_ball;
          column_ball += 1;
        }else if(previous_column_ball > column_ball){
          previous_column_ball = column_ball;
          column_ball -= 1;
        }
      }
    }else if(row_ball == 7){
      if((column_ball == position_board[0][0]) or (column_ball == position_board[0][1])){
        previous_row_ball = row_ball;
        row_ball -= 1;
        previous_column_ball = column_ball;
        column_ball -= 1;
      }else if((column_ball == position_board[0][3]) or (column_ball == position_board[0][4])){
        previous_row_ball = row_ball;
        row_ball -= 1;
        previous_column_ball = column_ball;
        column_ball += 1;
      }else if(column_ball == position_board[0][2]){
        previous_row_ball = row_ball;
        row_ball -= 1;
        previous_column_ball = column_ball;
      }else{
        printf("Perdeu Playboy!");
        break;
      }
    }else if(column_ball == 0){
      previous_column_ball = column_ball;
      column_ball += 1;
      if(previous_row_ball > row_ball){
        previous_row_ball = row_ball;
        row_ball -= 1;
      }else if(previous_row_ball < row_ball){
        previous_row_ball = row_ball;
        row_ball += 1;
      }
    }else if(column_ball == 10){
      previous_column_ball = column_ball;
      column_ball -= 1;
      if(previous_row_ball > row_ball){
        previous_row_ball = row_ball;
        row_ball -= 1;
      }else if(previous_row_ball < row_ball){
        previous_row_ball = row_ball;
        row_ball += 1;
      }
    }else{
      if(previous_column_ball == column_ball){
        if(previous_row_ball < row_ball){
          previous_row_ball = row_ball;
          row_ball += 1;
        }else{
          previous_row_ball = row_ball;
          row_ball -= 1;
        }
      }else if(previous_column_ball < column_ball){
        previous_column_ball = column_ball;
        column_ball += 1;
        if(previous_row_ball < row_ball){
          previous_row_ball = row_ball;
          row_ball += 1;
        }else{
          previous_row_ball = row_ball;
          row_ball -= 1;
        }
      }else if(previous_column_ball > column_ball){
        previous_column_ball = column_ball;
        column_ball -= 1;
        if(previous_row_ball < row_ball){
          previous_row_ball = row_ball;
          row_ball += 1;
        }else{
          previous_row_ball = row_ball;
          row_ball -= 1;
        }
      }
    }

    previous_position_ball[0][0] = previous_row_ball;
    previous_position_ball[0][1] = previous_column_ball;

    position_ball[0][0] = row_ball;
    position_ball[0][1] = column_ball;

    mudarArray(board, position_ball, position_board);
    printaArray(board);
    sleep(1);
    cont++;
  }
}

int main(void){
  char board[LINHA][COLUNA];
  int position_ball[RB][CB];
  int position_board[R][C];
  int previous_position_ball[RB][CB];

  montaArray(board);
  printaArray(board);

  posicoesArray(position_board);

  posicaoArrayBarra(board, position_board);

  posicaoBarra(board, position_ball);

  mudarArray(board, position_ball, position_board);

  moverBola(board, position_ball, previous_position_ball, position_board);
}