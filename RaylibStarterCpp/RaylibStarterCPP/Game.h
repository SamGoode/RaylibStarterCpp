#pragma once
#include "List.h"
#include "BrickMap.h"
#include "Tank.h"
#include "Bullet.h"

class Game {
private:
    int screenWidth;
    int screenHeight;

    int score;
    bool gameover;
    BrickMap brickMap;
    Tank tank;
    List<Bullet> bullets;
    List<int> despawnQueue;

public:
    Game(int screenWidth, int screenHeight);

    void processInputs();

    void spawnBullet(MathClasses::Vector3 pos, float rot);

    void despawnBullet(int index);

    void processCollisions();

    void update();

    void draw();
};