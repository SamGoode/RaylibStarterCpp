#pragma once
#include "GameObject.h"
#include "Turret.h"

class Tank : public GameObject {
private:
    float size;
    float speed;
    MathClasses::Vector3 vel;
    Turret turret;
    bool active;

public:
    Tank();

    Tank(MathClasses::Vector3 _pos, float _rot, float _size);

    Tank(const Tank& copy);

    Tank& operator=(const Tank& copy);

    const float& getSize() const;

    Turret& getTurret();

    bool isWithinBounds(MathClasses::Vector3 vec);

    bool isActive();

    void destroy();

    void setSpeed(float newSpeed);

    void steer(float radians);

    void update();

    void draw();
};
