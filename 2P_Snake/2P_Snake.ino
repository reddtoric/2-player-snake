#include <LinkedList.h> //https://github.com/ivanseidel/LinkedList
#include <gamma.h>
#include <RGBmatrixPanel.h>


//speed of game & frame rate
//lower number = faster, higher number = slower
int speed = 150;

//dimension of led matrix
#define MAX_X 32
#define MAX_Y 32



//player 1 d-pad
#define P1_LEFT 36
#define P1_DOWN 34
#define P1_RIGHT 40
#define P1_UP 38

//player 2 d-pad
#define P2_LEFT 46
#define P2_DOWN 48
#define P2_RIGHT 42
#define P2_UP 44

enum Direction {
  up,
  down,
  left, 
  right
};

typedef struct Position {
  int x;
  int y;
};

typedef struct Player{
  LinkedList <Position> snake;
  int length;
  Direction direction;
};

//Arduino Mega pins
RGBmatrixPanel matrix(A0, A1, A2, A3, 11, 10, 9, false);

bool gameover = false;

Player p1;
Player p2;
Position food;

int p1Up;
int p1Down;
int p1Left;
int p1Right;

int p2Up;
int p2Down;
int p2Left;
int p2Right;

unsigned long previousTime;
unsigned long currentTime;
unsigned long elapsedTime;


//check validity of food position
bool isValidFoodPosition(){
  Position slice;

  //check against snake 1
  int n = p1.length;
  for (int i = 0; i < n; i++){
    slice = p1.snake.get(i);
    if (food.x == slice.x && food.y == slice.y){
      return false;
    }
  }
  
  //check against snake 2
  n = p2.length;
  for (int i = 0; i < n; i++){
    slice = p2.snake.get(i);
    if (food.x == slice.x && food.y == slice.y){
      return false;
    }
  }

  //food is not on any snake position = valid
  return true;
}

//spawn food on valid position
void spawnFood(){
  while(!isValidFoodPosition()){
    food = randomPosition();
  }
}

//spawn both snakes
void spawnSnakes(){
  p1.snake.unshift(randomPosition());
  p1.length = 1;
  p1.direction = randomDirection();
  
  Position tmp;
  do {
    tmp = randomPosition();
  }
  while(tmp.x != p1.snake.get(0).x && tmp.y != p1.snake.get(0).y);

  p2.snake.unshift(tmp);
  p2.length = 1;
  p2.direction = randomDirection();
}

void eat(){
  if (food.x == p1.snake.get(0).x && food.y == p1.snake.get(0).y){
    spawnFood();
    p1.snake.add(p1.snake.get(p1.snake.size()-1));
    p1.length = p1.snake.size();
  }
  if (food.x == p2.snake.get(0).x && food.y == p2.snake.get(0).y){
    spawnFood();
    p2.snake.add(p2.snake.get(p2.snake.size()-1));
    p2.length = p2.snake.size();
  }
}

void move(){
  Position newSnakeHead;
  newSnakeHead.x = p1.snake.get(0).x + ((p1.direction == left)  ? -1 : ((p1.direction == right)  ? 1 : 0));
  newSnakeHead.y = p1.snake.get(0).y + ((p1.direction == up)    ? -1 : ((p1.direction == down)   ? 1 : 0));

  newSnakeHead.x = (newSnakeHead.x < 0) ? MAX_X-1 : ((newSnakeHead.x >= MAX_X) ? 0 : newSnakeHead.x);
  newSnakeHead.y = (newSnakeHead.y < 0) ? MAX_Y-1 : ((newSnakeHead.y >= MAX_Y) ? 0 : newSnakeHead.y);

  p1.snake.unshift(newSnakeHead);
  //pop tail
  p1.snake.pop();

  
  newSnakeHead.x = p2.snake.get(0).x + ((p2.direction == left)  ? -1 : ((p2.direction == right)  ? 1 : 0));
  newSnakeHead.y = p2.snake.get(0).y + ((p2.direction == up)    ? -1 : ((p2.direction == down)   ? 1 : 0));

  newSnakeHead.x = (newSnakeHead.x < 0) ? MAX_X-1 : ((newSnakeHead.x >= MAX_X) ? 0 : newSnakeHead.x);
  newSnakeHead.y = (newSnakeHead.y < 0) ? MAX_Y-1 : ((newSnakeHead.y >= MAX_Y) ? 0 : newSnakeHead.y);

  p2.snake.unshift(newSnakeHead);
  //pop tail
  p2.snake.pop();
}

Direction randomDirection(){
  return (Direction)random(0, 4);
}

