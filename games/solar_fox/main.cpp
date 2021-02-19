/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** solarFox
*/

#include <math.h>
#include "solarFox.hpp"

arcade::SolarFox::SolarFox()
{
    this->score = 0;
    this->status = arcade::statusGame::INGAME;
    this->player = Player();
    coord_t begin;
    begin.x = 0.50;
    begin.y = 0.50;
    player.setPosition(begin);
    this->bonus.push_back(object(0.31, 0.32));
    this->bonus.push_back(object(0.4, 0.42));
    this->bonus.push_back(object(0.61, 0.6));
    this->bonus.push_back(object(0.31, 0.5));
    this->bonus.push_back(object(0.41, 0.5));
    this->end = bonus.size();
    this->enemies.push_back(Enemy(0, 0.23));
    this->enemies.push_back(Enemy(0.23, 0));
}

arcade::object::object()
{
}

arcade::object::object(float x, float y)
{
    this->setPositionX(x);
    this->setPositionY(y);
}

arcade::object::~object()
{
}

arcade::SolarFox::~SolarFox()
{
}

arcade::Player::Player()
{
}

arcade::Player::~Player()
{
}

arcade::Enemy::Enemy(float x, float y)
{
    this->setPositionX(x);
    this->setPositionY(y);
}

arcade::Enemy::Enemy()
{
}

arcade::Enemy::~Enemy()
{
}

void arcade::SolarFox::initMap()
{
}

arcade::Projectile::Projectile(float x, float y)
{
    setPositionX(x);
    setPositionY(y);
}

arcade::Projectile::~Projectile()
{
}

void arcade::Projectile::movePX(float speed)
{
    prev_x = getPosition().x;
    prev_y = getPosition().y;
    setPositionX(getPosition().x + speed);
}

void arcade::Projectile::movePY(float speed)
{
    prev_x = getPosition().x;
    prev_y = getPosition().y;
    setPositionY(getPosition().y + speed);
}

bool arcade::SolarFox::speedGame()
{
    duration<double> time_span = duration_cast<duration<double>>(steady_clock::now() - timer);

    if (time_span.count() >= 0.08)
    {
        timer = steady_clock::now();
        return true;
    }
    return false;
}

std::vector<arcade::Projectile> &arcade::Player::getProjectile()
{
    return (projectile);
}

std::vector<arcade::Projectile> &arcade::Enemy::getProjectile()
{
    return (projectile);
}

size_t arcade::SolarFox::getEnd()
{
    return (this->end);
};

float arcade::Projectile::getPrevPos(char opt)
{
    if (opt == 'x')
        return (prev_x);
    if (opt == 'y')
        return (prev_y);
    return 0;
}

void arcade::object::setPositionX(float x)
{
    this->position.x = x;
}

void arcade::object::setPosition(coord_t pos)
{
    this->position = pos;
}

void arcade::object::setPositionY(float y)
{
    this->position.y = y;
}

arcade::Coordinates arcade::object::getPosition()
{
    return (position);
}

void arcade::Player::shoot()
{
}

void arcade::Enemy::shootX()
{
    projectile.push_back(Projectile(getPosition().x + 0.04, getPosition().y));
}

void arcade::Enemy::shootY()
{
    projectile.push_back(Projectile(getPosition().x, getPosition().y + 0.04));
}

void arcade::SolarFox::printProjectile(std::vector<Projectile> proj)
{
    for (size_t i = 0; i < proj.size(); i++)
    {
        to_display.push_back(newElement("", "*", proj[i].getPosition().x, proj[i].getPosition().y));
        to_display.push_back(newElement("", " ", proj[i].getPrevPos('x'), proj[i].getPrevPos('y')));
    }
}
void arcade::SolarFox::printObject(std::vector<arcade::object> proj)
{
    for (size_t i = 0; i < proj.size(); i++)
    {
        to_display.push_back(newElement("", "O", proj[i].getPosition().x, proj[i].getPosition().y));
    }
}

void arcade::SolarFox::printPlayer(Player player)
{
    to_display.push_back(newElement("", "P", player.getPosition().x, player.getPosition().y));
}

void arcade::SolarFox::printEnemy(std::vector<arcade::Enemy> en)
{
    for (size_t i = 0; i < en.size(); i++)
        to_display.push_back(newElement("", "E", en[i].getPosition().x, en[i].getPosition().y));
}
std::vector<arcade::Enemy> &arcade::SolarFox::getEnemy()
{
    return (enemies);
}

