#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
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
static int snakeLength = 0;
void clearScreen(void);

int isSnake(int x,int y){
  for(int i=0;i<snakeLength;i++){
    if(snake[i].x ==x && snake[i].y == y){
      return 1;
    }
  }
  return 0;
}

int generateFruit(){
  while(1){
    srand(time(NULL));
    int col= rand()%COL;

    int row= rand()%ROW;
    printf("s%", row+","+col);
    if(isSnake(col,row)==0){
      snakeGrid[col][row]= "🍎";
        return 0;
    }
  }
  return 0;
}
int gameOver(){
  clearScreen();
  printf(
"\n"
"=====================================\n"
"             GAME OVER               \n"
"=====================================\n"
"\n"
"            ████████                 \n"
"          ██        ██               \n"
"         ██  X    X   ██              \n"
"         ██    ▄▄     ██              \n"
"         ██   ████    ██              \n"
"          ██        ██               \n"
"            ████████                 \n"
"\n"
"        Thanks for playing!           \n"
"        Press any key to exit         \n"
"\n"
);

}
void initiateGame()
{
    for (int i = 0; i < COL; i++)
    {
        for (int j = 0; j < ROW; j++)
       {
            snakeGrid[i][j] = "🔳";
       } 
    }
    // set head of snake
    snake[0].x = COL / 2;
    snake[0].y = ROW / 2;
    snakeGrid[snake[0].x][snake[0].y] = "🟪";

    // set body of snake
    for (int i = 1; i < 5; i++)
    {
        snake[i].x = COL / 2;
        snake[i].y = ROW / 2 - i;
        snakeGrid[snake[i].x][snake[i].y] = "🟦";
    }
    snakeLength += 5;
}
// print snake and board
void printArray()
{
    // Clear screen using ANSI escape codes (works in VS Code)
    clearScreen();
    
    for (int i = 0; i < COL; i++)
    {
        for (int j = 0; j < ROW; j++){
          if(
            snakeGrid[i][j] != "🍎"){
            snakeGrid[i][j] = "🔳";}
        }
    }

    snakeGrid[snake[0].x][snake[0].y] = "🟪";

    // set body of snake
    for (int i = 1; i < snakeLength; i++)
    {
        snakeGrid[snake[i].x][snake[i].y] = "🟦";
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
int hasFruit(){
  for (int i = 0; i < COL; i++)
    {
        for (int j = 0; j < ROW; j++){
          if(
            snakeGrid[i][j] == "🍎"){
            return 1;
        }
    }}
        return 0;
}
int adaptSnake(int newX, int newY)
{
    if (newX == snake[0].x && newY == snake[0].y)
    {
        newX = snake[0].x + (snake[0].x - snake[1].x);
        newY = snake[0].y + (snake[0].y - snake[1].y);
    }
    boolean isFruit =snakeGrid[newX][newY]=="🍎";

    struct Cell snakePos = {snake[0].x, snake[0].y};
    printf(" x=%d", snake[0].x);
    printf(" y=%d", snake[0].y);
    if(isSnake(newX,newY)==1){
      return 0;
    }
    snake[0].x = newX;
    snake[0].y = newY;
    printf(" %d", newX);
    printf(" %d", newY);
    for (int i = 1; i < snakeLength; i++)
    {
        struct Cell tempPos = snake[i];
        snake[i] = snakePos;
        snakePos = tempPos;
    }
    if(isFruit){
      snake[snakeLength]= snakePos;
      snakeLength++;
    }
    
    return 1;
}

void clearScreen(void) {
    printf("\033[H");       // Cursor nach oben
    printf("\033[2J");      // Bildschirm löschen
    printf("\033[3J");      // Scrollback löschen (nicht überall unterstützt)
    fflush(stdout);
}

int main()
{
    srand(time(NULL));
    // Set console to UTF-8 for emojis
    SetConsoleOutputCP(65001);
    initiateGame();

    /*// Enable ANSI escape codes for Windows
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);*/

    printArray();
    adaptSnake(snake[0].x, snake[0].y + 1);
    printArray();
    // add snake to map
    int additionToX = 0;
    int additionToY = 0;
    int count=0;
    while (1)
    {

        if(snake[0].x < 0  || snake[0].x > COL  || snake[0].y < 0 || snake[0].y > ROW ){ 
          gameOver();
          return 0;
        }else{if(count==7){
        adaptSnake(snake[0].x + additionToX, snake[0].y + additionToY);
        additionToX = 0;
        additionToY = 0;
        printArray();
        count=0;}
        count++;
        printf("%d",count);
        if (kbhit())
        {
            char key = getch();
            printf(" %c", key);
            if (key == 'w')
                additionToX = -1;
            if (key == 'a')
                additionToY = -1;
            if (key == 's')
                additionToX = +1;
            if (key == 'd')
                additionToY = +1;
          }
        }
        if(hasFruit()==0){
        generateFruit();}
        Sleep(17);
    
    
    }return 0;
}
