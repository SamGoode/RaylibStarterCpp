#pragma once
#include "GameObject.h"

class Turret : public GameObject {
private:
    float length;

public:
    Turret();

    Turret(MathClasses::Vector3 _pos, float _rot, float _length);

    Turret(const Turret& copy);

    Turret& operator=(const Turret& copy);

    const float& getLength() const;

    void fire();

    void turn(float radians);

    void draw();
};