arcade::Enemy &arcade::SolarFox::getEnemy1(int i)
{
    if (i == 0)
        return getEnemy()[0];
    if (i == 1)
        return getEnemy()[1];
    return getEnemy()[0];
}

void arcade::SolarFox::move(char input)
{

    static bool first = false;
    static bool speed = false;
    static bool up = true;
    static bool up2 = false;
    const float upper_valuex = 0.84;
    const float lower_valuex = 0.12;
    const float upper_value = 0.22;
    const float lower_value = 0.84;
    static arcade::SolarFox::Direction currentDir;

    status = INGAME;
    if (getEnd() == 0)
    {
        status = WIN;
    }
    if (input == arcade::SolarFox::Commands::up && currentDir != arcade::SolarFox::dirDown && currentDir != arcade::SolarFox::dirUp)
        currentDir = arcade::SolarFox::dirUp;
    if (input == arcade::SolarFox::Commands::down && currentDir != arcade::SolarFox::dirUp && currentDir != arcade::SolarFox::dirDown)
        currentDir = arcade::SolarFox::dirDown;
    if (input == arcade::SolarFox::Commands::right && currentDir != arcade::SolarFox::dirLeft && currentDir != arcade::SolarFox::dirRight)
        currentDir = arcade::SolarFox::dirRight;
    if (input == arcade::SolarFox::Commands::left && currentDir != arcade::SolarFox::dirRight && currentDir != arcade::SolarFox::dirLeft)
        currentDir = arcade::SolarFox::dirLeft;
    if (input == currentDir)
        speed = true;
    else
        speed = false;

    if (speed == false)
    {
        if (currentDir == arcade::SolarFox::dirUp)
            update(player.getPosition().x, player.getPosition().y - 0.02);
        if (currentDir == arcade::SolarFox::dirDown)
            update(player.getPosition().x, player.getPosition().y + 0.02);
        if (currentDir == arcade::SolarFox::dirRight)
            update(player.getPosition().x - 0.012, player.getPosition().y);
        if (currentDir == arcade::SolarFox::dirLeft)
            update(player.getPosition().x + 0.012, player.getPosition().y);
    }

    if (speed == true)
    {
        if (currentDir == arcade::SolarFox::dirUp)
            update(player.getPosition().x, player.getPosition().y + 0.04);
        if (currentDir == arcade::SolarFox::dirDown)
            update(player.getPosition().x, player.getPosition().y - 0.04);
        if (currentDir == arcade::SolarFox::dirRight)
            update(player.getPosition().x - 0.012, player.getPosition().y);
        if (currentDir == arcade::SolarFox::dirLeft)
            update(player.getPosition().x + 0.012, player.getPosition().y);
    }

    //destroy out of window projectile for player
    for (size_t i = 0; i < player.getProjectile().size(); i++)
    {
        // player.getProjectile().move()
        if (player.getProjectile()[i].getPosition().x > MaxBound ||
            player.getProjectile()[i].getPosition().y > MaxBound ||
            player.getProjectile()[i].getPosition().x < MinBound ||
            player.getProjectile()[i].getPosition().y < MinBound)
        {
            player.getProjectile()[i].~Projectile();
        }
    }
    if (first == false)
    {
        enemies[0].shootX();
        enemies[1].shootY();
        first = true;
    }
    static int timer1 = 0;
    static int timer2 = 0;

    if (enemies[0].getProjectile()[timer1].getPosition().x > 0.50)
    {
        enemies[0].shootX();
        timer1++;
    }
    if (enemies[1].getProjectile()[timer2].getPosition().y > 0.20)
    {
        enemies[1].shootY();
        timer2++;
    }
    for (size_t i = 0; i < enemies[0].getProjectile().size(); i++)
    {
        enemies[0].getProjectile()[i].movePX(0.01);
        enemies[1].getProjectile()[i].movePY(0.01);
    }
    printProjectile(enemies[0].getProjectile());
    printProjectile(enemies[1].getProjectile());
    printObject(bonus);
    printPlayer(player);

    if (getEnemy1(0).getPosition().y < 0.82 && up == true)
    {
        updateE(getEnemy1(0).getPosition().x, getEnemy1(0).getPosition().y + 0.01, 0);
    }
    else if (fabs(getEnemy1(0).getPosition().y - lower_value) < fabs(getEnemy1(0).getPosition().y - upper_value))
    {
        up = false;
        updateE(getEnemy1(0).getPosition().x, getEnemy1(0).getPosition().y - 0.01, 0);
    }
    int a = rand() % 2;
    if (fabs(getEnemy1(0).getPosition().y - 0.53) <= 0.1 && a == 1)
        up = true;

    if (getEnemy1(1).getPosition().x < upper_valuex && up2 == true)
    {
        updateE(getEnemy1(1).getPosition().x + 0.01, getEnemy1(1).getPosition().y, 1);
    }
    else if (fabs(getEnemy1(1).getPosition().x - lower_valuex) < fabs(getEnemy1(1).getPosition().x - upper_valuex))
    {
        up2 = false;
        updateE(getEnemy1(1).getPosition().x - 0.01, getEnemy1(1).getPosition().y, 1);
    }
    if (fabs(getEnemy1(1).getPosition().x - 0.20) <= 0.1)
        up2 = true;
    if (fabs(getEnemy1(1).getPosition().x - 0.85) <= 0.1)
        updateE(getEnemy1(1).getPosition().x - 0.51, getEnemy1(1).getPosition().y, 1);
    printEnemy(getEnemy());

    if (player.getPosition().x >= 0.87 ||
        player.getPosition().y >= 0.84 ||
        player.getPosition().y <= 0.24 ||
        player.getPosition().x <= 0.11)
    {
        status = LOSE;
        // À ENLEVER IMPERATIVEMENT
    }
}

