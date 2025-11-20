#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<windows.h>
#include<conio.h>
#include<time.h>

/*
    A game about a parkour guy who runs around the map and gets to a orange square
*/

// roomLayouts
// This is a global variable that needs to exist because this will tell all the other functions what room level we are on
int roomLevel = 0;


struct roomData {
    int roomX;
    int roomY;
    int roomTime;
    int attempts;
};

struct roomData room[10] =
{
    // Room 0
    {11, 10, 30, 5},
    // Room 1
    {17, 10, 30, 5},
    // Room 2
    {17, 20, 30, 5}
};

/*                  Room Height || Room Length ||  Room Time    || Attempt Times
    Room Level 0:     20 Units      30 Units       30 Seconds           3 Times


*/


// Container of all the roomLayouts we're in
const int roomLayouts[3][100][100] = {
    {
        // Room 0
        {5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5},
        {5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5},
        {5, 3, 4, 0, 0, 0, 0, 0, 0, 0, 5},
        {5, 3, 4, 0, 0, 0, 9, 10, 0, 0, 5},
        {5, 5, 5, 5, 5, 5, 5, 5, 5, 0, 5},
        {5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5},
        {5, 0, 0, 0, 0, 0, 0, 0, 0, 7, 5},
        {5, 8, 0, 1, 0, 0, 0, 0, 7, 5, 5},
        {5, 5, 8, 2, 11, 12, 0, 7, 5, 5, 5},
        {5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5},
    },
    {
        // Room 1
        {5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5},
        {5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5},
        {5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5},
        {5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5},
        {5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5},
        {5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5},
        {5, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5},
        {5, 1, 0, 7, 5, 0, 8, 0, 0, 0, 0, 0, 0, 0, 3, 4, 5},
        {5, 2, 7, 5, 5, 0, 5, 8, 0, 0, 0, 0, 0, 0, 3, 4, 5},
        {5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5},
    },
    {
        // Room 2
        {5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5},
        {5, 0, 0, 0, 0, 0, 0, 0, 3, 4, 5},
        {5, 0, 0, 0, 0, 0, 0, 0, 3, 4, 5},
        {5, 0, 5, 5, 5, 5, 5, 5, 5, 5, 5},
        {5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5},
        {5, 8, 0, 0, 0, 0, 0, 0, 0, 0, 5},
        {5, 5, 5, 5, 5, 5, 5, 5, 5, 0, 5},
        {5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5},
        {5, 0, 0, 0, 0, 0, 0, 0, 0, 7, 5},
        {5, 0, 0, 0, 0, 0, 0, 0, 7, 5, 5},
        {5, 0, 5, 5, 5, 0, 5, 5, 5, 5, 5},
        {5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5},
        {5, 8, 0, 0, 0, 0, 0, 0, 0, 0, 5},
        {5, 5, 8, 0, 0, 0, 0, 0, 0, 0, 5},
        {5, 5, 5, 5, 0, 5, 5, 0, 5, 0, 5},
        {5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5},
        {5, 0, 0, 0, 0, 0, 0, 0, 0, 7, 5},
        {5, 0, 1, 0, 0, 0, 0, 0, 7, 5, 5},
        {5, 0, 2, 0, 0, 9, 0, 7, 5, 5, 5},
        {5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5},
    }
};

// This variable is for handling the current room we have, basically we just make this room equal to all the values in the room we're currently at
int curRoom[100][100];

// Function prototypes declaration
void update();
void start();
void initialize();

// UI
void startScreen();
void drawGameOver();


// Functions for displaying the screen
void drawScreen();
void printCell(int);
void clearScreen();
void setPlayerBackground();

// Function responsible for the roomLayouts
void setRoom(int);

// Functions responsible for input
void getInput();

// Function for moving the player
void findPlayerPos(); // Finds the location of the players head
void movePlayer(char inputData[],int inputLength);
void moveX(int);
void moveRight();
void jump(bool);
void gravCheck();
void changePlayerPos(int);
int convertToNum(char);
const int jumpHeight = 2;

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
void gameOver();
void winCheck();

// A set of colors, 16 bit color palatte
// Standard colors
#define BLACK         "\033[30m"
#define RED           "\033[31m"
#define GREEN         "\033[32m"
#define YELLOW        "\033[33m"
#define BLUE          "\033[34m"
#define MAGENTA       "\033[35m"
#define CYAN          "\033[36m"
#define WHITE         "\033[37m"

