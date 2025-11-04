#include<stdio.h>
#include<string.h>
#include<stdbool.h>

#include<time.h>

/*
    A game about a parkour guy who runs around the map and gets to a orange square
*/

// Rooms
// This is a global variable that needs to exist because this will tell all the other functions what room level we are on
int roomLevel = 0;
int roomData[10][3] =
    {
        {35, 26, 30}
    };

/*                  Room Height || Room Length ||  Room Time
    Room Level 0:     20 Units      30 Units       30 Seconds


*/


// Container of all the rooms we're in
const int rooms[1][100][100] = {
    {
        {5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5},
        {5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5},
        {5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,4,5},
        {5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,4,5},
        {5,0,0,0,0,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,0,5,5,5,5,5,5},
        {5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5},
        {5,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5},
        {5,5,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5},
        {5,5,5,5,5,0,0,5,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5},
        {5,0,0,0,0,0,0,5,5,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5},
        {5,0,0,0,0,0,0,5,5,5,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5},
        {5,0,0,0,0,0,0,5,5,5,5,5,5,0,0,5,5,5,5,5,5,5,0,0,5,5,5,5,5,0,0,0,0,0,5},
        {5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5},
        {5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,5},
        {5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,5,5},
        {5,0,0,0,0,5,5,5,5,5,0,0,5,5,5,5,5,0,0,5,5,5,5,5,5,0,0,5,5,5,0,0,0,0,5},
        {5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5},
        {5,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5},
        {5,5,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5},
        {5,5,5,5,5,5,0,0,5,5,5,5,5,5,5,5,0,0,5,5,5,5,5,5,5,5,5,5,5,5,5,5,0,0,5},
        {5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5},
        {5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5},
        {5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,5},
        {5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,5,5,5,5},
        {5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,5,5,5,5,5},
        {5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5}
    }
};

// This variable is for handling the current room we have, basically we just make this room equal to all the values in the room we're currently at
int curRoom[100][100];


/*
    Keeping the display simple:
    0 - Blank space
    1 - ()Player head - 1 pixel
    2 - ||Player body - 1 pixel
    3 - |_
    4 - _|
    5 - [], A block
    6 - /\, A spike
*/


// Function prototypes declaration
void update();
void start();
void initialize();

// Functions for displaying the screen
void drawScreen();
void printCell(int);
void clearScreen();

// Function responsible for the rooms
void setRoom(int);

// Functions responsible for input
void getInput();

// Function for moving the player
void findPlayerHeadPos(); // Finds the location of the players head
void movePlayer(char inputData[],int inputLength);
void moveLeft();
void moveRight();
void jump();
void gravCheck();
int plPos[2];
int jumpHeight = 4;

// Function for time
void waitDelay(float);
void timeHandler();
clock_t previousFrameTime = 0;
clock_t currentFrameTime = 0;
double deltaTime = 0;
float moveSpeed = 100;



int main()
{

    // Initialize function
    initialize();

    // Start Function - Used for the start of the game
    start();

    // Update Function - Used for the update function of the game
    update();

}

// Initialize functions
void initialize()
{
    setRoom(0);
}

// Beginning of the game function
void start()
{
    drawScreen();
}

// Update Functions
void update()
{
    // The idea is that we ask the user for input then we do stuff based on what we inputted
    getInput();

    // Get input

}

void drawScreen()
{
    clearScreen();
    // Responsible for drawing the entire room
    for(int y = 0; y < roomData[roomLevel][1]; y++)
    {
        for(int x = 0; x < roomData[roomLevel][0]; x++)
        {
            // Send the value of the current room to the printCell function
            printCell(curRoom[y][x]);
        }
        printf("\n");
    }
}


void printCell(int value)
{
    // Function for quick printing
    switch(value)
    {
        case 0: printf("  "); break;
        case 1: printf(":P"); break;
        case 2: printf("||"); break;
        case 3: printf("|-"); break;
        case 4: printf("-|"); break;
        case 5: printf("[]"); break;
        case 6: printf("/\\"); break;
        default: printf("er"); break;
    }
}


void setRoom(int desiredRoom)
{
    // Sets the current room equal to the room we want to be, this is so that we're working with a copy of the room rather than the original room itself
    for(int y = 0; y < 100; y++)
    {
        for(int x = 0; x < 100; x++)
        {
            curRoom[y][x] = rooms[desiredRoom][y][x];
        }
    }
}

void getInput()
{
    char inputData[100];
    printf("\nControls are: \n    D/d - Right\n    A/a - Left\n    W/w - Jump\n    F/f - Wait\nInput: ");

    // Scanf reads all the values up until the new line and stores them in inputData
    scanf("%[^\n]c", &inputData);


    // Finds the length of the given data, we can read this as a string so we use strLen
    int inputLength = strlen(inputData);
    previousFrameTime = clock();


    movePlayer(inputData, inputLength);
}


