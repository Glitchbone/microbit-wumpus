#include "MicroBit.h"

MicroBit uBit;

int currentRoom = 0;
int currentDirection = 0;

int cave[][3] = {
    {1, 7, 4},
    {2, 9, 0},
    {3, 11, 1},
    {4, 13, 2},
    {0, 5, 3},
    {6, 4, 14},
    {7, 16, 5},
    {8, 0, 6},
    {9, 17, 7},
    {10, 1, 8},
    {11, 18, 9},
    {12, 2, 10},
    {13, 19, 11},
    {14, 3, 12},
    {5, 15, 13},
    {16, 14, 19},
    {17, 6, 15},
    {18, 8, 16},
    {19, 10, 17},
    {15, 12, 18}
};

MicroBitImage walls("1 1 1 1 1\n0 0 0 0 0\n0 0 0 0 0\n0 0 0 0 0\n1 0 0 0 1\n");

const char wallsSprites[][51] = {
    {"1 0 0 0 1\n0 0 0 0 0\n0 0 0 0 0\n0 0 0 0 0\n1 1 1 1 1\n"}, // Top exit
    {"1 1 1 1 1\n0 0 0 0 0\n0 0 0 0 0\n0 0 0 0 0\n1 0 0 0 1\n"} // Bottom exit
};

const char playerSprites[][37] = {
    {"0 16 0\n16 0 0\n0 16 0\n"}, // Left
    {"0 16 0\n16 0 16\n0 0 0\n"}, // Top
    {"0 16 0\n0 0 16\n0 16 0\n"}, // Right
    {"0 0 0\n16 0 16\n0 16 0\n"} // Bottom
};

void drawWalls()
{
    int spriteIndex = currentRoom < cave[currentRoom][1] ? 0 : 1;
    MicroBitImage image(wallsSprites[spriteIndex]);
    uBit.display.image.paste(image, 0, 0);
}

void drawPlayer()
{
    int spriteIndex = currentDirection;

    if (currentDirection == 1) {
        spriteIndex = currentRoom < cave[currentRoom][1] ? 1 : 3;
    }

    MicroBitImage image(playerSprites[spriteIndex]);
    uBit.display.image.paste(image, 1, 1);
}

void drawRoom()
{
    uBit.display.clear();
    drawWalls();
    drawPlayer();
}

void changeDirection()
{
    currentDirection = currentDirection == 2 ? 0 : currentDirection + 1;
    drawRoom();
}

void changeRoom(int room)
{
    //currentDirection = 0;
    currentRoom = room;
    //uBit.display.scroll(room + 1, 50);
    drawRoom();
}

void onButton(MicroBitEvent e)
{
    if (e.source == MICROBIT_ID_BUTTON_A) {
        changeDirection();
    }

    if (e.source == MICROBIT_ID_BUTTON_B) {
        changeRoom(cave[currentRoom][currentDirection]);
    }
}

int main()
{
    uBit.init();
    uBit.display.setDisplayMode(DISPLAY_MODE_GREYSCALE);

    uBit.messageBus.listen(MICROBIT_ID_BUTTON_A, MICROBIT_BUTTON_EVT_CLICK, onButton);
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_B, MICROBIT_BUTTON_EVT_CLICK, onButton);

    changeRoom(0);
    
    release_fiber();
}