// Bright colors
#define GRAY           "\033[90m"
#define BRIGHT_RED     "\033[91m"
#define BRIGHT_GREEN   "\033[92m"
#define BEIGE  "\033[93m"
#define BRIGHT_BLUE    "\033[94m"
#define BRIGHT_MAGENTA "\033[95m"
#define BRIGHT_CYAN    "\033[96m"
#define BRIGHT_WHITE   "\033[97m"

#define RESET         "\033[0m"






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
    // Start at a set room
    startScreen();

    // Start from the beginning room

    //setRoom(0);
}

void startScreen()
{
    printf("******************************************************\n");
    Sleep(100);
    printf("*                                                    *\n");
    Sleep(100);
    printf("*              P R E M O V E   P A U L               *\n");
    Sleep(100);
    printf("*                                                    *\n");
    Sleep(100);    printf("*                                                    *\n");
    Sleep(100);
    printf("*               This shit is so ass T-T              *\n");
    Sleep(100);
    printf("*                                                    *\n");
    Sleep(100);
    printf("*                 PRESS ANY BUTTON                   *\n");
    Sleep(100);
    printf("******************************************************\n");

    while(!_kbhit());
    getch();
    system("cls");
}

void drawGameOver()
{
    system("cls");
    printf("******************************************************\n");
    Sleep(100);
    printf("*                                                    *\n");
    Sleep(100);
    printf("*                   GIT GUD SCRUB                    *\n");
    Sleep(100);
    printf("*                     (##)                           *\n");
    Sleep(100);
    printf("*                     |()|                           *\n");
    Sleep(100);    printf("*                    _|()|_ _                        *\n");
    Sleep(100);
    printf("*                   (()()()())                       *\n");
    Sleep(100);
    printf("*                   (        |                       *\n");
    Sleep(100);
    printf("*                   (        |                       *\n");
    Sleep(100);
    printf("*                    \\      /                        *\n");
    Sleep(100);
    printf("*                     |     |                        *\n");
    Sleep(100);
    printf("******************************************************\n");
    Sleep(100);

    while(!_kbhit());
    getch();
}

// Beginning of the game function
void start()
{
    attemptTimes = room[roomLevel].attempts;
    setRoom(roomLevel);
    drawScreen();
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
        } else
        {
            gameOn = false;
            break;
        }

    }

    // Checks if the game should still run
    if(gameOn) update();

    gameOver();


    return;
}

void gameOver()
{
    drawGameOver();
}