void movePlayer(char inputData[],int inputLength)
{

    // Test input of the data
    for(int i = 0; i < inputLength; i++)
    {
        // Determine how the said data will be used, we can use a switch statement here

        if(inputData[i] != ' ')printf("\nYou did: %c", inputData[i]);
        switch(inputData[i])
        {
            case 'a':
            case 'A':
                moveLeft();
                gravCheck();
                break;
            case 'd':
            case 'D':
                moveRight();
                gravCheck();
                break;
            case 'w':
            case 'W':
                jump(); break;
            case 'f':
            case 'F':
                printf("\nYou stopped moving"); break;
            case ' ':
                continue; break;
            default:
                printf("\nThat is not a valid movement option"); break;

        }
    }

    gravCheck();
}

void moveLeft()
{
    // Finds position of the head
    findPlayerHeadPos();
    //printf("\nPlayer head is at x = %d and y = %d", plPos[0] + 1, plPos[1] + 1);

    // We know where head is, we also know where the body is, we add one because Y axis is inverted
    int headX = plPos[0], headY = plPos[1], bodyX = plPos[0], bodyY = plPos[1] + 1;

    // Check if it can move to the left, that means all things to the left are 0
    bool canMove = (curRoom[headY][headX - 1] == 0) && (curRoom[bodyY][bodyX - 1] == 0);
    if(!canMove) return;

    curRoom[headY][headX - 1] = 1;
    curRoom[bodyY][bodyX - 1] = 2;

    curRoom[headY][headX] = 0;
    curRoom[bodyY][bodyX] = 0;

    //printf("\nYou moved left\n");
    drawScreen();
    waitDelay(moveSpeed);
}

void moveRight()
{
    // Finds position of the head
    findPlayerHeadPos();
    //printf("\nPlayer head is at x = %d and y = %d", plPos[0] + 1, plPos[1] + 1);

    // We know where head is, we also know where the body is, we add one because Y axis is inverted
    int headX = plPos[0], headY = plPos[1], bodyX = plPos[0], bodyY = plPos[1] + 1;

    // Check if it can move to the left, that means all things to the left are 0
    bool canMove = (curRoom[headY][headX + 1] == 0) && (curRoom[bodyY][bodyX + 1] == 0);
    if(!canMove) return;

    curRoom[headY][headX + 1] = 1;
    curRoom[bodyY][bodyX + 1] = 2;

    curRoom[headY][headX] = 0;
    curRoom[bodyY][bodyX] = 0;

    //printf("\nYou moved right\n");
    drawScreen();
    waitDelay(moveSpeed);
}

void jump()
{
    // Finds position of the head
    findPlayerHeadPos();
    //printf("\nPlayer head is at x = %d and y = %d", plPos[0] + 1, plPos[1] + 1);

    // We know where head is, we also know where the body is, we add one because Y axis is inverted
    int headX = plPos[0], headY = plPos[1], bodyX = plPos[0], bodyY = plPos[1] + 1;

    bool canJump = curRoom[bodyY + 1][bodyX] != 0;

    if(!canJump)
    {
        gravCheck();
        return;
    }

    for(int i = 1; i <= jumpHeight; i++)
    {
        if(curRoom[headY-i][headX] != 0)
        {
            curRoom[bodyY][bodyX] = 0;
            curRoom[headY][headX] = 0;

            curRoom[headY - i+1][headX] = 1;
            curRoom[bodyY - i+1][bodyX] = 2;
            break;
        }

        if(i == jumpHeight)
        {
            curRoom[bodyY][bodyX] = 0;
            curRoom[headY][headX] = 0;

            curRoom[headY - 4][headX] = 1;
            curRoom[bodyY - 4][bodyX] = 2;
        }
    }

    drawScreen();
    waitDelay(moveSpeed);

}

void findPlayerHeadPos()
{
    for(int y = 0; y < roomData[roomLevel][1]; y++)
    {
        for(int x = 0; x < roomData[roomLevel][0]; x++)
        {
            if(curRoom[y][x] == 1)
            {
                plPos[0] = x;
                plPos[1] = y;
                break;
            }
        }
    }
}


void timeHandler()
{
    currentFrameTime = clock();
    deltaTime = ((double)(currentFrameTime - previousFrameTime) / CLOCKS_PER_SEC * 1000);
    previousFrameTime = currentFrameTime;
}


void waitDelay(float waitForMS)
{
    // Function that replicates Sleep() in windows.h
    int t = 0;
    while(t < waitForMS)
    {
        t += (float)deltaTime;
        timeHandler();
    }
}

void clearScreen()
{
    // Gives the illusion of clearing the screen
    printf("\033[H");
}

void gravCheck()
{
    // Finds position of the head
    findPlayerHeadPos();
    //printf("\nPlayer head is at x = %d and y = %d", plPos[0] + 1, plPos[1] + 1);

    // We know where head is, we also know where the body is, we add one because Y axis is inverted
    int headX = plPos[0], headY = plPos[1], bodyX = plPos[0], bodyY = plPos[1] + 1;

    if(curRoom[bodyY+1][bodyX] == 0)
    {
        curRoom[bodyY][bodyX] = 0;
        curRoom[headY][headX] = 0;

        curRoom[headY + 1][headX] = 1;
        curRoom[bodyY + 1][bodyX] = 2;
        drawScreen();
        waitDelay(moveSpeed);
    }
}


