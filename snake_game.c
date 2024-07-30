/*
Welcome to the snake game!

*****************************
*                           *
*                           *
*                           *
*         #                 *
*                           *
*         0                 *
*                           *
*                           *
*                           *
*                           *
*                           *
*****************************

Rules to play:
    * The user can move in-between the * borders.
    * The user aim is to eat the #.
    * Game ends hits a border.
    * 
To-do:
    * Include a points system.
    * Auto move in direction.
    * Grow the snake after eating a fruit.
    * Fruit disappears after eating.
    * The snake dies after eating itself.
    * Make sure the fruit does not appear on snake.

*/

#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#define BORDER_LENGTH 20
#define BORDER_WIDTH 50


void create_border(char block[][BORDER_WIDTH], int *fruit, int *snake){
    
    char border = '*';
    char empty = ' ';
    char fruitchar = '#';
    char snakechar = '0';

    for (int i=0; i < BORDER_LENGTH; i++){
        for(int j = 0; j < BORDER_WIDTH; j++){
            if(i == 0 || j == 0 || i == BORDER_LENGTH-1 || j == BORDER_WIDTH-1 ){
                block[i][j] = border;
            } else if(i == fruit[0] && j== fruit[1]){
                block[i][j] = fruitchar;          
            } else if(i == snake[0] && j== snake[1]){
                block[i][j] = snakechar;  
            } else {
                block[i][j] = empty;
            }
            printf("%c", block[i][j]);
        }
        printf("\n");
    }
}

void get_random_position(int *row, int *col){
    *row = (rand() % (BORDER_LENGTH -2)) +1;
    *col = (rand() % (BORDER_WIDTH -2)) +1;
}

int  movesnake(char c, int *snake, int *fruit){

    if (c == 'w' || c == 'W')
        snake[0]--;
    else if (c == 's' || c == 'S')
        snake[0]++;
    else if (c == 'a' || c == 'A')
        snake[1]--;
    else if (c == 'd' || c == 'D')
        snake[1]++; 
        
    if(snake[0] == 0 || snake[1] == 0 || snake[0] == BORDER_LENGTH-1 || snake[1] == BORDER_WIDTH-1 ){
        printf("Sorry, you lost the game!");
        return 0; //lost the game
    } else if(snake[0] == fruit[0] && snake[1]== fruit[1]){
        printf("Yay, you got the fruit!");
        return 1; //ate a fruit
    } 
    return 2; //continue playing

}

int main(){
    
    srand(time(NULL));
    int row = 0;
    int col = 0;
    int cont = 2;

    int *row_pointer = &row;
    int *col_pointer = &col;
    char block [BORDER_LENGTH][BORDER_WIDTH] ={0};
    char c = ' ';

    get_random_position(row_pointer, col_pointer);
    int snake [2] = {row, col};

    get_random_position(row_pointer, col_pointer);
    int fruit [2] = {row, col};

    do {
        system("cls"); 
        create_border(block, fruit, snake);

        printf("W (Up) \t A (Left) \t D (Right) \t S (Down)\n");

        if (_kbhit()){
            c = getch();
            cont = movesnake(c, snake, fruit);
        } else {
            cont = movesnake(c, snake, fruit);

        }
        Sleep(500);

    } while (cont == 2) ;

    return 0;
}