void drawScreen()
{
    clearScreen();
    // Responsible for drawing the entire room
    for(int y = 0; y < room[roomLevel].roomY; y++)
    {
        for(int x = 0; x < room[roomLevel].roomX; x++)
        {
            // Send the value of the current room to the printCell function
            printCell(curRoom[y][x]);
            if(x == room[roomLevel].roomX - 1) printf(" > %d",  room[roomLevel].roomY - y);
        }
        printf("\n");
    }

    int currentCharacter = 'A';

    for(int i = 0; i < 2; i++)
    {
        for(int y = 0; y < room[roomLevel].roomY + 1; y++)
        {
                if (i == 0)
                {
                    printf("v ");
                } else
                {
                    printf("%c ", (char)currentCharacter);
                    currentCharacter++;
                }
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
        case 1: printf(BEIGE"()"); break;    // Player head
        case 2: printf(RED"||"); break;    // Player body
        case 3: printf("|-"); break;    // Door left side
        case 4: printf("-|"); break;    // Door Right side
        case 5: printf(WHITE"[]"); break;    // Normal block
        case 6: printf("/\\"); break;   // Spike
        case 7: printf("/T"); break;    // Right side staircase
        case 8: printf("T\\"); break;    // Left side staircase
        case 9: printf("[-"); break;    // Left side Couch
        case 10: printf("-]"); break;    // Left side Couch
        case 11: printf("[="); break;    // Upside Lamp
        case 12: printf("=]"); break;    // Downside Lamp
        default: printf("er"); break;   // Error case
    }

    printf(RESET);
}


void setRoom(int desiredRoom)
{
    // Sets the current room equal to the room we want to be, this is so that we're working with a copy of the room rather than the original room itself
    for(int y = 0; y < 100; y++)
    {
        for(int x = 0; x < 100; x++)
        {
            curRoom[y][x] = roomLayouts[desiredRoom][y][x];
        }
    }
}

void getInput()
{
    char inputData[100] = "";

    printf("\nYou have %d attempts left", attemptTimes);
    printf("\nControls are: \n    D/d - Right\n    A/a - Left\n    W/w - Jump\n    F/f - Wait\nInput: ");

    // Because we are using sounds and such, we cannot use scanf() because it is a blocking function
    // So we opt to recreate it's functionality using conio.h


    // Initially clear the input buffer
    while(_kbhit())
    {
        getch();
    }

    int inpIndex = 0;

    while(1)
    {
        // Handles time functionality even while getting input, this is so stuff doesn't pause even if we're inputting inputs
        timeHandler();

        // kbhit() detects if there is an input in the input buffer
        if(_kbhit())
        {
            // Will get the current character and place it on the screen
            char c = getch();

            // All printable readable characters in ascii are from 36 - 126
            if(((int)c >= 36 && (int)c <= 126) || c == ' ')
            {
                // We use our index to keep track of where we are on the Input array
                inputData[inpIndex] = c;
                printf("%c", c);
                // We increase our index by 1
                inpIndex++;
            } else if((int)c == 8 && inpIndex > 0)
            {
                // 8 is the ASCII value of backspace
                inputData[inpIndex] = ' ';
                printf("\b \b");
                inpIndex--;
            } else if((int)c == 13)
            {
                // 13 is the ASCII value of
                printf("hello");
                break;
            }
        }

    }


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



        // Determine how the said data will be used, we can use a switch statement here

        bool withinNumRange = ((int)inputData[i+1] >= 48) && ((int)inputData[i+1] <= 57);

        if((i == inputLength - 1 && !withinNumRange) || !withinNumRange || inputLength == 1)
        {
            // When player uses the character only input style
            changePlayerPos(inputData[i]);
        } else
        {
            // When the player uses a line command

            // Read the values of the line
            // i + 1 is a the highest number
            int moveTimes = 0;
            int j = 0;

            // Converts the string of numbers into a integer
            while((int)inputData[i+1+j] >= 48 && (int)inputData[i+1+j] <= 57)
            {
                moveTimes *= 10;
                moveTimes += convertToNum(inputData[i+1]);
                j++;
            }

            // Does the movement n amount of times
            for(int c = 0; c < moveTimes; c++)
            {
                changePlayerPos(inputData[i]);
            }

            i += j;
        }
    }


    // We check if the player is grounded
    findPlayerPos();
    while(curRoom[bodyPosPL.y + 1][bodyPosPL.x] != 5 && curRoom[bodyPosPL.y+1][bodyPosPL.x] != 7 && curRoom[bodyPosPL.y+1][bodyPosPL.x] != 8)
    {
        gravCheck();
    }

    // After doing all those actions, we check if our current position is at the door
    winCheck();

}

void changePlayerPos(int value)
{
        findPlayerPos();
        bool canJump = curRoom[bodyPosPL.y + 1][bodyPosPL.x] != 0;
        bool jumped = false;

        switch(value)
        {
            case 'a':
            case 'A':
                Beep(1700, moveSpeed/3);
                moveX(-1);
                break;
            case 'd':
            case 'D':
                Beep(1450, moveSpeed/3);
                moveX(1);
                break;
            case 'w':
            case 'W':
                Beep(2000, moveSpeed/3);
                jump(canJump);
                jumped = true;
                break;
            case 'f':
            case 'F':
                printf("\nYou stopped moving");
                break;
            case ' ':
                return;
                break;
            default:
                Beep(1000, moveSpeed);
                printf("\nThat is not a valid movement option");
                break;
        }

        if(!jumped) gravCheck();
        drawScreen();
        waitDelay(moveSpeed);
}


int convertToNum(char value)
{

    int converted = 0;

    switch(value)
    {
        case '1': converted = 1; break;
        case '2': converted = 2; break;
        case '3': converted = 3; break;
        case '4': converted = 4; break;
        case '5': converted = 5; break;
        case '6': converted = 6; break;
        case '7': converted = 7; break;
        case '8': converted = 8; break;
        case '9': converted = 9; break;
        case '0': converted = 0; break;
    }

    return converted;



}



