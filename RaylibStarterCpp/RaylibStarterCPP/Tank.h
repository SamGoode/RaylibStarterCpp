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

    Tank(MathClasses::Vector3 pos, float rot, float size);

    Tank(const Tank& copy);

    Tank& operator=(const Tank& copy);

    const float& getSize() const;

    Turret& getTurret();

    void destroy();

    void setSpeed(float speed);

    void steer(float radians);

    void update();

    void draw();
};
