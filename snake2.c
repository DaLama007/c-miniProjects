#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#define COL 12
#define ROW 24
#define MAX_SNAKE_LEN 100
static char *snakeGrid[COL][ROW];
struct Cell
    {
        int x;
        int y;
    };
    // make vector to save snake part position

static struct Cell snake[MAX_SNAKE_LEN];
static int snakeLength =0;
void initiateGame()
{   
    for (int i = 0; i < COL; i++)
    {
        for (int j = 0; j < ROW; j++)
        {
            snakeGrid[i][j] = "⬛";
        }
    }
    //set head of snake
    snake[0].x = COL/2;
    snake[0].y = ROW/2;
    snakeGrid[snake[0].x][snake[0].y]="🟪";
    

    //set body of snake
    for(int i=1;i<5;i++){
        snake[i].x = COL/2;
        snake[i].y = ROW/2-i;
        snakeGrid[snake[i].x][snake[i].y]="🟦";
    }
    snakeLength+=5;
}
    //print snake and board
void printArray(){
    // Clear screen using ANSI escape codes (works in VS Code)
    printf("\x1b[2J\x1b[H");
    for (int i = 0; i < COL; i++)
    {
        for (int j = 0; j < ROW; j++)
        {
            snakeGrid[i][j] = "⬛";
        }
    }

    snakeGrid[snake[0].x][snake[0].y]="🟪";

    //set body of snake
    for(int i=1;i<snakeLength;i++){
        snakeGrid[snake[i].x][snake[i].y]="🟦";
    }
    
    for (int i = 0; i < COL; i++)
    {
        for (int j = 0; j < ROW; j++)
        {
            printf("%s ", snakeGrid[i][j]);
        }
        printf("\n");
    }
}

void adaptSnake(int newX, int newY){
    if(newX==snake[0].x && newY==snake[0].y){
        newX=snake[0].x+(snake[0].x-snake[1].x);
        newY=snake[0].y+(snake[0].y-snake[1].y);
    }
    struct Cell snakePos = {snake[0].x, snake[0].y};
    printf(" x=%d", snake[0].x);
    printf(" y=%d", snake[0].y);
    snake[0].x = newX;
    snake[0].y = newY;
    printf(" %d", newX);
    printf(" %d", newY);
    for(int i=1;i<snakeLength;i++){
        struct Cell tempPos = snake[i];
        snake[i] = snakePos;
        snakePos = tempPos;
    }
}    

int main()
{   
    // Set console to UTF-8 for emojis
    SetConsoleOutputCP(65001);
    initiateGame();
    printArray();
    adaptSnake(snake[0].x,snake[0].y+1);
    printArray();
    // add snake to map
    int additionToX = 0;
    int additionToY = 0;
    while(snake[0].x>=0 && snake[0].x<COL && snake[0].y>0 && snake[0].y<ROW){
        
        adaptSnake(snake[0].x+additionToX,snake[0].y+additionToY);
        int additionToX = 0;
        int additionToY = 0;
        printArray();
        if(_kbhit()){
            
            char key= _getch();
            printf(" %f", key);
            if(key=='w') additionToX=-1;
            if(key=='a') additionToY=-1;
            if(key=='s') additionToX=+1;
            if(key=='d') additionToY=+1;
        }
        Sleep(1000);
    }

    return 0;
}