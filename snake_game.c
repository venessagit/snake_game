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
    * Get 100 points.
    * Game ends hits a border.
    * 
To-do:
    * Include a points system.
    * Increase speed after eating each fruit.
    * Auto move in direction.
    * Fruit disappears after eating.
    * Grow the snake after eating a fruit.
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

typedef struct {
    int row [100];
    int col [100];
    int score;
    int speed;
    int length;
    int inputchar;
} snakestruct;

void create_border(char block[][BORDER_WIDTH], int *fruit, snakestruct *snake){

    for (int i=0; i < BORDER_LENGTH; i++){
        for(int j = 0; j < BORDER_WIDTH; j++){
            if(i == 0 || j == 0 || i == BORDER_LENGTH-1 || j == BORDER_WIDTH-1 ){
                block[i][j] = '#'; //Borders
            } else if(i == fruit[0] && j== fruit[1]){
                block[i][j] = '*'; //Fruits
            } else {
                block[i][j] = ' '; //Empty Space
            }
            for(int k = 0; k <= snake->length; k++){
                if(i == snake->row[k] && j== snake->col[k]){
                block[i][j] = '0'; //Snake
                }
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

int  movesnake(snakestruct *snake, int *fruit){

    switch (snake->inputchar) {
        case 'w':
        case 'W':
            snake->row[snake->length]--;
            break;
        case 's':
        case 'S':
            snake->row[snake->length]++;
            break;
        case 'a':
        case 'A':
            snake->col[snake->length]--;
            break;
        case 'd':
        case 'D':
            snake->col[snake->length]++;
            break;
        default:
            break;
    }

    for(int i = 0; i < snake->length; i++){
        snake->row[i] = snake->row[i+1];
        snake->col[i] = snake->col[i+1];
    }
        
    if(snake->row[snake->length] == 0 || snake->col[snake->length] == 0 || snake->row[snake->length] == BORDER_LENGTH-1 || snake->col[snake->length] == BORDER_WIDTH-1 ){
        printf("Sorry, you lost the game! \n\tTotal Points: %d", snake->score);
        return 0; //lost the game
    } else if(snake->row[snake->length] == fruit[0] && snake->col[snake->length]== fruit[1]){
        snake->score += 10;
        int head = snake->length + 1;

        //Creates a body
        if (snake->length == 0){
            snake->row[head] = snake->row[snake->length];
            snake->col[head] = snake->col[snake->length];
            snake->length++;
            head++;
        }

        snake->row[head] = snake->row[snake->length];
        snake->col[head] = snake->col[snake->length];
        snake->length++ ;

        if (snake->score == 100){
            printf("Congratulations, you won!\n\tTotal Points: %d", snake->score);
            return 0; // End game
        }
        return 1; //ate a fruit
    } 
    return 2; //continue playing

}

int main(){
    
    snakestruct snake = {.speed = 550};
    get_random_position(&snake.row[0], &snake.col[0]);

    char block [BORDER_LENGTH][BORDER_WIDTH] ={0};
    int fruit [2] = {0,0};
    int cont = 1;

    srand(time(NULL));
    
    do {
        if (cont == 1){
            get_random_position(&fruit[0], &fruit[1]);
            snake.speed -= 50;
        }
        
        system("cls"); 
        create_border(block, fruit, &snake);

        printf("Score: %d Points\n", snake.score);
        printf("W (Up) \t A (Left) \t D (Right) \t S (Down)\n");

        Sleep(snake.speed);

        if (_kbhit())
            snake.inputchar = getch();

        cont = movesnake(&snake, fruit);

    } while (cont > 0) ;

    return 0;
}