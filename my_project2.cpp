#include <iostream>
#include <conio.h>
#include <graphics.h>
#include <dos.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

class SnakeGame {
private:
    int headX, headY, eggX, eggY, eggColor, eggGenFlag, prevDir, currDir, length, color, step, delayTime, maxX, maxY;
    long score;
    int startX, startY, endX, endY;
    int position[100][2];

    void checkEggCollision();
    void generateEgg();
    void updateScore();
    void handleCollision();
    void changeDirection();
    void generateConditionalMovement();
    void generateUnconditionalMovement();
    void checkBounds();
    void showSnake();
    void moveSnake();
    void playEatSound();
    void playCaughtSound();
    int isEggPositionValid();

public:
    SnakeGame();
    ~SnakeGame();
    void initialize();
    void start();
};

SnakeGame::SnakeGame() {}
SnakeGame::~SnakeGame() {}

void SnakeGame::checkEggCollision() {
    if ((eggX == headX) && (eggY == headY)) {
        playEatSound();
        generateEgg();
        delayTime--;
        updateScore();
        length++;
    }
}

void SnakeGame::playEatSound() {
    nosound();
    sound(2500);
    delay(2);
    nosound();
}

void SnakeGame::playCaughtSound() {
    nosound();
    for (int i = 1000; i > 0; i--) {
        sound(i);
        delay(1);
    }
    nosound();
}

void SnakeGame::updateScore() {
    char scoreStr[10];
    ltoa(score, scoreStr, 10);
    settextstyle(8, 0, 1);
    setcolor(0);
    outtextxy(585, 40, scoreStr);

    if (eggGenFlag != 1) {
        score = score + delayTime / 10;
    }

    ltoa(score, scoreStr, 10);
    setcolor(10);
    outtextxy(585, 40, scoreStr);
}

void SnakeGame::generateConditionalMovement() {
    if (length < 367) {
        if (currDir == 8 && (prevDir != 8 && prevDir != 2)) {
            position[0][0] = headX;
            position[0][1] = headY - step;
            prevDir = currDir;
        }
        if (currDir == 4 && (prevDir != 4 && prevDir != 1)) {
            position[0][0] = headX + step;
            position[0][1] = headY;
            prevDir = currDir;
        }
        if (currDir == 2 && (prevDir != 8 && prevDir != 2)) {
            position[0][0] = headX;
            position[0][1] = headY + step;
            prevDir = currDir;
        }
        if (currDir == 1 && (prevDir != 1 && prevDir != 4)) {
            position[0][0] = headX - step;
            position[0][1] = headY;
            prevDir = currDir;
        }
    }
}

void SnakeGame::generateUnconditionalMovement() {
    if (prevDir == 8) {
        position[0][0] = headX;
        position[0][1] = headY - step;
    }
    if (prevDir == 4) {
        position[0][0] = headX + step;
        position[0][1] = headY;
    }
    if (prevDir == 2) {
        position[0][0] = headX;
        position[0][1] = headY + step;
    }
    if (prevDir == 1) {
        position[0][0] = headX - step;
    }

    headX = position[0][0];
    headY = position[0][1];
}

void SnakeGame::checkBounds() {
    if (headX > endX) {
        headX = startX;
    } else if (headX < startX) {
        headX = endX;
    }

    if (headY > endY) {
        headY = startY;
    } else if (headY < startY) {
        headY = endY;
    }

    position[0][0] = headX;
    position[0][1] = headY;

    for (int i = 1; i < length; i++) {
        if (headX == position[i][0] && headY == position[i][1]) {
            handleCollision();
            break;
        }
    }
}

void SnakeGame::showSnake() {
    int currColor = getcolor();

    if (eggGenFlag != 1) {
        setcolor(getbkcolor());
        setfillstyle(1, getbkcolor());
        fillellipse(eggX, eggY, maxY, maxY);
    } else {
        eggGenFlag = 0;
    }

    if (eggGenFlag == 2) {
        eggGenFlag--;
    }

    setcolor(color);
    setfillstyle(1, 9);

    if (currDir == 8 || currDir == 2) {
        fillellipse(position[0][0], position[0][1], maxX, maxY);
    } else if (currDir == 4 || currDir == 1) {
        fillellipse(position[0][0], position[0][1], maxY, maxX);
    }

    setcolor(currColor);
}

void SnakeGame::moveSnake() {
    int paused = 0;
    do {
        if (!kbhit()) {
            checkEggCollision();
            if (!paused) {
                showSnake();
            } else {
                paused = 0;
            }

            delay(delayTime / 4);
            generateUnconditionalMovement();
            delay(delayTime / 4);
            checkBounds();
            delay(delayTime / 4);
        } else if (step) {
            changeDirection();
            generateConditionalMovement();
            checkBounds();
            showSnake();
            paused = 1;
        }
    } while (step);
}

