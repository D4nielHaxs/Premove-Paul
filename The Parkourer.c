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
int roomData[10][4] =
    {
        {11, 10, 30, 5}
    };

/*                  Room Height || Room Length ||  Room Time    || Attempt Times
    Room Level 0:     20 Units      30 Units       30 Seconds           3 Times


*/


// Container of all the rooms we're in
const int rooms[1][100][100] = {
    {
        {5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5},
        {5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5},
        {5, 3, 4, 0, 0, 0, 0, 0, 0, 0, 5},
        {5, 3, 4, 0, 0, 0, 0, 0, 0, 0, 5},
        {5, 5, 5, 5, 5, 5, 5, 5, 5, 0, 5},
        {5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5},
        {5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5},
        {5, 8, 0, 1, 0, 0, 0, 0, 7, 5, 5},
        {5, 5, 8, 2, 0, 0, 0, 7, 5, 5, 5},
        {5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5},
    }
};

// This variable is for handling the current room we have, basically we just make this room equal to all the values in the room we're currently at
int curRoom[100][100];

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
void findPlayerPos(); // Finds the location of the players head
void movePlayer(char inputData[],int inputLength);
void moveLeft();
void moveRight();
void jump();
void gravCheck();
int plPos[2];
const int jumpHeight = 3;

// Variables for player
int attemptTimes = 0; // Amount of times the player can pre-move



// Function for time
void waitDelay(float);
void timeHandler();
clock_t previousFrameTime = 0;
clock_t currentFrameTime = 0;
double deltaTime = 0;

//  Create vector 2 struct: A Vector 2 only holds 2 integers, a x and a y
typedef struct  {int x, y;} Vec2;
Vec2 headPosPL;
Vec2 bodyPosPL;

float moveSpeed = 300; // The delay in displaying the next move

// Game Loop Variable
bool gameOn = true;

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
    attemptTimes = roomData[roomLevel][3];
}

// Update Functions
void update()
{
    // The idea is that we ask the user for input then we do stuff based on what we inputted
    while (gameOn == true)
    {
        if(attemptTimes > 0)
        {
            getInput();
            attemptTimes--;
        }
        update();
    }

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
        case 0: printf("  "); break;    // Blank space
        case 1: printf("()"); break;    // Player head
        case 2: printf("||"); break;    // Player body
        case 3: printf("|-"); break;    // Door left side
        case 4: printf("-|"); break;    // Door Right side
        case 5: printf("[]"); break;    // Normal block
        case 6: printf("/\\"); break;   // Spike
        case 7: printf("/T"); break;    // Right side staircase
        case 8: printf("T\\"); break;    // Left side staircase
        default: printf("er"); break;   // Error case
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

    printf("\nYou have %d attempts left", attemptTimes);
    printf("\nControls are: \n    D/d - Right\n    A/a - Left\n    W/w - Jump\n    F/f - Wait\nInput: ");

    // Scanf reads all the values up until the new line and stores them in inputData
    scanf(" %[^\n]c", &inputData);


    // Finds the length of the given data, we can read this as a string so we use strLen
    int inputLength = strlen(inputData);
    previousFrameTime = clock();

    printf("\033[2J\033[H"); //  Makes the screen black for 1 frame
    movePlayer(inputData, inputLength);
}


void movePlayer(char inputData[],int inputLength)
{

    // Test input of the data
    for(int i = 0; i < inputLength; i++)
    {
        // Updates the system on the position of the player
        findPlayerPos();

        // Determine how the said data will be used, we can use a switch statement here
        switch(inputData[i])
        {
            case 'a':
            case 'A':
                moveLeft();
                gravCheck();
                drawScreen();
                waitDelay(moveSpeed);
                break;
            case 'd':
            case 'D':
                moveRight();
                gravCheck();
                drawScreen();
                waitDelay(moveSpeed);
                break;
            case 'w':
            case 'W':
                jump();
                drawScreen();
                waitDelay(moveSpeed);
                break;
            case 'f':
            case 'F':
                printf("\nYou stopped moving"); break;
            case ' ':
                continue; break;
            default:
                printf("\nThat is not a valid movement option"); break;

        }
    }


    // We check if the player is grounded
    findPlayerPos();
    while(curRoom[bodyPosPL.y + 1][bodyPosPL.x] == 0)
    {
        gravCheck();
        waitDelay(moveSpeed);
        findPlayerPos();
        drawScreen();
        printf("\nBody Position X = %d, Body Position Y = %d", bodyPosPL.x, bodyPosPL.y);
    }
}

