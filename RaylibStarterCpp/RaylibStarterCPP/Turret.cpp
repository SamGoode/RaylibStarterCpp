#include "Turret.h"
#include "raylib.h"
#include "Game.h"

Turret::Turret() {
    length = 0;
}

Turret::Turret(MathClasses::Vector3 _pos, float _rot, float _length) {
    setPos(_pos);
    setRot(_rot);
    length = _length;
}

Turret::Turret(const Turret& copy) {
    setPos(copy.getPos());
    setRot(copy.getRot());
    length = copy.length;
}

Turret& Turret::operator=(const Turret& copy) {
    setPos(copy.getPos());
    setRot(copy.getRot());
    length = copy.length;

    return *this;
}

const float& Turret::getLength() const {
    return length;
}

void Turret::fire() {
    getLevel()->spawnBullet(getWorldPos() + (getWorldUnitDir() * getLength()), getWorldRot());
}

void Turret::turn(float radians) {
    if (abs(getRot() + radians) > MathClasses::pi / 6) {
        return;
    }

    rotate(radians);
}

void Turret::draw() {
    MathClasses::Vector3 start = getWorldPos();
    MathClasses::Vector3 end = start + (getWorldUnitDir() * length);
    DrawLineEx({ start.x, start.y }, { end.x, end.y }, 6.f, DARKGRAY);
    DrawCircle(start.x, start.y, 6.f, GRAY);
}