vector<display_t> &arcade::SolarFox::getInitState()
{
    float ya;
    float ab;

    if (defaultMap.empty())
    {
        for (float x = 0.09; x < 0.89; x += 0.012)
            defaultMap.push_back(newElement("", "X", x, 0.18));
        for (ya = 0.2; ya < 0.89; ya += 0.012)
        {
            defaultMap.push_back(newElement("", "X", 0.09, ya));
            for (ab = 0.1; ab < 0.89; ab += 0.012)
                defaultMap.push_back(newElement("", " ", ab, ya));
            defaultMap.push_back(newElement("", "X", ab - 0.012, ya));
        }
        for (float x = 0.1; x < 0.89; x += 0.012)
            defaultMap.push_back(newElement("", "X", x, ya - 0.02));
        to_display = defaultMap;
        to_display.push_back(newElement("", "P", player.getPosition().x, player.getPosition().y));
        for (size_t i = 0; i < bonus.size(); i++)
            to_display.push_back(newElement("", "O", bonus[i].getPosition().x, bonus[i].getPosition().y));
    }
    return to_display;
}
display_t arcade::SolarFox::newElement(string path, string ascii, float x, float y)
{
    display_t newElement;

    newElement.background = "";
    newElement.foreground = "";
    newElement.image = path;
    newElement.ascii = ascii;
    newElement.x = x;
    newElement.y = y;
    newElement.isPrint = true;
    return newElement;
}

void arcade::SolarFox::update(float x, float y)
{
    float prev_x = player.getPosition().x;
    float prev_y = player.getPosition().y;

    //bonus collision
    for (size_t i = 0; i < bonus.size(); i++)
    {
        if (fabs(x - bonus[i].getPosition().x) <= 0.019 && fabs(y - bonus[i].getPosition().y) <= 0.01)
        {
            score += 74.2;
            bonus[i].setPositionX(-1);
            bonus[i].setPositionY(-1);
            bonus[i].~object();
            end--;
        }
    }
    //missile collision
    for (size_t j = 0; j < enemies.size(); j++)
    {
        for (size_t i = 0; i < enemies[j].getProjectile().size(); i++)
        {
            if (fabs(x - enemies[j].getProjectile()[i].getPosition().x) <= 0.015 && fabs(y - enemies[j].getProjectile()[i].getPosition().y) <= 0.005)
            {
                status = LOSE;
            }
        }
    }

    player.setPositionX(x);
    player.setPositionY(y);
    to_display.push_back(newElement("", " ", prev_x, prev_y));
}

void arcade::SolarFox::updateE(float x, float y, int opt)
{
    float prev_x = getEnemy1(opt).getPosition().x;
    float prev_y = getEnemy1(opt).getPosition().y;
    getEnemy1(opt).setPositionX(x);
    getEnemy1(opt).setPositionY(y);
    printEnemy(getEnemy());
    to_display.push_back(newElement("", " ", prev_x, prev_y));
}

uint64_t arcade::SolarFox::getScore()
{
    return score;
}

arcade::statusGame &arcade::SolarFox::getStatus()
{
    return status;
}

vector<display_t> &arcade::SolarFox::getState()
{
    return to_display;
}

void arcade::SolarFox::restart()
{
    to_display.clear();
    getInitState();
    return;
}

extern "C" arcade::IGame *create()
{
    return new arcade::SolarFox();
}