void moveLeft()
{
    int blockVal = curRoom[bodyPosPL.y][headPosPL.x - 1]; // This is the value of the the block
    Vec2 blockPos = {bodyPosPL.x - 1, bodyPosPL.y};

    // Staircase checking
    if(blockVal == 0)
    {
        // Check if it can move to the left, that means all things to the left are 0
        bool canMove = (curRoom[headPosPL.y][headPosPL.x - 1] == 0) && (curRoom[bodyPosPL.y][bodyPosPL.x - 1] == 0);
        if(!canMove) return;

        curRoom[headPosPL.y][headPosPL.x - 1] = 1;
        curRoom[bodyPosPL.y][bodyPosPL.x - 1] = 2;

        curRoom[headPosPL.y][headPosPL.x] = 0;
        curRoom[bodyPosPL.y][bodyPosPL.x] = 0;
    } else if (blockVal == 8)
    {
        // This happens when we are about to hit a stair case

        // Check if the 2 blocks above the staircase are free
        bool canGetUp = (curRoom[blockPos.y-1][blockPos.x] == 0 && curRoom[blockPos.y-2][blockPos.x] == 0);
        if(!canGetUp) return;

        curRoom[headPosPL.y - 1][headPosPL.x - 1] = 1;
        curRoom[bodyPosPL.y - 1][bodyPosPL.x - 1] = 2;

        curRoom[headPosPL.y][headPosPL.x] = 0;
        curRoom[bodyPosPL.y][bodyPosPL.x] = 0;
    }
}

void moveRight()
{
    int blockVal = curRoom[bodyPosPL.y][headPosPL.x + 1]; // This is the value of the the block
    Vec2 blockPos = {bodyPosPL.x - 1, bodyPosPL.y};

    // Staircase checking
    if(blockVal == 0)
    {
        // Check if it can move to the left, that means all things to the left are 0
        bool canMove = (curRoom[headPosPL.y][headPosPL.x + 1] == 0) && (curRoom[bodyPosPL.y][bodyPosPL.x + 1] == 0);
        if(!canMove) return;

        curRoom[headPosPL.y][headPosPL.x + 1] = 1;
        curRoom[bodyPosPL.y][bodyPosPL.x + 1] = 2;

        curRoom[headPosPL.y][headPosPL.x] = 0;
        curRoom[bodyPosPL.y][bodyPosPL.x] = 0;
    } else if (blockVal == 7)
    {
        // This happens when we are about to hit a stair case

        // Check if the 2 blocks above the staircase are free
        bool canGetUp = (curRoom[blockPos.y-1][blockPos.x] == 0 && curRoom[blockPos.y-2][blockPos.x] == 0);
        if(!canGetUp) return;

        curRoom[headPosPL.y - 1][headPosPL.x + 1] = 1;
        curRoom[bodyPosPL.y - 1][bodyPosPL.x + 1] = 2;

        curRoom[headPosPL.y][headPosPL.x] = 0;
        curRoom[bodyPosPL.y][bodyPosPL.x] = 0;
    }
}

void jump()
{

    bool canJump = curRoom[bodyPosPL.y + 1][bodyPosPL.x] != 0;


    // This checks if we're in the air, if we are at the air then we don't jump but instead fall
    if(!canJump)
    {
        gravCheck();
        return;
    }

    // We check the spaces above the player's head if it is free
    for(int i = 1; i <= jumpHeight; i++)
    {
        // When we hit a block (the block above is not free) then the head position will be the space below it
        if(curRoom[headPosPL.y - i][headPosPL.x] != 0)
        {
            curRoom[headPosPL.y][headPosPL.x] = 0;
            curRoom[bodyPosPL.y][bodyPosPL.x] = 0;


            curRoom[headPosPL.y - i + 1][headPosPL.x] = 1; // Set the head
            curRoom[bodyPosPL.y - i + 1][bodyPosPL.x] = 2; // Set the body
            break;
        }

        if(i == jumpHeight)
        {
            curRoom[headPosPL.y][headPosPL.x] = 0;
            curRoom[bodyPosPL.y][bodyPosPL.x] = 0;


            curRoom[headPosPL.y - jumpHeight][headPosPL.x] = 1; // Set the head
            curRoom[bodyPosPL.y - jumpHeight][bodyPosPL.x] = 2; // Set the body
        }
    }
}

void findPlayerPos()
{
    for(int y = 0; y < roomData[roomLevel][1]; y++)
    {
        for(int x = 0; x < roomData[roomLevel][0]; x++)
        {
            if(curRoom[y][x] == 1)
            {
                headPosPL.x = x;
                headPosPL.y = y;
                bodyPosPL.x = x;
                bodyPosPL.y = y + 1;
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
    findPlayerPos();


    if(curRoom[bodyPosPL.y+1][bodyPosPL.x] == 0)
    {
        curRoom[bodyPosPL.y][bodyPosPL.x] = 0;
        curRoom[headPosPL.y][headPosPL.x] = 0;

        curRoom[headPosPL.y + 1][headPosPL.x] = 1;
        curRoom[bodyPosPL.y + 1][bodyPosPL.x] = 2;
        drawScreen();
        waitDelay(moveSpeed);
    }
}