Position randomPosition(){
  return {random(0, MAX_X), random(0, MAX_Y)};
}

void clearFrame(){
  matrix.fillScreen(matrix.Color333(0, 0, 0));
}

void displayFrame(){
  matrix.drawPixel(food.x, food.y, matrix.Color333(7,0,0));

  Position snakeSlice;
  int n = p1.snake.size();
  for(int i = 0; i < n; i++){
    snakeSlice = p1.snake.get(i);
    matrix.drawPixel(snakeSlice.x, snakeSlice.y, matrix.Color333(5, 5, 5));
  }

  n = p2.snake.size();
  for(int i = 0; i < n; i++){
    snakeSlice = p2.snake.get(i);
    matrix.drawPixel(snakeSlice.x, snakeSlice.y, matrix.Color333(0, 0, 5));
  }
}

void check(){
  Position snakeHead = p1.snake.get(0);
  int n = p2.snake.size();
  for(int i = 0; i < n; i++){
    Position snakeSlice = p2.snake.get(i);
    if (snakeHead.x == snakeSlice.x && snakeHead.y == snakeSlice.y){
      gameover = true;
    }
  }

  snakeHead = p2.snake.get(0);
  n = p1.snake.size();
  for(int i = 0; i < n; i++){
    Position snakeSlice = p1.snake.get(i);
    if (snakeHead.x == snakeSlice.x && snakeHead.y == snakeSlice.y){
      gameover = true;
    }
  }
}

void reset(){
  p1.snake.clear();
  p2.snake.clear();
}

void setup() {
  matrix.begin();
  Serial.begin(9600);
  randomSeed(analogRead(0));

  pinMode(P1_UP, INPUT);
  pinMode(P1_DOWN, INPUT);
  pinMode(P1_LEFT, INPUT);
  pinMode(P1_RIGHT, INPUT);
  
  pinMode(P2_UP, INPUT);
  pinMode(P2_DOWN, INPUT);
  pinMode(P2_LEFT, INPUT);
  pinMode(P2_RIGHT, INPUT);
  
  
  spawnSnakes();
  spawnFood();
}

void loop() {
  currentTime = millis();
  elapsedTime = currentTime - previousTime;

  if (!gameover){
    p1Up = digitalRead(P1_UP);
    p1Down = digitalRead(P1_DOWN);
    p1Left = digitalRead(P1_LEFT);
    p1Right = digitalRead(P1_RIGHT);
    
    p2Up = digitalRead(P2_UP);
    p2Down = digitalRead(P2_DOWN);
    p2Left = digitalRead(P2_LEFT);
    p2Right = digitalRead(P2_RIGHT);
    
    p1.direction = (p1Up == HIGH && p1.direction != down) ? up : p1.direction;
    p1.direction = (p1Down == HIGH && p1.direction != up) ? down : p1.direction;
    p1.direction = (p1Left == HIGH && p1.direction != right) ? left : p1.direction;
    p1.direction = (p1Right == HIGH && p1.direction != left) ? right : p1.direction;
    
    p2.direction = (p2Up == HIGH && p2.direction != down) ? up : p2.direction;
    p2.direction = (p2Down == HIGH && p2.direction != up) ? down : p2.direction;
    p2.direction = (p2Left == HIGH && p2.direction != right) ? left : p2.direction;
    p2.direction = (p2Right == HIGH && p2.direction != left) ? right : p2.direction;
    
    if (elapsedTime > speed){
      clearFrame();
      displayFrame();
      
      move();
      eat();
      check();
      previousTime = currentTime;
    }
  }
  else{
    clearFrame();
    matrix.setCursor(2, 0);    // start at top left, with one pixel of spacing
    matrix.setTextSize(1);     // size 1 == 8 pixels high
    matrix.setTextWrap(false); // Don't wrap at end of line - will do ourselves
    
    matrix.setTextColor(matrix.Color333(0,0,5));
    matrix.println("game");
    matrix.println(" over");

    matrix.println("  3");
    delay(1000);
    
    matrix.setCursor(2, 0);
    matrix.fillScreen(matrix.Color333(0, 0, 0));
    matrix.setTextColor(matrix.Color333(0,0,5));
    matrix.println("game");
    matrix.println(" over");
    matrix.println("  2");
    delay(1000);
    
    matrix.setCursor(2, 0);
    matrix.fillScreen(matrix.Color333(0, 0, 0));
    matrix.setTextColor(matrix.Color333(0,0,5));
    matrix.println("game");
    matrix.println(" over");
    matrix.println("  1");
    delay(1000);

    reset();
    spawnSnakes();
    spawnFood();
    gameover = false;
  }
}
