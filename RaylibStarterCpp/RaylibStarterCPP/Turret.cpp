#include "Turret.h"
#include "raylib.h"
#include "Tank.h"

Turret::Turret() {
    length = 0;

    firing = false;
}

Turret::Turret(MathClasses::Vector3 pos, float rot, float length) {
    setPos(pos);
    setRot(rot);
    this->length = length;

    firing = false;
}

Turret::Turret(const Turret& copy) {
    //setParent(copy.getParent());
    setPos(copy.getPos());
    setRot(copy.getRot());
    length = copy.length;

    firing = copy.firing;
}

Turret& Turret::operator=(const Turret& copy) {
    //setParent(copy.getParent());
    setPos(copy.getPos());
    setRot(copy.getRot());
    length = copy.length;

    firing = copy.firing;

    return *this;
}

const float& Turret::getLength() const {
    return length;
}

void Turret::fire() {
    firing = true;
}

bool Turret::isFiring() {
    return firing;
}

void Turret::turn(float radians) {
    if (abs(getRot() + radians) > acos(-1) / 6) {
        return;
    }

    rotate(radians);
}

void Turret::update() {
    firing = false;
}

void Turret::draw() {
    MathClasses::Vector3 start = MathClasses::Vector3(getWorldPos());
    MathClasses::Vector3 end = MathClasses::Vector3(start + (getWorldUnitDir() * length));
    DrawLineEx({ start.x, start.y }, { end.x, end.y }, 6.f, DARKGRAY);
}