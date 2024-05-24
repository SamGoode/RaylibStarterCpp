#pragma once
#include "GameObject.h"

class Turret : public GameObject {
private:
    float length;

    //temp solution for implementing firing
    bool firing;

public:
    Turret();

    Turret(MathClasses::Vector3 pos, float rot, float length);

    Turret(const Turret& copy);

    Turret& operator=(const Turret& copy);

    const float& getLength() const;

    void fire();

    bool isFiring();

    void turn(float radians);

    void update();

    void draw();
};