/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Nibbler
*/

#include <time.h>
#include <math.h>
#include "Nibbler.hpp"

arcade::Nibbler::Nibbler()
    : timer(steady_clock::now())
{
    status = arcade::statusGame::INGAME;
    srand(time(0));
    score = 0;
    fruits.push_back("./assets/ball2.png");
    fruits.push_back("./assets/ball3.png");
    fruits.push_back("./assets/ball4.png");
    fruits.push_back("./assets/ball5.png");
    fruits.push_back("./assets/ball6.png");
}

arcade::Nibbler::~Nibbler()
{
}

vector<display_t> &arcade::Nibbler::getInitState()
{
    float ya(0), ab(0), s(0.50), fruitX(rand() % 90), fruitY(rand() % 90);

    if (initedMap.empty()) {
        initedMap.push_back(initNode("./assets/grass.jpg", "X", 0.00, 0.00));
        for (float x = 0.00; x < 0.99; x += 0.01)
            initedMap.push_back(initNode("", "X", x, 0.00));
        for (ya = 0.03; ya < 0.99; ya += 0.01) {
            initedMap.push_back(initNode("", "X", 0.00, ya));
            for (ab = 0.02; ab < 0.99; ab += 0.01)
                initedMap.push_back(initNode("", " ", ab, ya));
            initedMap.push_back(initNode("", "X", ab - 0.01, ya));
        }
        for (float x = 0.02; x < 0.99; x += 0.01)
            initedMap.push_back(initNode("", "X", x, ya-0.02));
        initedMap.push_back(initNode("./assets/bushes.png", "X", 0., 0.));
        fruit = initNode(fruits[rand() % fruits.size()], "@", fruitX / 100 + 0.035, fruitY / 100 + 0.035);//fruit
        map = initedMap;
        for (int a = 0; a < 4; a++) {
            display_t tmp = initNode(fruits[rand() % fruits.size()], "o", (s += 0.01), 0.50);//body
            initedMap.push_back(tmp);
            initedSnake.push_back(tmp);
        }
        initedSnake.begin()->ascii = "<";
        initedSnake.begin()->image = "./assets/pikachu_left.png";
        snake = initedSnake;
    }
    return initedMap;
}

vector<display_t> &arcade::Nibbler::getState()
{
    returnMap = map;
    for (list<display_t>::iterator it = snake.begin(); it != snake.end(); ++it)
        returnMap.push_back(*it);
    returnMap.push_back(fruit);
    return returnMap;
}

display_t arcade::Nibbler::initNode(string path, string ascii, float x, float y)
{
    display_t newNode;

    newNode.background = "";
    newNode.foreground = "";
    newNode.image = path;
    newNode.ascii = ascii;
    newNode.x = x;
    newNode.y = y;
    newNode.isPrint = true;
    return newNode;
}

uint64_t arcade::Nibbler::getScore()
{
    return score;
}

void arcade::Nibbler::changePos(float x, float y)
{
    list<display_t>::iterator head = snake.begin();
    float tmpX, tmpY, stockX, stockY;

    tmpX = head->x;
    tmpY = head->y;
    head->x += x;
    head->y += y;
    for (list<display_t>::iterator it = ++head; it != snake.end(); ++it) {
        stockX = tmpX;
        stockY = tmpY;
        tmpX = it->x;
        tmpY = it->y;
        it->x = stockX;
        it->y = stockY;
    }
}

bool arcade::Nibbler::floatTolerance(float a, float b, float ecart)
{
    return (fabs(a - b) < ecart);
}

void arcade::Nibbler::selfCol()
{
    list<display_t>::iterator head = snake.begin();

    ++head;
    for (list<display_t>::iterator it = head; it != snake.end(); ++it)
        if (floatTolerance(snake.begin()->x, it->x, 0.001) && floatTolerance(it->y, snake.begin()->y, 0.001)) {
            status = LOSE;
            break;
        }
}

void arcade::Nibbler::move(char dir)
{
    static int direction = 4;
    float fruitX = rand() % 90;
    float fruitY = rand() % 90;
    bool autoIa = false;

    if (dir == 10 && autoIa == false)
        autoIa = true;
    if (autoIa == false) {
        if (dir == 122 && direction != 1 && direction != 3)
            direction = 1;
        if (dir == 115 && direction != 3 && direction != 1)
            direction = 3;
        if (dir == 113 && direction != 4 && direction != 2)
            direction = 4;
        if (dir == 100 && direction != 2 && direction != 4)
            direction = 2;
    } else {
        if (!floatTolerance(fruit.x, snake.begin()->x,0.01)) {
            if ((fruit.x - snake.begin()->x) > 0 && direction == 4)
                direction = 3;
            else if ((fruit.x - snake.begin()->x) < 0 && direction == 2)
                direction = 1;
            else if ((fruit.x - snake.begin()->x) > 0 && direction != 4)
                direction = 2;
            else if ((fruit.x - snake.begin()->x) < 0 && direction != 2)
                direction = 4;
        } else if (!floatTolerance(fruit.y, snake.begin()->y, 0.02)) {
            if ((fruit.y - snake.begin()->y) > 0 && direction == 1)
                direction = 2;
            else if ((fruit.y - snake.begin()->y) < 0 && direction == 3)
                direction = 4;
            else if ((fruit.y - snake.begin()->y) > 0 && direction != 1)
                direction = 3;
            else if ((fruit.y - snake.begin()->y) < 0 && direction != 3)
                direction = 1;
        }
    }
    if (direction == 1) {
        changePos(0.00, -0.03);
        snake.begin()->ascii = "^";
        snake.begin()->image = "./assets/pikachu_up.png";
    }
    if (direction == 2) {
        changePos(0.02, 0.00);
        snake.begin()->ascii = ">";
        snake.begin()->image = "./assets/pikachu_right.png";
    }
    if (direction == 3) {
        changePos(0.00, 0.03);
        snake.begin()->ascii = "v";
        snake.begin()->image = "./assets/pikachu_down.png";
    }
    if (direction == 4) {
        changePos(-0.02, 0.00);
        snake.begin()->ascii = "<";
        snake.begin()->image = "./assets/pikachu_left.png";
    }
    if (floatTolerance(fruit.x, (snake.begin())->x) && floatTolerance(fruit.y, (snake.begin())->y, 0.015f)) {
        score += 100;
        fruit.x = fruitX / 100 + 0.035;
        fruit.y = fruitY / 100 + 0.035;
        snake.push_back(initNode(fruit.image, "o", (snake.end())->x, (snake.end())->y));
        fruit.image = fruits[rand() % fruits.size()];
    }
    if ((snake.begin())->x < 0.01 || (snake.begin())->x > 0.99 || (snake.begin())->y < 0.01 || (snake.begin())->y > 0.99)
        status = arcade::statusGame::LOSE;
    if (autoIa == false)
        selfCol();
}

arcade::statusGame &arcade::Nibbler::getStatus()
{
    return status;
}

void arcade::Nibbler::restart()
{
    initedMap.clear();
    initedSnake.clear();
    getInitState();
}

bool arcade::Nibbler::speedGame()
{
    duration<double> time_span = duration_cast<duration<double>>(steady_clock::now() - timer);
    
    if (time_span.count() >= 0.08) {
        timer = steady_clock::now();
        return true;
    }
    return false;
}

extern "C" arcade::IGame *create()
{
    return new arcade::Nibbler();
}