void moveX(int moveForce)
{
    // Move force is the direction we want to go in the x axis

    Vec2 blockPos = {bodyPosPL.x + moveForce, bodyPosPL.y};
    int blockVal = curRoom[blockPos.y][blockPos.x]; // This is the value of the the block

    // Staircase checking
    if(blockVal != 5 && blockVal != 8 && blockVal != 7)
    {
        // Check if it can move to the left, that means all things to the left are 0
        bool canMove = (curRoom[headPosPL.y][headPosPL.x + moveForce] != 5) && (curRoom[bodyPosPL.y][bodyPosPL.x + moveForce] != 5);
        if(!canMove) return;

        curRoom[headPosPL.y][headPosPL.x + moveForce] = 1;
        curRoom[bodyPosPL.y][bodyPosPL.x + moveForce] = 2;

        curRoom[headPosPL.y][headPosPL.x] = roomLayouts[roomLevel][headPosPL.y][headPosPL.x];
        curRoom[bodyPosPL.y][bodyPosPL.x] = roomLayouts[roomLevel][bodyPosPL.y][bodyPosPL.x];


        // Draws the background objects of the player
        setPlayerBackground();

    } else if (blockVal == 8 || blockVal == 7)
    {
        // This happens when we are about to hit a stair case

        // Check if the 2 blocks above the staircase are free
        bool canGetUp = (curRoom[blockPos.y - 1][blockPos.x] != 5 && curRoom[blockPos.y-2][blockPos.x] != 5);
        if(!canGetUp) return;

        curRoom[headPosPL.y - 1][headPosPL.x + moveForce] = 1;
        curRoom[bodyPosPL.y - 1][bodyPosPL.x + moveForce] = 2;

        switch(roomLayouts[roomLevel][headPosPL.y][headPosPL.x])
        {
            case 1:
                curRoom[headPosPL.y][headPosPL.x] = 0;
                break;
            default:
                curRoom[headPosPL.y][headPosPL.x] = roomLayouts[roomLevel][headPosPL.y][headPosPL.x];
        }

        switch(roomLayouts[roomLevel][bodyPosPL.y][bodyPosPL.x])
        {
            case 2:
                curRoom[bodyPosPL.y][bodyPosPL.x] = 0;
                break;
            default:
                curRoom[bodyPosPL.y][bodyPosPL.x] = roomLayouts[roomLevel][bodyPosPL.y][bodyPosPL.x];
        }
    }
}

void jump(bool canJump)
{



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
            setPlayerBackground();


            curRoom[headPosPL.y - i + 1][headPosPL.x] = 1; // Set the head
            curRoom[bodyPosPL.y - i + 1][bodyPosPL.x] = 2; // Set the body
            break;
        }

        if(i == jumpHeight)
        {
            setPlayerBackground();


            curRoom[headPosPL.y - jumpHeight][headPosPL.x] = 1; // Set the head
            curRoom[bodyPosPL.y - jumpHeight][bodyPosPL.x] = 2; // Set the body
        }
    }
}

void findPlayerPos()
{
    for(int y = 0; y < room[roomLevel].roomY; y++)
    {
        for(int x = 0; x < room[roomLevel].roomX; x++)
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


    if(curRoom[bodyPosPL.y+1][bodyPosPL.x] != 5 && curRoom[bodyPosPL.y+1][bodyPosPL.x] != 7 && curRoom[bodyPosPL.y+1][bodyPosPL.x] != 8)
    {
        Beep(1000, moveSpeed/4);
        setPlayerBackground();

        curRoom[headPosPL.y + 1][headPosPL.x] = 1;
        curRoom[bodyPosPL.y + 1][bodyPosPL.x] = 2;
        drawScreen();
        waitDelay(moveSpeed);
    }
}

void setPlayerBackground()
{
        // We use 2 separate switch statements because we check behind the head and we check behind the body
        switch(roomLayouts[roomLevel][headPosPL.y][headPosPL.x])
        {
            case 1:
            case 2:
                curRoom[headPosPL.y][headPosPL.x] = 0;
                break;
            default:
                curRoom[headPosPL.y][headPosPL.x] = roomLayouts[roomLevel][headPosPL.y][headPosPL.x];
        }

        switch(roomLayouts[roomLevel][bodyPosPL.y][bodyPosPL.x])
        {
            case 1:
            case 2:
                curRoom[bodyPosPL.y][bodyPosPL.x] = 0;
                break;
            default:
                curRoom[bodyPosPL.y][bodyPosPL.x] = roomLayouts[roomLevel][bodyPosPL.y][bodyPosPL.x];
        }
}

void winCheck()
{
    // This function is called when alll the input actions have been completed, this checks if the player is currently at a door
    findPlayerPos();

    int hdX = headPosPL.x, hdY = headPosPL.y, bdX = bodyPosPL.x, bdY = bodyPosPL.y;

    if(roomLayouts[roomLevel][hdY][hdX] == 4 || roomLayouts[roomLevel][hdY][hdX] == 3)
    {
        printf("\nYou win!!!");
        Beep(2000, 1000);

        roomLevel++;
        start();
    } else
    {
        attemptTimes--;
    }

}
