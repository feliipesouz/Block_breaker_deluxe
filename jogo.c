#include<stdio.h>
#include<iso646.h>
#include<stdlib.h>
#include"conio.h"


//Variáveis globais

//Quantidade de linhas do tabuleiro
#define ROW 8
//Quatidade de colunas do tabuleiro
#define COLUMN 11
//Quantidade de linhas do vetor que irá guardar as posições da paleta
#define R 1
//Quatidade de colunas do vetor que irá guardar as posições da paleta
#define C 5

//Função para criar o tabuleiro
//Essa função é sem retorno, pois, como ela está recebendo a matriz da main, ela está usando referência
//Essa referência possibilita que o que eu alterar na matriz daqui, também vai alterar na matriz da main.
void fill_array(char board[ROW][COLUMN]){
  for(int i=0; i<ROW; i++){
    for(int j=0; j<COLUMN; j++){
      //Aqui só especifiquei as posições onde ele deve colocar o #. Tipo de qual linha até qual linha e de que coluna até que coluna
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

//Aqui vai só inicializar o vetor colocando a posição 0 em todos. Só para inicializar. 
//Do mesmo modo, por referência. 
void fill_array_positions(int position_board[R][C]){
  for(int i=0; i<R; i++){
    for(int j=0; j<C; j++){
      position_board[R][C] = 0;
    }
  }
}


//Printar a matriz
void print_array(char board[ROW][COLUMN]){
  system("@cls||clear");
  for(int i=0; i<ROW; i++){
    for(int j=0; j<COLUMN; j++){
      if(j != 10){
        printf("%c", board[i][j]);
        printf(" ");
      }else{
        printf("%c\n", board[i][j]);
      }
    }
  }
}


//Procura a posição da paleta e coloca no vetor
void search_positions_pallet(char board[ROW][COLUMN], int position_board[R][C]){
  int cont = 0;
  for(int i=0; i<ROW; i++){
    for(int j=0; j<COLUMN; j++){
      if(board[i][j] == '*'){
        position_board[0][cont] = j;
        cont++;
      }   
    }
  }
}

void move_pallet(char board[ROW][COLUMN], int position_board[R][C], char key){
  //Recolocando os valores na matriz para não ocorrer o bug
  for(int i=0; i<ROW; i++){
    for(int j=0; j<COLUMN; j++){
      if((i>0) and (i<4) and (j>1) and (j<9)){
        board[i][j] = '#';
      }else if((i == 6) and (j == 5)){
        board[i][j] = 'O';
      }else if(i != 7){
        board[i][j] = '.';
      }
    }
  }

  //Essa parte aqui eu te explico amanhã
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

int main(void){
  char board[ROW][COLUMN];
  int position_board[R][C];

  fill_array(board);
  print_array(board);

  fill_array_positions(position_board);

  while(1){
    char key;
    if (_kbhit()){
      key =_getch();
      if(key == 'Q' or key == 'q'){
        break;
      }
      search_positions_pallet(board, position_board);
      move_pallet(board, position_board, key);
      print_array(board);
    }    
  }
}
