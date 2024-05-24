#pragma once
#include "GameObject.h"

class Bullet : public GameObject {
private:
    float size;
    float speed;
    MathClasses::Vector3 vel;

public:
    Bullet();

    Bullet(MathClasses::Vector3 _pos, float _rot);

    Bullet(const Bullet& copy);

    Bullet& operator=(const Bullet& copy);

    void bounce(float wallAngle);

    void setSpeed(float newSpeed);

    void update();

    void draw();
};