/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** solarFox
*/

#ifndef SOLARFOX_HPP_
#define SOLARFOX_HPP_

#include "IGraphics.hpp"
#include <map>
#include <chrono>

using namespace std::chrono;

namespace arcade
{
enum Direction
{
    dirUp = '1',
    dirDown = '2',
    dirLeft = '3',
    dirRight = '4',
};
typedef struct Coordinates
{
    float x;
    float y;
} coord_t;

class object
{
public:
    object(float x, float y);
    object();
    ~object();
    bool isColiding(object &Object);
    coord_t getPosition();
    void setPosition(coord_t pos);
    void setPositionX(float);
    void setPositionY(float);
    void setSpeed();
    float getSpeed();

private:
    coord_t position;
};
class Projectile : public object
{

public:
    float getPrevPos(char);
    void movePX(float speed);
    void movePY(float speed);
    Projectile(float, float);
    ~Projectile();

private:
    float prev_x;
    float prev_y;
};

class Player : public object
{
public:
    void shoot();
    Player();
    ~Player();
    std::vector<Projectile> &getProjectile();

private:
    std::vector<Projectile> projectile;
};

class Enemy : public object
{
public:
    void shootX();
    void shootY();
    Enemy(float x, float y);
    Enemy();
    ~Enemy();
    std::vector<Projectile> &getProjectile();

private:
    float prev_x;
    float prev_y;
    std::vector<Projectile> projectile;
};

class SolarFox : public IGame
{
public:
    const float MaxBound = 1;
    const float MinBound = 0;
    enum Commands
    {
        up = 122,
        down = 115,
        right = 113,
        left = 100,
        shoot = 200
    };
    enum Direction
    {
        dirUp = '1',
        dirDown = '2',
        dirLeft = '3',
        dirRight = '4',
    };
    SolarFox();
    ~SolarFox();
    void moveE1(arcade::Enemy);
    void printEnemy(std::vector<arcade::Enemy> en);
    //void moveE2(arcade::Enemy);
    size_t getEnd();
    void initMap();
    void update(float, float);
    std::vector<arcade::Enemy> &getEnemy();
    arcade::Enemy &getEnemy1(int);
    arcade::statusGame &getStatus();
    vector<display_t> &getInitState();
    vector<display_t> &getState();
    uint64_t getScore();
    display_t newElement(string path, string ascii, float x, float y);
    void updateE(float x, float y, int opt);
    void move(char);
    void printProjectile(std::vector<Projectile>);
    void printObject(std::vector<arcade::object> obj);
    void printPlayer(Player player);
    void restart();
    bool speedGame() final;

private:
    arcade::Player player;
    std::vector<arcade::Enemy> enemies;
    std::vector<arcade::object> bonus;
    std::vector<display_t> to_display;
    std::vector<display_t> defaultMap;
    int score;
    size_t end;
    steady_clock::time_point timer;

    arcade::statusGame status;
    bool pause;
};

} // namespace arcade

#endif /* !SOLARFOX_HPP_ */