void SnakeGame::initialize() {
    srand(time(NULL));
    step = 20;
    length = 5;
    prevDir = 4;

    for (int i = 4; i >= 0; i--) {
        position[i][0] = 201 + (length - i - 1) * step;
        position[i][1] = 301;
    }

    startX = 21;
    startY = 21;
    endX = 481;
    endY = 361;
    color = 14;
    currDir = prevDir;
    step = 20;
    step = 111;
    delayTime = 150;
    maxX = 3;
    maxY = 9;
    generateEgg();
    eggGenFlag = 1;
    updateScore();

    int currColor = getcolor();
    setlinestyle(0, 1, 3);
    setcolor(15);
    rectangle(startX - 15, startY - 15, endX + 15, endY + 15);
    rectangle(endX + 25, startY - 15, getmaxx() - 15, endY + 15);
    rectangle(startX - 15, endY + 25, getmaxx() - 15, getmaxy() - 5);
    line(endX + 25, startY + 75, getmaxx() - 15, startY + 75);
    line(endX + 25, startY + 200, getmaxx() - 15, startY + 200);
    line(endX + 25, startY + 275, getmaxx() - 15, startY + 275);

    setlinestyle(0, 1, 1);
    settextstyle(8, 0, 1);
    setcolor(14);
    outtextxy(500, 40, "SCORE");
    outtextxy(520, 90, "EGG");
    outtextxy(520, 125, "CONTROLS");
    outtextxy(522, 155, "p = PAUSE");
    outtextxy(522, 175, "g = RESUME");
    outtextxy(522, 195, "e = EXIT");
    outtextxy(513, 215, "ARROWS");
    outtextxy(512, 235, "    -MOVEMENT");

    setcolor(14);
    settextstyle(4, 0, 9);
    outtextxy(getmaxx() - 500, getmaxy() - 110, "SNAKE");
    settextstyle(8, 0, 1);
    setcolor(currColor);
}

void SnakeGame::handleCollision() {
    step = 0;
    playCaughtSound();

    for (int i = 0; i <= 7; i++) {
        if (i % 2) {
            setcolor(10);
            outtextxy(512, 250, "GAME OVER");
            delay(900);
        } else {
            setcolor(0);
            outtextxy(512, 250, "GAME OVER");
            delay(500);
        }
    }

    sleep(1);
}

void SnakeGame::changeDirection() {
    char key = getch();

    if (key == 72) currDir = 8;
    else if (key == 77) currDir = 4;
    else if (key == 80) currDir = 2;
    else if (key == 75) currDir = 1;
    else if (key == 'e') handleCollision();
    else if (key == 'p') {
        int blink = 1;
        settextstyle(11, 0, 9);

        while (1) {
            if (kbhit()) {
                int c = getch();
                if (c == 'g') {
                    int currColor = getcolor();
                    setcolor(0);
                    rectangle(endX + 40, endY - 10, getmaxx() - 35, getmaxy() - 160);
                    outtextxy(endX + 60, endY - 29, "PAUSE");
                    break;
                }
            } else {
                if (blink % 2) {
                    int currColor = getcolor();
                    setcolor(10);
                    rectangle(endX + 40, endY - 10, getmaxx() - 35, getmaxy() - 160);
                    outtextxy(endX + 60, endY - 29, "PAUSE");
                    setcolor(currColor);
                    delay(1000);
                } else {
                    int currColor = getcolor();
                    setcolor(0);
                    rectangle(endX + 40, endY - 10, getmaxx() - 35, getmaxy() - 160);
                    outtextxy(endX + 60, endY - 29, "PAUSE");
                    delay(1000);
                }
            }
            blink++;
        }
        settextstyle(8, 0, 1);
    }
}

void SnakeGame::generateEgg() {
    do {
        eggX = (rand() % 100) * step + startX;
        eggY = (rand() % 100) * step + startY;
    } while (isEggPositionValid());

    int currColor = getcolor();
    setcolor(7);
    setfillstyle(1, random(15) + 1);
    fillellipse(eggX, eggY, maxX + 2, maxX + 2);
    setcolor(currColor);
    eggGenFlag = 2;
}

int SnakeGame::isEggPositionValid() {
    for (int i = 0; i < length; i++) {
        if (eggX == position[i][0] && eggY == position[i][1])
            break;
        if (eggX >= endX + 1 || eggY >= endY + 1)
            break;
    }

    return (i != length);
}

void SnakeGame::start() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");
    initialize();
    moveSnake();
    closegraph();
}

int main() {
    SnakeGame game;
    game.start();
    return 0;
}
